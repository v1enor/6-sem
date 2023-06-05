const net = require('net');
const HOST = '127.0.0.1';
const PORT = 4000;


let server = net.createServer(socket => {
    console.log(`\nClient connected: ${socket.remoteAddress}:${socket.remotePort}`);

    socket.on('data', data => {
        console.log(`Server received: ${data}`);
        socket.write(`ECHO: ${data}`);
        socket.destroy();
    })

    socket.on('close', () => { console.log(`Connection closed.`); })
    socket.on('error', error => { console.log('[ERROR] Client: ' + error.message); });
}).listen(PORT, HOST);


server.on('error', error => { console.log('[ERROR] Server: ' + error.message); });