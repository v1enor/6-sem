const Weapons = require('../models/weapons.js');
const { Op } = require("sequelize");

async function  FindAllWeapons() { 
  return await Weapons.findAll();
}

async function  FindWeaponById(id) { 
  return await Weapons.findOne({
    where: {
        weapons_id: id
    }
  })
}

async function  FindHighDPSWeapons(m) { 
  return await Weapons.findAll({
    where: {
        weapons_dps: {
        [Op.gt]: m,     
      }
    }
  })
}

async function  FindLowDPSWeapons(m) { 
  return await Weapons.findAll({
    where: {
        weapons_dps: {
        [Op.lt]: m,     
      }
    }
  })
}

async function  CreateWeapons(weaponsName, weaponsDPS) { 
  return await Weapons.create({
    weapons_name: weaponsName,
    weapons_dps: weaponsDPS
  })
}

async function  UpdateWeapons(id, weaponsName, weaponsDPS) { 
  return await Weapons.update({ 
    weapons_name: weaponsName, 
    weapons_dps: weaponsDPS }, {
    where: {
        weapons_id: id
    }
  })
}

async function  DeleteWeapons(id) { 
  return await Weapons.destroy({
    where: {
      weapons_id: id
    }
  })
}

module.exports = { FindAllWeapons, FindWeaponById, FindHighDPSWeapons, FindLowDPSWeapons, CreateWeapons, UpdateWeapons, DeleteWeapons}