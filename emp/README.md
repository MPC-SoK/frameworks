# EMP-toolkit

[EMP-toolkit](https://github.com/emp-toolkit) is an extensive set of MPC frameworks based on garbled circuits. The core toolkit includes an oblivious transfer library, a secure types library, and several custom protocol implementations. We have tested the [semi-honest implementation of Yao](https://github.com/emp-toolkit/emp-sh2pc) (`sh2pc`), a [maliciously secure protocol with authenticated garbling](https://github.com/emp-toolkit/emp-ag2pc) (`ag2pc`), and a [maliciously secure, multi-party protocol with authentiated garbling](https://github.com/emp-toolkit/emp-agmpc) (`agmpc`).

Our recommendation: We recommend the semi-honest library (`sh2pc`) for general use. The entire platform is well suited to cryptographic experts looking to implement a novel circuit-based protocol, because it has an effective circuit generation tool and supporting libraries (OT). However, for protocols other than `sh2pc`, we note that the end-to-end flow is not seamless and has limited flexibility and IO support.


## Docker setup

Create a Docker image. This will take a few minutes. You only have to do this
once.
```
$ docker build -t emp .
```
Spin up a Docker container from the image. 
```
$ docker run -it --rm emp
```
Please note that any changes you make in the container are not persistent.

## Architecture

EMP-toolkit is implemented as a C library: there are secure Integer, Bit and Float classes. The default `sh2pc` behavior is a continuous execution model (a single execution stage that does not generate the circuit by default). However, if necessary, you can generate the entire circuit for any backend. Programs written using EMP-toolkit are compiled in one step, using a CMake/Makefile system, which produces an executable.

## Running examples

Run your Docker container. We have implemented examples in the `sh_test` directory, which uses `emp-sh2pc` as an external lib. You should run all this code from the `sh_test` directory. 

Our examples are all run the same way. `<ex>` can be one of `mult3`, `innerprod`, or `xtabs`.

Generate input. EMP-toolkit supports arbitrary size integers, replace the `-n` argument with your desired bitsize. Data will be output in the `data/<ex>` directory.

```
$ python geninput.py -e <ex> -n 32
```

Run the example. The executable takes three arguments and must be run from the `sh_test` directory. 
```
$ ./bin/<ex> <party> <port> <bitsize>
```
You can open two terminals and run each party separately, or run them in the same command:
```
$ ./bin/xtabs 1 12345 32 & ./bin/xtabs 2 12345 32
```


### Generating circuits for other protocol implementations
EMP-toolkit only supports end-to-end execution for the `sh2pc` implementation. However,
you can also use the semi-honest repository to generate circuits compatible with the other
protocol implementations included in the library.

For the `mult3` and `innerprod` examples, we include a runtime option (`-m`) that 
uses the `sh2pc` library to generate a circuit rather than execute a computation. 
This circuit should be compatible with any of the protocol implementations and
will be placed in the `sh_test` directory.
```
$ cd ~/sh_test
$ ./bin/<ex> -m
$ ls 
... <ex>.circuit.txt ...
```

We used EMP-toolkit scripts as a model for our protocol execution script for
`mult3`. We hardcoded input and execute the protocol in the file
`~/ag_test/test/mult3.ag2pc.cpp`. We haven't created a parallel for the other examples.
We compiled this file; run the executable for each party execute the two-party computation. 

```
$ cd ~/ag_test
$ cp ~/sh_test/mult3.circuit.txt .
$ ./bin/mult3.ag2pc 1 12345 & ./bin/mult3.ag2pc 2 12345
connected
connected
48 48 16 527
[...]
```

[In the wiki](https://github.com/MPC-SoK/frameworks/wiki/EMP-toolkit), we explain the ag2pc circuit file format, some restrictions on programs, and modifications required for 3 or more party executions.

## Modifying examples

Source code for these examples is in `sh_test/test/`. If you'd like to experiment with the code yourself, you can build it as follows. We'll assume you've written code in a file called `my_code.cpp` and placed it in the `test` directory.

Add your example to the `cmake` build system and rebuild the system. You only have to do this once.
```
$ echo "add_test (my_code)" >> CMakeLists.txt
$ cmake .
```
Then, make your example using the generated `Makefile`. Do this every time you update your code.
```
$ make my_code
```
You'll now have an executable: `build/bin/my_code`. You can run it using appropriate arguments.

__Changes made in the container are not persistent__. You can keep your container running by not using the `--rm` argument, or run it with a volume to save your changes.

