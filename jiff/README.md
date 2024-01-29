# JIFF

[JIFF](https://github.com/multiparty/jiff) is a Javascript library. It implements a custom set of hybrid protocols and can be integrated easily with web apps in the browser or via Node.js.

## Docker setup

Create a Docker image. This will take a few minutes. You only have to do this once.
```
docker build -t jiff .
```
Spin up a Docker container from the image. 
```
docker run -it --rm jiff 
```
Please note that any changes you make in the container are not persistent.

## Architecture
There are two types of parties, a single central server that serves a client interface and routes messages, and individual clients that provide data and execute the computation. The server can be untrusted as long as clients are part of a public-key infrastructure.
This architecture allows clients to disconnect temporarily during a computation without shutting everything down.

Individual examples are mostly divided into the following files:
```
+ demos/<example>
  - client.html : client front-end webpage
  - client.js : implements client-side connections and input-passing
  - mpc.js : defines MPC computation
  - party.js : parses command line inputs and initializes MPC 
  - server.js : implements server-side communications and hosting
  - test.js : implements tests
```

See [extended documentation](https://multiparty.org/jiff/docs/jsdoc/) by the JIFF developers.

## Running examples

Run the Docker container. We implemented three examples, `mult3`, `innerprod`, and `xtabs`. You can either run them in the browser or via automated tests.

To run tests, execute
```
cd ~/jiff
npm run-script test-demo -- demos/<ex>
```
Note that the `xtabs` test is relatively slow to execute.

To run interactively in the browser, first run the server node
```
$ cd ~/jiff
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

Then you can connect to the client interface in your web browser to the IP address you found. The server should tell you the correct URL, too.

`172.17.0.1:8080/demos/<ex>/client.html`

Open the appropriate number of client tabs in the browser (3 for `mult3`, 2 for the other examples).
First, connect all clients by clicking the `Connect` button. Then enter data and click the `Submit` button.

## Modifying examples

To create an example, just add a new folder in the `jiff/demos` directory. The main files to be modified are `client.html`, `client.js`, `mpc.js`, and `test.js`. In most cases, `server.js` and `party.js` can be left as-is. Some debug info is in the javascript console. 

