# CBMC-GC

[CBMC-GC](https://gitlab.com/securityengineering/CBMC-GC-2) is a circuit compiler that produces Boolean circuits from a subset of ANSI-C. 
It is based on CBMC, a bounded model checker that translates a C program into a boolean constraint; CBMC-GC adapts the output of this tool to produce an optimized circuit. 
Optimization can be for minimal size or minimal depth circuts (depending on your use case). 
It supports an arbitrary number of parties.

CBMC-GC includes a tool for running circuits with [ABY](https://github.com/MPC-SoK/frameworks/tree/master/aby), but we weren't able to use it; the CBMC-GC adapter seems to reference a deprecated ABY API. 
CBMC-GC also includes a tool to output circuits in other formats, but we weren't able to successfully execute any of these (not clear whose fault that is).

CBMC-GC was created by Niklas Büscher and others in the security engineering group at TU Darmstadt. 
This work examines v2.

Our recommendation: CBMC-GC uses powerful tools to produce optimized circuits, but we were unable to successfully execute any of the circuits it produced.

## Docker setup

Create a Docker image. This will take 8-10 minutes. You only have to do this once.
```
$ docker build -t cbmcgc .
```
Spin up a Docker container from the image. 
```
$ docker run -it --rm cbmcgc 
```

## Architecture

Compiling the `CBMC-GC` source code produces a set of executables which are kept in `CBMC-GC-2/bin/` (we also copied these to `/usr/bin` for ease of use). This includes:
- `cbmc-gc`: the circuit compiler
- `cmbc`: a compiled executable for the underlying software tool
- `circuit-sim`: an insecure circuit simulator for testing purposes
- `circuit-utils`: another tool whose purpose we don't know


## Running Examples
Each example has a folder in `CBMC-GC-2/examples/`. To compile a circuit,
`cd` into the appropriate directory and run `make`. 

```
$ cd ~/CBMC-GC-2/examples/<program>
$ make
```

We have included four example programs: `mult3`, `innerprod`, `xtabs`, and `xtabs-hash`. 
There are also four examples provided by the library that you can explore.

CBMC-GC is purely a circuit compiler: it does not run an MPC computation. In order to test the correctness of a circuit, you can specify a test set and run it _in the clear_. We've provided a tool to generate sample test files for each of our examples.
```
$ python3 geninput.py -e <program> -t <# trials>
$ cd <program>
$ make run-sim
...
```
This runs a _simulation in the clear_. This is not a secure computation.

To run a secure computation, you must use an outside library. 
CBMC-GC includes support to export circuits to ABY, Bristol, Fairplay's SHDL, or the JustGarble format. 
We have not (yet) explored this functionality.


## Modifying Examples
We've structured our examples as follows:
```
my_example
+--- main.c
+--- Makefile
+--- test.spec
```

The `Makefile` is generic for any example with these names. Using our Makefile,
you can put this directory anywhere (the Makefile included with the CBMC-GC
examples has a hardcoded path to the executables). Run as above to test
your code:

```
$ make
...
$ make run-sim
```

Some language limitations are discussed [in the wiki](https://github.com/mpc-sok/frameworks/wiki/CBMC-GC).
