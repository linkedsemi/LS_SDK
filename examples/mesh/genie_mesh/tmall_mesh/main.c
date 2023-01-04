#define LOG_TAG "MAIN"
#include <string.h>
#include <stdio.h>
#include "ls_ble.h"
#include "platform.h"
#include "ls_sig_mesh.h"
#include "log.h"
#include "ls_dbg.h"
#include "ls_hal_flash.h"
#include "tinyfs.h"
#include "tinycrypt/sha256.h"
#include "tinycrypt/constants.h"
#include "field_manipulate.h"
#include "le501x.h"
#include "sys_stat.h"
#include "tmall_mesh_ctl.h"
#include "tmall_light_cfg.h"

#define ALI_COMPANY_ID 0x01a8
#define COMPA_DATA_PAGES 1
#define TRIPLE_PID_LEN 4
#define MAX_NB_ADDR_REPLAY 20
#define TRIPLE_MAC_LEN 6
#define TRIPLE_SECRET_LEN 16
#define ALI_AUTH_VALUE_LEN 16
#define ALI_TRIPLE_SUM_LEN (TRIPLE_PID_LEN + TRIPLE_MAC_LEN + TRIPLE_SECRET_LEN)
#define PROV_AUTH_ACCEPT 1
#define PROV_AUTH_NOACCEPT 0
#define TMALL_TRITUPLE_FLASH_OFFSET (0x0200)
#define UPADTE_GLP_STOP_TYPE 0xfe
#define UPADTE_GLP_STOP_TIMEOUT_TYPE 0xfd

static bool sent_adv_ready=true;

uint8_t vendor_tid = 0;
#define RECORD_KEY1 1
#define RECORD_KEY2 2

tinyfs_dir_t mesh_dir;
struct mesh_model_info model_env;

SIGMESH_NodeInfo_TypeDef Node_Get_Proved_State = 0;
SIGMESH_NodeInfo_TypeDef Node_Proved_State = 0;

static uint8_t ali_pid[TRIPLE_PID_LEN] = {0};
uint32_t ali_pid_u32 = 12449;
uint8_t ali_mac[TRIPLE_MAC_LEN] = {0x28,0xfa,0x7a,0x3a,0xfe,0xd7};
uint8_t ali_secret[TRIPLE_SECRET_LEN] = {0xe3,0x89,0x92,0x38,0xfa,0xbe,0x3c,0xef,0x10,0x12,0x8d,0x18,0xb1,0x47,0xb4,0xe9};
static uint8_t ali_authvalue[ALI_AUTH_VALUE_LEN] = {0};

uint8_t rsp_data_info[40] = {0};
uint8_t tmall_ModelHandle = 0;

static uint16_t provisioner_unicast_addr;
static uint8_t adv_obj_hdl;
static void create_adv_obj(void);


uint8_t sha256_handler(const char *input_str, uint8_t *chiper)
{
    uint8_t ret = TC_CRYPTO_FAIL;
    uint8_t g_auth[32];
    struct tc_sha256_state_struct sha256_ctx;

    ret = tc_sha256_init(&sha256_ctx);
    if (ret == TC_CRYPTO_FAIL)
    {
        return ret;
    }

    ret = tc_sha256_update(&sha256_ctx, (const uint8_t *)input_str, strlen(input_str));
    if (ret == TC_CRYPTO_FAIL)
    {
        return ret;
    }

    ret = tc_sha256_final(&g_auth[0], &sha256_ctx);
    if (ret == TC_CRYPTO_FAIL)
    {
        return ret;
    }

    memcpy(chiper, &g_auth[0], 16);
    return ret;
}

void hextostring(const uint8_t *source, char *dest, int len)
{
    int i;
    char tmp[3];

    for (i = 0; i < len; i++)
    {
        sprintf(tmp, "%02x", (unsigned char)source[i]);
        memcpy(&dest[i * 2], tmp, 2);
    }
}

