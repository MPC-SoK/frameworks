# FRESCO

[FRESCO]() is a FRamework for Efficient Secure COmputation. It was developed at the Alexandra Institue.It is designed for easy development of prototype applications and also supports developers who wish to implement MPC protocols.

It is [well documented](https://fresco.readthedocs.io/en/latest/intro.html) online!

This sample code was contributed by [Peter Nordholt](https://github.com/GuutBoy). Thanks!

## Docker setup

The FRESCO development team produced their own Docker images. This repo runs just the [sample programs](https://github.com/aicis/fresco-samples).
```
$ docker build -t frescosamples .
$ docker run -it --rm frescosamples
```

There are additional demos and more implementations in their main image:
```
$ docker run -it --rm frescompc/fresco
```
The text of this Dockerfile can be found [in their repository](https://github.com/aicis/fresco/blob/master/Dockerfile).


## Architecture


## Running examples


### Using different protocol implementations
This sample code uses the SPDZ protocol, but FRESCO also has support for other protocols.

## Modifying examples