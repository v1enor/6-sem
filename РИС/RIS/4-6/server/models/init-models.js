var DataTypes = require("sequelize").DataTypes;
var _Records = require("./Records");

function initModels(sequelize) {
  var Records = _Records(sequelize, DataTypes);
  return {
    Records,
  };
}
module.exports = initModels;
module.exports.initModels = initModels;
module.exports.default = initModels;