static uint8_t gen_ali_authValue(void)
{
    uint8_t status = TC_CRYPTO_FAIL;
    char cal_ble_key_input[55] = ""; // pid + ',' + mac + ',' + secret = 8+1+12+1+32+'\0'
    char mac_str[(TRIPLE_MAC_LEN << 1) + 1] = "";
    char secret_str[(TRIPLE_SECRET_LEN << 1) + 1] = "";
    uint8_t tmp_arry[ALI_AUTH_VALUE_LEN] = {0};

    uint8_t ali_trituple[ALI_TRIPLE_SUM_LEN] = {0};
    hal_flash_fast_read(TMALL_TRITUPLE_FLASH_OFFSET, &ali_trituple[0], ALI_TRIPLE_SUM_LEN);
    if ((ali_trituple[0] != 0xff) && (ali_trituple[1] != 0xff) && (ali_trituple[2] != 0xff))
    {
        ali_pid_u32 = (((uint32_t)ali_trituple[0]) << 24) | (((uint32_t)ali_trituple[1]) << 16) | (((uint32_t)ali_trituple[2]) << 8) | (((uint32_t)ali_trituple[3]));
        memcpy(&ali_mac[0], &ali_trituple[TRIPLE_PID_LEN], TRIPLE_MAC_LEN);
        memcpy(&ali_secret[0], &ali_trituple[TRIPLE_PID_LEN + TRIPLE_MAC_LEN], TRIPLE_SECRET_LEN);
    }

    hextostring(ali_mac, mac_str, TRIPLE_MAC_LEN);
    hextostring(ali_secret, secret_str, TRIPLE_SECRET_LEN);

    sprintf(&cal_ble_key_input[0], "%08lx,%s,%s", ali_pid_u32, mac_str, secret_str);

    status = sha256_handler(&cal_ble_key_input[0], &ali_authvalue[0]);

    memcpy(&ali_pid[0], ((uint8_t *)&ali_pid_u32), TRIPLE_PID_LEN);

    memcpy(tmp_arry, ali_mac, TRIPLE_MAC_LEN);
    for (uint8_t j = 0; j < TRIPLE_MAC_LEN; j++)
    {
        ali_mac[j] = tmp_arry[TRIPLE_MAC_LEN - 1 - j];
    }

    memcpy(tmp_arry, ali_authvalue, ALI_AUTH_VALUE_LEN);
    for (uint8_t j = 0; j < ALI_AUTH_VALUE_LEN; j++)
    {
        ali_authvalue[j] = tmp_arry[ALI_AUTH_VALUE_LEN - 1 - j];
    }

    if (status == TC_CRYPTO_FAIL)
    {
        memset(&ali_authvalue[0], 0, ALI_AUTH_VALUE_LEN);
        return (0);
    }

    return (1);
}

void auto_check_unbind(void)
{
    uint16_t length = 1;
    uint8_t coutinu_power_up_num = 0;
    tinyfs_mkdir(&mesh_dir, ROOT_DIR, 5);
    tinyfs_read(mesh_dir, RECORD_KEY1, &coutinu_power_up_num, &length);
    LOG_I("coutinu_power_up_num:%d", coutinu_power_up_num);

    if (coutinu_power_up_num > 4)
    {
        coutinu_power_up_num = 0;
        tinyfs_write(mesh_dir, RECORD_KEY1, &coutinu_power_up_num, sizeof(coutinu_power_up_num));
        SIGMESH_UnbindAll();
    }
    else
    {
        coutinu_power_up_num++;
        tinyfs_write(mesh_dir, RECORD_KEY1, &coutinu_power_up_num, sizeof(coutinu_power_up_num));
        tinyfs_write_through();
    }
}

void enable_tx_unprov_beacon(void)
{
    struct bcn_start_unprov_param info;
    info.DevUuid[0] = 0xA8;
    info.DevUuid[1] = 0x01;
    info.DevUuid[2] = 0x71;
    memcpy(&info.DevUuid[3], &ali_pid[0], TRIPLE_PID_LEN);
    memcpy(&info.DevUuid[3 + TRIPLE_PID_LEN], &ali_mac[0], TRIPLE_MAC_LEN);
    info.DevUuid[13] = 0x02;
    info.DevUuid[14] = 0x00;
    info.DevUuid[15] = 0x00;
    info.UriHash = 0xd97478b3;
    info.OobInfo = 0x0000;
    info.UriHash_Present = true;
    start_tx_unprov_beacon(&info);
}

void disable_tx_unprov_beacon(void)
{
    stop_tx_unprov_beacon();
}

void report_provisioner_unicast_address_ind(uint16_t unicast_address)
{
    provisioner_unicast_addr = unicast_address;
    tinyfs_write(mesh_dir, RECORD_KEY2, (uint8_t *)&unicast_address, sizeof(unicast_address));
    tinyfs_write_through();
}

void vendor_indication_handler(uint8_t const *info, uint16_t const info_len)
{
    struct model_send_info rsp;
    rsp.opcode = APP_MESH_VENDOR_INDICATION;
    rsp.app_key_lid = mesh_key_lid;
    rsp.ModelHandle = model_env.info[1].model_lid;
    rsp.dest_addr = provisioner_unicast_addr;
    rsp.len = info_len;
    rsp.info[0] = vendor_tid;
    memcpy(&(rsp.info[1]), info, info_len);
    rsp.len += 1; //1 :tid_len
    model_send_info_handler(&rsp);
    vendor_tid++;
}

