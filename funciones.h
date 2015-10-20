/* 
 * File:   funciones.h
 * Author: jose y cris
 *
 * Created on 18 de octubre de 2015, 23:17
 */
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#ifndef FUNCIONES_H
#define	FUNCIONES_H

#ifdef	__cplusplus
extern "C" {
#endif
void euclidesExtendido(const mpz_t a, const mpz_t b,mpz_t mcd, mpz_t s, mpz_t t);


#ifdef	__cplusplus
}
#endif

#endif	/* FUNCIONES_H */