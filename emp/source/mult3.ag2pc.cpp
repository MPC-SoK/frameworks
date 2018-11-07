#include <emp-tool/emp-tool.h>
#include "emp-ag2pc/emp-ag2pc.h"
using namespace std;
using namespace emp;

//const string circuit_file_location = macro_xstr(EMP_CIRCUIT_PATH);
void test(int party, NetIO* io, string name, string check_output = "") {
    // read in the circuit from the location where it was generated
	string file = "/root/emp-sh2pc/build/" + name;
        cout << file << endl;
	CircuitFile cf(file.c_str());
    //
    // initialize some timing stuff?
	auto t1 = clock_start();
	C2PC twopc(io, party, &cf);
	io->flush();
	cout << "one time:\t"<<party<<"\t" <<time_from(t1)<<endl;

    // preprocessing?
	t1 = clock_start();
	twopc.function_independent();
	io->flush();
	cout << "inde:\t"<<party<<"\t"<<time_from(t1)<<endl;

    // more preprocessing?
	t1 = clock_start();
	twopc.function_dependent();
	io->flush();
	cout << "dep:\t"<<party<<"\t"<<time_from(t1)<<endl;

    // create and fill in input vectors (to all zeros with memset)
	bool *in = new bool[max(cf.n1, cf.n2)];
	cout << "input size: max " << cf.n1 << "\t" << cf.n2;
	bool * out = new bool[cf.n3];
	if (party == ALICE) {
	    memset(in, false, max(cf.n1, cf.n2));
	} else {
	    memset(in, false, max(cf.n1, cf.n2));
	}
	memset(out, false, cf.n3);

    // online protocol execution
	t1 = clock_start();
	twopc.online(in, out);
	cout << "online:\t"<<party<<"\t"<<time_from(t1)<<endl;

    // compare result to our hardcoded expected result
	if(party == BOB and check_output.size() > 0){
		string res = "";
		for(int i = 0; i < cf.n3; ++i)
			res += (out[i]?"1":"0");
		cout << "result: " << res << endl;
		cout << (res == hex_to_binary(check_output)? "GOOD!":"BAD!")<<endl;
	}
	delete[] in;
	delete[] out;
}

int main(int argc, char** argv) {
    // set up parties
	int party, port;
	parse_party_and_port(argv, &party, &port);
	NetIO* io = new NetIO(party==ALICE ? nullptr:IP, port);
	io->set_nodelay();
	test(party, io, "mult3.circuit.txt", string("c000"));
	delete io;
	return 0;
}

