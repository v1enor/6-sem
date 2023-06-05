const Pizzas = require('../models/pizzas.js');
const { Op } = require("sequelize");

const db = require("../db.js");

// транзакция
async function CheckTran() {
await db.transaction(async (t) => {
  try {
  const pizzas = await Pizzas.findAll({ where: 
    { pizzas_calories: { [Op.gt]: 1500 } }, transaction: t 
  });

  await Promise.all(pizzas.map((pizza) => {
    pizza.pizzas_description = " SUPER FAT!";
    return pizza.save({ transaction: t });
  }));
  } catch (err) {
    await t.rollback();
    console.error(err);
  }
});
}
// CheckTran(); 

async function  FindAllPizzas() { 
  return await Pizzas.findAll();
}

async function  FindPizzaById(id) { 
  return await Pizzas.findOne({
    where: {
      pizzas_id: id
    }
  })
}

async function  FindHighCaloriePizza(m) { 
  return await Pizzas.findAll({
    where: {
      pizzas_calories: {
        [Op.gt]: m,     
      }
    }
  })
}

async function  FindLowCaloriePizza(m) { 
  return await Pizzas.findAll({
    where: {
      pizzas_calories: {
        [Op.lt]: m,     
      }
    }
  })
}

async function  CreatePizza(pizzasName, pizzasCalories) { 
  return await Pizzas.create({
    pizzas_name: pizzasName,
    pizzas_calories: pizzasCalories
  })
}

async function  UpdatePizza(id, pizzasName, pizzasCalories) { 
  return await Pizzas.update({ 
    pizzas_name: pizzasName, 
    pizzas_calories: pizzasCalories }, {
    where: {
      pizzas_id: id
    }
  })
}

async function  DeletePizza(id) { 
  return await Pizzas.destroy({
    where: {
      pizzas_id: id
    }
  })
}

module.exports = { FindAllPizzas, FindPizzaById, FindHighCaloriePizza, CreatePizza, UpdatePizza, DeletePizza, FindLowCaloriePizza}

