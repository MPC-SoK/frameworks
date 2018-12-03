## SCALE-MAMBA

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
SCALE-MAMBA executes a two-phase GMW-based protocol. 
The phases run back-to-back with a single executable.
Users need to configure the parameters for the computation, compile the program
with those parameters, and then run each computation party.

## Running Examples

First step is to set up parameters for the computation, including network
participants and secret-sharing setup. The framework provides a setup script to
interactively produce the appropriate config files.

Run the following commands. You will need to create BOTH config files (Secret
Sharing and Cert). 
```
$ cd ~/SCALE-MAMBA
$ ./Setup.x
What do you want to set up?
    1) Certs
    2) Secret Sharing
    3) Both
Enter a number (1-3)..
```
Enter `3`.

We've placed all necessary certificate infrastructure in `SCALE-MAMBA/Cert-Store`. The root certificate is called `RootCA` and the individual player certificate names are `Player<i>.crt`. We ran examples using localhost (127.0.0.1) for the IP address. You can test with real or fake offline and sacrifice phases.

For secret sharing setup, we used Full Threshold sharing (option 1), with
varying length modulus. Try 32 for initial testing purposes. _IMPORTANT_: Full
threshold sharing insecurely generates keys! For secure key generation, use a
different sharing scheme.

This setup script produces two configuration files: `Data/NetworkingData.txt` and
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

Our examples are compatible with the repository as of July 2018, but we note that the project is under active development.
