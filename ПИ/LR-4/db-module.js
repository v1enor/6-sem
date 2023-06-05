var http = require('http');
var url = require('url');
var util = require('util');
var ee = require('events');
console.log('imported db-module');


let db = 
[
    {
        id: 1,
        name: "illa",
        bday: "02-08-2002"
    },
    {
        id: 2,
        name: "vad",
        bday: "44-19-1002"
    },
];





function DB()
{
    this.select = () => 
    {
        console.log("[SELECT]\n");
        return JSON.stringify(db, null, 2);
    }


    this.insert = (insertString) => 
    {
        for (let i = 0; i < db.length; ++i)
            if (JSON.parse(insertString).id == db[i].id) { return; }
        db.push(JSON.parse(insertString));
        console.log("[INSERT]\n");
        return JSON.stringify(db, null, 2);
    }


    this.update = (updateString) => 
    {
        console.log("[UPDATE]");
        var jsonString = JSON.parse(updateString);
        console.log(jsonString);
        var id = jsonString.id;
        console.log("id to update: " + id + "\n");
        var index = db.findIndex(elem => elem.id === parseInt(id));
        db[index].name = jsonString.name;
        db[index].bday = jsonString.bday;
        return JSON.stringify(db[index], null, 2);
    }


    this.delete = (id) => 
    {
        console.log("[DELETE]\n");
        var index = db.findIndex(elem => elem.id === parseInt(id));
        var deleted = db[index];
        db.splice(index, 1);
        return JSON.stringify(deleted, null, 2);
    }
} 


util.inherits(DB, ee.EventEmitter);
exports.DB = DB;