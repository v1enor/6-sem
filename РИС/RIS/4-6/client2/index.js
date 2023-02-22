const Sequelize = require('sequelize');
const initModels = require('./models/init-models');
const config = require('./config');
const sequelize = new Sequelize('Client2','User','1234',config.config);
const models = initModels(sequelize);
const express = require('express');
const app = express();
const axios = require('axios');

async function InsertOrUpdate(item, clientId = 2) {
    models.Client2.findOne({where: Sequelize.and({source: item.source}, {clientId: clientId})}).then((result) => {
        if (!result) {
            models.Client2.create(item);
            console.log('added');
        } else {
            models.Client2.update({data: item.data, date: item.date}, {
                where: Sequelize.and({source: item.source}, {clientId: clientId})
            });
            console.log("updated");
        }
    }).catch((error) => {
        console.log('error', error);
    });
};

function generateItem() {
    return {data: Math.random() * 1000, source: getRandomSource(), date: new Date().getTime(), clientId: 2};
};

function getRandomSource() {
    const source = ["A", "B", "C", "D", "E", "F", "G", "K", "L", "M", "N", "O", "P"];
    return source.sort(() => Math.random() - 0.5)[0];
};

setInterval(async () => {
    await InsertOrUpdate(generateItem());
}, 2000);


app.get('/data/:id', (req, resp) => {
    models.Client2.findAll({where: {clientId: req.params.id}}).then(items => resp.json(items));
});

setInterval(async () => {
    await axios.get("http://192.168.43.195:3000/data/1").then((result) => {
        result.data.forEach((item) => {
            InsertOrUpdate(item, item.clientId);
        })}).catch((error) => {
            console.log(error);
        });
}, 12000);


app.listen(3002);

