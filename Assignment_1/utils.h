#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <gmp.h>
#include <time.h>

#define PRIM_ROOT_LIMIT 100000

/*
 * Flag that tells us whether some algorithm gave a probabilistic result.
 */
bool not_certain;

/*
 * Prints the usage message for Diffie-Hellman Key Exchange.
 */
void info_dh(void);

/*
 * Prints the usage message for RSA.
 */
void info_rsa(void);

/*
 * Checks whether an integer is prime.
 * arg0: Positive number that we want to test.
 */
bool is_prime(mpz_t);

/*
 * Check whether the arg1 is a primitive root of arg0.
 * arg0: Prime number.
 * arg1: Positive number that is tested on whether it's a primitive root of arg0.
 */
bool is_primitive_root(mpz_t, mpz_t);

#endif
