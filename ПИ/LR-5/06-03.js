const http = require('http');
const send = require('./m0603.js');

http.createServer((request, response) => {
    response.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
    send(' а я думал сова');
    response.end('<h2>Message sucessfully sent.</h2>');
}).listen(5000, () => console.log('Server running at localhost:5000/\n'));
