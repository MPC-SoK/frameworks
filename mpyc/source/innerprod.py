import numpy as np
from mpyc.runtime import mpc

async def main():

    # initialize mpc, define secure int type
    LEN = 10
    await mpc.start()
    secint = mpc.SecInt(64) # work in a 64-bit prime field

    # party 0 samples the inputs locally... 
    if mpc.pid == 0:
        vec1 = [np.random.randint(1,1000) for _ in range(LEN)]
        vec2 = [np.random.randint(1,1000) for _ in range(LEN)]

    # ...and secret-shares them with the others
    result_type = [secint()] * LEN
    sec_vec1 = mpc.input([secint(v) for v in vec1] if mpc.pid == 0 else result_type, senders=0)
    sec_vec2 = mpc.input([secint(v) for v in vec2] if mpc.pid == 0 else result_type, senders=0)

    # compute inner product
    ip = mpc.in_prod(sec_vec1, sec_vec2)
   
    # output result (to everybody)
    result = await mpc.output(ip)
    print("result:", result)
    if mpc.pid == 0:
        assert(result == np.dot(vec1, vec2))
    await mpc.shutdown()


if __name__ == '__main__':
    
    mpc.run(main())
