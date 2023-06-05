const Express = require('express');
const exphds = require("express-handlebars");
const bodyParser = require('body-parser');
const db = require('./db.js');
const PORT = 3000;
const app = Express();

//app.use(app.static(__dirname + "/images"));
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

const pizzasRouter = require("./Routes/pizzasRouter.js");
const weaponsRouter = require("./Routes/weaponsRouter.js");
const turtlesRouter = require("./Routes/turtlesRouter.js");

app.use('/api', pizzasRouter);
app.use('/api', weaponsRouter);
app.use('/api', turtlesRouter);


const Pizzas = require('./models/pizzas.js');
const Weapons = require('./models/weapons.js');
const Turtles = require('./models/turtles.js');

Pizzas.hasMany(Turtles,{
    foreignKey: {
      name: 'turtles_favoritepizzaid', 
      allowNull: true
    }
});

Pizzas.hasMany(Turtles, { foreignKey: 'turtles_secondfavoritepizzaid' });
Weapons.hasMany(Turtles, { foreignKey: 'turtles_weaponid' });

const hbs = exphds.create({
  defaultLayout: "main",
  extname: "hbs"
});

app.engine('hbs', hbs.engine);
app.set('view engine', 'hbs');
app.set("views","views");

app.listen(PORT,'127.0.0.1', ()=> {
    console.log('Сервер запущен!');
})

db.sync({ force: true }).then(result=>{
    //console.log(result);
})

//db.authenticate().catch(error => console.error(error))