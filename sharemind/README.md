
Sharemind was developed by Cybernetica AS.

## Docker Setup

Create a Docker image. This will take around 20 minutes. You only have to do this once.
```
$ docker build -t sharemind .
```
Spin up a Docker container from the image.
```
$ docker run -it --rm sharemind
```

## Architecture
This container demonstrates the open-source emulator for the Sharemind MPC platform. It runs SecreC code, which is Sharemind's language for defining secure computations, but _does not perform a secure computation_. 

In the repository, we include supporting client code for running a secure computation with the full Sharemind MPC platform, which we had access to via an academic license. This code will not be used in the following instructions, it's here for illustrative purposes and so that those who license the platform can test these examples. Note that this code is compatible with the 2018.03 release and may be incompatible with later versions.

On the full platform, the code is compiled in two parts: the SecreC function definition is compiled and copied to each computation server, and the supporting code, which we wrote in C, is compiled into an executable. A single "input" party runs the executable, which sends input to three computation servers. The servers execute the computation and return the result to the original party. It is possible to write computations with multiple input parties using a database structure on the servers, but we didn't implement this.

In the emulator, only the SecreC function definition is used. Users must compile
this to SecreC byte code (`.sb`), then run the emulator.

## Running Examples
We have three examples (`mult3`,`scalar_product`, and `xtabs`), which are in `source/`.  Each directory is organized as as follows:

```
+ secrec
| - <ex>.sc
+ src
| - <ex>.cpp
- CMakeLists.txt
- README.md
- config.local
```

The only file needed for the emulator is `secrec/<ex>.sc`. The `README.md` explains how to run the example in VM provided with the academic license.

To run an example, navigate to `~/source/<ex>/secrec` and compile the source using the secrec compiler (and explicitly linking to the standard library functions).
```
$ scc -o <ex>.sb -I/root/build-sdk/secrec-stdlib <ex>.sc 
```

The emulator requires all inputs to be passed as arguments. Generally speaking, this will look something like the following:
```
$ sharemind-emulator <ex>.sb --str=<arg_name> --str=pd_shared3p --str=<type> --size=<datatype size * array len> --<type>=<value> ...
```
Repeat `<type>=<value>` for each value in an array, and the entire string for each argument.

For example, running the `scalar_prod` example with party A input `[1,2]` and party B input `[3,4]` would look like this: 
```
$ sharemind-emulator innerprod.sb --str=a --str=pd_shared3p --str=uint64 --size=16 --uint64=1 --uint64=2 --str=b --str=pd_shared3p --str=uint64 --size=16 --uint64=3 --uint64=4
```

The result of the program is returned as a byte array. To see the value in plain text, add a `print(declassify(<arg>))` statement to the code.


## Modifying Examples
Sharemind produced [documentation for the 2018 Q1
release](https://docs.sharemind.cyber.ee/) which includes high-level
architectural descriptions and other useful diagrams.
Extensive low-level [documentation for the SecreC language](https://sharemind-sdk.github.io/stdlib/reference/index.html) is available online. 


