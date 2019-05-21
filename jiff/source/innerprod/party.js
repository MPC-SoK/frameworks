/**
 * Do not change this unless you have to.
 * This code parses input command line arguments,
 * and calls the appropriate initialization and MPC protocol from ./mpc.js
 */

console.log('Command line arguments: <input> [<party count> [<computation_id> [<party id>]]]]');

var mpc = require('./mpc');

// Read Command line arguments
var input = JSON.parse(process.argv[2]);

// verify input has length power of 2
var lg = input.length;
while (lg > 1) {
  if (lg % 2 !== 0) {
    console.log('Input array length must be a power of 2!');
    return;
  }

  lg = lg / 2;
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

var party_id = process.argv[5];
if (party_id != null) {
  party_id = parseInt(party_id, 10);
}

// JIFF options
var options = {party_count: party_count, party_id: party_id};
options.onConnect = function (jiff_instance) {
  var promise = mpc.compute(input);
  promise.then(function (v) {
    console.log(v);
    jiff_instance.disconnect(true);
  });
};

// Connect
mpc.connect('http://localhost:8080', computation_id, options);
