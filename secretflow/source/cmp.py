#!/usr/bin/env python

import sys

import secretflow as sf
import spu

import jax
import jax.numpy as jnp

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
data = [jnp.array(x) for x in (list(range(n)), list(range(1, n + 1)))]

spu_data = [parties[i](
    lambda: data[i])().to(spu_device) for i in range(2)]

def cmp(a, b):
    def map_i(i):
        return a[i] < b[i]

    return jax.vmap(map_i)(jnp.arange(n))

res = spu_device(cmp)(*spu_data)

print('result', [int(x) for x in sf.reveal(res)].count(1))
print('expected', list(cmp(*data)).count(True))
print('size', n)
