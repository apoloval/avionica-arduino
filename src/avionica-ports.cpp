#include <Arduino.h>

#include "avionica-ports.h"

#define AVIONICA_CLOCK_PIN 2
#define AVIONICA_LATCH_PIN 3
#define AVIONICA_PORT_COUNT 12

namespace Avionica {

Port::Port(byte pin0, byte pin1, byte pin2, byte pin3) {
  enabled[0] = enabled[1] = enabled[2] = enabled[3] = false;
  pin[0] = pin0;
  pin[1] = pin1;
  pin[2] = pin2;
  pin[3] = pin3;
}

void Port::setupLine(byte line, byte io_mode) {
  if (validLine(line)) {
    enabled[line] = true;
    mode[line] = io_mode;
    switch (io_mode) {
      case AVIONICA_INPUT:
        pinMode(pin[line], INPUT);
        break;
      case AVIONICA_SERIAL_INPUT:
        pinMode(pin[line], INPUT);
        break;
      case AVIONICA_SERIAL_OUTPUT:
        pinMode(pin[line], OUTPUT);
        break;
    }
  }
}

word Port::read(byte line) {
  if (validLine(line, AVIONICA_SERIAL_INPUT)) {
    return buffer[line];
  } else {
    return 0;
  }
}

byte Port::readLevel(byte line) {
  if (validLine(line, AVIONICA_INPUT)) {
    return digitalRead(pin[line]);
  } else {
    return 0;
  }
}

void Port::write(byte line, word value) {
  if (validLine(line, AVIONICA_SERIAL_OUTPUT)) {
    buffer[line] = value;
  }
}

bool Port::validLine(byte line) {
  return line < 4;
}

bool Port::validLine(byte line, byte io_mode) {
  return validLine(line) && mode[line] == io_mode;
}

void Port::send_bit() {
  for (int line = 0; line < 4; line++) {
    if (validLine(line, AVIONICA_SERIAL_OUTPUT)) {
      digitalWrite(pin[line], (buffer[line] & 0x8000) >> 15);
      buffer[line] = buffer[line] << 1;
    }
  }
}

void Port::receive_bit() {
  for (int line = 0; line < 4; line++) {
    if (validLine(line, AVIONICA_SERIAL_INPUT)) {
      word value = digitalRead(pin[line]);
      buffer[line] = (buffer[line] << 1) | value;
    }
  }
}

Port ports[] = {
  Port(22, 23, 24, 25),
  Port(26, 27, 28, 29),
  Port(53, 52, 51, 50),
  Port(10, 11, 12, 13),
  Port(37, 36, 35, 34),
  Port(33, 32, 31, 30),
  Port(21, 20, 19, 18),
  Port(49, 48, 47, 46),
  Port(45, 44, 43, 42),
  Port(6, 7, 8, 9),
  Port(17, 16, 15, 14),
  Port(41, 40, 39, 28)
};

void setup() {
  pinMode(AVIONICA_CLOCK_PIN, OUTPUT);
  pinMode(AVIONICA_LATCH_PIN, OUTPUT);
  digitalWrite(AVIONICA_CLOCK_PIN, LOW);
  digitalWrite(AVIONICA_LATCH_PIN, LOW);
}

void clock_pulse() {
  digitalWrite(AVIONICA_CLOCK_PIN, HIGH);
  delay(1);
  digitalWrite(AVIONICA_CLOCK_PIN, LOW);
}

void latch_pulse() {
  digitalWrite(AVIONICA_LATCH_PIN, HIGH);
  delay(1);
  digitalWrite(AVIONICA_LATCH_PIN, LOW);
}

void swap() {
  for (int bit = 0; bit < 16; bit++) {
    for (int port = 0; port < AVIONICA_PORT_COUNT; port++) {
      ports[port].send_bit();
    }
    clock_pulse();
  }
  latch_pulse();
  for (int bit = 0; bit < 16; bit++) {
    for (int port = 0; port < AVIONICA_PORT_COUNT; port++) {
      ports[port].receive_bit();
    }
    clock_pulse();
  }
}

Port& P1 = ports[0];
Port& P2 = ports[1];
Port& P3 = ports[2];
Port& P4 = ports[3];
Port& P5 = ports[4];
Port& P6 = ports[5];
Port& P7 = ports[6];
Port& P8 = ports[7];
Port& P9 = ports[8];
Port& P10 = ports[9];
Port& P11 = ports[10];
Port& P12 = ports[11];

Port& PortA = ports[0];
Port& PortB = ports[1];
Port& PortC = ports[2];
Port& PortD = ports[3];
Port& PortE = ports[4];
Port& PortF = ports[5];
Port& PortG = ports[6];
Port& PortH = ports[7];
Port& PortI = ports[8];
Port& PortJ = ports[9];
Port& PortK = ports[10];
Port& PortL = ports[11];

} // namespace Avionica
