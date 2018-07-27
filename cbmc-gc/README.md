CBMC-GC is a circuit compiler produced by Niklas Büscher and others in the security engineering group at TU Darmstadt. This work examines v2.

## Docker setup

Create a Docker image. This will take a few minutes. You only have to do this once.
```
$ docker build -t cbmcgc .
```
Spin up a Docker container from the image. 
```
$ docker run -it --rm cbmcgc 
```

## Architecture

Compiling the `CBMC-GC` source code produces a set of executables which are kept in `cbmc-gc/bin/` (we also copied these to `/usr/bin` for ease of use). This includes:
- `cbmc-gc`: the circuit compiler
- `cmbc`: a compiled executable for the underlying software tool
- `circuit-sim`: an insecure circuit simulator for testing purposes
- `circuit-utils`: another tool whose purpose we don't know


## Running Examples
Each example has a folder in `cbmc-gc/examples/`. To compile a circuit,
`cd` into the appropriate directory and run `make`. 

```
$ cd ~/cbmc-gc/examples/<program>
$ make
```

We have included four example programs: `mult3`, `innerprod`, `xtabs`, and
`xtabs-hash`. There are also four examples provided by the library that you can
explore.

CBMC-GC is purely a circuit compiler: it does not run an MPC computation. In order to test the correctness of a circuit, you can specify a test set and run it _in the clear_. We've provided a tool to generate sample test files for each of our examples.
```
$ python geninput.py -e <program> -t <# trials>
$ cd <program>
$ make run-sim
...
```
This runs a _simulation in the clear_. This is not a secure computation.

To run a secure computation, you must use an outside library. CBMC-GC includes
support to export circuits to ABY, Bristol, Fairplay's SHDL, or the JustGarble format. We have not (yet) explored this functionality.


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
$ make run_sim
```

Some language limitations are discussed [in the wiki](https://github.com/bhemen/MPC_compilers/wiki/CBMC-GC-v2).


