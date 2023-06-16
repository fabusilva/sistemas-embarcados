
# Projeto de unidade

Projeto avaliativo da I unidade, da diciplina de sistemas embarcados do curso ADS do IFPE *Campus* Garanhuns.
___
>
#### componentes eletrônico utilizado:

- Placa De Desenvolvimento [Nucleo-f303re](https://os.mbed.com/platforms/ST-Nucleo-F303RE/)
- Display de 7 segmentos
- Botão de 4 pinos
- Módulo joystick

#### Escopo
Utilizar duas placas Nucleo-F303RE para estabelecer uma conexão serial utilizando o protocolo UART entre elas. O objetivo é utilizar o display de 7 segmentos para exibir uma sequência numérica de 0 a 9. Além disso, vamos utilizar a inclinação do joystick da primeira placa para controlar a luminosidade do display de 7 segmentos da segunda placa. Para interagir com o sistema, faremos uso tanto do botão de 4 pinos quanto do botão integrado da placa, que permitirão aumentar ou diminuir o número exibido no display de 7 segmentos. Essas ações serão realizadas através da conexão serial entre as placas.
___

## Documentação

- [BufferedSerial](https://os.mbed.com/docs/mbed-os/v6.16/apis/serial-uart-apis.html)
- [PwmOut](https://os.mbed.com/docs/mbed-os/v6.16/apis/pwmout.html)
- [AnalogIn](https://os.mbed.com/docs/mbed-os/v6.16/apis/i-o-apis.html)
- [InterruptIn](https://os.mbed.com/docs/mbed-os/v6.16/apis/interruptin.html)
- [Timer](https://os.mbed.com/docs/mbed-os/v6.16/apis/timer.html)
- [Thread](https://os.mbed.com/docs/mbed-os/v6.16/apis/thread.html)
- [EventFlags](https://os.mbed.com/docs/mbed-os/v6.16/apis/eventflags.html)

