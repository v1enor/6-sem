const Sequelize = require('sequelize');
module.exports = function(sequelize, DataTypes) {
  return sequelize.define('Records', {
    id: {
      type: DataTypes.INTEGER,
      allowNull: false,
      primaryKey: true,
      autoIncrement: true
    },
    data: {
      type: DataTypes.INTEGER,
      allowNull: true
    },
    source: {
      type: DataTypes.STRING(1),
      allowNull: true
    },
    date: {
      type: DataTypes.DATE,
      allowNull: true
    },
    clientId: {
      type: DataTypes.INTEGER,
      allowNull: true
    }
  }, {
    sequelize,
    tableName: 'Records',
    schema: 'dbo',
    timestamps: false
  });
};
