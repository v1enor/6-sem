const express = require('express');
const path = require('path');

const app = express();

app.get('/html', (req, res) => {
  const filePath = path.join(__dirname, 'index.html');
  res.sendFile(filePath);
});

app.listen(5000, () => {
  console.log('Server started on port 5000');
});
