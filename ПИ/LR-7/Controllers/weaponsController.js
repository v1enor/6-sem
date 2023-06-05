const weaponsService = require('../Services/weapons-service.js');

exports.findAllWeapons = async (req, res) => {
   let data = await weaponsService.FindAllWeapons();
   res.send(JSON.stringify(data));
};

exports.findWeaponsById = async (req, res) => {
    const weaponsId = parseInt(req.params["weapons_id"]);
    if(!Number.isInteger(weaponsId)){
        res.status(404).send(`Id не являетя числом`);
        return;
    }
    let weapon = await weaponsService.FindWeaponById(weaponsId);
    
    if (!weapon) {
        res.status(404).send(`Оружие с ID ${weaponsId} не найдено!`);
        return;
      }
    res.send(JSON.stringify(weapon));
};

exports.findWeaponsByDPS = async (req, res) => {
    
    const gtDPS = parseInt(req.query.gt);
    const ltDPS = parseInt(req.query.lt);
    
    let  filteredWeapons;
        if (gtDPS) {
            filteredWeapons = await weaponsService.FindHighDPSWeapons(gtDPS);
        } else if (ltDPS) {   
            filteredWeapons = await weaponsService.FindLowDPSWeapons(ltDPS);
        }
    if (!filteredWeapons) {
        res.status(404).send(`Оружие не найдено!`);
        return;
    }

    res.send(JSON.stringify(filteredWeapons));
};

exports.addWeapon = async (req, res) => {
    if(!req.body){
        res.status(404).send(`Тело не найдено`);
    }
    const weaponName = req.body.weapons_name;
    const weapoonDPS = req.body.weapons_dps;
    let weapon;
    if(weapoonDPS < 500 && weaponName && weapoonDPS ){
        weapon = await weaponsService.CreateWeapons(weaponName, weapoonDPS);
    }
    else {
        res.status(404).send(`Неверно введены данные`);
        return;
    }
   
    if (!weapon) {
        res.status(404).send(`Оружие не создана`);
        return;
      }
    res.send(JSON.stringify(weapon));
};

exports.updateWeapon = async (req, res) => {
    if(!req.body){
        res.status(404).send(`Тело не найдено`);
    }
    const weaponsId = req.body.weapons_id;
    const weaponsName = req.body.weapons_name;
    const weaponsDPS = req.body.weapons_dps;
    let weapons;
    if(weaponsDPS < 500 && weaponsName && weaponsDPS && weaponsId){
         await weaponsService.UpdateWeapons(weaponsId, weaponsName, weaponsDPS);
         weapons = await weaponsService.FindWeaponById(weaponsId);
    }
    else {
        res.status(404).send(`Не верно введены данные`);
        return;
    }
   
    if (!weapons) {
        res.status(404).send(`Оружие не обновлено!`);
        return;
      }
    res.send(JSON.stringify(weapons));
};

exports.deleteWeapon = async (req, res) => {
    const weaponId = parseInt(req.params["weapons_id"]);
    if(!Number.isInteger(weaponId)){
        res.status(404).send(`Id не являетя числом`);
        return;
    }
    let weapon = await weaponsService.DeleteWeapons(weaponId);
    
    if (!weapon) {
        res.status(404).send(`Оружие с ID ${weaponId} не найдена`);
        return;
      }
    res.send("Оружие удалено!");
};