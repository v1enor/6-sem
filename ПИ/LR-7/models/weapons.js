
const db = require('../db.js');
const { DataTypes } = require('sequelize')

const Weapons = db.define('weapons',
  {
    weapons_id: {
      type: DataTypes.INTEGER,
      primaryKey: true,
      autoIncrement: true,
      allowNull: false
    },
    weapons_name: {
      type: DataTypes.STRING,
      allowNull: false
    },
    weapons_dps: {
      type: DataTypes.INTEGER,
      allowNull: false
    }
  },
  {
    timestamps: false
  }
)

module.exports = Weapons;



















// const { DataTypes } = require('sequelize')
// const db = require('../db.js')




// const Weapons = db.define('weapons',
//   {
//     weapons_id: {
//       type: DataTypes.INTEGER,
//       primaryKey: true,
//       autoIncrement: true,
//       allowNull: false
//     },
//     weapons_name: {
//       type: DataTypes.STRING,
//       allowNull: false
//     },
//     weapons_dps: {
//       type: DataTypes.INTEGER,
//       allowNull: false
//     }
//   },
//   {
//     timestamps: false
//   }
// )


// module.exports = Weapons;