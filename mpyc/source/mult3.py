import numpy as np
from mpyc.runtime import mpc

async def main():

    # initialize mpc, define secure int type
    await mpc.start()
    secint = mpc.SecInt(64)

    # initialize inputs
    # 3 parties: random value for each party
    # any other number of parties: just use player 0's value 3 times.
    value = np.random.randint(1,10000)
    print("player {} input: {}".format(mpc.pid, value))

    n = len(mpc.parties)
    if n != 3:
        inputs = [secint(value), secint(value), secint(value)]
        print("expected: {}".format(value ** 3))
    else:
        inputs = mpc.input(secint(value), senders=[0,1,2])

    # compute product 
    prod = mpc.prod(inputs)
   
    # output result
    result = await mpc.output(prod)
    print("result:", result)
    await mpc.shutdown()


if __name__ == '__main__':
    
    mpc.run(main())
