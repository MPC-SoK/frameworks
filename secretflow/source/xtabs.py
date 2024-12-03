#!/usr/bin/env python

import sys

import secretflow as sf
import spu

# Check the version of your SecretFlow
print('The version of SecretFlow: {}'.format(sf.__version__))

# In case you have a running secretflow runtime already.
sf.shutdown()

sf.init(['alice', 'bob', 'carol'], address='local')


aby3_config = sf.utils.testing.cluster_def(parties=['alice', 'bob', 'carol'])


spu_device = sf.SPU(aby3_config)


parties = [sf.PYU(x) for x in ('alice', 'bob')]

spu_io = sf.device.SPUIO(spu_device.conf, spu_device.world_size)


n = int(sys.argv[1])
data = [[list(range(n))] * 2, [list(range(n)), [i % 5 for i in range(n)]]]

spu_data = [parties[i](lambda: data[i])().to(spu_device) for i in range(2)]

def xtabs(*data):
    (xid, yid), (vals, cats) = data
    res = [0] * 5
    for i in range(n):
        for j in range(n):
            for k in range(len(res)):
                add = (xid[i] == yid[j]) * (cats[j] == k) * vals[i]
                res[k] += add
    return res

res = spu_device(xtabs)(*spu_data)

print('result', [int(x) for x in sf.reveal(res)])
print('expected', xtabs(*data))
print('size', n)
