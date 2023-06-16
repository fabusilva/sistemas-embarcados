#include "mbed.h"

#define BLINKING_RATE 50ms
#define BOTTON_UP_FLAG (1UL << 0)
#define BOTTON_DONW_FLAG (1UL << 1)

BufferedSerial serial(PC_4, PA_10);
// Pc_4 TX
// PA_10 RX vermelho
Timer timer;
Thread threadButtonUp, threadButtonDown, threadRead, threadWrite;
EventFlags flags;

PwmOut ledA(PA_7);
PwmOut ledB(PB_6);
PwmOut ledC(PC_11);
PwmOut ledD(PC_12);
PwmOut ledE(PC_10);
PwmOut ledF(PC_7);
PwmOut ledG(PA_6);
PwmOut ledDP(PB_7);

AnalogIn vrx(PC_0);
AnalogIn vry(PC_1);

InterruptIn btUp(BUTTON1);
InterruptIn btDown(PB_9);

struct msg {
  char code;
  float joystickValue;
};
struct msg msg_sent, msg_received;

char up = '+';
char down = '-';

bool bt_up_pressed = false;
bool bt_down_pressed = false;

int displayCounter = 5;
float luminosityValue = 0.5f;

void luminosity() {
  if (displayCounter > 9) {
    displayCounter = 9;
  } else if (displayCounter < 0) {
    displayCounter = 0;
  }
  switch (displayCounter) {
  case 0:
    ledA = luminosityValue;
    ledB = luminosityValue;
    ledC = luminosityValue;
    ledD = luminosityValue;
    ledE = luminosityValue;
    ledF = luminosityValue;
    ledG = 0.0f;
    ledDP = 0.0f;
    break;
  case 1:
    ledA = 0.0f;
    ledB = luminosityValue;
    ledC = luminosityValue;
    ledD = 0.0f;
    ledE = 0.0f;
    ledF = 0.0f;
    ledG = 0.0f;
    ledDP = 0.0f;
    break;
  case 2:
    ledA = luminosityValue;
    ledB = luminosityValue;
    ledC = 0.0f;
    ledD = luminosityValue;
    ledE = luminosityValue;
    ledF = 0.0f;
    ledG = luminosityValue;
    ledDP = 0.0f;
    break;
  case 3:
    ledA = luminosityValue;
    ledB = luminosityValue;
    ledC = luminosityValue;
    ledD = luminosityValue;
    ledE = 0.0f;
    ledF = 0.0f;
    ledG = luminosityValue;
    ledDP = 0.0f;
    break;
  case 4:
    ledA = 0.0f;
    ledB = luminosityValue;
    ledC = luminosityValue;
    ledD = 0.0f;
    ledE = 0.0f;
    ledF = luminosityValue;
    ledG = luminosityValue;
    ledDP = 0.0f;
    break;
  case 5:
    ledA = luminosityValue;
    ledB = 0.0f;
    ledC = luminosityValue;
    ledD = luminosityValue;
    ledE = 0.0f;
    ledF = luminosityValue;
    ledG = luminosityValue;
    ledDP = 0.0f;
    break;
  case 6:
    ledA = luminosityValue;
    ledB = 0.0f;
    ledC = luminosityValue;
    ledD = luminosityValue;
    ledE = luminosityValue;
    ledF = luminosityValue;
    ledG = luminosityValue;
    ledDP = 0.0f;
    break;
  case 7:
    ledA = luminosityValue;
    ledB = luminosityValue;
    ledC = luminosityValue;
    ledD = 0.0f;
    ledE = 0.0f;
    ledF = 0.0f;
    ledG = 0.0f;
    ledDP = 0.0f;
    break;
  case 8:
    ledA = luminosityValue;
    ledB = luminosityValue;
    ledC = luminosityValue;
    ledD = luminosityValue;
    ledE = luminosityValue;
    ledF = luminosityValue;
    ledG = luminosityValue;
    ledDP = 0.0f;
    break;
  case 9:
    ledA = luminosityValue;
    ledB = luminosityValue;
    ledC = luminosityValue;
    ledD = 0.0f;
    ledE = 0.0f;
    ledF = luminosityValue;
    ledG = luminosityValue;
    ledDP = 0.0f;
    break;
  }
}

