#include<iostream>
#include <vector>
#include <assert.h>
#include "xtabs.h"

#include "aby3-DB/DBServer.h"

using namespace oc;
using namespace aby3;
using namespace std;

void xtabs_test( u64 partyIdx, std::vector<int> ids, std::vector<int> values){
    std::cout << "testing xtabs..." << std::endl;

    IOService ios;
    
    DBServer srv;
    if (partyIdx == 0) {
      Session s01(ios, "127.0.0.1:3030", SessionMode::Server, "01");
      Session s02(ios, "127.0.0.1:3031", SessionMode::Server, "02");
      srv.init(0, s02, s01);
     
    } else if (partyIdx == 1) {
      Session s10(ios, "127.0.0.1:3030", SessionMode::Client, "01");
      Session s12(ios, "127.0.0.1:3032", SessionMode::Server, "12");
      srv.init(1, s10, s12);
    } else {
      Session s20(ios, "127.0.0.1:3031", SessionMode::Client, "02");
      Session s21(ios, "127.0.0.1:3032", SessionMode::Client, "12");
      srv.init(2, s21, s20);
    }

    // 80 bits;
    u32 hashSize = 80;

    PRNG prng(ZeroBlock);

    auto keyBitCount = srv.mKeyBitCount;
    // to start: just have id column.
    std::vector<ColumnInfo>
        catCols = { ColumnInfo{ "key", TypeID::IntID, keyBitCount },
                    ColumnInfo{ "cat", TypeID::IntID, keyBitCount }},
        valCols = { ColumnInfo{ "key", TypeID::IntID, keyBitCount },
                    ColumnInfo{ "val", TypeID::IntID, keyBitCount } };

    u64 rows = 10;
    assert (ids.size() == rows);
    assert (values.size() == rows);

    Table a(rows, catCols)
        , b(rows, valCols);

    // ?
    auto intersectionSize = rows;

    // todo initialize properly
    Table catData, valData;
    for (auto& c : valData.mColumns) prng.get<i64>(c.mData.data(), c.mData.size());
    for (auto& c : catData.mColumns) prng.get<i64>(c.mData.data(), c.mData.size());









}

