#ifndef POLYNOMIAL
#define POLYNOMIAL

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_TERM 100
#define MAX_MEMBER 10
#define CLEARBUF                \
    while ((getchar()) != '\n') \
        ;

typedef struct 
{
	float coef;
	int32_t expo;
}polynomial;

typedef struct 
{
	int8_t used;
	char name[32];
	polynomial p[MAX_TERM];
}nameTag;

nameTag nameBook[MAX_MEMBER];

// main function
void menu();
void show_nameBook();
void init_poly();
void show_poly();
void coef();
void add_delete_term();

// common function
void initialize(polynomial P[MAX_TERM]);
polynomial *find_index();
void poly_sort(polynomial P[MAX_TERM]);
void print_poly(polynomial P[MAX_TERM]);
void shift(polynomial P[MAX_TERM], int32_t exponent); // eliminate zero term

#endif