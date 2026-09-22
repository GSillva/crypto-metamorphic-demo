#ifndef KEM_H
#define KEM_H

#include <stddef.h>
#include <stdint.h>

#define PK_LEN 32
#define SK_LEN 32
#define CT_LEN 32
#define SS_LEN 32

void kem_keygen(uint8_t pk[PK_LEN], uint8_t sk[SK_LEN]);
void kem_encaps(const uint8_t pk[PK_LEN], uint8_t ct[CT_LEN], uint8_t ss[SS_LEN]);
int kem_decaps(const uint8_t sk[SK_LEN], const uint8_t ct[CT_LEN], uint8_t ss[SS_LEN]);

#endif
