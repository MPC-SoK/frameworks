Frigate was developed by Benjamin Mood, Debayan Gupta, Henry Carter, Kevin R. B. Butler, and Patrick Traynor. 

## Docker setup
Create a Docker image. This will take a moment. You only have to do this once.
```
$ docker build -t frigate .
```

Spin up a Docker container from the image.
```
$ docker run -it --rm frigate
```

## Architecture
Frigate is a circuit compiler. Compiling the code provides an executable that
converts `.wir` files to circuits, in a special compressed frigate format. There
is also an option to produce output in other formats (e.g. gate by gate).

Since Frigate does not have a way to evaluate these circuits we have also
included in the docker the BMR implementation developed by Bar-Ilan Cryptography
Research Group which can be used to securely evaluate circuits.
The implementation is available at https://github.com/cryptobiu/Semi-Honest-BMR.
It is based on the paper "Optimizing Semi-Homest Secure Multiparty Computation 
for the Internet" by Aner Ben-Afraim, Yehuda Lindell and Eran Omri. 

## Running examples
We've copied our examples to their `test` directory, but since we've installed
the `frigate` binary in `/usr/bin/`, you can run an example from anywhere.

We've implemented `mult3`, `innerprod`, and `xtabs`. Replace `<ex>` below with
any of these examples, or with their provided tests. 

```
$ cd frigaterelease/src/tests/<ex>
$ frigate <ex>.wir -i_output <ex>.out -i
compiler:   time(s):0.24531
```

Frigate and the BMR implementation use different circuit formats.
We provide a script to convert from Frigate's format to BMR's.
It can be run as follows: 

```
$ cd
$ mkdir Semi-Honest-BMR/<ex>
$ ~/source/convert.py frigaterelease/src/tests/<ex>/<ex>.out > Semi-Honest-BMR/<ex>/<ex>
```

Then produce input files for the program. The input is represented in binary as a 
string of 0s and 1s on a single line, starting with the least significant bit. The
number of bits should match the number of input wires for that player in <ex>.wir.

```
$ cd Semi-Honest-BMR/<ex>
$ vim <ex>.P0

$ vim <ex>.P<nParties-1>
```

BMR is then run as follows:

```
$ cd ..
$ for i in {0..<N_PARTIES-1>}; do 
    ./BMRPassive.out ${i} ./<ex>/<ex> ./<ex>/<ex>.P${i} ./parties <Key> <Version Number> &
  done;
```

Here <Key> should be a random secret key.
BMR converts any (non-constant-round) secure multiparty protocol into a 
constant-round secure multiparty protocol. <Version Number> refers to 
which underlying secure multiparty protocol is used. It is an integer
between 0 and 3 inclusive.
Refer to the BMR implementation documentation and the paper it was based on
for more information about these protocols.


## Modifying examples

Modifying examples is no more complicated than running them. Simply make a
`.wir` file and compile and run using the instructions above.
