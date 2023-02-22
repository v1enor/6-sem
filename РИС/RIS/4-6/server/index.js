const Sequelize = require('sequelize');
const initModels = require('./models/init-models');
const config = require('./config');
const sequelize = new Sequelize('WebServer','User','123',config.config);
const models = initModels(sequelize);
const axios = require('axios');
const express = require('express');
const app = express();

setInterval(async () => {
    axios.get("http://192.168.0.111:3001/data/1").then((data) => {
        let items = data.data;
        items.forEach((item) => {
            InsertOrUpdate(item);
        })
    }).catch((error) => {
        console.log(error);
    });

    axios.get("http://192.168.0.111:3002/data/2").then((data) => {
        let items = data.data;
        items.forEach((item) => {
            InsertOrUpdate(item);
        })
    }).catch((error) => {
        console.log(error);
    });
}, 8000);

async function InsertOrUpdate(item) {
    models.Records.findOne({where: Sequelize.and({source: item.source}, {clientId: item.clientId})}).then((result) => {
        if (!result) {
            models.Records.create(item);
            console.log('added');
        } else {
            models.Records.update({data: item.data, date: item.date}, {
                where: Sequelize.and({source: item.source}, {clientId: item.clientId})
            });
            console.log("updated");
        }
    }).catch((error) => {
        console.log('error', error);
    });
};

app.get("/data/:id", (req, resp) => {
    console.log(req.params.id)
    models.Records.findAll({where: {clientId: req.params.id}, raw:true}).then(result => resp.json(result));
});

app.listen(3000);