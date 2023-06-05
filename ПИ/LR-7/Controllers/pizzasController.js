const pizzasService = require('../Services/pizzas-service');

exports.findAllPizzas = async (req, res) => {
   let data = await pizzasService.FindAllPizzas();
   console.log(data);
   //res.render('turtles', { data });
   res.send(JSON.stringify(data));
};

exports.findPizzasById = async (req, res) => {
    const pizzasId = parseInt(req.params["pizzas_id"]);
    if(!Number.isInteger(pizzasId)){
        res.status(404).send(`Id не являетя числом`);
        return;
    }
    let pizza = await pizzasService.FindPizzaById(pizzasId);
    
    if (!pizza) {
        res.status(404).send(`Пицца с ID ${pizzasId} не найдена`);
        return;
      }
    res.send(JSON.stringify(pizza));
};

exports.findPizzasByCalories = async (req, res) => {
    
    const gtCalories = parseInt(req.query.gt);
    const ltCalories = parseInt(req.query.lt);
    
    let  filteredPizzas;
        if (gtCalories) {
          filteredPizzas = await pizzasService.FindHighCaloriePizza(gtCalories);
        } else if (ltCalories) {   
          filteredPizzas = await pizzasService.FindLowCaloriePizza(ltCalories);
        }
    
    if (!filteredPizzas) {
        res.status(404).send(`Пиццы не найдены`);
        return;
    }

    res.send(JSON.stringify(filteredPizzas));
};

exports.addPizza = async (req, res) => {
    if(!req.body){
        res.status(404).send(`Тело не найдено`);
    }
    const pizzasName = req.body.pizzas_name;
    const pizzasCalories = req.body.pizzas_calories;
    let pizza;
    if(pizzasCalories < 2000 && pizzasName && pizzasCalories ){
        pizza = await pizzasService.CreatePizza(pizzasName, pizzasCalories);
    }
    else {
        res.status(404).send(`Не верно введены данные`);
        return;
    }
   
    if (!pizza) {
        res.status(404).send(`Пицца не создана`);
        return;
      }
    res.send(JSON.stringify(pizza));
};


exports.updatePizza = async (req, res) => {
    if(!req.body){
        res.status(404).send(`Тело не найдено`);
    }
    const pizzasId = req.body.pizzas_id;
    const pizzasName = req.body.pizzas_name;
    const pizzasCalories = req.body.pizzas_calories;
    let pizza;
    if(pizzasCalories < 2000 && pizzasName && pizzasCalories && pizzasId){
         await pizzasService.UpdatePizza(pizzasId, pizzasName, pizzasCalories);
         pizza = await pizzasService.FindPizzaById(pizzasId);
    }
    else {
        res.status(404).send(`Не верно введены данные`);
        return;
    }
   
    if (!pizza) {
        res.status(404).send(`Пицца не обновлена`);
        return;
      }
    res.send(JSON.stringify(pizza));
};


exports.deletePizza = async (req, res) => {
    const pizzasId = parseInt(req.params["pizzas_id"]);
    if(!Number.isInteger(pizzasId)){
        res.status(404).send(`Id не являетя числом`);
        return;
    }
    let pizza = await pizzasService.DeletePizza(pizzasId);
    
    if (!pizza) {
        res.status(404).send(`Пицца с ID ${pizzasId} не найдена`);
        return;
      }
    res.send("Пицца удалена");
};
