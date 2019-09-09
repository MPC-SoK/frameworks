// Chai
//var expect = require('chai').expect;
var assert = require('chai').assert;

var mpc = require('./mpc.js');

// Generic Testing Parameters
var party_count = 2;
var parallelismDegree = 1; // Max number of test cases running in parallel
var n = 1;

// Parameters specific to this demo
var maxID = 20;
var maxValue = 30;
var maxCat = 4;
var maxLength = 10; // don't do more tests or everything will bork.

var showProgress = true;
var Zp = 101; 

/**
 * CHANGE THIS: Generate inputs for your tests
 * Should return an object with this format:
 * {
 *   'party_id': [ 'test1_input', 'test2_input', ...]
 * }
 */
function generateInputs(party_count) {
  var inputs = {};
  for (var i = 1; i <= party_count; i++) {
    inputs[i] = [];
  }

  for (var t = 0; t < n; t++) {
    var length = Math.floor(Math.random() * maxLength) + 1;

    var id1 = [];
    var id2 = [];
    var cat = [];
    var val = [];
    while (id1.length < length) {
      id1.push(Math.floor(Math.random() * maxID));
      id2.push(Math.floor(Math.random() * maxID));
      cat.push(Math.floor(Math.random() * maxCat));
      val.push(Math.floor(Math.random() * maxValue));
    }

    inputs[1][t] = { ids:id1, dat:val };
    inputs[2][t] = { ids:id2, dat:cat };

  }

  return inputs;
}

/**
 * CHANGE THIS: Compute the expected results not in MPC
 * @param {object} inputs - same format as generateInputs output.
 * Should return a single array with the expected result for every test in order
 *   [ 'test1_output', 'test2_output', ... ]
 */
function computeResults(inputs) {
  var results = [];

  for (var t = 0; t < n; t++) {
    var len = inputs[1][t].ids.length
    var rescat = Array(maxCat).fill(0);
    for (var i1=0; i1<len; i1++) {
      for (var i2=0; i2<len; i2++) {
        if (inputs[1][t].ids[i1] === inputs[2][t].ids[i2]) {
          rescat[inputs[2][t].dat[i2]] += inputs[1][t].dat[i1];
        }
      }
    }
    results.push(rescat);
  }

  return results;
}

/**
 * Do not change unless you have to.
 */
// eslint-disable-next-line no-undef
describe('Test', function () {
  this.timeout(0); // Remove timeout

  // eslint-disable-next-line no-undef
  it('Exhaustive', function (done) {
    var count = 0;

    var inputs = generateInputs(party_count);
    var realResults = computeResults(inputs);

    var onConnect = function (jiff_instance) {
      var partyInputs = inputs[jiff_instance.id];

      var testResults = [];
      (function one_test_case(j) {
        if (jiff_instance.id === 1 && showProgress) {
          console.log('\tStart ', j > partyInputs.length ? partyInputs.length : j, '/', partyInputs.length);
        }

        if (j < partyInputs.length) {
          var promises = [];
          for (var t = 0; t < parallelismDegree && (j + t) < partyInputs.length; t++) {
            promises.push(mpc.compute(partyInputs[j+t].ids, partyInputs[j+t].dat, jiff_instance));
          }

          Promise.all(promises).then(function (parallelResults) {
            for (var t = 0; t < parallelResults.length; t++) {
              testResults.push(parallelResults[t]);
            }

            one_test_case(j+parallelismDegree);
          });

          return;
        }

        // If we reached here, it means we are done
        count++;
        for (var i = 0; i < testResults.length; i++) {
          // construct debugging message
          var ithInputs = inputs[1][i] + '';
          for (var p = 2; p <= party_count; p++) {
            ithInputs += ',' + inputs[p][i];
          }
          var msg = 'Party: ' + jiff_instance.id + '. inputs: [' + ithInputs + ']';

          // assert results are accurate
          try {
            assert.deepEqual(testResults[i].toString(), realResults[i].toString(), msg);
          } catch (assertionError) {
            done(assertionError);
            done = function () { };
          }
        }

        jiff_instance.disconnect(true);
        if (count === party_count) {
          done();
        }
      })(0);
    };

    var options = { party_count: party_count, onError: console.log, onConnect: onConnect, Zp: Zp };
    for (var i = 0; i < party_count; i++) {
      mpc.connect('http://localhost:8080', 'mocha-test', options);
    }
  });
});
