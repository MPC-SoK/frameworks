# ABY

ABY is a mixed-protocol two-party computation framework implemented as a C++ library. It aims to give developers fine-grained control over computation efficiency bby providing a mechanism for mixing protocols. 
ABY switches between three protocols: a GMW-based __A__rithmetic protocol that uses an additive sharing scheme with multiplicative triplets; a __B__oolean-circuit based implementation fo the original GMW protocol using an XOR-baseds ecret sharing scheme; and an optimized version of __Y__ao's garbled circuit protocol, also over a Boolean circuit.

ABY was developed by Daniel Demmler, Thomas Schneider and Michael Zohner in the [ENCRYPTO group](https://www.encrypto.informatik.tu-darmstadt.de/encrypto/) at TU Darmstadt.

Our recommendation: ABY provides a powerful low-level crytographic interface that gives the developer significant control over performance. We recommend ABY for users who are familiara with MPC protocols, their relative tradeoffs, and the circuit model of computation.

## Docker setup

Create a Docker image. This will take a few minutes. You only have to do this once.
```
$ docker build -t aby .
```
Spin up a Docker container from the image.
```
$ docker run -it --rm aby 
```
Please note that any changes you make in the container are not persistent.

## Architecture

ABY is roughly architected as a C++ library. It defines several classes that
implement the MPC protocol. It is written in an object-oriented style. 
Secure data is limited to unsigned C integer types (no arbitrary-length integers or an explicit Boolen type, though it does support 1-bit integers). Support for floating (fixed?)-point operations are under active development. ABY can tore secure data in a C struct and supports both C++ arrays and SIMD constructiosn for efficient parallelization, though retrieving individual elements out of a SIMD share is not well-supported.

Most examples have a similar format: 
- `<ex>_test.cpp` file reads input and sets parameters
- `common/<ex>.cpp` file creates objects, defines circuit, and executes the
  computation

The circuit itself is defined at a relatively low level: `share` objects are
manipulated by `gate` operations in a `Circuit`. 

## Running examples
To run our examples, you'll need to generate input. We've written input
generation scripts for `mult3`. It will tell you what the expected result is.
Data is stored in the `ABY/src/examples/<ex>/data` directory.
```
$ python ~/ABY/src/examples/geninput.py -e <ex>
Expected result: 621
```

Executables are in the `ABY/build/bin/` directory. 
Two parties must run each example. 
You can do it in one line as here, or in two separate terminals.
```
$ cd ~/ABY/build
$ ./bin/<ex>_test -r 0 & ./bin/<ex>_test -r 1
...
Result: 621
```

Notes: The `innerproduct` example was a sample program included with the ABY distribution and was not written by us. 
We modified it slightly to read input from a file. Our version is called
`innerprod`.

We now have a crosstabs example, but it is a little buggy (fails when the
number of bins is larger than the number of elements).

## Modifying examples
Create a directory in `ABY/src/examples` for your example. Copy the
`CMakeLists.txt` from another example directory and change the executable and file names appropriately. 

To build your example, add it to `ABY/src/examples/CMakeLists.txt` and re-run `make` in the `ABY/build` directory.

For more details on the ABY libraries, we recommend the helpful 
[Developer Guide](https://www.informatik.tu-darmstadt.de/media/encrypto/encrypto_code/abydevguide.pdf). 
While this document is minorly out-of-date, it contains much useful information
about the architecture and capabilities of the framework.
