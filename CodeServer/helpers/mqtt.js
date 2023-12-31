var mqtt = require('mqtt');
var config = require('../config/config')
const { addData } = require("../controllers/controller");
var client = mqtt.connect('mqtt://' + config.mqtt_host + ":" + config.mqttPort, {
    clientId: 'Server_Client',
    username: config.user_name,
    password: config.password,
    reconnectPeriod: 1000,
    keepalive: 300,
    clean: false,
});
module.exports = function (io) {
    client.on('connect', function () {
        console.log("Connect mqtt successful!")
        client.subscribe('Status/#', {qos: 1});
    });
    client.on('message', function (topic, message) {
        switch (topic) {
            case 'Status/Connected':
                console.log("Connected: " + message.toString());
                io.sockets.emit('Esp-connected', message.toString());
                break;
            case 'Status/Disconnected':
                let date_ob = new Date();
                // current date
                // adjust 0 before single digit date
                let date = ("0" + date_ob.getDate()).slice(-2);
                // current month
                let month = ("0" + (date_ob.getMonth() + 1)).slice(-2);
                // current year
                let year = date_ob.getFullYear();
                // current hours
                let hours = date_ob.getHours();
                // current minutes
                let minutes = date_ob.getMinutes();
                // current seconds
                let seconds = date_ob.getSeconds();
                console.log("Disconnect: "+ message.toString() + " "+ year + "-" + month + "-" + date + " " + hours + ":" + minutes + ":" + seconds);
                io.sockets.emit('Esp-disconnected', message.toString());
                break;
            case 'Status/Env':
                console.log("Environment: " + message.toString());
                data = JSON.parse(message.toString());
                if (data.error == 0)
                addData(data);
                io.sockets.emit('Environment-update', message.toString());
                break;
        }
    });
    return exports;
}
