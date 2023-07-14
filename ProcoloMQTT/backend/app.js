const express = require('express');
const client = require('./Connection/mqttConnection');
const cors = require("cors");
const topic = 'Dashboard';
const app = express();

app.use(cors());
app.use(express.json());

const path = require('path');

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');


/* GET home page. */
app.get('/', async (req, res, next) => {
  res.render('index', { title: 'Broker' });
});


app.post('/publish', (req, res) => {
    const message = req.body;
    const messageString = typeof message === 'string' ? message : JSON.stringify(message);
  
    // Publica a mensagem no tópico especificado
    client.publish('Dashboard', messageString, { qos: 0 }, (error) => {
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
   
    let receivedData = null;
  
    client.on('message', (topic, RegistrosDoClima) => {
      const data = JSON.parse(RegistrosDoClima.toString());
      console.log('Received Message:', topic, RegistrosDoClima.toString());
      receivedData = data;
    });
  
    // Aguarda um determinado período de tempo antes de enviar a resposta
    setTimeout(() => {
      if (receivedData) {
        res.json(receivedData);
      } else {
        res.status(404).json({ error: 'Nenhum dado recebido' });
      }
    }, 1000); // Aguarda 1 segundo (ajuste conforme necessário)
  });
  
app.get('/dashboard', (req, res) => {
  client.subscribe([topic], () => {
    console.log(`Subscribe to topic '${topic}'`);
  });
    res.render('dashboard', { title: 'Dashboard'});
  })


const port = 3000;
app.listen(port, () => {
  console.log(`View index.ejs rodando em http://localhost:${port}`);
  console.log(`View dashboard.ejs rodando em http://localhost:${port}/dashboard`);
});
