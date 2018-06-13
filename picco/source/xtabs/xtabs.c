/*
 * Computes crosstabs
 * Possible optimizations:
 * - inner product instead of inefficient if for bin assignment?
 */

public int LEN = 10;
public int BINS = 5;

public int main() {

    int A_vals[LEN][2], B_bins[LEN][2];

    int bin_sums[BINS];

    public int bid;
    for (bid = 0; bid < BINS; bid++) [
        bin_sums[bid] = 0;
    ]

    smcinput(A_vals,1,LEN,2);
    smcinput(B_bins,2,LEN,2);

    public int xid, yid;

    for (xid = 0; xid < LEN; xid++) {
        for (yid = 0; yid < LEN; yid++) {
            // if IDs match, add value to appropriate bin
            if (A_vals[xid][0] == B_bins[yid][0]) {
                int matching_bin = B_bins[yid][1]; 
                bin_sums[matching_bin] = bin_sums[matching_bin] + A_vals[xid][1];
            }
        }
    }

    smcoutput(bin_sums,1,BINS);
    return 0;

}
