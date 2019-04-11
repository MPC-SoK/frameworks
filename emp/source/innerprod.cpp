#include "emp-sh2pc/emp-sh2pc.h"
#include <new>
using namespace emp;
using namespace std;

int LEN = 10;

void test_innerprod(int bitsize, string inputs_a[], string inputs_b[], int len) {

    Integer sum(bitsize, 0, PUBLIC);
    Integer prod(bitsize, 0, PUBLIC);
	Integer a[len];
	Integer b[len];

    for( int i=0; i<len; i++) {
        a[i] = Integer(bitsize, inputs_a[i], ALICE);
        b[i] = Integer(bitsize, inputs_b[i], BOB);
    }

    for( int i=0; i<len; i++) {
        prod = a[i] * b[i];
        sum = sum + prod;
    }

    cout << "SUM: " << sum.reveal<int>() << endl;
}


int main(int argc, char** argv) {
    int bitsize;

    // generate circuit for use in malicious library
    if (argc == 2 && strcmp(argv[1], "-m") == 0 ) {
        setup_plain_prot(true, "innerprod.circuit.txt");
        bitsize = 16;
        string inputs[LEN] = {"0","0","0","0","0","0","0","0","0","0"};
        test_innerprod(bitsize, inputs, inputs, LEN);
        finalize_plain_prot();
	return 0;
    }

    // run computation with semi-honest model
    int port, party;
    parse_party_and_port(argv, &party, &port);
    NetIO * io = new NetIO(party==ALICE ? nullptr : "127.0.0.1", port);

    setup_semi_honest(io, party);

    if (argc != 4) {
      cout << "Usage: ./innerprod <party> <port> <bitsize>" << endl
           << endl;
      delete io;
      return 0;
    }

    cout << "Calculating inner product of two inputs of length " << LEN << endl;

    bitsize = atoi(argv[3]);

    char fname_a[40];
    char fname_b[40];

    sprintf(fname_a, "../data/innerprod/%d.1.dat", bitsize);
    sprintf(fname_b, "../data/innerprod/%d.2.dat", bitsize);

    ifstream infile_a(fname_a);
    ifstream infile_b(fname_b);

    string inputs_a[LEN];
    string inputs_b[LEN];

    if( infile_a.is_open() && infile_b.is_open()) {
        for( int i=0; i<LEN; i++) {
            getline( infile_a, inputs_a[i]);
            getline( infile_b, inputs_b[i]);
        }
        infile_a.close();
        infile_b.close();
    }

    test_innerprod(bitsize, inputs_a, inputs_b, LEN);
    delete io;
}


