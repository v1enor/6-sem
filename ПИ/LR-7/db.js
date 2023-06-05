const Sequilize = require('sequelize')

const db = new Sequilize('Laba7', 'postgres', '11', {
  host: 'localhost',
  dialect: 'postgres',
  pool: {
    max: 5,
    min: 0,
    acquire: 3000,
    idle: 10000
  }
})

module.exports = db;