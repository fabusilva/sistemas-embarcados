# Projeto de unidade

Projeto avaliativo da II unidade da disciplina de Sistemas Embarcados do curso de Análise e Desenvolvimento de Sistemas (ADS) do IFPE Campus Garanhuns.

## Escopo
O objetivo deste projeto é desenvolver um sistema que utilize um servidor broker MQTT para permitir a troca de dados climáticos entre diferentes dispositivos. 
O sistema consistirá em um aplicativo cliente MQTT que poderá ler e enviar dados para o broker. 
Serão utilizados dois tópicos específicos para essa troca de informações: 
um para envio de dados climáticos e outro para recebimento desses dados.
### Funcionalidades do sistema
* O aplicativo cliente MQTT se conectará a um servidor broker MQTT para estabelecer uma comunicação bidirecional.
* O aplicativo permitirá ao usuário inserir dados climáticos, como temperatura, umidade, pressão atmosférica, entre outros.
* Os dados inseridos serão publicados no tópico designado para envio de dados climáticos.
* O aplicativo cliente MQTT assinará o tópico específico para recebimento de dados climáticos.
* Quando novos dados forem publicados nesse tópico, o aplicativo exibirá as informações recebidas.

## Tecnologias usadas
* [Express](https://expressjs.com/pt-br/).
* [EMQX CLOUD](https://www.emqx.com/en/cloud).
* [EJS](https://ejs.co/).

## Referências
* [How to Use MQTT in Node.js](https://www.emqx.com/en/blog/how-to-use-mqtt-in-nodejs#node-js-mqtt-advanced).
