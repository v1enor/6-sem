const db = require('../db.js');
const { DataTypes } = require('sequelize')


const Turtles = db.define('turtles',
  {
    turtles_id: {
      type: DataTypes.INTEGER,
      primaryKey: true,
      autoIncrement: true,
      allowNull: false
    },
    turtles_name: {
      type: DataTypes.STRING,
      allowNull: false
    },
    turtles_color: {
      type: DataTypes.STRING,
      allowNull: false
    },
    // turtles_weaponId: {
    //   type: DataTypes.INTEGER,
    //   allowNull: false
    // },
  
    // turtles_favoritePizzaId: {
    // type: DataTypes.INTEGER,
    // allowNull: false
    // },
    // turtles_secondFavoritePizzaId: {
    // type: DataTypes.INTEGER,
    // allowNull: false
    // },
    turtles_image: {
    type: DataTypes.STRING,
    allowNull: true
    }
  },
  {
    timestamps: false
  }
)

// Pizzas.hasMany(Turtles,{
//   foreignKey: {
//     name: 'turtles_favoritepizzaid', 
//     allowNull: true
//   }
// });
// Pizzas.hasMany(Turtles, { foreignKey: 'turtles_secondfavoritepizzaid' });
// Weapons.hasMany(Turtles, { foreignKey: 'turtles_weaponid' });

// const Pizzas = require('./models/pizzas.js');
// const Weapons = require('./models/weapons.js');
// const Turtles = require('./models/turtles.js');

// let turtles = db.model('Turtles');
// let Pizzas = db.model('Pizzas');
// let Weapons = db.model('Weapons');

// Pizzas.hasMany(turtles, { foreignKey: 'firstFavoritePizza' });
// Pizzas.hasMany(turtles, { foreignKey: 'secondFavoritePizza' });
// Weapons.hasMany(turtles);

 
module.exports = Turtles;








































// const { DataTypes } = require('sequelize')
// const db = require('../db.js')

// // const Pizzas  = require('./pizzas.js');
// // const  Weapon  = require('./weapons.js');

// const Turtles = db.define('turtles',
//   {
//     turtles_id: {
//       type: DataTypes.INTEGER,
//       primaryKey: true,
//       autoIncrement: true,
//       allowNull: false
//     },
//     turtles_name: {
//       type: DataTypes.STRING,
//       allowNull: false
//     },
//     turtles_color: {
//       type: DataTypes.STRING,
//       allowNull: false
//     },
//     turtles_weaponId: {
//       type: DataTypes.INTEGER,
//       allowNull: false,
//       references: {
//         // This is a reference to another model
//         model: db.model.Weapon,
//         // This is the column name of the referenced model
//         key: 'weapons_id',
//         // With PostgreSQL, it is optionally possible to declare when to check the foreign key constraint, passing the Deferrable type.
//         deferrable: Deferrable.INITIALLY_IMMEDIATE
//         // Options:
//         // - `Deferrable.INITIALLY_IMMEDIATE` - Immediately check the foreign key constraints
//         // - `Deferrable.INITIALLY_DEFERRED` - Defer all foreign key constraint check to the end of a transaction
//         // - `Deferrable.NOT` - Don't defer the checks at all (default) - This won't allow you to dynamically change the rule in a transaction
//       }
//     },
  
//     turtles_favoritePizzaId: {
//     type: DataTypes.INTEGER,
//     allowNull: false
//     },
//     turtles_secondFavoritePizzaId: {
//     type: DataTypes.INTEGER,
//     allowNull: false
//     },
//     turtles_image: {
//     type: DataTypes.STRING,
//     allowNull: false
//     }
//   },
//   {
//     timestamps: false
//   }
// )
// const Pizzas = db.define('pizzas',
//   {
//     pizzas_id: {
//       type: DataTypes.INTEGER,
//       primaryKey: true,
//       autoIncrement: true,
//       allowNull: false
//     },
//     pizzas_name: {
//       type: DataTypes.STRING,
//       allowNull: false
//     },
//     pizzas_calories: {
//       type: DataTypes.INTEGER,
//       allowNull: false
//     }
//   },
//   {
//     timestamps: false
//   }
// )

// //cars.belongsTo(Pizzas, { as: 'fk_favoritePizzaId_turtles', foreignKey: 'turtles_favoritePizzaId' });
 
// // console.log(Pizzas);
// // Turtles.belongsTo(Pizzas, { as: 'fk_favoritePizzaId_turtles', foreignKey: 'turtles_favoritePizzaId' });
// // Turtles.belongsTo(Pizzas, { as: 'fk_secondFavoritePizzaId_turtles', foreignKey: 'turtles_secondFavoritePizzaId' });

// Pizzas.hasMany(Turtles);
// // Pizzas.hasMany(Turtles, { foreignKey: 'firstFavoritePizza' });
// // Pizzas.hasMany(Turtles, { foreignKey: 'secondFavoritePizza' });


// // Turtles.belongsTo(Weapon, { as: 'fk_weaponId_turtles', foreignKey: 'turtles_weaponId' });
// // Weapon.hasMany(Turtles, { foreignKey: 'turtles_weaponId' });



// module.exports = Turtles;


