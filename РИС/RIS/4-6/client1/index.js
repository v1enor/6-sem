const Sequelize = require('sequelize');
const initModels = require('./models/init-models');
const config = require('./config');
const sequelize = new Sequelize('Client1','User','1234',config.config);
const models = initModels(sequelize);
const express = require('express');
const app = express();
const axios = require('axios');

async function InsertOrUpdate(item, clientId = 1) {
    models.Client1.findOne({where: Sequelize.and({source: item.source}, {clientId: clientId})}).then((result) => {
        if (!result) {
            models.Client1.create(item);
            console.log('added');
        } else {
            models.Client1.update({data: item.data, date: item.date}, {
                where: Sequelize.and({source: item.source}, {clientId: 1})
            });
            console.log("updated");
        }
    }).catch((error) => {
        console.log('error', error);
    });
};

function generateItem() {
    return {data: Math.random() * 1000, source: getRandomSource(), date: new Date().getTime(), clientId: 1};
};

function getRandomSource() {
    const source = ["A", "B", "C", "D", "E", "F", "G", "K", "L", "M", "N", "O", "P"];
    return source.sort(() => Math.random() - 0.5)[0];
};

setInterval(async () => {
    await InsertOrUpdate(generateItem());
}, 2000);

app.get('/data/:id', (req, resp) => {
    models.Client1.findAll({where: {clientId: req.params.id}}).then(items => resp.json(items));
});

setInterval(async () => {
    axios.get("http://192.168.43.195:3000/data/2").then((result) => {
        result.data.forEach((item) => {
            InsertOrUpdate(item, item.clientId);
        })
    }).catch((error) => {
        console.log(error);
    });
}, 10000);

app.listen(3001);