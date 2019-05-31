/**
 * Do not change this unless you have to.
 * This code parses input command line arguments,
 * and calls the appropriate initialization and MPC protocol from ./mpc.js
 */

console.log('Command line arguments: <input> [<party count> [<computation_id> [<Zp>]]]');
console.log('Input is either a JSON array (without spaces) of numbers, or a number to search for in the array');

var mpc = require('./mpc');

// Read Command line arguments
var input = process.argv[2];
var party_id;
if (input.startsWith('[')) {
  party_id = 1;
  input = JSON.parse(input);
} else {
  party_id = 2;
  input = parseInt(input);
}

var party_count = process.argv[3];
if (party_count == null) {
  party_count = 2;
} else {
  party_count = parseInt(party_count);
}

var computation_id = process.argv[4];
if (computation_id == null) {
  computation_id = 'test';
}

var Zp = process.argv[5];
if (Zp == null) {
  Zp = 13;
}

// JIFF options
var options = {party_count: party_count, party_id: party_id, Zp: Zp};
options.onConnect = function (jiff_instance) {
  var promise = mpc.compute(input);

  promise.then(function (v) {
    console.log(v);
    jiff_instance.disconnect(true);
  });
};

// Connect
mpc.connect('http://localhost:8080', computation_id, options);
