# Binary Search Demo

Description and guide for binary search with secure MPC. 

## Protocol
Player 1 inputs an array of integer values. Player 2 inputs a single "search" integer. If that integer is present in player 1's 
input array, then 1 is output. Otherwise, 0 is output. A binary search is performed to determine this presence or absence
of the search integer in the array. 

The implementation of this protocol is located in lines 25 through 81 of mpc.js. First, the input array is sorted. Second,
the inputs are secret shared. Since each player executes both of these steps, both players technically share an input value 
and an array; one of these will just be null for each. Finally, a binary search is recursively called on the array, using 
MPC protocols for the comparison of secret shares. 

NOTE: As currently implemented, the input array is hard-coded into the MPC protocol as player 1's input. 
If player 1 inputs the search integer and player 2 inputs the array, the protocol will not perform as expected. 

## Running Demo

1. Running a server:
    ```shell
    node demos/array-binary-search/server.js
    ```

2. Either open browser based parties by going to *http://localhost:8080/demos/array-binary-search/client.html* in the browser, or a node.js party by running 
    ```shell
    node demos/array-binary-search/party.js <input> [<party count> [<computation_id> [<party id>]]]]'
    ```
    Party 1's input should be an array of integers with no spaces. Party 2's input should be a single integer value.  

3. Running tests: run the following. Note that you *do not* need to have the server running when running the tests; they run the server on their own.
    ```shell
    npm run-script test-demo -- demos/array-binary-search/test.js
    ```

## File structure
The demo consists of the following parts:
1. Server script: *server.js*
2. Web Based Party: Made from the following files:
    * *client.html*: UI for the browser.
    * *client.js*: Handlers for UI buttons and input validations.
3. Node.js-Based Party: 
    * *party.js*: Main entry point. Parses input from the command line and initializes the computation.
4. The MPC protocol: Implemented in *mpc.js*. This file is used in both the browser and node.js versions of the demo.
5. test.js: mocha unit tests.
6. Documentation:
    * This *README.md* file.

