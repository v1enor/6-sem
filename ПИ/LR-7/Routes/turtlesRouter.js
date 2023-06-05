const express = require('express');
const turtlesController = require('../Controllers/turtlesController.js');

const turtlesRouter = express.Router();
const Jsonpars = express.json();

turtlesRouter.get('/turtles/upload',  turtlesController.sendForm);
turtlesRouter.post('/turtles/upload', Jsonpars, turtlesController.uploadImage, turtlesController.getPhoto);

turtlesRouter.put('/turtles/',Jsonpars, turtlesController.updateTurtle);
turtlesRouter.put('/turtles/favoritePizzaBind',Jsonpars, turtlesController.AddFirstFavoritPizza); 
turtlesRouter.put('/turtles/secondFavoritePizzaBind',Jsonpars, turtlesController.AddSecondFavoritePizza); 
turtlesRouter.put('/turtles/weaponBind',Jsonpars, turtlesController.AddTurtleWeapon);  
turtlesRouter.delete('/turtles', Jsonpars, turtlesController.deleteTurtle);
turtlesRouter.delete('/turtles/weaponUnbind', Jsonpars, turtlesController.DeleteTurtleWeapon);
turtlesRouter.delete('/turtles/favoritePizzaUnbind', Jsonpars, turtlesController.DeleteTurtleFavoritePizza);
turtlesRouter.delete('/turtles/secondFavoritePizzaUnbind', Jsonpars, turtlesController.DeleteTurtleSecondFavoritePizza);
turtlesRouter.get('/turtles', turtlesController.findAllTurtles);

turtlesRouter.get('/turtles/images/:turtles_id', turtlesController.getTurtleImage);

turtlesRouter.get('/turtles/favoritePizza',Jsonpars, turtlesController.FindTurtlesByFavoritePizza);
turtlesRouter.get('/turtles/:turtles_id', turtlesController.findTurtleById);
turtlesRouter.post('/turtles',Jsonpars, turtlesController.addTurtle);

module.exports = turtlesRouter;