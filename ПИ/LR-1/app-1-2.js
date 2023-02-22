var http = require('http');
const port = 3000;

let getHeaders = (req) => {
	let headers = '';
	let i = 0;
	for (key in req.headers)
		headers += '<h3>' + ++i + '. ' + key + ': ' + req.headers[key] + '</h3>';
	return headers;
}

http.createServer(function (request, response) {
	let reqBody = '';
	request.on('data', str => {reqBody += str; console.log('data: ', reqBody);});
	response.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'});
	request.on('end', () => response.end(
		'<!DOCTYPE html><html><head></head>' +
		'<body>'+
			'<h1>Структура Запроса:</h1>' +
			'<h2>Метод:  ' + request.method + '</h2>' +
			'<h2>URI:    ' + request.url + '</h2>' +
			'<h2>Версия: ' + request.httpVersion + '</h2>' +
			'<h2>ЗАГОЛОВКИ</h2>' +
				getHeaders(request) + '<h2>Тело запроса: ' + reqBody + '</h2>' +
		'</body>' +
		'</html>'
		)
	)
}).listen(port);

console.log('Server running at localhost:3000');
