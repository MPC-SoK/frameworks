# JIFF

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
There is a jiff engine that must execute MPC.

The server executes `server.js`, which hosts the client website.
The clients can visit the webpage and execute the `client.js` script, which defines the interactions the user has with the webpage.
When a client submits data, they execute functions defined in `mpc.js`: `connect` finds an existing jiff instance; `compute` shares the input among other parties, receives input from the rest, and computes the function.

It's not clear to me yet where the sharing and distributed communications are implemented. There is a library `jiff-client.js`. 

The multiply function uses beaver triplets that seem to come from the jiff instance. Are they using the trusted third party model for generating offline data? How do the clients communicate? 

Based on errors I'm seeing, it looks like clients maintain some kind of open connection as long as the webpage is open, even if the server stops and restarts.

Why must array length be a power of 2?

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

