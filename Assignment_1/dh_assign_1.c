#include "dh_assign_1.h"

void check_args(mpz_t p, mpz_t g, mpz_t a, mpz_t b, char *output_file) {
    mpz_t zero; mpz_init(zero);
    if(mpz_cmp(p, zero) <= 0 || !is_prime(p)) {
		printf("ERROR: Number \"p\" needs to be prime greater than 1!\n");
		info_dh();
	} else if(mpz_cmp(g, zero) <= 0 || !is_primitive_root(p, g)) {
		printf("ERROR: Number \"g\" needs to be a primitive root of \"p\"!\n");
        info_dh();
	} else if(mpz_cmp(a, zero) <= 0 || mpz_cmp(a, p) >= 0) {
		printf("ERROR: 0 < a < p is not satisfied!\n");
		info_dh();
	} else if(mpz_cmp(b, zero) <= 0 || mpz_cmp(b, p) >= 0) {
		printf("ERROR: 0 < b < p is not satisfied.\n");
		info_dh();
	} else if(!output_file) {
        printf("ERROR: No output file!\n");
        info_dh();
    }
}

void comp_key(mpz_t p, mpz_t g, mpz_t a, mpz_t res) {
    mpz_powm(res, g, a, p);
    return;
}