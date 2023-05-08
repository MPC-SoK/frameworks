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
      JiffClient = require('../../lib/jiff-client');
      // eslint-disable-next-line no-undef,no-global-assign
      $ = require('jquery-deferred');
    }

    // eslint-disable-next-line no-undef
    saved_instance = new JiffClient(hostname, computation_id, opt);
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

    // execute xtabs once all data is shared
    Promise.all([id_promise, data_promise]).then(function (shares) {
      if (shares[1][1].length !== shares[1][2].length) {
        // not sure if this works
        deferred.resolve("ERROR: inputs have different lengths");
        return promise;
      }

      var result = xtabs(shares[0], shares[1], jiff_instance);

      // process array of outputs
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
    var NUM_TYPES = 4;
    var results = new Array(NUM_TYPES).fill(null);

    var eqid;
    var eqcat;
    var amt_added;

    // if ids match and categories match, add value
    // eg results[cat] += eqid * eqcat * value
    for (var i = 0; i < id_shares[1].length; i++) {
      for(var j = 0; j < id_shares[2].length; j++) {
        eqid = id_shares[1][i].eq( id_shares[2][j] );
        for (var cat=0; cat < NUM_TYPES; cat++) {
          eqcat = types[j].eq(cat);
          amt_added = values[i].smult(eqid.smult(eqcat));
          if (results[cat]) {
            results[cat] = results[cat].sadd(amt_added);
          } else {
            results[cat] = amt_added;
          }
        }
      }
    }

    return results;
  }

}((typeof exports === 'undefined' ? this.mpc = {} : exports), typeof exports !== 'undefined'));
