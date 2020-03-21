# Obliv-C

[Obliv-C](https://oblivc.org/) is an extension of C that executes a 2-party garbled circuit protocol. The main language addition is an _obliv_ qualifier, applied to C types and constructs. Typing rules enforce that `obliv` types remain secret unless explicitly revealed. 
Code within oblivious functions and conditionals cannot modify public data, except within a qualified _~obliv_ block, which executes in the clear. These rules allow programmers to develop modular libraries and efficient functionalities.

Our recommendation: Obliv-C is a robust garbled circut framework. We recommend it for general use, particularly to experts who wish to implement and optimize complex libraries such as ORAM.
We note that Obliv-C has been used for multiple practical applications.
Source code is [on Github](https://github.com/samee/obliv-c).

## Docker setup

Create a Docker image. This will take a few minutes. You only have to do 
this once.
```
$ docker build -t obliv-c .
```

Spin up a Docker container from the image.
```
$ docker run -it --rm obliv-c
```

Please note that any changes you make in the container are not persistent. 

## Architecture
Obliv-C is an extension of C. The `oblivcc` compiler first converts Obliv-C code
to native C, then combines it with any supporting C code into a single
executable. Obliv-C code is contained in a file with the `.oc` extension, and
supporting code can be either in the `.oc` file or in a `.c` file.

Circuits are generated on the fly (e.g. only in memory). This allows circuit sizes to depend on values not known during compilation.
 

## Running examples

Navigate to the directory of the program you would like to run, where 
<ex> is the name of the program. Our examples are at `/root/<ex>`.
```
$ cd <ex>
$ make
```

This should produce an executable `a.out`. This is run separately on each server:
```
$ ./a.out <port> <IP> <input file> 
```

We ran local tests as follows:

```
$ ./a.out 1234 -- <inputFile1> & 
$ ./a.out 1234 localhost <inputFile2>
```

Obliv-C also includes automated testing functions. 
```
$ cd /root/obliv-c/test
$ ./test2.sh ../naive
```

## Modifying examples
Modifying examples is straightforward. Oblivious keywords must be in the `.oc`
file. Rerun `make` to rebuild. The `Makefiles` included in our examples are
generic enough to be used for other examples; copy to your directory and change
the `testName` variable.


