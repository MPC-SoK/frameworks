/*
 * Do not modify this file unless you have too
 * This file has UI handlers.
 */
// eslint-disable-next-line no-unused-vars
function connect() {
  $('#connectButton').prop('disabled', true);
  var computation_id = $('#computation_id').val();
  var party_id = parseInt($('#role').val());

  var options = { party_id: party_id, party_count: 2};
  options.onError = function (error) {
    $('#output').append('<p class="error">'+error+'</p>');
    $('#connectButton').prop('disabled', false);
  };
  options.onConnect = function () {
    $('#input1').show();
    if (party_id === 1) {
      $('#party_values').show();
    } else {
      $('#party_types').show();
    }
    $('#result').append('All parties Connected!<br/>');
  };

  var hostname = window.location.hostname.trim();
  var port = window.location.port;
  if (port == null || port === '') {
    port = '80';
  } if (!(hostname.startsWith('http://') || hostname.startsWith('https://'))) {
    hostname = 'http://' + hostname;
  } if (hostname.endsWith('/')) {
    hostname = hostname.substring(0, hostname.length - 1);
  } if (hostname.indexOf(':') > -1 && hostname.lastIndexOf(':') > hostname.indexOf(':')) {
    hostname = hostname.substring(0, hostname.lastIndexOf(':'));
  }

  hostname = hostname + ':' + port;

  // eslint-disable-next-line no-undef
  mpc.connect(hostname, computation_id, options);
}

// eslint-disable-next-line no-unused-vars
function submitArray() {
  var party_id = parseInt($('#role').val());
  var ids = JSON.parse($('#idArray').val());
  var data = JSON.parse($('#valueArray').val());

  if (party_id === 2) {
    data = JSON.parse($('#typeArray').val());
    for (var i = 0; i < data.length; i++) {
      if (data[i] < 0 || data[i] > 3) {
        alert('Categories must be in the range [0,3]\nElement ',i,' is invalid');
        return;
      }
    }
  }
  console.log("data array: ", data)

  if (ids.length !== data.length) {
    alert("Input arrays must be the same length!");
    return;
  }


  // eslint-disable-next-line no-undef
  var promise = mpc.compute(ids,data);

  promise.then(function (result) {
    var msg;
    // return a string if there's an error
    if (! (result instanceof Array)) {
      console.log("result is not an array???")
      msg = result;
    } else {
      msg = "[ ";
      for(var i=0; i<result.length; i++) {
        msg = msg + ", " + result[i]; 
      }
      msg = msg + " ]";
    }
    $('#output').append('<p>' + msg + '</p>');
  });
}

