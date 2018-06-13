/*
Compute a simple crosstabulation

Party A has a two column array: 
Column 0 is a unique identifier (e.g. SSN as an int)
Column 1 is a value (e.g. salary)

Party B has a two column array: 
Column 0 is a unique identifier (e.g. SSN as an int)
Column 1 is a class (e.g. age group) -- This is assumed to be a small number in the range 0 ... BINS-1

This script computes the sum of salaries by age group, i.e., it computes the sum of A column 1 grouped by B column 1.
The result is a vector of length BINS

This is the brute-force O(n^2) solution
*/


#include <inttypes.h>
#define S 50 //Number of entries in the database
#define BINS 5 //Number of bins (e.g. number of distinct age groups)

typedef struct
{
    uint8_t d[2][S];
} DB;

typedef struct
{
    uint8_t d[BINS];
} HB;

typedef DB InputA;
typedef DB InputB;
typedef HB Output;


Output mpc_main(InputA INPUT_A, InputB INPUT_B)
{
    Output out;

    uint8_t CT[BINS];

    int i,j;
    //Brute force solution

    //Initialize all the bin counts to 0
    //I think unitialized variables default to zero anyway, but I'd like to make sure
    for( i=0; i<BINS; i++ ) {
        CT[i] = 0;
    }

    for( i=0; i<S; i++ ) {
        for( j=0; j<S; j++ ) {
            if( INPUT_A.d[0][i] == INPUT_B.d[0][j] ) { 
                CT[INPUT_B.d[1][j]%BINS] += INPUT_A.d[1][i];
            }
        }
    }

    for( i=0; i<BINS; i++ ) {
        out.d[i] = CT[i];
    }

    return out;
}

