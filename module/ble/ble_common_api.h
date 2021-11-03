#include "ls_ble.h"

/**
  * @brief Adv payload parsing struct.
  */
struct adv_payload_struct
{
    uint8_t *p_data;                               /*!< Adv payload data buffer*/ 
    uint16_t size;                                 /*!< Size of payload in units of byte*/ 
};

/**
 ****************************************************************************************
 * \brief Function for parsing adv payload.
 * 
 * \param[in]  type               Type of adv data user wants to search.
 * \param[in]  adv_report         Pointer to adv report to parse.
 * \param[out] typedata           Contains parsed adv data info.
 * \return                        Status of parsing. True means finding matched type data.
 *                                False means parsing failure.
 ****************************************************************************************
 */
bool dev_manager_adv_report_parse(uint8_t type, const struct adv_report_evt* adv_report, struct adv_payload_struct* typedata);
