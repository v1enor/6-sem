const Turtles = require('../models/turtles.js');
const Pizzas = require('../models/pizzas.js');
const { Op } = require("sequelize");

async function  FindAllTurtles() { 
  return await Turtles.findAll();
}

async function  FindTurtleById(id) { 
  return await Turtles.findOne({
    where: {
        turtles_id: id
    }
  })
}

async function  CreateTurtle(turtlesName, turtlesColor) { 
  return await Turtles.create({
    turtles_name: turtlesName,
    turtles_color: turtlesColor
  })
}

async function  UpdateTurtle(id, turtlesName, turtlesColor) { 
  return await Turtles.update({ 
    turtles_name: turtlesName, 
    turtles_color: turtlesColor }, {
    where: {
        turtles_id: id
    }
  })
}

async function  DeleteTurtle(id) { 
  return await Turtles.destroy({
    where: {
        turtles_id: id
    }
  })
}

async function  FindTurtlesByFavoritePizza(pizzasName) { 
  
    const pizzas = await Pizzas.findOne({
        where: { pizzas_name: pizzasName },
    });
    
    return await Turtles.findAll({
        where: { 
            [Op.or]: [
            {turtles_favoritepizzaid: pizzas.pizzas_id},
            {turtles_secondfavoritepizzaid: pizzas.pizzas_id}
            ]
        }
    });
}

async function  AddTurtleImage(turtleId, image) { 
  const turtle = await Turtles.findByPk(turtleId);
  return await turtle.update({ turtles_image: image });
}

async function  AddTurtleWeapon(turtleId, weaponID) { 
    const turtle = await Turtles.findByPk(turtleId);
    return await turtle.update({ turtles_weaponid: weaponID });
}

async function  DeleteTurtleWeapon(turtleId) { 
  const turtle = await Turtles.findByPk(turtleId);
  return await turtle.update({ turtles_weaponid: null });
}

async function  DeleteTurtleFirstFavoritePizza(turtleId) { 
    const turtle = await Turtles.findByPk(turtleId);
    return await turtle.update({ turtles_favoritepizzaid: null });
}

async function  AddTurtleFirstFavoritePizza(turtleId, firstFavoritePizzaId) { 
    const turtle = await Turtles.findByPk(turtleId);
    return await turtle.update({ turtles_favoritepizzaid: firstFavoritePizzaId });
}

async function  DeleteTurtleSecondFavoritePizza(turtleId) { 
    const turtle = await Turtles.findByPk(turtleId);
    return await turtle.update({ turtles_secondfavoritepizzaid: null });
}

async function  AddTurtleSecondFavoritePizza(turtleId, secondFavoritePizzaId) { 
    const turtle = await Turtles.findByPk(turtleId);
    return await turtle.update({ turtles_secondfavoritepizzaid: secondFavoritePizzaId });
}

module.exports = { CreateTurtle, FindAllTurtles, AddTurtleWeapon, AddTurtleImage,  AddTurtleFirstFavoritePizza, AddTurtleSecondFavoritePizza, FindTurtleById,  FindTurtlesByFavoritePizza, DeleteTurtleWeapon , DeleteTurtleFirstFavoritePizza, DeleteTurtleSecondFavoritePizza, DeleteTurtle, UpdateTurtle }

