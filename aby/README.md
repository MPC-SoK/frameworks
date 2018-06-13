ABY was developed by Daniel Demmler, Thomas Schneider and Michael Zohner in the [ENCRYPTO group](https://www.encrypto.informatik.tu-darmstadt.de/encrypto/) at TU Darmstadt.

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

Most examples have a similar format: 
- `<ex>_test.cpp` file reads input and sets parameters
- `common/<ex>.cpp` file creates objects, defines circuit, and executes the
  computation

The circuit itself is defined at a relatively low level: `share` objects are
manipulated by `gate` operations in a `Circuit`. 

## Running examples
Example executables are in the `ABY/bin/` directory. Two parties must run each
example. You can do it in one line as here, or in two separate terminals.
```
$ cd ABY
$ ./bin/<ex>.exe -r 0 & ./bin/<ex>.exe -r 1
```

Inputs are randomly generated in the code.

Note: The `innerproduct` example was a sample program included with the ABY distribution and was not written by us. We don't have a working crosstabs example at this time. 

## Modifying examples
Create a directory in `ABY/src/examples` for your example. Copy the `Example_Makefile` or create a symlink to it.

To make, simplyl re-run `make` in the `ABY` directory (there is likely a way to
compile a single program but we have yet to find it).

For more details on the ABY libraries, we recommend the helpful, though
incomplete, [Developer
Guide](https://www.encrypto.informatik.tu-darmstadt.de/fileadmin/user_upload/Group_ENCRYPTO/code/ABY/devguide.pdf).
