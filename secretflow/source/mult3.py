#!/usr/bin/env python

import sys

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


data = [int(sys.argv[i + 1]) for i in range(3)]
spu_data = [parties[i](lambda: data[i])().to(spu_device) for i in range(3)]

def mult3(a, b, c):
    return a * b * c

res = spu_device(mult3)(*spu_data)

print('result', sf.reveal(res))
print('expected', mult3(*data))
