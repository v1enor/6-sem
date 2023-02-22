config = {
    database: 'WebServer',
    user:'User',
    password:'123',
    host: '192.168.0.108',
    dialect: 'mssql',
    pool: {
        max: 5,
        min: 0,
        idle: 10000
    }
}

exports.config = config;