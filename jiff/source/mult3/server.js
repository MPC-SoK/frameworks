var express = require('express');
var app = express();
var http = require('http').Server(app);

//Serve static files
//Configure App
app.use('/demos', express.static('demos'));
app.use('/lib', express.static('lib'));
app.use('/lib/ext', express.static('lib/ext'));

require('../../lib/jiff-server').make_jiff(http, { logs:true });

// Serve static files.
try {
http.listen(8080, function () {
  console.log('listening on *:8080');
});
} catch (err) {
  console.log('ERROR:'+err.message)
}


console.log('Direct your browser to *:8080/demos/mult3/client.html.');
console.log('To run a node.js based party: node demos/mult3/party <input>');
console.log();
