const express = require('express');
const pizzasController = require('../Controllers/pizzasController');

const pizzasRouter = express.Router();
const Jsonpars = express.json();

pizzasRouter.put('/pizzas',Jsonpars, pizzasController.updatePizza);
pizzasRouter.delete('/pizzas/:pizzas_id', pizzasController.deletePizza);
pizzasRouter.get('/pizzas', pizzasController.findAllPizzas);
pizzasRouter.get('/pizzas/calories', pizzasController.findPizzasByCalories);
pizzasRouter.get('/pizzas/:pizzas_id', pizzasController.findPizzasById);
pizzasRouter.post('/pizzas',Jsonpars, pizzasController.addPizza);

module.exports = pizzasRouter;