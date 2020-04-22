# xtabs
# 
# computes a database join function (sums by category)
# this code is written as a script, so we call mpc.run() on each individual mpc operation instead of
# calling it once on the whole operation as in mult3, innerprod
#
# this code was contributed by Berry Schoenmakers via private correspondence
#

from mpyc.runtime import mpc
from mpyc.seclists import seclist
secint = mpc.SecInt()

N = 25 # number of samples
C = 4 # number of categories

# deterministic input data
# (no mpc.input to assign different inputs to different parties)
categories = [(secint(i), secint(i%C)) for i in range(N)]
values = [(secint(i), secint(i)) for i in range(N)]

mpc.run(mpc.start())

s = seclist([0]*C, secint)

for i,c in categories:
    for j,v in values:
        s[c] += mpc.if_else(i==j, v, 0)

print(mpc.run(mpc.output(list(s))))

mpc.run(mpc.shutdown())
