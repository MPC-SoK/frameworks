# EMP-toolkit

JIFF source is available [on github](https://github.com/multiparty/jiff).


## Docker setup

Create a Docker image. This will take a few minutes. You only have to do this
once.
```
$ docker build -t jiff.
```
Spin up a Docker container from the image. 
```
$ docker run -it --rm jiff 
```
Please note that any changes you make in the container are not persistent.

## Architecture


## Running examples

Run your Docker container. So far we haven't implemented any exampes, but you can try the included ones.

Start the server node
```
$ cd jiff
$ node demos/<ex>/server.js
```

This starts a server on the Docker localhost. To find the correct IP address, find the docker container name and inspect it to find the correct IP. Run this on your host machine (not in your Docker container):
```
$ docker ps -a
CONTAINER ID     IMAGE   COMMAND        CREATED         STATUS          PORTS   NAMES 
d16826c5137e     jiff    "/bin/bash"    27 minutes ago  Up 27 minutes           <container name> 
...
$ docker inspect <container name> | grep IP
...
            "IPAddress": "172.17.0.1",
...
```

Then you can connect to the client interface in the browser to the IP address you found. The server should tell you the correct URL, too.

`172.17.0.1:8080/demos/<ex>/client.html`

Connect as many clients as necessary.

## Modifying examples

