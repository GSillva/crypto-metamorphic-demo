#include "../src/kem.h"
#include <stdio.h>
#include <string.h>

/*
 * inspired by Virdia et al.
 *
 * GenInput: create a valid KEM instance.
 * Call:     run Decaps(sk, c).
 * Maul:     flip one bit in c.
 * Match:    a modified ciphertext must NOT be accepted.
 */

int main(void) {
    uint8_t pk[PK_LEN], sk[SK_LEN];
    uint8_t ct[CT_LEN], ct_mut[CT_LEN];
    uint8_t ss[SS_LEN], ss_mut[SS_LEN];

    kem_keygen(pk, sk);
    kem_encaps(pk, ct, ss);

    if (!kem_decaps(sk, ct, ss_mut)) {
        fprintf(stderr, "FAIL: valid ciphertext was rejected\n");
        return 1;
    }

    memcpy(ct_mut, ct, CT_LEN);
    ct_mut[0] ^= 0x01;

    int accepted = kem_decaps(sk, ct_mut, ss_mut);

    
    if (accepted) {
        fprintf(stderr,
                "METAMORPHIC VIOLATION: modified ciphertext was accepted\n");
        return 1; 
    }

    printf("PASS: modified ciphertext was rejected\n");
    return 0;
}
