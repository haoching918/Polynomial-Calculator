#ifndef COMPUTE
#define COMPUTE
#include "polynomial.h"

// main function
void addition();
void subtraction();
void multiplication();
void division();
    
// common function
void poly_addition(polynomial A[MAX_TERM], polynomial B[MAX_TERM], polynomial D[MAX_TERM]);
void poly_subtraction(polynomial A[MAX_TERM], polynomial B[MAX_TERM], polynomial D[MAX_TERM]);

#endif