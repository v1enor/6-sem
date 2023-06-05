const express = require('express');
const weaponsController = require('../Controllers/weaponsController.js');

const weaponsRouter = express.Router();
const Jsonpars = express.json();

weaponsRouter.put('/weapons',Jsonpars, weaponsController.updateWeapon);
weaponsRouter.delete('/weapons/:weapons_id', weaponsController.deleteWeapon);
weaponsRouter.get('/weapons', weaponsController.findAllWeapons);
weaponsRouter.get('/weapons/dps', weaponsController.findWeaponsByDPS);
weaponsRouter.get('/weapons/:weapons_id', weaponsController.findWeaponsById);
weaponsRouter.post('/weapons',Jsonpars, weaponsController.addWeapon);

module.exports = weaponsRouter;
