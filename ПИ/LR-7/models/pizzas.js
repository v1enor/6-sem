
const db = require('../db.js');
const { DataTypes } = require('sequelize')

const Pizzas = db.define('pizzas',
  {
    pizzas_id: {
      type: DataTypes.INTEGER,
      primaryKey: true,
      autoIncrement: true,
      allowNull: false
    },
    pizzas_name: {
      type: DataTypes.STRING,
      allowNull: false
    },
    pizzas_calories: {
      type: DataTypes.INTEGER,
      allowNull: false
    },
    pizzas_description: {
      type:  DataTypes.STRING,
      allowNull: true
    }
  },
  {
    timestamps: false
  }
)

module.exports = Pizzas;



























// const { DataTypes } = require('sequelize')
// const db = require('../db.js')


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

// module.exports =  Pizzas;