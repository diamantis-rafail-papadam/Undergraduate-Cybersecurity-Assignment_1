#include "rsa_assign_1.h"

void check_args(int mode, char *input_filename, char *output_filename, char *key_filename) {
	if(mode == -1) {
		printf("ERROR: No operation chosen!\n");
		info_rsa();
	} else if(!input_filename && mode != 0) {
		printf("ERROR: No input file!\n");
		info_rsa();
	} else if(!output_filename && mode != 0) {
		printf("ERROR: No output file!\n");
		info_rsa();
	} else if(!key_filename && mode != 0) {
		printf("ERROR: No key file!\n");
		info_rsa();
	}
}

void generate_keys(mpz_t n, mpz_t d, mpz_t e) {
	//Define & Initialize Variables.
	char *pub_key_path = strdup(PUBLIC_KEY_PATH), *priv_key_path = strdup(PRIVATE_KEY_PATH);
	mpz_t p, q, rand_num, p_minus_one, q_minus_one, lambda, one;
	mpz_init(p); mpz_init(q); mpz_init(rand_num), mpz_init(p_minus_one); mpz_init(q_minus_one); mpz_init(lambda); mpz_init(one);
	mpz_set_ui(one, 1);
	gmp_randstate_t state; gmp_randinit_default(state);
	mp_bitcnt_t digits = BINARY_DIGITS;
	FILE *f1, *f2;

	//Generate primes p and q.
	gmp_randseed_ui(state, rand());
	while(mpz_cmp_ui(rand_num, 1 << MIN_PRIME_LENGTH) <= 0) mpz_urandomb(rand_num, state, digits); //Making sure rand_num is fairly large.
	mpz_nextprime(p, rand_num); mpz_set_ui(rand_num, 0);
	while(mpz_cmp_ui(rand_num, 1 << MIN_PRIME_LENGTH) <= 0) mpz_urandomb(rand_num, state, digits); //Making sure rand_num is fairly large.
	mpz_nextprime(q, rand_num);
	is_prime(p); is_prime(q); //Checking if the 2 numbers are certainly primes or primes with high probability.

	//Compute n and lambda(n).
	mpz_mul(n, p, q);
	mpz_sub_ui(p_minus_one, p, 1);
	mpz_sub_ui(q_minus_one, q, 1);
	mpz_mul(lambda, p_minus_one, q_minus_one);

	//Choose a random prime e larger than lambda(n) so that both necessary conditions are satisfied.
	while(mpz_cmp(rand_num, lambda) <= 0) mpz_urandomb(rand_num, state, 2*digits + 1);
	mpz_nextprime(e, rand_num); 
	is_prime(e); //Checking if e is certainly prime or prime with high probability.

	//Choose d such that d is the modular inverse of (e, lambda).
	mpz_gcdext(rand_num, d, one, e, lambda);
	if(mpz_cmp_ui(d, 0) <= 0) mpz_add(d, d, lambda);

	//Write keys to files.
	f1 = fopen(pub_key_path, "w");
	f2 = fopen(priv_key_path, "w");
	if(!f1 || !f2) {
		printf("ERROR: Couldn't create file!\n");
		exit(-1);
	}
	mpz_out_str(f1, BASE, n); gmp_fprintf(f1, "\n"); mpz_out_str(f1, BASE, d);
	mpz_out_str(f2, BASE, n); gmp_fprintf(f2, "\n"); mpz_out_str(f2, BASE, e);
	fclose(f1);
	fclose(f2);
}

void encrypt(char *input_path, char *output_path, char *key_path) {
	//Define & Initialize Variables.
	char ch, buf[9];
	char *plaintext = (char *)malloc(MAX_TEXT_SIZE * sizeof(char));
	int i = 0, counter = 0, size;
	mpz_t n, e, m; mpz_init(n); mpz_init(e); mpz_init(m);
	FILE *f1, *f2, *f_key;

	//Initialize File Streams.
	f1 = fopen(input_path, "r");
	f2 = fopen(output_path, "w");
	f_key = fopen(key_path, "r");
	if(!f1) {
		printf("ERROR: Couldn't access input file!\n");
		exit(-1);
	}
	if(!f2) {
		printf("ERROR: Couldn't create output file!\n");
		exit(-1);
	}
	if(!f_key) {
		printf("ERROR: Couldn't access key file!\n");
		exit(-1);
	}

	//Read Keys.
	mpz_inp_str(n, f_key, BASE);
	mpz_inp_str(e, f_key, BASE);

	//Read plaintext.
	while(gmp_fscanf(f1, "%c", &ch) == 1) {
		sprintf(buf, "%d", ch);
		size = strlen(buf);
		plaintext[i++] = size + '0';
		for(int k = 0; k < size; k++) {
			plaintext[i++] = buf[k];
		}
		if(++counter == GROUP_SIZE) {
			plaintext[i] = '\0';
			i = 0; counter = 0;
			//Calculate and write output.
			mpz_set_str(m, plaintext, BASE);
			mpz_powm(m, m, e, n);
			mpz_out_str(f2, BASE, m); gmp_fprintf(f2, "\n");
		}
	}
	//For what's remaining.
	if(i > 0) {
		plaintext[i] = '\0';
		//Calculate and write output.
		mpz_set_str(m, plaintext, BASE);
		mpz_powm(m, m, e, n);
		mpz_out_str(f2, BASE, m); gmp_fprintf(f2, "\n");
	}
	
	//Close files & free memory.
	free(plaintext);
	fclose(f1);
	fclose(f2);
	fclose(f_key);
}

void decrypt(char *input_path, char *output_path, char *key_path) {
	//Define & Initialize Variables.
	char *encrypted_text = (char *)malloc(MAX_TEXT_SIZE * sizeof(char));
	char *decrypted_text = (char *)malloc(MAX_TEXT_SIZE * sizeof(char));
	int i = 0, j = 0, size, len;
	mpz_t n, d, m; mpz_init(n); mpz_init(d); mpz_init(m);
	FILE *f1, *f2, *f_key;

	//Initialize File Streams.
	f1 = fopen(input_path, "r");
	f2 = fopen(output_path, "w");
	f_key = fopen(key_path, "r");
	if(!f1) {
		printf("ERROR: Couldn't access input file!\n");
		exit(-1);
	}
	if(!f2) {
		printf("ERROR: Couldn't create output file!\n");
		exit(-1);
	}
	if(!f_key) {
		printf("ERROR: Couldn't access key file!\n");
		exit(-1);
	}

	//Read keys and ciphertext.
	mpz_inp_str(n, f_key, BASE);
	mpz_inp_str(d, f_key, BASE);

	while(gmp_fscanf(f1, "%s", encrypted_text) == 1) {
		mpz_set_str(m, encrypted_text, BASE);
		//Decrypt ciphertext.
		mpz_powm(m, m, d, n);
		mpz_get_str(encrypted_text, BASE, m);
		size = strlen(encrypted_text);
		while(i < size) {
			len = encrypted_text[i++] - '0';
			char buf[len + 1];
			for(int k = 0; k < len; k++) {
				buf[k] = encrypted_text[i++];
			}
			buf[len] = '\0';
			decrypted_text[j++] = atoi(buf);
		}
		decrypted_text[j] = '\0';
		i = 0; j = 0;

		//Output to file.
		gmp_fprintf(f2, decrypted_text);
	}

	//Close files & free memory.
	free(encrypted_text);
	free(decrypted_text);
	fclose(f1);
	fclose(f2);
	fclose(f_key);
}
