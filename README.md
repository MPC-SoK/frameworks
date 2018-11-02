This repository contains a collection of sample programs for a variety of multi-party computation (MPC) frameworks. For ease of examination, we have set up each framework in a Docker container. This minimizes the effort required to test framework functionality. 

This repository accompanies the paper <a href="http://marcellahastings.com/static/mpcsok.pdf">SoK: General-Purpose Compilers for Secure Multi-party Computation</a>, which includes a thorough evaluation of each framework across usability and architectural criteria. For a gentler introduction to MPC and this project, please read our [Layperson's Guide](https://github.com/MPC-SoK/frameworks/wiki/A-Layperson%27s-Guide).

We include a complete build environment and three sample programs for each of 12 frameworks (additional documentation of each framework can be found in the [wiki](https://github.com/mpc-sok/frameworks/wiki) pages). 
Each framework directory includes a `Dockerfile` and `install.sh` script, described below. There is a `README` that describes some relevant architecture along with instructions to compile, run, and modify examples. The `source` directory holds the sample programs and any additional code (including patches, vim syntax highlighting, and input generation scripts).

## About Sample Programs
We implemented three sample programs for each framework. These are small, unit tests and are not intended to exhaustively test framework functionality. We used them to learn about the architecture and set-up requirements of each framework. They illustrate a variety of common functionality requirements.

The first program multiplies three numbers together. It either takes input from three different parties (if supported) or takes three _secret shared_ inputs from two parties. Some frameworks provide built-in tools for secret-sharing input, while others required us to manually share inputs to two parties. It tests basic numeric capabilities, including integer I/O and basic computation. This is denoted as `mult3` in the sample code.

The second program computes an inner product on two integer vectors. Sometimes known as the scalar or dot product, this simple computation takes two vectors as input and computes the pairwise product of their elements. It requires that frameworks support input, access, and iteration over secret-valued arrays.  It is denoted `innerprod` in the sample code.

The third program computes a crosstabulation, a database operation that computes averages by category. The category table and value table share a primary key but are owned by different parties. This further tests array operations, including output and modification of arrays, and requires conditionals on secret data. We used a brute-force algorithm to solve this problem, and return a list of sums by category (rather than averages). It is denoted `xtabs` in the sample code.

## About Docker

Docker is a tool for creating containers. A container is lightweight, stand-alone package that sets up a complete run-time environment: OS, packages, libraries, and code. 

In this repository, we have defined a Docker image for each MPC framework. An image defines the environment that we'd like to run our software in. In this case, we download the MPC framework, install all necessary libraries, compile the framework (if necessary) and move our sample code to an appropriate directory. We include a separate `README` for each repository explaining how to run the examples.

For each framework, you'll find a `Dockerfile`. This defines everything that must be done to set up a suitable development environment. For example, it may define an operating system and a home directory, install some packages with `apt-get`, copy our source files, and run an install script we've defined.

### Images and Containers

A Docker image is defined by a `Dockerfile` and only needs to be created once. You can create it by running the Docker `build` command in the same directory as a Dockerfile:
```
$ docker build -t image1 .
```
The `-t` option lets you tag an image with a useful nickname. You can see all the images defined on your machine by running
```
$ docker image ls
REPOSITORY	TAG		IMAGE ID		CREATED		SIZE
image1		<none>	485973be2fed	1 day ago	123 mb
```

If you don't tag an image, you can use its ID to create a container.

A container is an instance of an image. Once you've defined an image using the `build` command, you can create any number of containers using that image. You create a container using the `run` command:
```
$ docker run -it --rm image1
root@<image-id>:~#
```
In this repository, we always use the `-it` option, which makes the container interactive. This provides access to a terminal from which the framework examples can be run.

The `--rm` tag deletes the container after it is closed. If you'd like to make changes to files within the container, they will not persist after the container is removed. You can remove this option to keep your container running for multiple sessions. 

Finally, `image1` is the tag of the image we're running. As mentioned, you can also use an image ID.

In this repository, the `run` command will open up a terminal in the `root` directory. See individual `README`s for further instructions.

### Downloading Docker

Docker is available for many popular operating systems. 

On many \*nix operating systems, you can install Docker via command line:
```
$ sudo apt-get install docker.io
```

The [Docker Community Edition](https://store.docker.com/search?type=edition&offering=community) is available for a variety of operating systems, including Windows 10, MacOS, Ubuntu, Debian, CentOS, and Fedora. The website includes OS-specific download instructions.

If your Mac or Windows version is particularly old, you can try [Docker Toolbox](https://docs.docker.com/toolbox/overview/) instead.

On some Ubuntu and other \*nix OSes, you may need to run the `docker build` and `docker run` commands with `sudo`.

## Questions
This software is offered as-is. It represents these frameworks at a single point in time (early- to mid-2018), and may not be up-to-date with the latest versions. We welcome pull requests for compatibility with new software versions, corrections to sample programs, and directories for new frameworks.

Questions and commentary should be raised publicly in the [Issue Tracker](https://github.com/MPC-SoK/frameworks/issues). 

If you use this work for an academic project, please cite:
```latex
    @inproceedings{mpc-sok,
       author = {Marcella Hastings and Brett Hemenway and Daniel Noble and Steve Zdancewic},
       title = {{SoK:} General-Purpose Compilers for Secure Multi-Party Computation},
       booktitle = {2019 IEEE Symposium on Security and Privacy (SP)},
       year = {2019},
    }
```

