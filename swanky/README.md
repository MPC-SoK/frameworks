# SWANKY

A set of rust libraries that implements 

for secure multi-party computation.

Consisting of:

1. [Fancy-Garbling](https://github.com/GaloisInc/swanky/tree/master/popsicle)
2. [Popsicle](https://github.com/GaloisInc/swanky/tree/master/popsicle)
3. [Ocelot](https://github.com/GaloisInc/swanky/tree/master/ocelot)
    Library containing:
        set of implementations of OT protocol that fits into semi-honest and malitious model
        set of implementations of PRF in the OT in semi-honest model(BaRK-OPRF)
4. [Scuttlebutt](https://github.com/GaloisInc/swanky/tree/master/scuttlebutt)



## Container setup

This setup is based on usage of 
[podman](https://podman.io/) and 
[buildah](https://buildah.io/). Both of this tools operate under [OCI](https://opencontainers.org/)standard and compatible with docker.
In addition they do not require `root` privileges and therefore more secure.

Container image can be created by running command below. This will take a few minutes. You only have to do this once.
```
$ ./make_container.sh
```

Spin up a container from the image. Source code of `swanky` can be found at `/root`
```
$ podman run -it --rm swanky
```

## Architecture

## Compiling/Running examples

In order to recompile examples go to the source code folder and call `cargo build` with additional options
```shell
cd /root/swanky
cargo build --release --examples
```

Resulting binaries would be located at `/usr/local/src/swanky/target/release/examples`.

### Ocelot

`ocelot` library goes with 2 examples:
    1. 
    2.


## Performance measurement

Consider using containers in order to measure overall resource consumption.
https://www.datadoghq.com/blog/how-to-collect-docker-metrics/