static void mesh_manager_callback(enum mesh_evt_type type, union ls_sig_mesh_evt_u *evt)
{
    switch (type)
    {
    case MESH_ACTIVE_ENABLE:
    {
        create_adv_obj();
        TIMER_Set(2, 3000); //clear power up num
    }
    break;
    case MESH_ACTIVE_DISABLE:
    {
        SIGMESH_UnbindAll();
        platform_reset(0);
    }
    break;
    case MESH_ACTIVE_REGISTER_MODEL:
    {
        for (uint8_t i = 0; i < model_env.nb_model; i++)
        {
            model_env.info[i].model_lid = evt->sig_mdl_info.info[i].model_lid;
        }
        model_env.app_key_lid = evt->sig_mdl_info.app_key_lid;

        model_subscribe(model_env.info[0].model_lid, 0xC000); //group address 0xc000
        model_subscribe(model_env.info[1].model_lid, 0xC000); //group address 0xc000
        model_subscribe(model_env.info[2].model_lid, 0xC000); //group address 0xc000
        model_subscribe(model_env.info[3].model_lid, 0xC000); //group address 0xc000
        model_subscribe(model_env.info[4].model_lid, 0xC000); //group address 0xc000
    }
    break;
    case MESH_ACTIVE_MODEL_PUBLISH:
    {
    }
    break;
    case MESH_ACTIVE_MODEL_GROUP_MEMBERS:
    {
        LOG_I("Prov Succeed");
        tmall_light_set_lightness(0xFFFF);
    }
    break;
    case MESH_ACTIVE_STORAGE_LOAD:
    {
        Node_Get_Proved_State = evt->st_proved.proved_state;
        if (Node_Get_Proved_State == PROVISIONED_OK)
        {
            uint16_t length = sizeof(provisioner_unicast_addr);
            LOG_I("The node is provisioned");
            tmall_light_set_lightness(0xffff);
            tinyfs_read(mesh_dir, RECORD_KEY2, (uint8_t*)&provisioner_unicast_addr, &length);
        }
        else
        {
            LOG_I("The node is not provisioned");
        }
        
    }
    break;
    case MESH_GET_PROV_INFO:
    {
        struct mesh_prov_info param;
        param.DevUuid[0] = 0xA8;
        param.DevUuid[1] = 0x01;
        param.DevUuid[2] = 0x71;
        memcpy(&param.DevUuid[3], &ali_pid[0], TRIPLE_PID_LEN);
        memcpy(&param.DevUuid[3 + TRIPLE_PID_LEN], &ali_mac[0], TRIPLE_MAC_LEN);
        param.DevUuid[13] = 0x02;
        param.DevUuid[14] = 0x00;
        param.DevUuid[15] = 0x00;
        param.UriHash = 0xd97478b3;
        param.OobInfo = 0x0000;
        param.PubKeyOob = 0x00;
        param.StaticOob = 0x01;
        param.OutOobSize = 0x00;
        param.InOobSize = 0x00;
        param.OutOobAction = 0x0000;
        param.InOobAction = 0x0000;
        param.Info = 0x00;
        set_prov_param(&param);
    }
    break;
    case MESH_GET_PROV_AUTH_INFO:
    {
        struct mesh_prov_auth_info param;
        param.Adopt = PROV_AUTH_ACCEPT;
        memcpy(&param.AuthBuffer[0], &ali_authvalue[0], ALI_AUTH_VALUE_LEN);
        param.AuthSize = ALI_AUTH_VALUE_LEN;
        set_prov_auth_info(&param);
    }
    break;
    case MESH_STATE_UPD_IND:
    {
       if(evt->update_state_param.upd_type == UPADTE_GLP_STOP_TYPE)
       {
          app_status_set(true);
       }

       if (evt->update_state_param.upd_type == UPADTE_GLP_STOP_TIMEOUT_TYPE)
       {
          app_status_set(false);
       }
    }break;
    case MESH_ACCEPT_MODEL_INFO:
    {
        if(evt->rx_msg.ModelHandle == model_env.info[0].model_lid)
        {
            tmall_mesh_recv_onoff_msg(&evt->rx_msg);
        }
        else if(evt->rx_msg.ModelHandle == model_env.info[1].model_lid)
        {
            tmall_mesh_recv_vendor_msg(&evt->rx_msg);
        }
        else if(evt->rx_msg.ModelHandle == model_env.info[2].model_lid)
        {
            tmall_mesh_recv_lightness_msg(&evt->rx_msg);
        }
        else if(evt->rx_msg.ModelHandle == model_env.info[3].model_lid)
        {
            tmall_mesh_recv_light_ctl_msg(&evt->rx_msg);
        }
        else if(evt->rx_msg.ModelHandle == model_env.info[4].model_lid)
        {
            tmall_mesh_recv_light_hsl_msg(&evt->rx_msg);
        }    
    }
    break;
    case MESH_REPORT_TIMER_STATE:
    {
        if (2 == evt->mesh_timer_state.timer_id)
        {
            uint8_t clear_power_on_num = 0;
            TIMER_Cancel(2);
            tinyfs_write(mesh_dir, RECORD_KEY1, &clear_power_on_num, sizeof(clear_power_on_num));
            tinyfs_write_through();
        }
    }
    break;
    case MESH_ADV_REPORT:
    {
        if(evt->adv_report.adv_addr->addr[5] == 0x20 && evt->adv_report.adv_addr->addr[4] == 0x17)
        {
            LOG_I("dev addr: %02x:%02x:%02x:%02x:%02x:%02x",evt->adv_report.adv_addr->addr[5],
                                                            evt->adv_report.adv_addr->addr[4],
                                                            evt->adv_report.adv_addr->addr[3],
                                                            evt->adv_report.adv_addr->addr[2],
                                                            evt->adv_report.adv_addr->addr[1],
                                                            evt->adv_report.adv_addr->addr[0]);
            //LOG_HEX(evt->adv_report.adv_addr.addr,6);
            LOG_HEX(evt->adv_report.data,evt->adv_report.length);
        }
        
    }
    break;
    default:
        break;
    }
}

