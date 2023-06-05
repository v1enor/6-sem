//                      'C:\\Users\\valda\\AppData\\Roaming\\npm\\node_modules\\secxmail'
//                      `${process.env.NODE_GLOBAL}\\secxmail`
const send = require('m0604_supermegailyaedit');
const http = require('http');

http.createServer((req, res) => {
    res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
    send('Привет, где наши алименты? 06-04');
    res.end('<h2>Message sucessfully sent.</h2>');
}).listen(5000, () => console.log('Server running at localhost:5000/\n'));