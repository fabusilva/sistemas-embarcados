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
  client.subscribe(topic, (error) => {
    if (error) {
      console.error(error);
      res.status(500).json({ error: 'Erro ao se inscrever no tópico' });
    } else {
      console.log('Inscrito no tópico:', topic);
      res.json({ message: 'Inscrito no tópico' });
    }
  });
});

client.on('message', (receivedTopic, receivedMessage) => {
  if (receivedTopic === topic) {
    console.log('Mensagem Recebida:', receivedMessage.toString());
    // Faça o que desejar com a mensagem recebida
    const response = receivedMessage.toString();
    res.json(response);

  }
});
const port = 3000;
app.listen(port, () => {
  console.log(`API rodando em http://localhost:${port}`);
});
