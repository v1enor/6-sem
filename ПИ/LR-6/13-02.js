const net = require('net');
const HOST = '127.0.0.1';
const PORT = 4000;
let client = new net.Socket();
let message = 'Hello from 13-02.js!';


setTimeout(() => {

    client.connect(PORT, HOST, () => {
        console.log(`\nConnected to server: ${client.remoteAddress}:${client.remotePort}`);
    });


    client.write(message);

    client.on('data', data => {
        console.log(`Client received: ${data.toString()}`);
        client.destroy();
    });

    client.on('close', () => { console.log(`Connection closed.`); });

    client.on('error', error => { console.log(`[ERROR] ${error.message}`); });

}, 500)