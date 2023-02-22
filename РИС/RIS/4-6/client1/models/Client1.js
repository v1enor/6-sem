const Sequelize = require('sequelize');
module.exports = function (sequelize, DataTypes) {
    return sequelize.define('Client1', {
        id: {
            type: DataTypes.INTEGER,
            allowNull: true,
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
        tableName: 'Client1',
        schema: 'dbo',
        timestamps: false
    });
};
