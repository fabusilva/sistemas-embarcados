const mqtt = require('mqtt');
const fs = require('fs');

const protocol = 'mqtts';
const host = 'ncece09e.ala.us-east-1.emqxsl.com';
const port = '8883';
const clientId = `mqtt_${Math.random().toString(16).slice(3)}`;

const connectUrl = `${protocol}://${host}:${port}`;

const client = mqtt.connect(connectUrl, {
  clientId,
  clean: true,
  connectTimeout: 4000,
  username: 'DQWh93C9E8xhJzn',
  password: 'DQWh93C9E8xhJzn',
  reconnectPeriod: 1000,

  ca: fs.readFileSync('./emqxsl-ca.crt'),
});

module.exports = client;
