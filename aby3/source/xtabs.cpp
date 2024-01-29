#include <iostream>
#include <vector>
#include <assert.h>
#include "xtabs.h"

#include "aby3-DB/DBServer.h"
#include <cryptoTools/Network/IOService.h>
#include "aby3/sh3/Sh3Runtime.h"
#include "aby3/sh3/Sh3Encryptor.h"
#include "aby3/sh3/Sh3Evaluator.h"

using namespace oc;
using namespace aby3;
using namespace std;

void xtabs_test(u64 partyIdx, std::vector<int> ids, std::vector<int> values)
{
  std::cout << "testing xtabs..." << std::endl;

  IOService ios;

  DBServer srv;

  PRNG prng(ZeroBlock);

  if (partyIdx == 0)
  {
    Session s01(ios, "127.0.0.1:3030", SessionMode::Server, "01");
    Session s02(ios, "127.0.0.1:3031", SessionMode::Server, "02");
    srv.init(0, s02, s01, prng);
  }
  else if (partyIdx == 1)
  {
    Session s10(ios, "127.0.0.1:3030", SessionMode::Client, "01");
    Session s12(ios, "127.0.0.1:3032", SessionMode::Server, "12");
    srv.init(1, s10, s12, prng);
  }
  else
  {
    Session s20(ios, "127.0.0.1:3031", SessionMode::Client, "02");
    Session s21(ios, "127.0.0.1:3032", SessionMode::Client, "12");
    srv.init(2, s21, s20, prng);
  }

  auto keyBitCount = srv.mKeyBitCount;
  std::vector<ColumnInfo>
      catCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount},
                 ColumnInfo{"cat", TypeID::IntID, keyBitCount}},
      valCols = {ColumnInfo{"key", TypeID::IntID, keyBitCount},
                 ColumnInfo{"val", TypeID::IntID, keyBitCount}};

  u64 rows = ids.size();
  assert(ids.size() == rows);
  assert(values.size() == rows);

  Table catData(rows, catCols), valData(rows, valCols);

  // initializes data into Table (still in the clear)
  for (u64 i = 0; i < rows; ++i)
  {
    if (partyIdx == 0)
    {
      catData.mColumns[0].mData(i, 0) = ids[i];
      catData.mColumns[0].mData(i, 1) = values[i];
    }
    else if (partyIdx == 1)
    {
      valData.mColumns[0].mData(i, 0) = ids[i];
      valData.mColumns[0].mData(i, 1) = values[i];
    }
  }

  SharedTable catTable, valTable;
  catTable = (partyIdx == 0) ? srv.localInput(catData) : srv.remoteInput(0);
  valTable = (partyIdx == 1) ? srv.localInput(valData) : srv.remoteInput(1);

  // i64Matrix keys(catTable.mColumns[0].rows(), catTable.mColumns[0].i64Cols());
  // srv.mEnc.revealAll(srv.mRt.mComm, catTable.mColumns[0], keys);
  //
  // if (partyIdx == 0)
  //{
  //  std::cout << keys << std::endl;
  //}

  auto res = srv.join(catTable["key"], valTable["key"], {catTable["cat"], valTable["val"]});
  cout << "not reached " << endl;
  // for (auto c : res.mColumns) {
  //   cout << c.mName << "xXx";
  // }

  aby3::i64Matrix cats(res.mColumns[0].rows(), res.mColumns[0].i64Cols());
  aby3::i64Matrix vals(res.mColumns[1].rows(), res.mColumns[1].i64Cols());

  srv.mEnc.revealAll(srv.mRt.mComm, res.mColumns[0], cats);
  srv.mEnc.revealAll(srv.mRt.mComm, res.mColumns[1], vals);

  if (partyIdx == 0)
  {
    std::cout << cats << std::endl;
  }
}
