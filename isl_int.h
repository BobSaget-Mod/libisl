/*
 * Copyright 2008-2009 Katholieke Universiteit Leuven
 *
 * Use of this software is governed by the MIT license
 *
 * Written by Sven Verdoolaege, K.U.Leuven, Departement
 * Computerwetenschappen, Celestijnenlaan 200A, B-3001 Leuven, Belgium
 */

#ifndef ISL_INT_H
#define ISL_INT_H
#define ISL_DEPRECATED_INT_H

#include <isl/hash.h>
#include <isl/printer.h>
#include <string.h>
#include <gmp.h>
#include <isl_config.h>

#ifndef mp_get_memory_functions
void mp_get_memory_functions(
		void *(**alloc_func_ptr) (size_t),
		void *(**realloc_func_ptr) (void *, size_t, size_t),
		void (**free_func_ptr) (void *, size_t));
#endif

/* isl_int is the basic integer type.  It currently always corresponds
 * to a gmp mpz_t, but in the future, different types such as long long
 * or cln::cl_I will be supported.
 */
typedef mpz_t	isl_int;

#define isl_int_init(i)		mpz_init(i)
#define isl_int_clear(i)	mpz_clear(i)

#define isl_int_set(r,i)	mpz_set(r,i)
#define isl_int_set_gmp(r,i)	mpz_set(r,i)
#define isl_int_set_si(r,i)	mpz_set_si(r,i)
#define isl_int_set_ui(r,i)	mpz_set_ui(r,i)
#define isl_int_get_gmp(i,g)	mpz_set(g,i)
#define isl_int_fits_slong(r)	mpz_fits_slong_p(r)
#define isl_int_get_si(r)	mpz_get_si(r)
#define isl_int_fits_ulong(r)	mpz_fits_ulong_p(r)
#define isl_int_get_ui(r)	mpz_get_ui(r)
#define isl_int_get_d(r)	mpz_get_d(r)
#define isl_int_get_str(r)	mpz_get_str(0, 10, r)
typedef void (*isl_int_print_gmp_free_t)(void *, size_t);
#define isl_int_free_str(s)					\
	do {								\
		isl_int_print_gmp_free_t gmp_free;			\
		mp_get_memory_functions(NULL, NULL, &gmp_free);		\
		(*gmp_free)(s, strlen(s) + 1);				\
	} while (0)
#define isl_int_abs(r,i)	mpz_abs(r,i)
#define isl_int_neg(r,i)	mpz_neg(r,i)
#define isl_int_swap(i,j)	mpz_swap(i,j)
#define isl_int_swap_or_set(i,j)	mpz_swap(i,j)
#define isl_int_add_ui(r,i,j)	mpz_add_ui(r,i,j)
#define isl_int_sub_ui(r,i,j)	mpz_sub_ui(r,i,j)

#define isl_int_add(r,i,j)	mpz_add(r,i,j)
#define isl_int_sub(r,i,j)	mpz_sub(r,i,j)
#define isl_int_mul(r,i,j)	mpz_mul(r,i,j)
#define isl_int_mul_2exp(r,i,j)	mpz_mul_2exp(r,i,j)
#define isl_int_mul_si(r,i,j)	mpz_mul_si(r,i,j)
#define isl_int_mul_ui(r,i,j)	mpz_mul_ui(r,i,j)
#define isl_int_pow_ui(r,i,j)	mpz_pow_ui(r,i,j)
#define isl_int_addmul(r,i,j)	mpz_addmul(r,i,j)
#define isl_int_addmul_ui(r,i,j)	mpz_addmul_ui(r,i,j)
#define isl_int_submul(r,i,j)	mpz_submul(r,i,j)
#define isl_int_submul_ui(r,i,j)	mpz_submul_ui(r,i,j)

#define isl_int_gcd(r,i,j)	mpz_gcd(r,i,j)
#ifdef GMP_NORMALIZE_GCDEXT
void isl_gmp_gcdext(mpz_t G, mpz_t S, mpz_t T, mpz_t A, mpz_t B);
#define isl_int_gcdext(g,x,y,i,j)	isl_gmp_gcdext(g,x,y,i,j)
#else
#define isl_int_gcdext(g,x,y,i,j)	mpz_gcdext(g,x,y,i,j)
#endif
#define isl_int_lcm(r,i,j)	mpz_lcm(r,i,j)
#define isl_int_divexact(r,i,j)	mpz_divexact(r,i,j)
#define isl_int_divexact_ui(r,i,j)	mpz_divexact_ui(r,i,j)
#define isl_int_tdiv_q(r,i,j)	mpz_tdiv_q(r,i,j)
#define isl_int_cdiv_q(r,i,j)	mpz_cdiv_q(r,i,j)
#define isl_int_fdiv_q(r,i,j)	mpz_fdiv_q(r,i,j)
#define isl_int_fdiv_r(r,i,j)	mpz_fdiv_r(r,i,j)
#define isl_int_fdiv_q_ui(r,i,j)	mpz_fdiv_q_ui(r,i,j)

#define isl_int_read(r,s)	mpz_set_str(r,s,10)
#define isl_int_print(out,i,width)					\
	do {								\
		char *s;						\
		s = mpz_get_str(0, 10, i);				\
		fprintf(out, "%*s", width, s);				\
		isl_int_free_str(s);                                        \
	} while (0)

#define isl_int_sgn(i)		mpz_sgn(i)
#define isl_int_cmp(i,j)	mpz_cmp(i,j)
#define isl_int_cmp_si(i,si)	mpz_cmp_si(i,si)
#define isl_int_eq(i,j)		(mpz_cmp(i,j) == 0)
#define isl_int_ne(i,j)		(mpz_cmp(i,j) != 0)
#define isl_int_lt(i,j)		(mpz_cmp(i,j) < 0)
#define isl_int_le(i,j)		(mpz_cmp(i,j) <= 0)
#define isl_int_gt(i,j)		(mpz_cmp(i,j) > 0)
#define isl_int_ge(i,j)		(mpz_cmp(i,j) >= 0)
#define isl_int_abs_eq(i,j)	(mpz_cmpabs(i,j) == 0)
#define isl_int_abs_ne(i,j)	(mpz_cmpabs(i,j) != 0)
#define isl_int_abs_lt(i,j)	(mpz_cmpabs(i,j) < 0)
#define isl_int_abs_gt(i,j)	(mpz_cmpabs(i,j) > 0)
#define isl_int_abs_ge(i,j)	(mpz_cmpabs(i,j) >= 0)


#define isl_int_is_zero(i)	(isl_int_sgn(i) == 0)
#define isl_int_is_one(i)	(isl_int_cmp_si(i,1) == 0)
#define isl_int_is_negone(i)	(isl_int_cmp_si(i,-1) == 0)
#define isl_int_is_pos(i)	(isl_int_sgn(i) > 0)
#define isl_int_is_neg(i)	(isl_int_sgn(i) < 0)
#define isl_int_is_nonpos(i)	(isl_int_sgn(i) <= 0)
#define isl_int_is_nonneg(i)	(isl_int_sgn(i) >= 0)
#define isl_int_is_divisible_by(i,j)	mpz_divisible_p(i,j)

uint32_t isl_gmp_hash(mpz_t v, uint32_t hash);
#define isl_int_hash(v,h)	isl_gmp_hash(v,h)

__isl_give isl_printer *isl_printer_print_isl_int(__isl_take isl_printer *p,
	isl_int i);

#endif
