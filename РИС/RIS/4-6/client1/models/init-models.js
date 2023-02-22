var DataTypes = require("sequelize").DataTypes;
var _Client1 = require("./Client1");

function initModels(sequelize) {
  var Client1 = _Client1(sequelize, DataTypes);


  return {
    Client1,
  };
}
module.exports = initModels;
module.exports.initModels = initModels;
module.exports.default = initModels;
