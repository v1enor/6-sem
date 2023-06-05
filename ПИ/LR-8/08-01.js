const express = require('express');
const session = require('express-session');
const passport = require('passport');
const LocalStrategy = require('passport-local').Strategy;
const users = require('./users.json');

const app = express();

// Настройка passport
passport.use(new LocalStrategy(
  function(username, password, done) {
    const user = users.find(user => user.username === username);
    if (!user) {
      return done(null, false);
    }
    if (user.password !== password) {
      return done(null, false);
    }
    return done(null, user);
  }
));

passport.serializeUser((user, done) => {
  done(null, user.id);
});
passport.deserializeUser((id, done) => {
  const user = users.find(user => user.id === id);
  done(null, user);
});

app.use(express.urlencoded({ extended: false }));
app.use(session({
  secret: 'secret',
  resave: false,
  saveUninitialized: false
}));
app.use(passport.initialize());
app.use(passport.session());


app.get('/login', (req, res) => {
  res.send(`
  <style type="text/css">
  * {
      font-family: system-ui, -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif;
      font-size: 18px;
  }

  #container {
      margin: 20px 0 0 10px;
  }

  input {
      border: 1px solid #dbdbdb;
      border-radius: 4px;
      padding: 5px;
  }


</style>
    <h1>Login</h1>
    <form method="post" action="/login">
      <div>
        <label>Username:</label>
        <input type="text" name="username"/>
      </div>
      <div>
        <label>Password:</label>
        <input type="password" name="password"/>
      </div>
      <div>
        <input type="submit" value="Log In"/>
      </div>
    </form>
  `);
});

app.post('/login', passport.authenticate('local', {
  successRedirect: '/profile',
  failureRedirect: '/login'
}));

app.get('/logout', (req, res) => {
  req.session.destroy(function(err) {
    if(err) {
      console.log(err);
    }
    res.redirect('/login');
  });
  
});

app.get('/profile', isAuthenticated, (req, res) => {
  res.send(`
  <style type="text/css">
  * {
      font-family: system-ui, -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif;
      font-size: 18px;
  }
  </style>
    <h1>Profi</style>le</h1>
    <p>привет, ${req.user.username}!</p>
  `);
});

app.use((req, res) => {
  res.status(404).send('404 Not Found');
});

// Запуск сервера
app.listen(3000, () => {
  console.log('Server started on port 3000');
});

// Вспомогательные функции
function isAuthenticated(req, res, next) {
  if (req.isAuthenticated()) {
    return next();
  }
  res.redirect('/login');
}
