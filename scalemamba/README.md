## SCALE-MAMBA

## Docker Setup
Create a Docker image. This will take a few minutes. You only have to do this
once.
```
$ docker build -t mamba .
```
Spin up a Docker container from the image. 
```
$ docker run -it --rm mamba 
```
Please note that any changes you make in the container are not persistent.

## Architecture
SCALE-MAMBA executes a two-phase GMW-based protocol. 
The phases run back-to-back with a single executable.
Users need to configure the parameters for the computation, compile the program
with those parameters, and then run each computation party.

## Running Examples

First step is to set up parameters for the computation, including network
participants and secret-sharing setup. The framework provides a setup script to
interactively produce the appropriate config files.

We've set up the necessary certicicate infrastructure in `SCALE-MAMBA/Cert-Store`. We ran our examples using localhost (127.0.0.1) for the IP address and `Player<i>.crt`, where `<i>` is a number 0-3. 

For secret sharing setup, we used Full Threshold sharing (option 1), with
varying length modulus. Try 32 for initial testing purposes.
```
$ cd ~/SCALE-MAMBA
$ ./Setup.x
```
The setup script produces two configuration files: `Data/NetworkingData.txt` and
`Data/SharingData.txt`.

Then, compile the directory containing the program you wish to run. We
implemented three examples: `mult3`, `innerprod` and `xtabs`.
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


