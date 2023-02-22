config = {
    database: 'client1',
    host: '192.168.43.195',
    user:'User',
    password:'1234',
    logging:false,
    trustServerCertificate: true,
    dialect: 'mssql',
    dialectOptions: {
        useUTC: false,
        dateFirst: 1,
    },
    pool: {
        max: 5,
        min: 0,
        idle: 10000
    }
}

exports.config = config;