void sentStruct() {
  msg_sent.code = 'j';
  msg_sent.joystickValue = vrx;
  if (serial.writable() == true) {
    serial.write(&msg_sent, sizeof(msg_sent));
  }
}
void receivedStruct() {
  if (serial.readable() == true) {
    serial.read(&msg_received, sizeof(msg_received));
    if (msg_received.code == '+') {
      displayCounter++;
    } else if (msg_received.code == '-') {
      displayCounter--;
    }
    luminosityValue = msg_received.joystickValue;
  }
}
void sentCode(char cod) {
  msg_sent.code = cod;
  msg_sent.joystickValue = vrx;
  if (serial.writable() == true) {
    serial.write(&msg_sent, sizeof(msg_sent));
  }
}

void decreasing() {
  static int last_interrupt_time = 0;
  std::chrono::microseconds interrupt_time = timer.elapsed_time();
  int interrupt_time_int = static_cast<int>(interrupt_time.count());
  if (interrupt_time_int - last_interrupt_time > 200000) {
    bt_down_pressed = true;
    flags.set(BOTTON_DONW_FLAG);
  }
  last_interrupt_time = interrupt_time_int;
}

void increasing() {
  static int last_interrupt_time = 0;
  std::chrono::microseconds interrupt_time = timer.elapsed_time();
  int interrupt_time_int = static_cast<int>(interrupt_time.count());
  if (interrupt_time_int - last_interrupt_time > 200000) {
    // bt_up_pressed = true;
    flags.set(BOTTON_UP_FLAG);
  }
  last_interrupt_time = interrupt_time_int;
}

void reading_msg_thread() {
  while (true) {
    if (serial.readable() == true) {
      serial.read(&msg_received, sizeof(msg_received));
      if (msg_received.code == '+') {
        displayCounter++;
      } else if (msg_received.code == '-') {
        displayCounter--;
      }
      luminosityValue = msg_received.joystickValue;
      luminosity();
    }
    ThisThread::sleep_for(BLINKING_RATE);
  }
}

void writing_msg_thread() {
  while (true) {
    msg_sent.code = 'j';
    msg_sent.joystickValue = vrx;
    if (serial.writable() == true) {
      serial.write(&msg_sent, sizeof(msg_sent));
    }
    ThisThread::sleep_for(BLINKING_RATE);
  }
}

void button_up_thread() {
  uint32_t flags_read = 0;
  while (true) {
    flags_read = flags.wait_any(BOTTON_UP_FLAG);
    // if (bt_up_pressed) {
    sentCode(up);
    // bt_up_pressed = false;
    //}
    ThisThread::sleep_for(BLINKING_RATE);
  }
}

void button_donw_thread() {
  uint32_t flags_read = 0;
  while (true) {
    flags_read = flags.wait_any(BOTTON_DONW_FLAG);
    // if (bt_down_pressed) {
    sentCode(down);
    // bt_down_pressed = false;
    //}
    ThisThread::sleep_for(BLINKING_RATE);
  }
}
int main() {
  serial.set_baud(9600);
  serial.set_format(8, SerialBase::None, 1);

  timer.start();

  threadWrite.start(writing_msg_thread);
  threadRead.start(reading_msg_thread);
  threadButtonUp.start(mbed::callback(button_up_thread));
  threadButtonDown.start(mbed::callback(button_donw_thread));

  btDown.fall(&decreasing);
  btUp.fall(&increasing);
  while (true) {
    /*if (bt_up_pressed) {
      sentCode(up);
      bt_up_pressed = false;
    }
    if (bt_down_pressed) {
      sentCode(down);
      bt_down_pressed = false;
    }
    sentStruct();
    receivedStruct();
    luminosity();*/
  }
}
