
const turtlesService = require('../Services/turtles-service.js');
const weaponsService = require('../Services/weapons-service.js');
const pizzasService = require('../Services/pizzas-service.js');
const path = require('path');
const multer  = require('multer');
const fs =  require('fs');

const storage =  multer.diskStorage({
  destination: function (req, file, cb) {
    cb(null, 'images/');
  },
  filename: async function (req, file, cb) {
    let turtle = await turtlesService.FindTurtleById(req.body.name);
    if (!turtle) {
        // const err = new Error(`Черепашка с ID ${req.body.name} не найдена`);
        // err.statusCode = 404;
        cb(`Черепашка с ID ${req.body.name} не найдена`);
        return;
    }
    cb(null, req.body.name + path.extname(file.originalname));
    let result = await turtlesService.AddTurtleImage(req.body.name, path.join(__dirname, `../images/${req.body.name + path.extname(file.originalname)}`))
    if(result){
       console.log("Файл добавлен");
    }
  }
});

const upload = multer({ storage: storage });

exports.getTurtleImage = async (req, res) => {
    const id = req.params["turtles_id"];
    const turtle = await turtlesService.FindTurtleById(id);
    if (!turtle) {
      return res.status(404).send('Turtle not found');
    }
    res.sendFile(turtle.turtles_image);
}

exports.uploadImage = upload.single('image');

exports.sendForm = async (req, res) => {
    res.sendFile(path.join(__dirname, '../Pages/index.html'));
}

exports.getPhoto = async (req, res, next) => {
    if(!req.body){
        res.status(404).send(`Тело не найдено`);
        return;
    }
    if (!req.file) {
    return res.status(400).send('Please upload a file');
    }
    res.send('File uploaded successfully');
};

exports.findAllTurtles = async (req, res) => {
    let data = await turtlesService.FindAllTurtles();

    function paginateTurtles(turtles, pageSize, currentPage) {
        const startIndex = (currentPage - 1) * pageSize;
        const endIndex = startIndex + pageSize;
        return turtles.slice(startIndex, endIndex);
    }

    const pageSize = 3;
    const currentPage = req.query.page || 1; 
    const result = paginateTurtles(data, pageSize, currentPage);
 
    res.render('turtles', { result , currentPage, 
        prevPage: Number(currentPage) - 1,
        nextPage: Number(currentPage) + 1  
    });
    //res.send(JSON.stringify(data));
};
 
exports.findTurtleById = async (req, res) => {
    const turtlesId = parseInt(req.params["turtles_id"]);
    if(!Number.isInteger(turtlesId)){
        res.status(404).send(`Id не являетя числом`);
        return;
    }
    let turtle = await turtlesService.FindTurtleById(turtlesId);
     
    if (!turtle) {
        res.status(404).send(`Черепашка с ID ${turtlesId} не найдена`);
        return;
    }
    res.send(JSON.stringify(turtle));
 };
 
 exports.FindTurtlesByFavoritePizza = async (req, res) => {
    if(!req.body){
        res.status(404).send(`Тело не найдено`);
        return;
    }
   const pizzasName = String(req.body.pizzas_name);
   let data = await turtlesService.FindTurtlesByFavoritePizza(pizzasName);
   res.send(JSON.stringify(data));
};

exports.DeleteTurtleWeapon = async (req, res) => {
    if(!req.body){
        res.status(404).send(`Тело не найдено`);
        return;
    }
   const turtles_id = String(req.body.turtles_id);
   let turtle = await turtlesService.FindTurtleById(turtles_id);
   if(!turtle){
       res.status(404).send(`Такой черепашки нет`);
       return;
   }
   let data = await turtlesService.DeleteTurtleWeapon(turtles_id);
   res.send(JSON.stringify(data));
};

exports.DeleteTurtleFavoritePizza = async (req, res) => {
    if(!req.body){
        res.status(404).send(`Тело не найдено`);
        return;
    }
    const turtles_id = String(req.body.turtles_id);
    let turtle = await turtlesService.FindTurtleById(turtles_id);
    if(!turtle){
        res.status(404).send(`Такой черепашки нет`);
        return;
    }

    let data = await turtlesService.DeleteTurtleFirstFavoritePizza(turtles_id);
    res.send(JSON.stringify(data));
};

