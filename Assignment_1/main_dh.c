#include "utils.h"
#include "dh_assign_1.h"

int main(int argc, char **argv) {
	//Declare and initialize variables.
	int opt;
	char *path = strdup("./dh_files/"), *filename = NULL;
	mpz_t p, g, a, b, public_key_A, public_key_B, shared_key, double_check;
	mpz_init(p); mpz_init(g); mpz_init(a); mpz_init(b); mpz_init(public_key_A); mpz_init(public_key_B); mpz_init(shared_key); mpz_init(double_check);
	FILE *f;
	not_certain = false;
	
	//Read arguments.
	while((opt = getopt(argc, argv, "o:p:g:a:b:h")) != -1) {
		switch(opt) {
            case 'o':
				filename = strdup(optarg);
				strcat(path, filename);
                break;
            case 'p':
				if(mpz_set_str(p, strdup(optarg), 10) == -1) {
					printf("ERROR: Failed to read \"p\".\n");
					info_dh();
				}
                break;
            case 'g':
            	if(mpz_set_str(g, strdup(optarg), 10) == -1) {
					printf("ERROR: Failed to read \"g\".\n");
					info_dh();
				}
                break;
            case 'a':
                if(mpz_set_str(a, strdup(optarg), 10) == -1) {
					printf("ERROR: Failed to read \"a\".\n");
					info_dh();
				}
                break;
            case 'b':
                if(mpz_set_str(b, strdup(optarg), 10) == -1) {
					printf("ERROR: Failed to read \"b\".\n");
					info_dh();
				}
                break;
            case 'h': 
            default:
                info_dh();
		}
	}

	//Check argument correctness.
	check_args(p, g, a, b, filename);

	//Implement the Diffie-Hellman Key Exchange.
	comp_key(p, g, a, public_key_A);
	comp_key(p, g, b, public_key_B);
	comp_key(p, public_key_B, a, shared_key);
	comp_key(p, public_key_A, b, double_check);
	if(mpz_cmp(shared_key, double_check) != 0) {
		printf("ERROR: The shared key is somehow not the same for alice and bob!");
		exit(-1);
	}

	//Write output to file.
	f = fopen(path, "w");
	if(!f) {
		printf("ERROR: Couldn't create file!");
		exit(-1);
	}
	mpz_out_str(f, 10, public_key_A); gmp_fprintf(f, ", ");
	mpz_out_str(f, 10, public_key_B); gmp_fprintf(f, ", ");
	mpz_out_str(f, 10, shared_key);   gmp_fprintf(f, "\n");
	if(not_certain) {
		printf("WARNING: At least one algorithm of the GMP library gave a probabilistic result for number primality.\n");
		printf("\t Almost certainly this won't cause any issues, but if it does generate the keys again.\n");
	}
	fclose(f);

	//Free allocated memory.
	free(filename);
	free(path);

	return 0;
}