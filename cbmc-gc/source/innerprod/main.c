
// computes an inner product
//
// input: arrays of equal length
// output: integer inner product
//


#define LEN 10

typedef struct {
    int xs[LEN];
} Array;


int mpc_main(Array INPUT_A, Array INPUT_B) {

    int product = 0;

    for( int i=0; i<LEN; i++) {
        product += INPUT_A.xs[i] * INPUT_B.xs[i]; 
    }

    return product;

}
