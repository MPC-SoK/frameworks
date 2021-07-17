# MOTION

[MOTION](https://github.com/encryptogroup/MOTION) is a framework for secure multi-party computation (MPC) implemented as a C++ library. 
It currently implements three MPC protocols for two or more parties: arithmetic and Boolean GMW as well as the BMR protocol, 
which is the multi-party version of the constant-round Yao's garbled circuit protocol.
All three protocols provide security against all but one passively corrupted parties, i.e., parties are supposed to follow the protocol but try to learn additional information from what they observe in the protocol.
MOTION allows to convert between all three protocols and provides both high-level interfaces such as secure integers as well as low-level APIs 
for oblivious transfer and fine-grained control over MOTION's internal mechanisms.
Two design aspects, asynchronous circuit evaluation and serialized communication, enable very flexible use of protocols and primitives, e.g.,
it is possible to use multiple different flavors of oblivious transfer and various MPC protocols all in parallel, which will wait for particular events to happen, 
without any need of manual synchronization. 

MOTION was developed by Lennart Braun (Aarhus University), Daniel Demmler (Universität Hamburg), 
Thomas Schneider and Oleksandr Tkachenko ([ENCRYPTO group](https://encrypto.de), TU Darmstadt).

Our recommendation: MOTION provides a powerful low-level crytographic interface that gives the developer significant control over performance. 
We recommend MOTION for users who are familiar with MPC protocols, their relative tradeoffs, and the circuit model of computation.
Furthermore, MOTION is well-suited for (non-invasive) prototyping and mixing of (new) protocols and conversions due to its asynchronous design. 
More details can be found in [our paper](https://ia.cr/2020/1137).

## Docker setup

Create a Docker image. This will take a few minutes. You only have to do this once.
```
$ docker build -t motion .
```
Spin up a Docker container from the image.
```
$ docker run -it --rm motion 
```
Please note that any changes you make in the container are not persistent.

Note: a Dockerfile as well as the provided examples are also contained in the [original MOTION repo](https://encrypto.de/code/MOTION) and very similar instructions can be used 
to build a Docker container from the original repo directly. See the [MOTION README](https://github.com/encryptogroup/MOTION/blob/master/README.md) for more details. 

## Architecture

MOTION is designed as a C++ library. It defines several classes that
implement the MPC protocols. It is written in an object-oriented way. 
Secure data is currently limited to unsigned C integer types.
Support for floating and fixed-point operations is under active development. 
MOTION supports SIMD operations for efficient parallelization.
MOTION is significantly more memory and running time efficient when using SIMD 
and needs slightly less communication due to better packing of messages, so we strongly encourage to use it.

### Format of examples

Most examples have a similar format: 
- `<example>_main.cpp` read inputs and set parameters
- `common/<example>.cpp` create MPC objects, define circuit, and execute the
  computation

### Circuit representation 

There is no explicit circuit object in MOTION.
The circuit is defined as a collection of `Shares` (containing primitive `Wire` objects) that are manipulated by `Gate` objects.
Each `Wire` contains `number_of_simd` data values, e.g., 10 integer values in arithmetic GMW, and computing a sum of two such values, `x` and `y`, would result into
10 additions, one for each `x[i]`, `y[i]`.
There is also currently no notion of circuit layers in MOTION.
In a nutshell, all `Gates` have `Shares` as both inputs and outputs.
The `Gates` wait for their input `Shares` to become "ready" to start their own evaluation.
After their evaluation, `Gates` set their output wires and mark them "ready" which gives the green light for the waiting gates to start their evaluation.
This procedure is done completely asynchronously using stackfull coroutines, namely `Boost.Fibers`. 

### Communication serialization

The communication in MOTION is serialized completely using the efficient `flatbuffers` serialization library.

### Benchmarks

We provide `Statistics` classes for analyzing communication and computation costs.
They have APIs to convert the collected statistics to either a human-readable format, e.g.,
to print them into the terminal, or to a machine-readable format, namely JSON, using `Boost.JSON`. 

## Running examples
We provide all three examples in a [tutorial directory in MOTION](https://github.com/encryptogroup/MOTION/blob/master/src/examples/tutorial), 
so they are not included here.
To run our examples, you'll need inputs to the circuit. We've written an input
generation script for `mult3` and other tutorial examples that allows to quickly test the examples. 
It will tell you what the expected result is.
```
$ python ~/MOTION/src/examples/tutorial/geninput.py -e <example>
Expected result: 621
```

Executables are located in the `MOTION/<build>/bin/` directory. 
In general, at least two parties must run each example.
You will find more details regarding the settings enabled in particular 
tutorial examples in the [tutorial README](https://github.com/encryptogroup/MOTION/blob/master/src/examples/tutorial/README.md). 
You can do it in one line as here, or in two separate terminals.
```
$ cd ~/MOTION/<build>/bin
$ my_parties="0,<ip0>,<port0> 1,<ip1>,<port1>"
$ ./<example> --my-id 0 --parties $my_parties & 
$ ./<example> --my-id 1 --parties $my_parties
...
Result: 621
```
To run this locally, replace `<ip0>` and `<ip1>` with 127.0.0.1.

For settings with more than two parties, the configurations may get quite complicated and inconvenient to use from the command line.
For this case, it is possible to store one or more configurations in files and input them via the command line.
The arguments in config files have the format `my-id=0`, one per line.
Command line inputs are preferred over the config file in case of a conflict.

For more info on command line arguments, enter `<example>_main --help`.

## Modifying examples
The fastest way is to copy/modify the `example_template` in `MOTION/src/examples`. 
Change the target name `example_template` to `<your_example>` in `CMakeLists.txt` and rename the source files correspondingly. 
If you only want to play around with the framework without real inputs and evaluate some circuit, 
you would only need to put your function in `example_template.cpp:EvaluateProtocol()`, 
similarly to the other provided examples.
To pass real inputs to your circuit, we recommend to use `Boost.ProgramOptions` in the `<example>_main.cpp`,
which allows to either pass inputs directly or pass a filename that contains the inputs. 

To build your example, add it to `MOTION/src/examples/CMakeLists.txt` and re-run `make` in the `MOTION/<build>` directory.

For an overview of the classes and their connections in MOTION, check out the [online doxygen documentation](https://motion-documentation.github.io).
Also, we are actively working on a developer guide that will contain more implementation guidelines and details about MOTION.
It will soon be available [here](https://motion-documentation.github.io/motiondevguide.pdf).

