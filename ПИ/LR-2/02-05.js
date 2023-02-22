const express = require('express');
const fs = require('fs');
const app = express();

app.get('/fetch', (req, res) => {
  fs.readFile('fetch.html', (err, data) => {
    if (err) {
      res.status(500).send('Error reading file');
    } else {
      res.setHeader('Content-Type', 'text/html');
      res.send(data);
    }
  });
});

app.get('/api/name', (req, res) => {
  res.setHeader('Content-Type', 'text/plain');
  res.send('Иванов Иван Иванович');
});

app.listen(5000, () => {
  console.log('Server started on http://localhost:5000');
});
