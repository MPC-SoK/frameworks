// Chai
var assert = require('chai').assert;

var mpc = require('./mpc.js');

// Generic Testing Parameters
var showProgress = false;
var party_count = 3;
var parallelismDegree = 10; // Max number of test cases running in parallel
var n = 100;
var Zp = null;

// Parameters specific to this demo
var maxValue = 100;


/**
 * Generates inputs for mult3 tests
 * Should return an object with this format:
 * {
 *   'party_id': [ 'test1_input', 'test2_input', ...]
 * }
 *
 * In this setting, each input is a single integer.
 */
function generateInputs(party_count) {
  var inputs = {};
  var i;

  for (i = 1; i <= party_count; i++) {
    inputs[i] = [];
  }

  for (t = 0; t < n; t++) {
    for (i = 1; i <= party_count; i++) {
      inputs[i].push(Math.floor((Math.random() * maxValue)));
    }
  }
  return inputs;
}

/**
 * Computes the expected results in the clear
 * @param {object} inputs - same format as generateInputs output.
 * Should return a single array with the expected result for every test in order
 *   [ 'test1_output', 'test2_output', ... ]
 */
function computeResults(inputs) {
  var results = [];

  for (var j = 0; j < n; j++) {
    var prod = 1;
    for (var i = 1; i <= party_count; i++) {
      prod = prod * inputs[i][j];
    }
    results.push(prod);
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
            promises.push(mpc.compute(partyInputs[j + t], jiff_instance));
          }

          Promise.all(promises).then(function (parallelResults) {
            for (var t = 0; t < parallelResults.length; t++) {
              testResults.push(parallelResults[t]);
            }

            one_test_case(j + parallelismDegree);
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
            done = function () {
            };
          }
        }

        jiff_instance.disconnect(true);
        if (count === party_count) {
          done();
        }
      })(0);
    };

    var options = { party_count: party_count, onError: console.log, onConnect: onConnect, Zp: Zp, crypto_provider: true };
    for (var i = 0; i < party_count; i++) {
      mpc.connect('http://localhost:8080', 'mocha-test', options);
    }
  });
});
