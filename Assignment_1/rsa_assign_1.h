#ifndef _RSA_ASSIGN_1_H
#define _RSA_ASSIGN_1_H

#include "utils.h"

#define BASE 16 //Use integer values between 10 and 62.
#define BINARY_DIGITS 512 //Use integer values between 14 and 4096. Larger values are possible but execution time will be slow.
#define MIN_PRIME_LENGTH (30 < BINARY_DIGITS/2 ? 30 : BINARY_DIGITS/2)
#define GROUP_SIZE (int)floor(BINARY_DIGITS*log10(2) / 4)
#define PUBLIC_KEY_PATH "./rsa_files/public.key"
#define PRIVATE_KEY_PATH "./rsa_files/private.key"
#define MAX_TEXT_SIZE 100000

/*
 * Generates private and public keys and saves them in "private.key" and "public.key" files respectively.
 * arg0: n.
 * arg1: d.
 * arg2: e.
 */
void generate_keys(mpz_t, mpz_t, mpz_t);

/*
 * Encrypts an input file and writes the ciphertext in an output file.
 * arg0: Path to the input file.
 * arg1: Path to the output file.
 * arg2: Path to the key file.
 */
void encrypt(char *, char *, char *);

/*
 * Decrypts an input file and writes the plaintext in an output file.
 * arg0: Path to the input file.
 * arg1: Path to the output file.
 * arg2: Path to the key file.
 */
void decrypt(char *, char *, char *);

/*
 * Checks the correctness of the arguments.
 * arg0: Operation.
 * arg1: Path to the input file.
 * arg2: Path to the output file.
 * arg3: Path to the key file.
 */
void check_args(int, char *, char *, char *);

#endif
