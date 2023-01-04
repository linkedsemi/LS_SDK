#ifndef __FOTA_SVC_SERVER_H__
#include <stdint.h>
#include <stdbool.h>
#include "prf_fotas.h"

#define USER_MAX_MTU  519

#define FOTAS_IDX_MAX (1)
#define FOTAS_PAGE_SIZE (256)
#define FOTAS_SECTOR_SIZE (4096)
#define FOTAS_SIGNATURE_CMD_DATA_LENGTH (16)
#define FOTAS_DIGEST_CMD_DATA_LENGTH (16)
#define FOTAS_ACK_BUF_LENGTH_MAX (27)
/**
 ****************************************************************************************
 * \brief OTA server read request indication handler.
 * 
 * \param[in]  att_idx           Attribute index.
 * \param[in]  con_idx           Connection ID number.
 ****************************************************************************************
 */
void ls_ota_server_read_req_ind(uint8_t att_idx, uint8_t con_idx);
/**
 ****************************************************************************************
 * \brief OTA server write request indication handler.
 * 
 * \param[in]  wr_req            Write request pointer.
 * \param[in]  con_idx           Connection ID number.
 ****************************************************************************************
 */
void ls_ota_server_write_req_ind(struct gatt_server_write_req *wr_req, uint8_t con_idx);
/**
 ****************************************************************************************
 * \brief Add OTA service.
 * 
 ****************************************************************************************
 */
void fotas_add_service(void);
/**
 ****************************************************************************************
 * \brief Register OTA service.
 * 
 * \param[in]  start_hdl           Start handle of OTA service.
 ****************************************************************************************
 */
void fotas_register_svc(uint16_t start_hdl);
/**
 ****************************************************************************************
 * \brief Clean fota service state.
 * 
 ****************************************************************************************
 */
void fota_clean_state(void);
#endif
