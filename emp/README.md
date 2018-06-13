# EMP-toolkit

EMP-toolkit source is available [on github](https://github.com/emp-toolkit).


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

EMP-toolkit is built like a library: there are secure Integer, Bit and Float classes. The runtime is flexible but by default, the entire circuit is not generated at once (for sh2pc). However, if necessary, you can generate the entire circuit for any backend. Programs written using EMP-toolkit are compiled in one step, using a CMake/Makefile system, which produces an executable.

## Running examples

Run your Docker container. We have implemented examples in the `emp-sh2pc` directory, which runs a semi-honest 2-party computations. You should run all this code from the `emp-sh2pc` directory. 

Our examples are all run the same way. `<ex>` can be one of `mult3`, `innerprod`, or `xtabs`.

Generate input. EMP-toolkit supports arbitrary size integers, replace the `-n` argument with your desired bitsize. Data will be output in the `data/<ex>` directory.

```
$ python geninput.py -e <ex> -n 32
```

Run the example. The executable takes three arguments and must be run from the `build` directory. 
```
$ ./bin/<ex> <party> <port> <bitsize>
```
You can open two terminals and run each party separately, or run them in the same command:
```
$ ./bin/xtabs 1 12345 32 & ./bin/xtabs 2 12345 32
```

This container also includes the `emp-sh2pc` examples produced by the author of the repository. These take different arguments than ours; please see the source code for details. 

## Modifying examples

Source code for these examples is in `emp-sh2pc/test/`. If you'd like to experiment with the code yourself, you can build it as follows. We'll assume you've written code in a file called `my_code.cpp` and placed it in the `test` directory.

Add your example to the `cmake` build system and rebuild the system. You only have to do this once.
```
$ echo "add_test (my_code)" >> CMakeLists.txt
$ cd build
$ cmake ..
```
Then, make your example using the generated `Makefile`. Do this every time you update your code.
```
$ make my_code
```
You'll now have an executable: `build/bin/my_code`. You can run it using appropriate arguments.

__Changes made in the container are not persistent__. You can keep your container running by not using the `--rm` argument, or run it with a volume to save your changes.

