"""Demo dot product.

This MPyC demo can be run with any number of parties m >= 1.

Each party locally generates two lists of LOAD random integers, and
uses these lists as *private* inputs for the multiparty computation.

All the privately contributed entries are concatenated to form two
secret-shared vectors x and y. The dot product x.y is then computed securely.
"""

from random import randint
from mpyc.runtime import mpc

LOAD = 100

flatten = lambda x: [a for _ in x for a in _]


async def main():

    # Use 32-bit (default) secure integers:
    secint = mpc.SecInt()

    # Each party locally generates LOAD random entries of type secint:
    my_entries_for_vec_x = [secint(randint(-1000, 1000)) for _ in range(LOAD)]
    my_entries_for_vec_y = [secint(randint(-1000, 1000)) for _ in range(LOAD)]

    # Start MPyC runtime to let all parties connect:
    await mpc.start()

    # The entries for vectors x and y are secret-shared between all parties:
    vec_x = flatten(mpc.input(my_entries_for_vec_x))
    vec_y = flatten(mpc.input(my_entries_for_vec_y))

    # Secure dot products are supported natively and *very* efficiently:
    c = mpc.in_prod(vec_x, vec_y)

    # Open the secret-shared value c and let all parties print the result:
    print('Dot product:', await mpc.output(c))

    # Shutdown MPyC runtime to close all connections:
    await mpc.shutdown()

if __name__ == '__main__':
    mpc.run(main())
