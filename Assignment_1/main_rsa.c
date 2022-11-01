#include "rsa_assign_1.h"
#include "utils.h"

int main(int argc, char **argv) {
	srand(time(NULL)); //randomize the seed of "rand()".

	//Declare and initialize variables.
	int opt, mode = -1;
	char *input_path = strdup("./rsa_files/"), *output_path = strdup("./rsa_files/"), *key_path = strdup("./rsa_files/");
	char *input_filename = NULL, *output_filename = NULL, *key_file = NULL;
	mpz_t n, d, e; mpz_init(n); mpz_init(d); mpz_init(e);
	not_certain = false;

	//Read arguments.
	while((opt = getopt(argc, argv, "i:o:k:gdeh")) != -1) {
		switch(opt) {
		case 'i':
			input_filename = strdup(optarg);
			strcat(input_path, input_filename);
			break;
		case 'o':
			output_filename = strdup(optarg);
			strcat(output_path, output_filename);
			break;
		case 'k':
			key_file = strdup(optarg);
			strcat(key_path, key_file);
			break;
		case 'g':
			mode = 0; //generate private and public keys and save them in 2 different files.
			break;
		case 'e':
			mode = 1; //encrypt the input file using the key in "public.key" and save it in the output file.
			break;
		case 'd':
			mode = 2; //decrypt the input file using the key in "private.key" and save it in the output file.
			break;
		case 'h':
		default:
			info_rsa();
		}
	}

	//Check argument correctness.
	check_args(mode, input_filename, output_filename, key_file);

	//Implementation according to operation.
	switch(mode) {
		case 0: //generate private and public keys and save them in 2 different files.
			generate_keys(n, d, e);
			break;
		case 1: //encrypt the input file using the key in "public.key" and save it in the output file.
			encrypt(input_path, output_path, key_path);
			break;
		case 2: //decrypt the input file using the key in "private.key" and save it in the output file.
			decrypt(input_path, output_path, key_path);
			break;
		default:
			printf("ERROR: No operation chosen and didn't detect it in argument check!\n"); //code shouldn't reach this place.
	}

	if(not_certain) {
		printf("WARNING: At least one algorithm of the GMP library gave a probabilistic result for number primality.\n");
		printf("\t Almost certainly this won't cause any issues, but if it does generate the keys again.\n");
		printf("\t If you don't want this to be happening, change BINARY_DIGITS macro in \"rsa_assign_1.h\" to be at most 24.\n");
	}

	//Free allocated memory.
	free(input_filename);
	free(output_filename);
	free(key_file);

	return 0;
}
