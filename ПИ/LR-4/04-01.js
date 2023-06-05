var http = require('http');
var url = require('url');
var fs = require('fs');
var util = require('util');
var ee = require('events');
var db_module = require('./db-module');
const route = 'api/db';
var db = new db_module.DB();


db.on('GET', (req, res) => {
    console.log('GET called');
    res.end(db.select());
});


db.on('POST', (req, res) => {
    console.log('POST called');
    req.on('data', data => {
        res.end(db.insert(data));
    })
});


db.on('PUT', (req, res) => {
    console.log('PUT called');
    req.on('data', data => {
        res.end(db.update(data));
    })
});


db.on('DELETE', (req, res) => {
    console.log('DELETE called');
    if (typeof url.parse(req.url, true).query.id != "undefined")
    {
        // console.log("id is not undefined");
        var id = parseInt(url.parse(req.url, true).query.id);
        console.log("id = " + id);
        if (Number.isInteger(id))
            res.end(db.delete(id));
        else 
            res.end("ERROR! Id parameter is NaN");
    }
    else res.end("ERROR! The Id parameter is missing");
});



http.createServer((request, response) => {
    if (url.parse(request.url).pathname === '/' + route)
        db.emit(request.method, request, response);
    else if (url.parse(request.url).pathname === '/')
    {
        let html = fs.readFileSync('./04-02.html');
        response.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
        response.end(html);
    }
    else 
        response.end('<html><body><h1>Error! Visit localhost:5000/' + route + '</h1></body></html>');
}).listen(5000, () => console.log('Server running at localhost:5000/' + route + '\n'));