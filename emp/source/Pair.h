#include "emp-sh2pc/emp-sh2pc.h"

using namespace emp;
using namespace std;

class Pair {

public: 
    Integer *id;
    Integer *val;
    int party;
    int bitlen;

    Pair() {
        party = PUBLIC;
        bitlen = 8;
    }
    Pair(int p);
    Pair(int p, int bl, int i, int v);
    Pair(int p, int bl, string i, string v);
    ~Pair();

    void set_id(int id);
    void set_value(int value);

    Integer get_id();
    Integer get_val();

};

Pair::Pair(int p) {
    party = p;
}

Pair::Pair(int p, int bl, int i, int v) {
    party = p;
    id = new Integer(bl, i, party);
    val = new Integer(bl, v, party);
}

Pair::Pair(int p, int bl, string i, string v) {
    party = p;
    id = new Integer(bl, i, party);
    val = new Integer(bl, v, party);
}

Pair::~Pair() {
  /*
  delete id;
  delete val;
  */
}


void Pair::set_id(int i) {
    id = new Integer(bitlen, i, party);
}

void Pair::set_value(int v) {
    val = new Integer(bitlen, v, party);
}

Integer Pair::get_id() {
    return *id;
}

Integer Pair::get_val() {
    return *val;
}
