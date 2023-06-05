const dgram = require('dgram');
const client = dgram.createSocket('udp4');

const PORT = 3000;
const HOST = 'localhost';

client.on('error', (err) => {
  console.log(`client error:\n${err.stack}`);
  client.close();
});

client.on('message', (msg, rinfo) => {
  console.log(`client got: ${msg} from ${rinfo.address}:${rinfo.port}`);
  client.close();
});

const message = 'Hello UDP server';
const buffer = Buffer.from(message);

client.send(buffer, 0, buffer.length, PORT, HOST, (err) => {
  if (err) {
    console.log(`client error sending message to ${HOST}:${PORT}`);
    client.close();
  }
  console.log(`client sent message to ${HOST}:${PORT}`);
});
