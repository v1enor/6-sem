var DataTypes = require("sequelize").DataTypes;
var _Client2 = require("./Client2");

function initModels(sequelize) {
  var Client2 = _Client2(sequelize, DataTypes);
  return {
    Client2,
  };
}
module.exports = initModels;
module.exports.initModels = initModels;
module.exports.default = initModels;
