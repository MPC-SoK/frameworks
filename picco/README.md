PICCO was developed by Yihua Zhang, Aaron Steele, and Marina Blanton at the
University of Notre Dame.

## Docker setup
Create a Docker image. This will take a moment. You only have to do this once.
```
$ docker build -t picco .
```

Spin up a Docker container from the image.
```
$ docker run -it --rm picco
```

## Architecture 


## Running examples
We've stored our examples in `/root/tests`. To run an example, go to the
appropriate directory. 

```
$ cd /root/tests/<ex>
$ ls
makefile    mult3.c mult3.gen.cpp   secure_servers  smc-compute smc_config  util_config 
$ ls secure_servers
keys  mult3  run_config  share1  share2  share3
```

We have done the following steps (see `install.sh` for details)
1. Converted PICCO code (`<ex>.c`) to native C++ (`<ex>.gen.cpp`)
2. Produced secure executable (`secure_servers/<ex>`)
3. Generated key pairs for three servers (`secure_servers/keys/`)

First, you must generate input and shares for the correct number of servers
(we use 3 computation servers, 1-2 input parties, and 1 output party in our
examples. These parameters are set in the `smc_config` file). 
The PICCO team describes the correct input file format in their [manual](https://github.com/PICCO-Team/picco/blob/master/picco-manual.pdf).
```
$ picco-utility -I <input ID> <input file> util_config secure_servers/share
```

To run the computation, enter the `secure_servers` directory and start the servers. If you get an error (`ERROR, on binding`, `Error connecting 111 - Connection refused `, `ERROR, connecting to node: Connection refused`) or if the program hangs, kill the processes and try again. Note that order matters here: the highest-numbered server must be started first. 
```
$ cd secure_servers
$ ./mult3 3 run_config keys/private3.pem 1 1 share3 output &
$ ./mult3 2 run_config keys/private2.pem 1 1 share2 output &
$ ./mult3 1 run_config keys/private1.pem 1 1 share1 output &
```

Then, share a secure seed to run the computation. Technically you have to do this for each server. In this setup, all servers are running on the same host so you only have to run it once.

```
$ picco-seed run_config ../util_config
```

Finally, reconstruct the secret-shared outputs for each output party (in our examples, there is only one)
```
$ picco-utility -O 1 output ../util_config result
```

The result of the computation is in the file `result`.


## Modifying examples
We've hardcoded a configuration for our sample programs, but PICCO is configurable. They include extensive documentation on configuring, compiling, and running examples in their [manual](https://github.com/PICCO-Team/picco/blob/master/picco-manual.pdf) 
