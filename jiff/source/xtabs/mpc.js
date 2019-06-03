(function (exports, node) {
  var saved_instance;

  /**
   * Connect to the server and initialize the jiff instance
   */
  exports.connect = function (hostname, computation_id, options) {
    var opt = Object.assign({}, options);
    // Added options goes here

    if (node) {
      // eslint-disable-next-line no-undef
      jiff = require('../../lib/jiff-client');
      // eslint-disable-next-line no-undef,no-global-assign
      $ = require('jquery-deferred');
    }

    // eslint-disable-next-line no-undef
    saved_instance = jiff.make_jiff(hostname, computation_id, opt);
    // if you need any extensions, put them here

    return saved_instance;
  };

  exports.compute = function (ids,data, jiff_instance) {
    if (jiff_instance == null) {
      jiff_instance = saved_instance;
    }

    var deferred = $.Deferred();
    var promise = deferred.promise();
    var allPromisedResults = [];

    // pass inputs
    var id_promise = jiff_instance.share_array(ids, ids.length);
    var data_promise = jiff_instance.share_array(data, data.length);

    Promise.all([id_promise, data_promise]).then(function (shares) {
      // pass ids and data to xtabs
      var result = xtabs(shares[0], shares[1], jiff_instance);

      // this processes the debug output for now
      for(var i = 0; i<result.length; i++){
        allPromisedResults.push(jiff_instance.open(result[i]));
      }

      Promise.all(allPromisedResults).then(function (results) {
          deferred.resolve(results);
      });
    });

    return promise;
  };

  // input is two independent lists of ids
  // player 1's data shares are values
  // player 2's data shares are categories
  function xtabs(id_shares, data_shares, jiff_instance) {
    var values = data_shares[1];
    var types = data_shares[2];

    // number of categories is fixed at 4 for now.
    //var results = new Array(4);

    // debugging: returns booleans indicating whether ids match
    var debug_results = [];

    for (var i = 0; i < id_shares[1].length; i++) {
      for(var j = 0; j < id_shares[2].length; j++) {
        debug_results.push( id_shares[1][i].eq( id_shares[2][j] ));
      }
    }

    //return results;
    return debug_results;


    /*
    if (array.length === 1) {
      return array[0].seq(element);
    }

    // comparison
    var mid = Math.floor(array.length/2);
    var cmp = element.slt(array[mid]);

    // Slice array in half, choose slice depending on cmp
    var nArray = [];
    for (var i = 0; i < mid; i++) {
      var c1 = array[i];
      var c2 = array[mid+i];
      nArray[i] = cmp.if_else(c1, c2);
    }

    // watch out for off by 1 errors if length is odd.
    if (2*mid < array.length) {
      nArray[mid] = array[2*mid];
    }

    return binary_search(nArray, element);
    */
  }

}((typeof exports === 'undefined' ? this.mpc = {} : exports), typeof exports !== 'undefined'));
