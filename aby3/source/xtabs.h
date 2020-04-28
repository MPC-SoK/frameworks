#pragma once

#include <cryptoTools/Common/CLP.h>
void xtabs_test(oc::u64 partyIdx, std::vector<int> ids, std::vector<int> values);

#include <cryptoTools/Network/IOService.h>
#include "aby3/sh3/Sh3Runtime.h"
#include "aby3/sh3/Sh3Encryptor.h"
#include "aby3/sh3/Sh3Evaluator.h"
void setup_samples(
    aby3::u64 partyIdx,
    oc::IOService& ios,
    aby3::Sh3Encryptor& enc,
    aby3::Sh3Evaluator& eval,
    aby3::Sh3Runtime& runtime);

