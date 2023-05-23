# MP-SPDZ

[MP-SPDZ](https://github.com/data61/MP-SPDZ) features a python-based front end and implements a large set of schemes, including multi-party circuit based, hybrid, and garbled circuit protocols. The source-code is available [on Github](https://github.com/data61/MP-SPDZ); [additional documentation is also online](https://mp-spdz.readthedocs.io/en/latest/).

## Docker setup

Create a Docker image. This will take a few minutes. You only have to do this
once.
```
$ docker build -t mp-spdz .
```

Spin up a Docker container from the image.
```
$ docker run -it --rm mp-spdz
```

## Architecture

While MP-SPDZ implements a number of schemes.
We focus on computation using an integer length of 64.
Computations are performed modulo a large enough prime here, which is output by the compiler.
See the the MP-SPDZ [readme](https://github.com/data61/MP-SPDZ) for details on other domains such as computation modulo 2^k and binary circuits.

## Running examples

First, compile the example source. We provide three examples (mult3, innerprod,
xtabs).
```
$ cd MP-SPDZ
$ ./compile.py -C -F 64 <ex>
```
The `-C` argument is optional but it speeds up the compilation of xtabs.

Generate input for each party (as above).
You'll need to fill in `Player-Data/Input-P<x>-0` with ASCII data for each party
`<x>`.
For example, to run mult3 with inputs 14, 12, and 8, we'd do the following:
```
$ cd MP-SPDZ
$ mkdir Player-Data
$ echo 14 > Player-Data/Input-P0-0
$ echo 12 > Player-Data/Input-P1-0
$ echo 8 > Player-Data/Input-P2-0
```

Execute the three parties. The output transcript will include the
computed solution.
```
$ ./mascot-party.x -N 3 -p 0 <ex> & ./mascot-party.x -N 3 -p 1 <ex> & ./mascot-party.x -N 3 -p 2 <ex>
```

For example, the output from the following will include `Mult3 prod = 1344`.
```
$ ./mascot-party.x -N 3 -p 0 mult3 & ./mascot-party.x -N 3 -p 1 mult3 & ./mascot-party.x -N 3 -p 2 mult3
```

`./mascot-party.x` provides high security in that it tolerates two
corrupted parties and it tolerates these two parties to deviate from
the protocol, in which case the protocol aborts. `./hemi-party.x`
provides less security in that it doesn't tolerate deviation but it
still tolerates any two parties colluding by sharing their information.

Using Shamir's secret
sharing, it is possible to create a faster protocol that tolerates
only one corrupted party, either tolerating deviation as well or not
even that for a faster execution. You can use
`./malicious-shamir-party.x` instead of `./mascot-party.x` for the
more security variant and `./shamir-party.x` for the less secure but
faster variant. Note that Shamir's secret sharing requires encrypted
channels, so you will have to run the following script in order to
generate the required keys and certificates:
```
Scripts/setup-ssl.sh 3
```

This [blog
post](https://sharemind.cyber.ee/the-many-flavours-of-multiparty-computation)
contains more information on the various security models in MPC.

All implementations above support any number of parties by changing
the `-N` command-line argument. For the ones based on Shamir's secret
sharing, make sure to run `Scripts/setup-ssl.sh` with the number of parties.

## Modifying examples

Other examples exist in Programs/Source (some of these come with MP-SPDZ, others we wrote). These can be compiled and run in the same way as shown above, though note that the number of parties is different in different examples. You can learn the SPDZ syntax by reading and modifying these examples, as well as by reading `MP-SPDZ/Programs/Source/tutorial.mpc`.
