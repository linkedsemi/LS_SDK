#include "ble_common_api.h"

bool dev_manager_adv_report_parse(uint8_t type, const struct adv_report_evt* adv_report, struct adv_payload_struct* typedata)
{
    bool result = false;
    uint8_t *p_data = adv_report->data;
    uint16_t index = 0;
    while (index < adv_report->length)
    {
        uint8_t field_length = p_data[index];
        uint8_t field_type = p_data[index + 1];

        if (field_type == type)
        {
            typedata->p_data = &p_data[index + 2];
            typedata->size = field_length - 1;
            result = true;
            break;
        }
        index += field_length + 1;
    }
    return result;
}
