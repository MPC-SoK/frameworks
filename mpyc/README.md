# MPyC

[MPyC](https://www.win.tue.nl/~berry/mpyc/) is a python package for MPC. It runs a semi-honest, mostly information-theoretically secure protocol. Source code is available [on Github](https://github.com/lschoe/mpyc).

Our recommendation: We recommend MPyC for general use. It is extremely easy to install and use with minimal Python experience. The library is straightforward and effective. (Further notes [in the wiki](https://github.com/MPC-SoK/frameworks/wiki/MPyC).)


## Docker setup

MPyC is easy to install on any machine with Python3 enabled. Feel free to simply run the last 2 commands in `install.sh` and run these examples locally.

Otherwise, create a Docker image. You only have to do this once.
```
$ docker build -t mpyc .
```
Spin up a Docker container from the image. 
```
$ docker run -it --rm mpyc 
```
Please note that any changes you make in the container are not persistent.

## Architecture

MPyC is an asynchronous Python library. The `mpc` module provides a basic MPC session (e.g. sets up communication, handles scheduling). It has support for integer and fixed point classes as well as some special-purpose secure lists. 

## Running examples

In the Docker container, our examples are stored in `~/source/`. 
They are all run the same way. In the following commands, replace `<ex>` with one of of `mult3`, `innerprod`, or `xtabs`.
Right now, we use random input and don't compute an ``expected'' value.

To run an example with `N` parties, use:
```
$ python <ex>.py -M N
```
You can also skip the `-M` argument to run locally.

Many more code examples are available in the MPyC repository. Run:
```
$ git clone https://github.com/lschoe/mpyc.git
$ cd mpyc/demos
```
