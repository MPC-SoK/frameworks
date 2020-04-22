import numpy as np
from mpyc.runtime import mpc

async def main():

    # initialize mpc, define secure int type
    LEN = 10
    await mpc.start()
    secint = mpc.SecInt(64)

    # initialize inputs
    values = [np.random.randint(1,1000) for _ in range(LEN)]

    n = len(mpc.parties)
    inputs = mpc.input([secint(v)for v in values], senders=list(range(n)))

    # compute pairwise products
    prod = inputs[0]
    for inp in inputs[1:]:
        prod = mpc.schur_prod(prod, inp)
    ip = mpc.sum(prod)
   
    # output result
    result = await mpc.output(ip)
    print("result:", result)
    await mpc.shutdown()


if __name__ == '__main__':
    
    mpc.run(main())

