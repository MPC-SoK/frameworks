# SCALE-MAMBA

SCALE-MAMBA includes a custom compiler and MPC execution engine that implements a maliciously secure hybrid protocol. It supersedes the SPDZ framework. MAMBA is a Python-like language that compiles to a documented bytecode representation. SCALE implements a two-phase protocol, first offloading public-key operatiosn to a offline, function-independent pre-processing stage, then executing an optiized hybrid protocol.

SCALE-MAMBA is developed by a team at [KU Leuven](https://homes.esat.kuleuven.be/~nsmart/SCALE/).

Our recommendation: SCALE-MAMBA is an actively maintained, highly flexible, extensively documented framework. It supports an arbitrary number of parties and has strong security guarantees and we recommend it for most use cases. Our only caveat is that it may consume significant computing resources.

## Docker Setup
Create a Docker image. This will take a few minutes. You only have to do this
once.
```
$ docker build -t scalemamba .
```
Spin up a Docker container from the image. 
```
$ docker run -it --rm scalemamba 
```
Please note that any changes you make in the container are not persistent.

## Architecture
SCALE-MAMBA executes a two-phase hybrid protocol. 
The preprocessing and execution phases run back-to-back with a single executable.
Users need to configure the parameters for the computation, compile the program
with those parameters, and then run each computation party.

## Running Examples

### configuration
First step is to set up parameters for the computation, including network
participants and secret-sharing setup. The framework provides a setup script to
interactively produce config files.

In the `SCALE-MAMBA` directory, run the `Setup.x` script to set up parameters. Our parameter recommendations follow.
```
$ cd ~/SCALE-MAMBA
$ ./Setup.x
What do you want to set up?
    1) Certs
    2) Secret Sharing
    3) Conversion circuit for LSSS<->GC computations
    4) All three
Enter a number (1-4)..
```
Enter `4`.

`Certs`: SCALE-MAMBA requires certificate infrastructure. We've built the necessary certs for up to 4 players (see `SCALE-MAMBA/Cert-Store`).
The root certificate is called `RootCA` and the individual player certificate names are `Player<i>.crt`. We run examples using localhost (`127.0.0.1`) for the IP address. We recommend running the computation with real offline and sacrifice data (better tested).
Certificate config output is in `Data/NetworkingData.txt`.

`Secret Sharing`: There are several options for sharing schemes. We recommend Shamir sharing. For our examples, you can choose a modulus that's at least 31 bits (e.g 2147483999). The Full Threshold option generates keys insecurely. For full details about these options, see their documentation.
Secret sharing config output is in `Data/SharingData.txt`.

`Conversion circuit`: For our small prime examples, you don't need to do this manually. See their documentation for more details about this option.

### compilition and execution
Compile the directory containing the program you wish to run. We
implemented three examples: `mult3`, `innerprod` and `xtabs`. Data for our examples is hard-coded.
```
$ ./compile.py Programs/<ex>
```

Then, run each computation party. 
```
$ ./Player.x <id> Programs/<ex>
```

To run our examples, we ran all players together locally:
```
$ ./Player.x 0 Programs/innerprod & ./Player.x 1 Programs.innerprod
```

## Modifying Examples
Secure code is stored in `Programs/<ex>/<ex>.mpc`. Add new programs by creating
a directory for them. Note that if you change the networking or sharing setup
(ie by adding another player or changing the modulus size), you'll need to
recompile the program.

Our examples don't have custom input--right now, input is hard coded in the examples. Feel free to push an IO scheme that reads from files. We'll get around to it eventually.

Our examples are compatible with the repository as of March 2019, but we note that the project is under active development.
