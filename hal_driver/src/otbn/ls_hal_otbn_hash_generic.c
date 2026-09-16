#include "ls_hal_otbn_sha.h"

static uint32_t get_hash_outLength(otbn_hash_algo algo)
{
    switch (algo)
    {
    case OTBN_HASH_ALGO_SHA256:
        return SHA256_RESULT_SIZE;
    case OTBN_HASH_ALGO_SHA384:
        return SHA384_RESULT_SIZE;
    case OTBN_HASH_ALGO_SHA512:
        return SHA512_RESULT_SIZE;
    case OTBN_HASH_ALGO_SM3:
        return SM3_RESULT_SIZE;
    default:
        return 0;
    }
}

static uint32_t get_hash_blockSize(otbn_hash_algo algo)
{
    switch (algo)
    {
    case OTBN_HASH_ALGO_SHA256:
        return OTBN_HASH_BLOCK_SIZE_SHA256;
    case OTBN_HASH_ALGO_SHA384:
        return OTBN_HASH_BLOCK_SIZE_SHA384;
    case OTBN_HASH_ALGO_SHA512:
        return OTBN_HASH_BLOCK_SIZE_SHA512;
    case OTBN_HASH_ALGO_SM3:
        return OTBN_HASH_BLOCK_SIZE_SM3;
    default:
        return 0;
    }
}

ls_otbn_status_t HAL_OTBN_HASH_Init(otbn_hash_algo algo)
{
    ls_otbn_status_t return_val = LS_OTBN_OK;
    switch (algo)
    {
    case OTBN_HASH_ALGO_SHA256:
        return_val = HAL_OTBN_SHA256_Init();
        break;
    case OTBN_HASH_ALGO_SHA384:
        return_val = HAL_OTBN_SHA384_Init();
        break;
    case OTBN_HASH_ALGO_SHA512:
        return_val = HAL_OTBN_SHA512_Init();
        break;
    case OTBN_HASH_ALGO_SM3:
        return_val = HAL_OTBN_SM3_Init();
        break;
    default:
        return_val = LS_OTBN_ENGINE;
        break;
    }
    return return_val;
}

ls_otbn_status_t HAL_OTBN_HASH_Update(otbn_hash_algo algo, uint8_t *msg, uint32_t msg_size)
{
    ls_otbn_status_t return_val = LS_OTBN_OK;
    switch (algo)
    {
    case OTBN_HASH_ALGO_SHA256:
        return_val = HAL_OTBN_SHA256_Update(msg, msg_size);
        break;
    case OTBN_HASH_ALGO_SHA384:
        return_val = HAL_OTBN_SHA384_Update(msg, msg_size);
        break;
    case OTBN_HASH_ALGO_SHA512:
        return_val = HAL_OTBN_SHA512_Update(msg, msg_size);
        break;
    case OTBN_HASH_ALGO_SM3:
        return_val = HAL_OTBN_SM3_Update(msg, msg_size);
        break;
    default:
        return_val = LS_OTBN_ENGINE;
        break;
    }
    return return_val;
}

ls_otbn_status_t HAL_OTBN_HASH_Final(otbn_hash_algo algo, uint8_t *out)
{
    ls_otbn_status_t return_val = LS_OTBN_OK;
    switch (algo)
    {
    case OTBN_HASH_ALGO_SHA256:
        return_val = HAL_OTBN_SHA256_Final(out);
        break;
    case OTBN_HASH_ALGO_SHA384:
        return_val = HAL_OTBN_SHA384_Final(out);
        break;
    case OTBN_HASH_ALGO_SHA512:
        return_val = HAL_OTBN_SHA512_Final(out);
        break;
    case OTBN_HASH_ALGO_SM3:
        return_val = HAL_OTBN_SM3_Final(out);
        break;
    default:
        return_val = LS_OTBN_ENGINE;
        break;
    }
    return return_val;
}

