#ifndef MAIN_H_
#define MAIN_H_

#include "ls_ble.h"

/**defgroup SEC mode and level**/
#define SEC_MODE1_LEVEL1  0x00    /**< No security is needed. */
#define SEC_MODE1_LEVEL2  0x01    /**< Encrypted link is required. Unnecessary: MITM and SC. */
#define SEC_MODE1_LEVEL3  0x02    /**< Encrypted link is required. Necessary: MITM; unnecessary: SC. */
#define SEC_MODE1_LEVEL4  0x03    /**< Encrypted link is required. Necessary: MITM and SC. */
#define SEC_MODE2_LEVEL1  0x04    /**< Data signing is required. Unnecessary: MITM and SC. */
#define SEC_MODE2_LEVEL2  0x05    /**< Data signing is required. Necessary: MITM; unnecessary: SC. */

/**defgroup SEC Parameter**/
#define OOB_DATA_FLAG                     0x0                               /**< Indicate whether OOB is supported. */
#define AUTHREQ                           (AUTH_MITM | AUTH_BOND)           /**< Set the auth. */
#define KEY_SIZE                          0x10                              /**< Indicate the supported maximum LTK size (range: 7-16). */
#define INIT_KEY_DIST                     (KDIST_ENCKEY | KDIST_IDKEY)      /**< Set the initial key distribution. */
#define RESP_KEY_DIST                     (KDIST_ENCKEY | KDIST_IDKEY)      /**< Set the response key distribution. */
#define passkey_number                    {'1','2','3','4','5','6'}         /**< Set the passkey,size(6). */

#endif
