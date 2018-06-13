Wysteria was developed by Aseem Rastogi, Matthew Hammer, and Michael Hicks at       
the University of Maryland.

## Docker setup

Create a Docker image. This will take a few minutes. You only have to do this once.
```
$ docker build -t wysteria .
```
Spin up a Docker container from the image.
```
$ docker run -it --rm wysteria
```
Please note that any changes you make in the container are not persistent.

## Architecture
A Wysteria program is completely self-contained; both secure and insecure code
is written in the Wysteria language. A program is run in two steps:

1. Set up servers for each party. These servers are independent of the program being run, except that they must know how many parties are involved. The server binary is called `mpc.exe`.

2. Run a computation. This requires a program described in a `.wy` file. The program's secure blocks are compiled into circuits and computed. The executable that compiles secure blocks and runs the mixed-mode computation is called `wysteria`.

We've installed both these binaries in `/usr/bin`. 

The files `addresses.txt` and `princs.txt` must also be in the directory. They contain public information about the parties involved in the computation.

## Running examples

We were only able to write one of our sample programs, `mult3`. Participant input values are hardcoded. We've included several other examples in `~/source/examples/other`, including a partial, broken crosstabs implementation and an alternate implementation of the millionaire's problem.

We provide two scripts to aid in running a computation.
                                                                                    
The script `runtest.sh` will run an example starting separate screen tabs for three servers and clients. By default, this runs the millionaire's problem, but you can pass a different example as a parameter.
```
$ ./runtest.sh mult3.wy
Running test examples/mult3.wy
$ screen -r wysteria

# wysteria --i-am \!Charlie --gmw-port 9002 examples/mill.wy
typing the program under top
done with type checking the program
!Charlie output: [!Charlie:10]
# 
```
Press `ctrl-D` to cycle through the screens and see the output for each party and `ctrl-AD` to close all screens.

The script `cleanup.sh` will kill the running screen session and delete the numerous temp files created by the MPC computation.

## Modifying examples

Source code for these examples is in `wysteria/src/examples`. After editing an example, you can run the computation as above (via `./runtest.sh`) or you can try running a single Wysteria participant, which will type-check the program. Once it type-checks, you should run via `./runtest.sh`.
```
$ wysteria --i-am \!Alice --gmw-port 9000 examples/mytest.wy
typing the program under top
done with type checking the program
Fatal error: exception Unix.Unix_error(Unix.ECONNREFUSED, "connect", "")
```
