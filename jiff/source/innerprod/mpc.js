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

  /**
   * The MPC computation
   */
  exports.compute = function (input, jiff_instance) {
    try {
      if (jiff_instance == null) {
        jiff_instance = saved_instance;
      }

      var final_deferred = $.Deferred();
      var final_promise = final_deferred.promise();

      // Share the arrays
      jiff_instance.share_array(input, input.length).then(function (shares) {
        try {
          // multipy all shared input arrays element wise
          var array = shares[1];
          for (var p = 2; p <= jiff_instance.party_count; p++) {
            for (var i = 0; i < array.length; i++) {
              array[i] = array[i].smult(shares[p][i]);
            }
          }
 
          // sum up elements
          var sum = array[0];
          for (var i = 1; i < array.length; i++) {
            sum = sum.sadd(array[i]);
          }

          // Open the array
          jiff_instance.open(sum).then(function (results) {
            final_deferred.resolve(results);
          });

        } catch (err) {
          console.log(err);
        }
      });

    } catch (err) {
      console.log(err);
    }

    return final_promise;
  };
}((typeof exports === 'undefined' ? this.mpc = {} : exports), typeof exports !== 'undefined'));
