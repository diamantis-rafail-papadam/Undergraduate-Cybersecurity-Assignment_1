#ifndef _DH_ASSIGN_1_H
#define _DH_ASSIGN_1_H

#include "utils.h"

/*
 * Checks the correctness of the arguments.
 * arg0: Prime Number p.
 * arg1: Primitive Root of p.
 * arg2: Private exponent a.
 * arg3: Private exponent b.
 * arg4: Output File.
 */
void check_args(mpz_t, mpz_t, mpz_t, mpz_t, char *);

/*
 * Calculates the formula ((arg1 ^ arg2) mod arg0) and stores the result in arg3.
 * arg0: Prime number p.
 * arg1: Base g.
 * arg2: Exponent [a | b].
 * arg3: The result will be stored here.
 */
void comp_key(mpz_t, mpz_t, mpz_t, mpz_t);

#endif