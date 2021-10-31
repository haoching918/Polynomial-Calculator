#include "polynomial.h"

// put A + B into D
void poly_addition(polynomial A[MAX_TERM], polynomial B[MAX_TERM], polynomial D[MAX_TERM])
{
    int32_t a_idx = 0, b_idx = 0, d_idx = 0;
    initialize(D);
    while (A[a_idx].coef != 0 && B[b_idx].coef != 0)
    {
        if (A[a_idx].expo > B[b_idx].expo)
        {
            D[d_idx] = A[a_idx];
            a_idx++;
        }
        else if (A[a_idx].expo < B[b_idx].expo)
        {
            D[d_idx] = B[b_idx];
            b_idx++;
        }
        else
        {
            D[d_idx].coef = A[a_idx].coef + B[b_idx].coef;
            D[d_idx].expo = A[a_idx].expo;
            a_idx++;
            b_idx++;
            if (D[d_idx].coef == 0)
            {
                D[d_idx].expo = 0;
                d_idx--;
            }    
        }
        d_idx++;
    }
    // add the rest
    if (A[a_idx].coef == 0)
    {
        for (; B[b_idx].coef != 0 && b_idx != MAX_TERM; b_idx++, d_idx++)
            D[d_idx] = B[b_idx];
    }
    else
    {
        for (; A[a_idx].coef != 0 && a_idx != MAX_TERM; a_idx++, d_idx++)
            D[d_idx] = A[a_idx];
    }
}

// put A - B into D
void poly_subtraction(polynomial A[MAX_TERM], polynomial B[MAX_TERM], polynomial D[MAX_TERM])
{
    // form A + (-B)
    for (size_t i = 0; i < MAX_TERM && B[i].coef != 0; i++)
        B[i].coef *= -1;
    poly_addition(A, B, D);
}

void addition()
{
    // get p1
    polynomial A[MAX_TERM];
    memcpy(A, find_index(), sizeof(A));
    // get p2
    polynomial B[MAX_TERM];
    memcpy(B, find_index(), sizeof(B));
    // result
    polynomial D[MAX_TERM];

    poly_addition(A, B, D);
    printf("\n");
    print_poly(D);
}

void subtraction()
{
    // get p1
    polynomial A[MAX_TERM];
    memcpy(A, find_index(), sizeof(A));
    // get p2
    polynomial B[MAX_TERM];
    memcpy(B, find_index(), sizeof(B));
    // result
    polynomial D[MAX_TERM];

    poly_subtraction(A, B, D);
    printf("\n");
    print_poly(D);
}

void multiplication()
{
    // get p1
    polynomial A[MAX_TERM];
    memcpy(A, find_index(), sizeof(A));
    // get p2
    polynomial B[MAX_TERM];
    memcpy(B, find_index(), sizeof(B));
    // Sum
    polynomial S[MAX_TERM];
    initialize(S);

    for (size_t i = 0; i < MAX_TERM && B[i].coef != 0; i++)
    {
        // tempory total
        polynomial tmpT[MAX_TERM];
        initialize(tmpT);
        // previous sum
        polynomial preS[MAX_TERM];
        memcpy(preS, S, sizeof(preS));
        
        for (size_t j = 0; j < MAX_TERM && A[j].coef != 0; j++)
        {
            tmpT[j].coef = A[j].coef * B[i].coef;
            tmpT[j].expo = A[j].expo + B[i].expo;
        }
        poly_addition(tmpT, preS, S);
    }
    printf("\n");
    print_poly(S);
}

void division()
{
    // get p1
    polynomial A[MAX_TERM];
    memcpy(A, find_index(), sizeof(A));
    // get p2
    polynomial B[MAX_TERM];
    memcpy(B, find_index(), sizeof(B));
    
    // quotient
    polynomial Q[MAX_TERM];
    int32_t q_idx = 0;
    initialize(Q);
    // remainder
    polynomial R[MAX_TERM];
    initialize(R);

    while (A[0].expo >= B[0].expo)
    {
        // record quotient
        Q[q_idx].coef = A[0].coef / B[0].coef;
        Q[q_idx].expo = A[0].expo - B[0].expo;

        // tmpT = B * Q[q_idx]
        polynomial tmpT[MAX_TERM];
        initialize(tmpT);
        for (size_t i = 0; i < MAX_TERM && B[i].coef != 0; i++)
        {
            tmpT[i].coef = B[i].coef * Q[q_idx].coef;
            tmpT[i].expo = B[i].expo + Q[q_idx].expo;
        }

        polynomial preA[MAX_TERM];
        memcpy(preA, A, sizeof(preA));
        poly_subtraction(preA, tmpT, A);
        q_idx++;
    }
    // get remainder
    for (size_t i = 0; i < MAX_TERM && A[i].coef != 0; i++)
        R[i] = A[i];
    
    printf("Quotient: ");
    print_poly(Q);
    printf("Remainder: ");
    print_poly(R);
}