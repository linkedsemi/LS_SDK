#ifndef FIELD_MANIPULATE_H_
#define FIELD_MANIPULATE_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Exported_macros
  * @{
  */
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         (REG)

#define SET_BIT(REG, BIT)     (WRITE_REG(REG, (READ_REG(REG) | (BIT))))

#define CLEAR_BIT(REG, BIT)   (WRITE_REG(REG, (READ_REG(REG) & ~(BIT))))

#define READ_BIT(REG, BIT)    ((READ_REG(REG)) & (BIT))

#define CLEAR_REG(REG)        (WRITE_REG(REG, 0x0))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  \
        WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define REG_FIELD_WR(reg,field,val)\
        do{                                 \
        uint32_t old_val = READ_REG(reg);\
        uint32_t new_val = ((unsigned int)(val)<<(field##_POS)&(unsigned int)(field##_MASK))|(old_val &~(unsigned int)(field##_MASK));\
        WRITE_REG(reg, new_val);\
    }while(0)

#define REG_FIELD_RD(reg,field)\
    (((READ_REG(reg))&(unsigned int)(field##_MASK))>>(field##_POS))

#define FIELD_BUILD(field,val) \
    ((unsigned int)(val)<<(field##_POS)&(unsigned int)(field##_MASK))

#ifdef __cplusplus
}
#endif

#endif
