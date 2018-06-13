#include "emp-sh2pc/emp-sh2pc.h"
#include <new>
#include "Pair.h"
using namespace emp;
using namespace std;

int LEN = 10;
int BINS = 5;

void test_xtabs(int party, int bitsize, string xids[], string bins[], 
                                        string yids[], string vals[]) {
    Pair xs[LEN];
    Pair ys[LEN];
    Integer binsums[BINS];

    // convert to secure values
    for( int i=0; i<LEN; i++ ) {
        xs[i] = Pair(ALICE, bitsize, xids[i], bins[i]); 
        ys[i] = Pair(BOB, bitsize, yids[i], vals[i]);
    }

    // initialize sums
    for( int i=0; i<BINS; i++) {
        binsums[i] = Integer(bitsize, 0, PUBLIC);
    }

    // brute-force xtabs
    Integer zero(bitsize, 0, PUBLIC);
    for( int xit=0; xit<LEN; xit++) {
        for( int yit=0; yit<LEN; yit++) {
            Bit eqid = xs[xit].get_id().equal(ys[yit].get_id());
            Integer result = zero.select(eqid, ys[yit].get_val());

            for( int bit=0; bit < BINS; bit++) {
                Integer bin(bitsize, bit);
                Bit eqbin = xs[xit].get_val().equal(bin);
                binsums[bit] = binsums[bit] + zero.select(eqbin, result);
            }
        }
    }

    // reveal sums
    for(int i=0; i<BINS; i++) {
        cout << "bin " << i << ": " << binsums[i].reveal<int>() << endl;
    }
}



int main(int argc, char** argv) {
    int port, party;
    parse_party_and_port(argv, &party, &port);
    NetIO * io = new NetIO(party==ALICE ? nullptr : "127.0.0.1", port);

    setup_semi_honest(io, party);

    if (argc != 4) {
      cout << "Usage: ./mult3 <party> <port> <bitsize>" << endl
           << endl;
      delete io;
      return 0;
    }

    // read inputs from file
    // (assume parties have a dummy file for the other's input)
    int bitsize = atoi(argv[3]);

    char fname[30];
    sprintf(fname, "../data/xtabs/%d.bins.dat", bitsize);
    ifstream infile(fname);

    string xids[LEN];
    string bins[LEN];
    if( infile.is_open()) {
        for( int i=0; i<LEN; i++) {
            getline(infile, xids[i], ' ');
            getline(infile, bins[i]);
        }
        infile.close();
    }

    sprintf(fname, "../data/xtabs/%d.vals.dat", bitsize);
    infile.open(fname);

    string yids[LEN];
    string vals[LEN];
    if( infile.is_open()) {
        for( int i=0; i<LEN; i++) {
            getline(infile, yids[i], ' ');
            getline(infile, vals[i]);
        }
        infile.close();
    }
    
    test_xtabs(party, bitsize, xids, bins, yids, vals);

    delete io;
    return 0;

}