exports.DeleteTurtleSecondFavoritePizza = async (req, res) => {
    if(!req.body){
        res.status(404).send(`Тело не найдено`);
        return;
    }
    const turtles_id = String(req.body.turtles_id);
    let turtle = await turtlesService.FindTurtleById(turtles_id);
    if(!turtle){
        res.status(404).send(`Такой черепашки нет`);
        return;
    }

    let data = await turtlesService.DeleteTurtleSecondFavoritePizza(turtles_id);
    res.send(JSON.stringify(data));
};


 exports.deleteTurtle = async (req, res) => {
    if(!req.body){
        res.status(404).send(`Тело не найдено`);
        return;
    }
    const turtles_id = String(req.body.turtles_id);

    if(!Number(turtles_id)){
        res.status(404).send(`Не число`);
        return;
    }
    let turtle = await turtlesService.DeleteTurtle(turtles_id);
     
    if (!turtle) {
         res.status(404).send(`Черепашка с ID ${turtles_id} не найдена`);
         return;
       }
     res.send("Черепашка удалена");
 };

 exports.addTurtle = async (req, res) => {
     if(!req.body){
         res.status(404).send(`Тело не найдено`);
         return;
     }
     const turtlesName = req.body.turtles_name;
     const turtlesColor = req.body.turtles_color;
     let turtle;
     if(turtlesName && turtlesColor){
        turtle = await turtlesService.CreateTurtle(turtlesName, turtlesColor);
     }
     else {
         res.status(404).send(`Не верно введены данные`);
         return;
     }
    
     if (!turtle) {
         res.status(404).send(`Черепашка не создана`);
         return;
       }
     res.send(JSON.stringify(turtle));
 };
 
 
 exports.updateTurtle = async (req, res) => {
     if(!req.body){
         res.status(404).send(`Тело не найдено`);
         return;
     }
     const turtlesId = req.body.turtles_id;
     const turtlesName = req.body.turtles_name;
     const turtlesColor = req.body.turtles_color;
     let turtle;
     if(turtlesId && turtlesName && turtlesColor){
          await turtlesService.UpdateTurtle(turtlesId, turtlesName, turtlesColor);
          turtle = await turtlesService.FindTurtleById(turtlesId);
     }
     else {
         res.status(404).send(`Не верно введены данные`);
         return;
     }
    
     if (!turtle) {
         res.status(404).send(`Пицца не обновлена`);
         return;
       }
     res.send(JSON.stringify(turtle));
 };


 exports.AddTurtleWeapon = async (req, res) => {
    if(!req.body){
        res.status(404).send(`Тело не найдено`);
        return;
    }
    const turtles_id = req.body.turtles_id;
    const weapon_id = req.body.weapons_id;
 
   if (isNaN(turtles_id)){
    res.status(404).send(`Такой черепашки нет`);
    return;
   }
   let turtle = await turtlesService.FindTurtleById(turtles_id);
   if(!turtle){
       res.status(404).send(`Такой черепашки нет`);
       return;
   }
   if (isNaN(weapon_id)){
    res.status(404).send(`Такого оружия нет`);
    return;
   }
   let weapon = await weaponsService.FindWeaponById(weapon_id);
   
   if(!weapon){
       res.status(404).send(`Такого оружия нет`);
       return;
   }

   let data = await turtlesService.AddTurtleWeapon(turtles_id,weapon_id);
   res.send(JSON.stringify(data));
};

exports.AddFirstFavoritPizza = async (req, res) => {
    if(!req.body){
        res.status(404).send(`Тело не найдено`);
        return;
    }
    const turtles_id = req.body.turtles_id;
    const pizzas_id = req.body.pizzas_id;
 
   if (isNaN(turtles_id)){
    res.status(404).send(`Такой черепашки нет`);
    return;
   }
   let turtle = await turtlesService.FindTurtleById(pizzas_id);
   if(!turtle){
       res.status(404).send(`Такой черепашки нет`);
       return;
   }
   if (isNaN(pizzas_id)){
    res.status(404).send(`Такой пиццы нет`);
    return;
   }
   let weapon = await pizzasService.FindPizzaById(pizzas_id);
   
   if(!weapon){
       res.status(404).send(`Такой пиццы нет`);
       return;
   }

   let data = await turtlesService.AddTurtleFirstFavoritePizza(turtles_id,pizzas_id);
   res.send(JSON.stringify(data));
};

exports.AddSecondFavoritePizza = async (req, res) => {
    if(!req.body){
        res.status(404).send(`Тело не найдено`);
        return;
    }
    const turtles_id = req.body.turtles_id;
    const pizzas_id = req.body.pizzas_id;
    
    if (isNaN(turtles_id)){
    res.status(404).send(`Такой черепашки нет`);
    return;
    }
    let turtle = await turtlesService.FindTurtleById(pizzas_id);
    if(!turtle){
        res.status(404).send(`Такой черепашки нет`);
        return;
    }
    if (isNaN(pizzas_id)){
    res.status(404).send(`Такой пиццы нет`);
    return;
    }
    let weapon = await pizzasService.FindPizzaById(pizzas_id);
    
    if(!weapon){
        res.status(404).send(`Такой пиццы нет`);
        return;
    }

    let data = await turtlesService.AddTurtleSecondFavoritePizza(turtles_id,pizzas_id);
    res.send(JSON.stringify(data));
};