ls_otbn_status_t HAL_OTBN_HASH(otbn_hash_algo algo, uint8_t *msg, uint32_t msg_size, uint8_t *out)
{
    if (HAL_OTBN_HASH_Init(algo) != LS_OTBN_OK)
        return LS_OTBN_ENGINE;
    if (HAL_OTBN_HASH_Update(algo, msg, msg_size) != LS_OTBN_OK)
        return LS_OTBN_ENGINE;
    return HAL_OTBN_HASH_Final(algo, out);
}


ls_otbn_status_t HAL_OTBN_HASH_HMAC_SetKey(otbn_hash_hamc_env *hmac, uint8_t *key, uint32_t key_size)
{
    hmac->key = key;
    hmac->key_size = key_size;
    hmac->block_size = get_hash_blockSize(hmac->hash_algo);

    if (hmac->key_size > hmac->block_size)
    {
        if (HAL_OTBN_HASH_Init(hmac->hash_algo) != LS_OTBN_OK)
            return LS_OTBN_ENGINE;
        if (HAL_OTBN_HASH_Update(hmac->hash_algo, hmac->key, hmac->key_size) != LS_OTBN_OK)
            return LS_OTBN_ENGINE;
        if (HAL_OTBN_HASH_Final(hmac->hash_algo, hmac->kh) != LS_OTBN_OK)
            return LS_OTBN_ENGINE;

        hmac->key = hmac->kh;
        hmac->key_size = get_hash_outLength(hmac->hash_algo);
    }

    for (uint8_t i = 0; i < hmac->key_size; i++)
        hmac->kx[i] = HMAC_I_PAD ^ hmac->key[i];
    for (uint8_t i = hmac->key_size; i < hmac->block_size; i++)
        hmac->kx[i] = HMAC_I_PAD ^ 0;

    if (HAL_OTBN_HASH_Init(hmac->hash_algo) != LS_OTBN_OK)
        return LS_OTBN_ENGINE;
    return HAL_OTBN_HASH_Update(hmac->hash_algo, hmac->kx, hmac->block_size);
}

ls_otbn_status_t HAL_OTBN_HASH_HMAC_Update(otbn_hash_hamc_env *hmac, uint8_t *msg, uint32_t msg_size)
{
    return HAL_OTBN_HASH_Update(hmac->hash_algo, msg, msg_size);
}

ls_otbn_status_t HAL_OTBN_HASH_HMAC_Final(otbn_hash_hamc_env *hmac, uint8_t *out)
{
    if (HAL_OTBN_HASH_Final(hmac->hash_algo, out) != LS_OTBN_OK)
        return LS_OTBN_ENGINE;

    for (uint8_t i = 0; i < hmac->key_size; i++)
        hmac->kx[i] = HMAC_O_PAD ^ hmac->key[i];
    for (uint8_t i = hmac->key_size; i < hmac->block_size; i++)
        hmac->kx[i] = HMAC_O_PAD ^ 0;

    if (HAL_OTBN_HASH_Init(hmac->hash_algo) != LS_OTBN_OK)
        return LS_OTBN_ENGINE;
    if (HAL_OTBN_HASH_Update(hmac->hash_algo, hmac->kx, hmac->block_size) != LS_OTBN_OK)
        return LS_OTBN_ENGINE;
    if (HAL_OTBN_HASH_Update(hmac->hash_algo, out, get_hash_outLength(hmac->hash_algo)) != LS_OTBN_OK)
        return LS_OTBN_ENGINE;
    return HAL_OTBN_HASH_Final(hmac->hash_algo, out);
}

