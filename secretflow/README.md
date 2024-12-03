# SecretFlow

[SecretFlow](https://github.com/secretflow/secretflow) features a
python-based front end and implements a range of primitives including
a few multi-party computation schemes. The source-code is available
[on GitHub](https://github.com/secretflow/secretflow); [additional
documentation is also
online](https://www.secretflow.org.cn/en/docs/secretflow).

## Docker setup

Create a Docker image. This will take a few minutes depending on the
network connection. It will download a few gigabytes. You only have to
do this once.
```
$ docker build -t secretflow .
```

Spin up a Docker container from the image.
```
$ docker run -it --rm secretflow
```

## Architecture

SecretFlow is a Python library with a C++ backup called SPU, see
[the USENIX ATC
paper](https://www.usenix.org/conference/atc23/presentation/ma) for
details. Our examples use the [ABY3](https://eprint.iacr.org/2018/403)
implementation as described in [the
tutorial](https://www.secretflow.org.cn/en/docs/secretflow/v1.10.0b1/tutorial/spu_basics). The
computation is specified as in Python, either with the internal
datatypes or numpy functionality (see the innerprod example for the latter).

## Running examples

We provide five examples (mult3, innerprod, xtabs, xtabs_jax, cmp). The
tutorial runs all parties in one script, and so do we. mult3 takes the
three inputs as commend-line arguments, and innerprod and xtabs takes
a single argument for the size and then generate some data in the script:
```
$ ./mult3.py <a> <b> <c>
$ ./innerprod.py <vector size>
$ ./xtabs.py <dataset size>
$ ./xtabs_jax.py <dataset size>
$ ./cmp.py <dataset size>
```

The examples will output the secure computation result and the
expected result:
```
$ ./mult3.py 1 2 3
...
result 6
expected 6
```

## Modifying examples

All examples have all input data in the `data` variable and a function
that describes the computation. Consider for example the mult3
example:
```
data = [int(sys.argv[i + 1]) for i in range(3)]
spu_data = [parties[i](lambda: data[i])().to(spu_device) for i in range(3)]

def mult3(a, b, c):
    return a * b * c

res = spu_device(mult3)(*spu_data)
```

The first line defines data, the second line converts it to data to be
used in the secure computation, and the last line runs the function on
the converted data.

Some NumPy functionality also works as demonstrated in the innerprod
example:
```
data = [numpy.array(list(range(int(sys.argv[1]))))] * 2
spu_data = [parties[i](lambda: data[i])().to(spu_device) for i in range(2)]

def innerprod(a, b):
    return a.dot(b)

res = spu_device(innerprod)(*spu_data)
```

Similarly, JAX can be used to parallelize the execution as in the
cmp example:
```
n = int(sys.argv[1])
data = [jnp.array(x) for x in (list(range(n)), list(range(1, n + 1)))]

spu_data = [parties[i](
    lambda: data[i])().to(spu_device) for i in range(2)]

def cmp(a, b):
    def map_i(i):
        return a[i] < b[i]

    return jax.vmap(map_i)(jnp.arange(n))

res = spu_device(cmp)(*spu_data)
```
