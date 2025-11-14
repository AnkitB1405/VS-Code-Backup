var express = require('express');
var bodyParser = require('body-parser');
var app = express();
var port = 3000;

app.get('/', function(req, res) {
    res.render('form');
});

app.set('view engine', 'pug');
app.set('views', './views');

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.post('/submit', function(req, res) {
    console.log('Received data:', req.body);
    res.send('Data received successfully!');
});

app.listen(port, function() {
    console.log(`Server is running at http://localhost:${port}`);
});