ls_otbn_status_t HAL_OTBN_HASH_HMAC(otbn_hash_algo algo, uint8_t *out,
                        uint8_t *key, uint32_t key_size,
                        uint8_t *msg, uint32_t msg_size)
{
    uint8_t kh[OTBN_HASH_RESULT_MAXSIZE];
    uint8_t kx[OTBN_HASH_BLOCK_MAXSIZE];
    uint8_t i;
    uint32_t blockSize = get_hash_blockSize(algo);

    if (key_size > blockSize)
    {
        if (HAL_OTBN_HASH_Init(algo) != LS_OTBN_OK)
            return LS_OTBN_ENGINE;
        if (HAL_OTBN_HASH_Update(algo, key, key_size) != LS_OTBN_OK)
            return LS_OTBN_ENGINE;
        if (HAL_OTBN_HASH_Final(algo, kh) != LS_OTBN_OK)
            return LS_OTBN_ENGINE;
        key_size = get_hash_outLength(algo);
        key = kh;
    }

    for (uint32_t i = 0; i < key_size; i++)
        kx[i] = HMAC_I_PAD ^ key[i];
    for (uint32_t i = key_size; i < blockSize; i++)
        kx[i] = HMAC_I_PAD ^ 0;

    if (HAL_OTBN_HASH_Init(algo) != LS_OTBN_OK)
        return LS_OTBN_ENGINE;
    if (HAL_OTBN_HASH_Update(algo, kx, blockSize) != LS_OTBN_OK)
        return LS_OTBN_ENGINE;
    if (HAL_OTBN_HASH_Update(algo, msg, msg_size) != LS_OTBN_OK)
        return LS_OTBN_ENGINE;
    if (HAL_OTBN_HASH_Final(algo, out) != LS_OTBN_OK)
        return LS_OTBN_ENGINE;
    for (i = 0; i < key_size; i++)
        kx[i] = HMAC_O_PAD ^ key[i];
    for (i = key_size; i < blockSize; i++)
        kx[i] = HMAC_O_PAD ^ 0;

    if (HAL_OTBN_HASH_Init(algo) != LS_OTBN_OK)
        return LS_OTBN_ENGINE;
    if (HAL_OTBN_HASH_Update(algo, kx, blockSize) != LS_OTBN_OK)
        return LS_OTBN_ENGINE;
    if (HAL_OTBN_HASH_Update(algo, out, get_hash_outLength(algo)) != LS_OTBN_OK)
        return LS_OTBN_ENGINE;
    return HAL_OTBN_HASH_Final(algo, out);
}

ls_otbn_status_t HAL_OTBN_HASH_HKDF_Extract(otbn_hash_algo algo,
                                uint8_t *salt, uint32_t salt_len,
                                uint8_t *ikm, uint32_t ikm_len,
                                uint8_t *prk, uint32_t *prk_length)
{
    uint8_t nullsalt[OTBN_HASH_RESULT_MAXSIZE];
    if (salt == NULL)
    {
        salt = nullsalt;
        salt_len = get_hash_outLength(algo);
        memset(salt, 0, salt_len);
    }
    *prk_length = get_hash_outLength(algo);
    return HAL_OTBN_HASH_HMAC(algo, prk, salt, salt_len, ikm, ikm_len);
}

