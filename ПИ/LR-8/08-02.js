const express = require('express');
const jwt = require('jsonwebtoken');
const bodyParser = require('body-parser');
const fs = require('fs');

const app = express();
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

const secretKey = 'mySecretKey';
const tokenLife = '1m';

app.post('/login', (req, res) => {
  const { username, password } = req.body;
  const users = JSON.parse(fs.readFileSync('./users.json'));

  const user = users.find((user) => user.username === username && user.password === password);
  
  if (user) {
    const token = jwt.sign({ username }, secretKey, { expiresIn: tokenLife });
    res.json({ token });
  } else {
    res.status(401).json({ message: 'Неправильный логин или пароль' });
  }
});

app.get('/profile', (req, res) => {
  const token = req.headers.authorization.split(' ')[1];
  try {
    const decoded = jwt.verify(token, secretKey);
    const users = JSON.parse(fs.readFileSync('./users.json'));

    const user = users.find((user) => user.username === decoded.username);

    if (user) {
        res.send(`
        <h1>Профиль пользователя</h1>
        <p>Имя пользователя: ${user.username}</p>
        <p>Email: ${user.email}</p>
      `);
      //res.json({ username: user.username, email: user.email });
    } else {
      res.status(401).json({ message: 'Невалидный токен' });
    }
  } catch (error) {
    res.status(401).json({ message: 'Невалидный токен' });
  }
});

app.get('/login', (req, res) => {
    res.send(`
    <style type="text/css">
    * {
        font-family: system-ui, -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif;
        font-size: 18px;
        #container {
          margin: 20px 0 0 10px;
      }
    
      input {
          border: 1px solid #dbdbdb;
          border-radius: 4px;
          padding: 5px;
      }
      input {
        height: 2em;
        font-size: 1rem;
        background-color: rgb(248, 248, 248);
        color: #2f2f2f;
        border: 1px solid #c4c4c4;
        border-radius: 4px;
        margin: 10px 10px;
        cursor: pointer;
    }
    </style>
      <h1>Аутентификация пользователя</h1>
      <form method="post" action="/login">
        <div>
          <label for="username">Имя пользователя:</label>
          <input type="text" id="username" name="username">
        </div>
        <div>
          <label for="password">Пароль:</label>
          <input type="password" id="password" name="password">
        </div>
        <button type="submit">Войти</button>
      </form>
    `);
  });

app.use((req, res) => {
  res.status(404).json({ message: 'Not Found' });
});

app.listen(3000, () => {
  console.log('Server is listening on port 3000');
});
