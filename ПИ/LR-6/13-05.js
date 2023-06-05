const dgram = require('dgram');

const server = dgram.createSocket('udp4');

server.on('error', (err) => {
  console.log(`server error:\n${err.stack}`);
  server.close();
});

server.on('message', (msg, rinfo) => {
  console.log(`server got: ${msg} from ${rinfo.address}:${rinfo.port}`);
  const responseMsg = Buffer.from(`ECHO: ${msg}`);
  server.send(responseMsg, rinfo.port, rinfo.address, (err) => {
    if (err) {
      console.log(`server error sending message to ${rinfo.address}:${rinfo.port}`);
      server.close();
    }
  });
});

server.on('listening', () => {
  const address = server.address();
  console.log(`server listening ${address.address}:${address.port}`);
});

server.bind(3000);
