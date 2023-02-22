const express = require('express');
const app = express();
const port = 5000;

app.get('/jquery', (req, res) => {
  res.sendFile(__dirname + '/jquery.html');
});

app.get('/api/name', (req, res) => {
  res.send('Парибок Илья Александрович');
});

app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
