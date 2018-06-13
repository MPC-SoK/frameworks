## SPDZ

As of May 2018, SPDZ is superseded by the SCALE-MAMBA system. We leave this here
for posterity.
SPDZ source-code is available at https://github.com/bristolcrypto/SPDZ-2.

## Docker setup

Create a Docker image. This will take a few minutes. You only have to do this
once.
```
$ docker build -t spdz .
```

Spin up a Docker container from the image.
```
$ docker run -it --rm spdz
```

## Generating pre-processing data

SPDZ has two parts:
- A pre-processing phase which generates shared randomness between the different parties. 
    This does not depend on the function to be computed and once pre-processing data is generated
    it can be used by many different parties until it is used up. 
    Pre-processing is VERY RESOURCE INTENSIVE. **It needs about 3GB RAM per party.**
- An online phase which uses pre-processing data to evaluate any function. This is quite fast.

Once in the docker, run the pre-processing phase for, say, 3 parties by executing the following:
```
$ cd SPDZ-2
$ ./spdz2-offline.x -p 0 -N 3 &
$ ./spdz2-offline.x -p 1 -N 3 &
$ ./spdz2-offline.x -p 2 -N 3
```

This will run for a while to generate the pre-processing data. After the program outputs "Inv. 9500 out of 9600" wait a further 5 minutes. Then kill the process and the other spdz2-offline.x background processes. (If you wait longer than 5 minutes before killing them, it will generate more shared randomness, but for most applications 5 minutes worth should suffice.)

You should be able to see the pre-processing data files in SPDZ-2/Player-Data.

See ./spdz2-offline.cpp for other cmd line options, such as how to specify IP addresses to run on the parties on different machines. The protocol is convertly secure; spdz2-offline.x also has a cmd line option for specifying the covert security parameter.

## Running examples

First, compile the example source. We provide three examples (mult3, innerprod,
xtabs).
```
$ cd SPDZ-2
$ ./compile.py -p 128 <ex>
```

Generate input for each party and transform it into the SPDZ binary format.
You'll need to fill in `<ex>.P<x>` with correctly-formatted data for each party
`<x>`.
```
$ cd SPDZ-2
$ mkdir Programs/InputData
$ touch Programs/InputData/<ex>.P<x> 
$ ./gen_input_fp.x -N 3 -i ./Programs/InputData/<ex>.P<x> -o ./Player-Data/Private-Input-<x>
```

For example, to run mult3 with inputs 14, 12, and 8, we'd do the following:
```
$ cd SPDZ-2
$ mkdir Programs/InputData
$ printf "1\n14\n" > Programs/InputData/mult3.P0 
$ printf "1\n12\n" > Programs/InputData/mult3.P1 
$ printf "1\n8\n" > Programs/InputData/mult3.P2 
$ ./gen_input_fp.x -N 3 -i ./Programs/InputData/mult3.P0 -o ./Player-Data/Private-Input-0
$ ./gen_input_fp.x -N 3 -i ./Programs/InputData/mult3.P1 -o ./Player-Data/Private-Input-1
$ ./gen_input_fp.x -N 3 -i ./Programs/InputData/mult3.P2 -o ./Player-Data/Private-Input-2
```

Execute the server and each player. The output transcript will include the
computed solution.
``` 
$ ./Server.x <# players> <port #> 
$ ./Player-Online.x <player ID> <ex>
```

For example, the output from the following will include `Mult3 prod = 1344`. 
```
$ ./Server.x 3 5000 &
$ ./Player-Online.x 0 mult3 & ./Player-Online.x 1 mult3 & ./Player-Online.x 2 mult3
```

## Modifying examples

Other examples exist in Programs/Source (some of these come with SPDZ, others we wrote). These can be compiled and run in the same way as shown above, though note that the number of parties is different in different examples. You can learn the SPDZ syntax by reading and modifying these examples, as well as by reading SPDZ-2/tutorial.md.
