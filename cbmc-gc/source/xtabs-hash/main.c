#include <inttypes.h>

#define S 50
#define BINS 5
#define HASHBINS 2*S
#define BINSIZE 5
#define hash(x) (x%HASHBINS)
#define max(x,y) ((x) > (y) ? (x) : (y))

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

	int i,j,m,n,k;
	int abincounts[HASHBINS]; //Store the number of people in each of A's hash bins
	int bbincounts[HASHBINS];
	int abins[HASHBINS][BINSIZE][2];
	int bbins[HASHBINS][BINSIZE][2];

	for( i=0;i<BINS;i++ ) {
		CT[i]=0;
	}

	//Put each person into a hash bin
	for( i=0; i<S; i++ ) {
		j = hash(INPUT_A.d[0][i]);
		abins[j][abincounts[j]][0] = INPUT_A.d[0][i];
		abins[j][abincounts[j]][1] = INPUT_A.d[1][i];
		abincounts[j]++;

		j = hash(INPUT_B.d[0][i]);	
		bbins[j][bbincounts[j]][0] = INPUT_B.d[0][i];
		bbins[j][bbincounts[j]][1] = INPUT_B.d[1][i];
		bbincounts[j]++;
	}

	//For each hash bin
	for( i=0; i<HASHBINS;i++ ) {
		k = max( abincounts[i], bbincounts[i] );
		k = max( k, BINSIZE );
		//Do brute force matching in the bucket
		for( m=0; m < k; m++ ){ 
			for( n=0; n< k; n++ ) {
				if( abins[i][m][0] == bbins[i][n][0] ) {
					CT[bbins[i][n][1]%BINS] += abins[i][m][1];
				}
			}
		}
	}

	for( i=0;i<BINS;i++ ) {
		out.d[i]=CT[i];
	}

	return out;
}

