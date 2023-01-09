#ifndef _LS_MESH_H_
#define _LS_MESH_H_
#include <stdint.h>

/** \addtogroup LSMESH
 *  @{
 */

#define __LS_MESH_EMPTY   /*!< flexible array length*/

/**
  * @brief Linkedsemi mesh event type definition
  */
enum ls_mesh_evt_type
{
    LS_MESH_RX_MSG_EVT,    /*!< rx message event*/
    LS_MESH_FINISH_EVT,    /*!< finished event*/
};

/**
  * @brief Linkedsemi mesh rx message structure
  */
struct ls_mesh_rx_msg_evt
{
    uint8_t  msg_len;     /*!< rx message length include adv_type/uuid/handle/version and vlaue*/
    uint8_t  adv_type;     /*!< defined 0x16*/
    uint16_t uuid;         /*!< defined 0xFEE4*/
    uint16_t handle;       /*!< rx message handle*/
    uint32_t version;      /*!< Version dependent handle*/
    uint8_t value[__LS_MESH_EMPTY];  /*!< rx message value*/
}__attribute__((packed));

/**
  * @brief Linkedsemi mesh event union
  */
union ls_mesh_evt_u {
    struct ls_mesh_rx_msg_evt ls_mesh_send_msg;   /*!< Linkedsemi mesh rx message event*/
};

/**
****************************************************************************************
 * \brief Initialization for rx messages API of linkedsemi mesh.
 * 
 * \param[in] evt_cb  Callback function to handle all the ls mesh messages.
 ****************************************************************************************
 */
void prf_ls_mesh_callback_init(void (*evt_cb)(enum ls_mesh_evt_type, union ls_mesh_evt_u *));
/**
****************************************************************************************
 * \brief Initialization of linkedsemi mesh.
 * 
 ****************************************************************************************
 */
void ls_mesh_init(void);
/**
 ****************************************************************************************
 * \brief Add profile of linkedsemi mesh to the database
 * 
 * \param[in]  sec_lvl         no security 
 * \param[in]  param           default NULL.
 * 
 ****************************************************************************************
 */
void dev_manager_prf_ls_mesh_add(uint8_t sec_lvl, void *param);
/**
 ****************************************************************************************
 * \brief Active task of linkedsemi mesh 
 * 
 ****************************************************************************************
 */
void ls_mesh_start(void);
/**
 ****************************************************************************************
 * \brief API for Tx message of linkedsemi mesh
 * 
 * \param[in]  value         application data 
 * \param[in]  len           length of application data
 * 
 ****************************************************************************************
 */
void ls_mesh_set_beacon_value_ind(const uint8_t *value, uint8_t len);

/** @}*/

#endif //_LS_MESH_H_
