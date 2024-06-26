#ifndef EFUSE_H_
#define EFUSE_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct efuse_data
{
    uint64_t lsi_code:12,
            adc12b_vref_trim_0:5,
            adc12b_vref_trim_1:5,
            vref_dac_trim_0:5,
            vref_dac_trim_1:5,
            lpldo_trim:4,
            msi_cal:4,
            adc0_offset:8,
            adc1_offset:8,
            adc0_gain_l:8;
    uint64_t bg_vref_trim:6,
            bg_vref_fine:2,
            oscrc_cal:10,
            hpldo_trim:2,
            dpll_ldo_trim:3,
            peci_ldo_trim:3,
            adc0_gain_h:4,
            adc1_gain:12,
            wafer_id_xy:20,
            reserved:1,
            cp_flag:1;
};

void efuse_read(struct efuse_data *data);

#ifdef __cplusplus
}
#endif

#endif
