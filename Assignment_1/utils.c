#include "utils.h"

void info_rsa(void) {
	printf(
	    "Usage:\n"
	    "\t./rsa_assign_1 -g\n" 
	    "\t./rsa_assign_1 -i in_file -o out_file -k key_file [-d | -e]\n" 
	    "\t./rsa_assign_1 -h\n\n"
	);
	printf(
	    "Options:\n"
	    "\t-i    path    Path to the input file\n"
	    "\t-o    path    Path to the output file\n"
	    "\t-k    path    Path to the key file\n"
		"\t-g            Perform RSA key-pair generation\n"
	    "\t-d            Decrypt input and store results to output\n"
	    "\t-e            Encrypt input and store results to output\n"
	    "\t-h            Prints help message\n\n"
	);
	printf(
		"Details:\n"
		"\tThe arguments \"i\", \"o\" and \"k\" are always required when using \"e\" or \"d\".\n"
		"\tBy using -g the tool generates a public and a private key and stores them in \"./rsa_files/public.key\" and \"./rsa_files/private.key\" files respectively.\n"
		"\tBy using -d you specify that the tool shall read the ciphertext from the input file, decrypt it and then store the plaintext in the output file.\n"
		"\tBy using -e you specify that the tool shall read the plaintext from the input file, encrypt it and store the ciphertext in the output file.\n"
	);
	exit(-1);
}

void info_dh() {
    printf(
	    "Usage:\n"
	    "\t./dh_assign_1 -o output_file -p prime_number -g primitive_root -a private_key_a -b private_key_b\n" 
	    "\t./dh_assign_1 -h\n\n"
	);
	printf(
	    "Options:\n"
	    "\t-o    path       Path to output file\n"
	    "\t-p    number     Prime number (>1)\n"
	    "\t-g    number     Primitive Root for previous prime number\n"
	    "\t-a    number     Alice's private key/exponent (0 < a < p)\n"
	    "\t-b    number     Bob's private key/exponent (0 < b < p)\n"
	    "\t-h               Prints help message\n\n"
	);
	printf(
		"Details:\n"
		"\tThe program will store the result in the specified output file as: <public key A>, <public key B>, <secret key>.\n"
	);
    exit(-1);
}

bool is_prime(mpz_t n) {
	int res = mpz_probab_prime_p(n, 12);
	if(res == 0) return false;
	else {
		if(res == 1) not_certain = true;
		return true;
	}
}

//Primitive root algorithm is based on the fact that:
//The primitive root of a prime number n is an integer r between[1, n-1] such that the values of r^x(mod n) where x is in the range[0, n-2]
//are different. Return -1 if n is a non-prime number.
//Source: https://www.geeksforgeeks.org/primitive-root-of-a-prime-number-n-modulo-n/
bool is_primitive_root(mpz_t p, mpz_t g) {
	if(mpz_cmp(p, g) <= 0) return false; //g must be smaller than p.
	if(mpz_cmp_ui(p, PRIM_ROOT_LIMIT) > 0) return true; //If p is too big, assume correctness from user.
	else {
		mpz_t res; mpz_init(res);
		int n = mpz_get_ui(p);
		int counter[n];
		int r;
		for(int i = 0; i < n; i++) counter[i] = 0;
		for(int i = 0; i < n - 2; i++) {
			mpz_powm_ui(res, g, i, p);
			r = mpz_get_ui(res);
			if(counter[r]++ > 0) return false;
		}
		return true;
	}
}