This repository contains a collection of sample programs for a variety of multi-party computation (MPC) frameworks. For ease of examination, we have set up each framework in a Docker container, which will allow you to run examples with as little effort as possible.

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
