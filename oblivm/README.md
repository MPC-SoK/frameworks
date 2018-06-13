## ObliVM

ObliVM was developed by Chang Liu, Xiao Wang, Kartik Nayak, Yan Huang and Elaine Shi, at the University of Maryland and Indiana University. The source-code is available at https://github.com/oblivm/ObliVMLang.

## Docker setup

Create a Docker image. This will take a few minutes. You only have to do this once.
```
$ docker build -t oblivm .
```

Spin up a Docker container from the image.
```
$ docker run -it --rm oblivm
```

## Compiling/Running examples

Examples are located in /root/ObliVMLang/examples. This includes both the examples that are included in the ObliVMLang git repository and the examples we have provided, namely `mult3`, `innerProd` and `xtabs`. 

To compile examples, navigate to `/root/ObliVMLang` in the docker then execute the following:
```
$ ./run-compiler.sh [PORT] examples/<program>/<program>.lcc
```

ObliVM reads input in a binary format- we have provided a script to facilitate this. It can be run as follows:
```
$ python ./genInput.py -i examples/<program>/human_input_alice.txt -o examples/<program>/input_alice.txt
$ python ./genInput.py -i examples/<program>/human_input_bob.txt -o examples/<program>/input_bob.txt
```

Following this, the examples can be run as follows:
```
$ ./runtogether.sh examples/<program>/input_alice.txt examples/<program>/input_bob.txt
```

