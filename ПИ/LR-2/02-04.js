const express = require('express');
const path = require('path');

const app = express();

app.get('/xmlhttprequest', (req, res) => {
  res.sendFile(__dirname + '/xmlhttprequest.html');
});

app.get('/api/name', (req, res) => {
  res.type('text/plain');
  res.send('Парибок Илья');
});


app.listen(5000, () => {
  console.log('Server started on port 5000');
});
