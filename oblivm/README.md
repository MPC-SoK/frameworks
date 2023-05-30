# ObliVM

[ObliVM](http://oblivm.com/) compiles a custom Java-like language, ObliVM-lang and executes a two-party garbled circuit protocol. It aims to provide a language intuitive to non-experts while implementing domain-specific programming abstractions for improved performance. 

ObliVM was developed by Chang Liu, Xiao Wang, Kartik Nayak, Yan Huang and Elaine Shi, at the University of Maryland and Indiana University. The source code is available [on Github](https://github.com/oblivm/ObliVMLang).

Our recommendation: Although ObliVM implements advanced cryptographic constructs, its usability for practicial applications is significantly limited by minimal documentation and restricted IO functionality. We weren't able to implement our crosstabs example.

## Docker setup

Create a Docker image. This will take a few minutes. You only have to do this once.
```
$ docker build -t oblivm .
```

Spin up a Docker container from the image.
```
$ docker run -it --rm oblivm
```

## Architecture
This container downloads the `ObliVMLang` repository, which runs a garbled circuit backend (see `ObliVMLang/lib/oblivm-flexsc-0.2.jar`).
The source code for this backend is available in the [`ObliVMGC`](https://github.com/oblivm/ObliVMGC) repository, and is based on the [FlexSC](https://github.com/wangxiao1254/FlexSC) project.

## Compiling/Running examples

Examples are located in /root/ObliVMLang/examples. This includes both the examples that are included in the ObliVMLang git repository and the examples we have provided, namely `mult3`, `innerProd` and `xtabs`. 

To compile examples, navigate to `/root/ObliVMLang` in the docker then execute the following:
```
$ ./run-compiler.sh [PORT] examples/<program>/<program>.lcc
```

ObliVM reads input in a binary format- we have provided a script to facilitate this. It can be run as follows:
```
$ python3 ./genInput.py -i examples/<program>/human_input_alice.txt -o examples/<program>/input_alice.txt
$ python3 ./genInput.py -i examples/<program>/human_input_bob.txt -o examples/<program>/input_bob.txt
```

Following this, the examples can be run as follows:
```
$ ./runtogether.sh examples/<program>/input_alice.txt examples/<program>/input_bob.txt
```

