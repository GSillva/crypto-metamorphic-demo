#include "kem.h"
#include <string.h>

/*
 * Educational toy KEM.
 *
 * This is NOT cryptography. It exists only to demonstrate the
 * metamorphic-testing workflow used in the Virdia et al. paper.
 */

static void toy_hash(const uint8_t *in, size_t n, uint8_t out[SS_LEN]) {
    for (size_t i = 0; i < SS_LEN; ++i) {
        uint8_t x = (uint8_t)(0xA5u + 31u * i);
        for (size_t j = 0; j < n; ++j)
            x = (uint8_t)((x ^ in[j]) + (uint8_t)(j * 17u + i));
        out[i] = x;
    }
}

void kem_keygen(uint8_t pk[PK_LEN], uint8_t sk[SK_LEN]) {
    for (size_t i = 0; i < SK_LEN; ++i) {
        sk[i] = (uint8_t)(0x10u + 3u * i);
        pk[i] = (uint8_t)(sk[i] ^ 0x5Au);
    }
}

void kem_encaps(const uint8_t pk[PK_LEN], uint8_t ct[CT_LEN], uint8_t ss[SS_LEN]) {
    for (size_t i = 0; i < CT_LEN; ++i)
        ct[i] = (uint8_t)(pk[i] ^ 0xC3u);

    uint8_t buf[PK_LEN + CT_LEN];
    memcpy(buf, pk, PK_LEN);
    memcpy(buf + PK_LEN, ct, CT_LEN);
    toy_hash(buf, sizeof(buf), ss);
}

int kem_decaps(const uint8_t sk[SK_LEN], const uint8_t ct[CT_LEN], uint8_t ss[SS_LEN]) {
    uint8_t pk[PK_LEN];
    for (size_t i = 0; i < PK_LEN; ++i)
        pk[i] = (uint8_t)(sk[i] ^ 0x5Au);

    uint8_t expected_ct[CT_LEN];
    for (size_t i = 0; i < CT_LEN; ++i)
        expected_ct[i] = (uint8_t)(pk[i] ^ 0xC3u);

    if (memcmp(ct, expected_ct, CT_LEN) != 0)
        return 0;  // reject modified ciphertext

    uint8_t buf[PK_LEN + CT_LEN];
    memcpy(buf, pk, PK_LEN);
    memcpy(buf + PK_LEN, ct, CT_LEN);
    toy_hash(buf, sizeof(buf), ss);
    return 1;
}