static void create_adv_obj()
{
    struct legacy_adv_obj_param adv_param = {
        .adv_intv_min = 0x64,
        .adv_intv_max = 0x64,
        .own_addr_type = PUBLIC_OR_RANDOM_STATIC_ADDR,
        .filter_policy = 0,
        .ch_map = 0x7,
        .disc_mode = ADV_MODE_GEN_DISC,
        .prop = {
            .connectable = 0,
            .scannable = 1,
            .directed = 0,
            .high_duty_cycle = 0,
        },
    };
    dev_manager_create_legacy_adv_object(&adv_param);
}

void mesh_send_custom_adv(uint16_t duration,uint8_t *adv_data,uint8_t adv_data_length)
{
    if (sent_adv_ready==true)
    {
        sent_adv_ready = false;
       dev_manager_set_adv_duration(duration);
       dev_manager_start_adv(adv_obj_hdl,adv_data,adv_data_length,NULL,0);
    }
}

static void dev_manager_callback(enum dev_evt_type type, union dev_evt_u *evt)
{
    switch (type)
    {
    case STACK_INIT:
    {
        struct ble_stack_cfg cfg = {
            .private_addr = true,
            .controller_privacy = false,
        };
        dev_manager_set_mac_addr(&ali_mac[0]);
        dev_manager_stack_init(&cfg);
    }
    break;

    case STACK_READY:
    {
        uint8_t addr[6];
        struct ls_sig_mesh_cfg feature = {
            .MeshFeatures = EN_RELAY_NODE | EN_MSG_API,
            .MeshCompanyID = ALI_COMPANY_ID,
            .MeshProID = 0,
            .MeshProVerID = 0,
            .MeshLocDesc = 0,
            .NbAddrReplay  = MAX_NB_ADDR_REPLAY,
            .NbCompDataPage = COMPA_DATA_PAGES,
        };

        bool type;
        dev_manager_get_identity_bdaddr(addr, &type);
        dev_manager_prf_ls_sig_mesh_add(NO_SEC, &feature);
    }
    break;

    case SERVICE_ADDED:
    {
    }
    break;
    case PROFILE_ADDED:
    {
        prf_ls_sig_mesh_callback_init(mesh_manager_callback);

        model_env.nb_model = 5;
        model_env.info[0].model_id = GENERIC_ONOFF_SERVER;
        model_env.info[0].element_id = 0;
        model_env.info[1].model_id = VENDOR_TMALL_SERVER;
        model_env.info[1].element_id = 0;
        model_env.info[2].model_id = LIGHTNESS_SERVER;
        model_env.info[2].element_id = 0;
        model_env.info[3].model_id = LIGHTS_CTL_SERVER;
        model_env.info[3].element_id = 0;
        model_env.info[4].model_id = LIGHTS_HSL_SERVER;
        model_env.info[4].element_id = 0;
        ls_sig_mesh_init(&model_env);
    }
    break;
    case ADV_OBJ_CREATED:
    {
        adv_obj_hdl = evt->obj_created.handle;
        LOG_I("adv obj hdl:%d",adv_obj_hdl);
    }
    break;
    case ADV_STOPPED:
    {
        sent_adv_ready = true;
    }
    break;
    case SCAN_STOPPED:
    {
    }
    break;
    default:

        break;
    }
}

int main()
{
    sys_init_app();
    mesh_stack_data_bss_init();
    tmall_light_init();
    gen_ali_authValue();
    ble_init();
    auto_check_unbind();
    dev_manager_init(dev_manager_callback);
    ble_loop();
    return 0;
}
