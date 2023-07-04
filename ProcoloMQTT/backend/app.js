const express = require('express');
const client = require('./Connection/mqttConnection');
const cors = require("cors");
const topic = 'Teste';
const app = express();

app.use(cors());
app.use(express.json());

app.post('/publish', (req, res) => {
    const message = req.body;
    const messageString = typeof message === 'string' ? message : JSON.stringify(message);
  
    // Publica a mensagem no tópico especificado
    client.publish(topic, messageString, { qos: 0 }, (error) => {
      if (error) {
        console.error('Erro ao publicar mensagem:', error);
        res.status(500).json({ error: 'Erro ao publicar mensagem' });
      } else {
        console.log('Mensagem publicada:', message);
        res.json({ message: 'Mensagem publicada com sucesso' });
      }
    });
  });

  app.get('/received', (req, res) => {
    client.subscribe([topic], () => {
        console.log(`Subscribe to topic '${topic}'`);
        client.on('message', (topic, RegistrosDoClima) => {
          const data = JSON.parse(RegistrosDoClima.toString());
          console.log('Received Message:', topic, RegistrosDoClima.toString());
          res.json(data);
        });
      });
  });
  


const port = 3000;
app.listen(port, () => {
  console.log(`API rodando em http://localhost:${port}`);
});