ls_otbn_status_t HAL_OTBN_HASH_HKDF_Expand(otbn_hash_algo algo,
                               uint8_t *prk, uint32_t prk_len,
                               uint8_t *info, uint32_t info_len,
                               uint8_t *okm, uint32_t okm_len)
{
    uint32_t hash_len, N, T_len, where;
    uint8_t T[OTBN_HASH_RESULT_MAXSIZE];
    otbn_hash_hamc_env hmac;
    hmac.hash_algo = algo;
    if (info == NULL)
    {
        info = (uint8_t *)"";
        info_len = 0;
    }
    hash_len = get_hash_outLength(algo);
    if (okm == NULL)
        return LS_OTBN_ENGINE;
    if (prk_len < hash_len)
        return LS_OTBN_ENGINE;
    N = okm_len / hash_len;
    if ((okm_len % hash_len) != 0)
        N++;
    if (N > 0xff)
        return LS_OTBN_ENGINE;
    T_len = 0;
    where = 0;
    for (uint8_t i = 1; i <= N; i++)
    {
        uint8_t c = i;
        if (HAL_OTBN_HASH_HMAC_SetKey(&hmac, prk, hash_len) != LS_OTBN_OK)
            return LS_OTBN_ENGINE;
        if (T_len != 0x0) {
            if (HAL_OTBN_HASH_HMAC_Update(&hmac, T, T_len) != LS_OTBN_OK)
                return LS_OTBN_ENGINE;
        }
        if (HAL_OTBN_HASH_HMAC_Update(&hmac, info, info_len) != LS_OTBN_OK)
            return LS_OTBN_ENGINE;
        if (HAL_OTBN_HASH_HMAC_Update(&hmac, &c, 1) != LS_OTBN_OK)
            return LS_OTBN_ENGINE;
        if (HAL_OTBN_HASH_HMAC_Final(&hmac, T) != LS_OTBN_OK)
            return LS_OTBN_ENGINE;
        memcpy(okm + where, T, (i != N) ? hash_len : (okm_len - where));
        where += hash_len;
        T_len = hash_len;
    }
    return LS_OTBN_OK;
}

ls_otbn_status_t HAL_OTBN_HASH_HKDF(otbn_hash_algo algo,
                        uint8_t *salt, uint32_t salt_len,
                        uint8_t *ikm, uint32_t ikm_len,
                        uint8_t *info, uint32_t info_len,
                        uint8_t *okm, uint32_t okm_len)
{
    uint8_t T[OTBN_HASH_RESULT_MAXSIZE];
    uint8_t prk[OTBN_HASH_RESULT_MAXSIZE];
    uint8_t nullsalt[OTBN_HASH_RESULT_MAXSIZE];
    uint32_t N, T_len, where;
    otbn_hash_hamc_env hmac;
    hmac.hash_algo = algo;
    uint32_t hash_len = get_hash_outLength(algo);

    if (salt == NULL)
    {
        salt = nullsalt;
        salt_len = hash_len;
        memset(salt, 0, salt_len);
    }
    uint32_t prk_len = 0;
    if (HAL_OTBN_HASH_HKDF_Extract(algo, salt, salt_len, ikm, ikm_len, prk, &prk_len) != LS_OTBN_OK)
        return LS_OTBN_ENGINE;

    if (info == NULL)
    {
        info = (uint8_t *)"";
        info_len = 0;
    }
    if (okm == NULL)
        return LS_OTBN_ENGINE;
    N = okm_len / hash_len;
    if ((okm_len % hash_len) != 0)
        N++;
    if (N > 0xff)
        return LS_OTBN_ENGINE;
    T_len = 0x0;
    where = 0x0;
    for (uint8_t i = 1; i <= N; i++)
    {
        uint8_t c = i;
        if (HAL_OTBN_HASH_HMAC_SetKey(&hmac, prk, hash_len) != LS_OTBN_OK)
            return LS_OTBN_ENGINE;
        if (T_len != 0x0) {
            if (HAL_OTBN_HASH_HMAC_Update(&hmac, T, T_len) != LS_OTBN_OK)
                return LS_OTBN_ENGINE;
        }
        if (HAL_OTBN_HASH_HMAC_Update(&hmac, info, info_len) != LS_OTBN_OK)
            return LS_OTBN_ENGINE;
        if (HAL_OTBN_HASH_HMAC_Update(&hmac, &c, 1) != LS_OTBN_OK)
            return LS_OTBN_ENGINE;
        if (HAL_OTBN_HASH_HMAC_Final(&hmac, T) != LS_OTBN_OK)
            return LS_OTBN_ENGINE;
        memcpy(okm + where, T, (i != N) ? hash_len : (okm_len - where));
        where += hash_len;
        T_len = hash_len;
    }
    return LS_OTBN_OK;
}
