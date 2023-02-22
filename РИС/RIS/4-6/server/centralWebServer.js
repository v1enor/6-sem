const express = require('express');
const bodyParse = require('body-parser');
const axios = require('axios');
const app = express();

const Sequelize = require('sequelize');
const initModels = require('./models/init-models');
const config = require('./config');
const sequelize = new Sequelize('WebServer','User','123',config.config);
const models = initModels(sequelize);

app.use(bodyParse.json());

app.get('/time', async (req, resp) => {
    let time = new Date().toISOString();
    console.log('/time', time);
    resp.send(JSON.stringify(time));
});

app.get('/avaliable', async (req, resp) => {
    Check('http://192.168.0.111', 3001);
    Check('http://192.168.0.111', 3002);
});

app.listen(8000, () => {
    console.log('server listening port 8000');
});


function Check(host, port) {
    let url = `${host}:${port}`;
    axios.get(`${url}`).then(() => {
        console.log(`${url} is avaliable`);
    }).catch((error) => {
        console.log(`${url}:${error.text()}`)
    });
};