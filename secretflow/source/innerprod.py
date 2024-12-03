#!/usr/bin/env python

import sys
import numpy

import secretflow as sf
import spu

# Check the version of your SecretFlow
print('The version of SecretFlow: {}'.format(sf.__version__))

# In case you have a running secretflow runtime already.
sf.shutdown()

names = ['alice', 'bob', 'carol']
sf.init(names, address='local')


aby3_config = sf.utils.testing.cluster_def(parties=names)


spu_device = sf.SPU(aby3_config)


parties = [sf.PYU(name) for name in names]


spu_io = sf.device.SPUIO(spu_device.conf, spu_device.world_size)


data = [numpy.array(list(range(int(sys.argv[1]))))] * 2
spu_data = [parties[i](lambda: data[i])().to(spu_device) for i in range(2)]

def innerprod(a, b):
    return a.dot(b)

res = spu_device(innerprod)(*spu_data)

print('result', sf.reveal(res))
print('expected', innerprod(*data))
