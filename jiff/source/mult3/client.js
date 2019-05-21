/**
 * Do not modify this file unless you have to.
 * This file has UI handlers.
 */

// eslint-disable-next-line no-unused-vars
function connect() {
  $('#connectButton').prop('disabled', true);
  var computation_id = $('#computation_id').val();
  var party_count = parseInt($('#count').val());

  if (isNaN(party_count)) {
    $('#output').append("<p class='error'>Party count must be a valid number!</p>");
    $('#connectButton').prop('disabled', false);
  } else {
    var options = { party_count: party_count};
    options.onError = function (error) {
      $('#output').append("<p class='error'>"+error+'</p>');
    };
    options.onConnect = function () {
      $('#button').attr('disabled', false); $('#output').append('<p>All parties Connected!</p>');
    };

    var hostname = window.location.hostname.trim();
    var port = window.location.port;
    if (port == null || port === '') {
      port = '80';
    }
    if (!(hostname.startsWith('http://') || hostname.startsWith('https://'))) {
      hostname = 'http://' + hostname;
    }
    if (hostname.endsWith('/')) {
      hostname = hostname.substring(0, hostname.length-1);
    }
    if (hostname.indexOf(':') > -1 && hostname.lastIndexOf(':') > hostname.indexOf(':')) {
      hostname = hostname.substring(0, hostname.lastIndexOf(':'));
    }

    hostname = hostname + ':' + port;
    // eslint-disable-next-line no-undef
    mpc.connect(hostname, computation_id, options);
  }
}

// eslint-disable-next-line no-unused-vars
function submit() {
  var input = parseInt($('#number').val());

  if (isNaN(input)) {
    $('#output').append("<p class='error'>Input a valid number!</p>");
  } else if (100 < input || input < 0 || input !== Math.floor(input)) {
    $('#output').append("<p class='error'>Input a WHOLE number between 0 and 100!</p>");
  } else {
    $('#button').attr('disabled', true);
    $('#output').append('<p>Starting...</p>');
    // eslint-disable-next-line no-undef
    var promise = mpc.compute(input);
    promise.then(handleResult);
  }
}

function handleResult(result) {
  $('#output').append('<p>Result is: ' + result + '</p>');
  $('#button').attr('disabled', false);
}
