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

const topic = 'Teste';
const payload = 'Testando 1,2,3... Testando'

client.on('connect', () => {
  console.log('Conectado!');

  client.subscribe([topic], () => {
    console.log(`Subscribe to topic '${topic}'`);
  });

  client.publish(topic, payload, { qos: 0, retain: false }, (error) => {
    if (error) {
      console.error(error)
    }
  });
});

client.on('message', (topic, payload) => {
  console.log('Received Message:', topic, payload.toString())
});

  