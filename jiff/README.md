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
There are two types of parties, a single central server that serves a client interface and routes messages, and individual clients that provide data and execute the computation. The server can be untrusted as long as clients are part of a public-key infrastructure.
This architecture allows clients to disconnect temporarily during a computation without shutting everything down.

Individual examples are mostly divided into the following files:
```
+ demos/example
  - client.html : client front-end webpage
  - client.js : implements client-side connections and input-passing
  - mpc.js : defines MPC computation
  - party.js : parses command line inputs and initializes MPC 
  - server.js : implements server-side communications and hosting
  - test.js : implements tests
```

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

Connect as many clients as necessary. The client interface lets you connect to the server and enter data.

## Modifying examples

To create an example, just add a new folder in the `jiff/demos` directory. The main files to be modified are `client.html`, `client.js`, `mpc.js`, and `test.js`. In most cases, `server.js` and `party.js` can be left as-is. Some debug info is in the javascript console. 

