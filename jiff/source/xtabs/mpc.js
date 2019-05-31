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

    // var value_array_shares = jiff_instance.share_array(value_array, 2, [1, 2], [ 2 ]);

    // TODO: update this to take one array of pairs (2-el arrays)
    // e.g. [[id,val], ... , [id,val]]
    //  and [[id,cat], ... , [id,cat]]
    id_promise = jiff_instance.share_array(ids, ids.length);

    jiff_instance.share_array(data, data.length).then(function (shares) {
      console.log("shares: ", shares)
      var result = xtabs(shares[1], shares[2]);
      result.open().then(function (result) {
        deferred.resolve(result);
      });
    });

    return promise;
  };

  function xtabs(value_array_shares, type_array_shares) {


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
