#include "emp-sh2pc/emp-sh2pc.h"
using namespace emp;
using namespace std;

void test_mult3(int bitsize, int party, string inputs_a[], string inputs_b[]) {
  int result_bits = 3*bitsize;
  Integer product(result_bits, 1);

  int validate = 1;

  for (int i=0; i<3; i++) {
    Integer a(result_bits, inputs_a[i], ALICE);
    Integer b(result_bits, inputs_b[i], BOB);

    a = a + b;

    product = product * a;

    // calculate correct answer IN THE CLEAR
    // fails if input files aren't in the same place
    if (result_bits < 33) {
      validate *= stoi(inputs_a[i]) + stoi(inputs_b[i]);
    }
  }

  if (result_bits < 33) {
    cout << "Expected: " << validate << endl;
  }

  cout << "Product (binary notation): ";
  for(int i=result_bits-1; i>=0; i--) {
      cout << product[i].reveal();
  }
  cout << endl;
}

int main(int argc, char** argv) {
	int port, party;
	parse_party_and_port(argv, &party, &port);
	NetIO * io = new NetIO(party==ALICE ? nullptr : "127.0.0.1", port);

	setup_semi_honest(io, party);

    if (argc != 4) {
      cout << "Usage: ./mult3 <party> <port> <bitsize>" << endl
           << "where <value> are secret shares of the three inputs"
           << endl;
      delete io;
      return 0;
    }

    int bitsize = atoi(argv[3]);
    char fname_a[40];
    char fname_b[40];

    sprintf(fname_a, "../data/mult3/%d.1.dat", bitsize);
    sprintf(fname_b, "../data/mult3/%d.2.dat", bitsize);

    ifstream infile_a(fname_a);
    ifstream infile_b(fname_b);

    string inputs_a[3];
    string inputs_b[3];

    if( infile_a.is_open() && infile_b.is_open()) {
        for( int i=0; i<3; i++) {
            getline( infile_a, inputs_a[i]);
            getline( infile_b, inputs_b[i]);
        }
        infile_a.close();
        infile_b.close();
    }


    test_mult3(bitsize, party, inputs_a, inputs_b);
	delete io;
}

