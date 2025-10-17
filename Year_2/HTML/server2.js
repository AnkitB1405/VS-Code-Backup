import http from 'http';

const hostname = '127.0.0.1';
const port = 5000;

const server = http.createServer((req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/plain');
  res.write('This is an exaple of a JavaScript based server.\n');
  res.write('The server is running at http://' + hostname + ':' + port + '/\n');
  res.end('Hello World\n');
});

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});

// To run this server, use the command: node server2.js
// Then open your browser and go to http://127.0.0.1:5000