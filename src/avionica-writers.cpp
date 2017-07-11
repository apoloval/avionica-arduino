#include <Arduino.h>

#include "avionica-writers.h"

#define MAX7219_NOOP_ADDR          0x00
#define MAX7219_DIGIT0_ADDR        0x01
#define MAX7219_DECODE_MODE_ADDR   0x09
#define MAX7219_INTENSITY_ADDR     0x0a
#define MAX7219_SCAN_LIMIT_ADDR    0x0b
#define MAX7219_SHUTDOWN_ADDR      0x0c
#define MAX7219_DISPLAY_TEST_ADDR  0x0f

Avionica::Max7219Writer::Max7219Writer(Avionica::Port& port, byte line)
  : port(port), line(line), buffer_index(0), decode_modes(0) {
  port.setupLine(line, AVIONICA_SERIAL_OUTPUT);
  resetBuffer();
}

void Avionica::Max7219Writer::setNormalOperation() {
  send(MAX7219_SHUTDOWN_ADDR, 1);
}

void Avionica::Max7219Writer::setDecodeMode(byte digit, byte mode) {
  switch (mode) {
    case AVIONICA_MAX7219_NO_DECODE:
      bitClear(decode_modes, digit);
      break;
    case AVIONICA_MAX7219_MODE_B:
      bitSet(decode_modes, digit);
      break;
  }
  send(MAX7219_DECODE_MODE_ADDR, decode_modes);
}

void Avionica::Max7219Writer::setDecodeModeForAll(byte mode) {
  switch (mode) {
    case AVIONICA_MAX7219_NO_DECODE:
      decode_modes = 0x00;
      break;
    case AVIONICA_MAX7219_MODE_B:
      decode_modes = 0xff;
      break;
  }
  send(MAX7219_DECODE_MODE_ADDR, decode_modes);
}

void Avionica::Max7219Writer::setIntensity(float value) {
  if (value > 1.0f) { value = 1.0f; }
  if (value < 0.0f) { value = 0.0f; }
  byte data = 0x0f * value;
  send(MAX7219_INTENSITY_ADDR, data);
}

void Avionica::Max7219Writer::setScanLimit(byte limit) {
  send(MAX7219_SCAN_LIMIT_ADDR, limit);
}

void Avionica::Max7219Writer::setNoDecodeDigit(byte digit, byte value) {
  send(MAX7219_DIGIT0_ADDR + digit, value);
}

void Avionica::Max7219Writer::send(byte addr, byte data) {
  if (buffer_index < AVIONICA_MAX7219_BUFFER_SIZE) {
    buffer[buffer_index] = word(data) | (word(addr) << 8);
    buffer_index++;
  }
}

void Avionica::Max7219Writer::flush() {
  if (buffer_index > 0) {
    port.write(line, buffer[0]);
    for (byte i = 0; i < buffer_index - 1; i++) {
      buffer[i] = buffer[i + 1];
    }
    buffer[buffer_index - 1] = 0;
    buffer_index--;
  }
}

void Avionica::Max7219Writer::resetBuffer() {
  for (int i = 0; i < AVIONICA_MAX7219_BUFFER_SIZE; i++) {
    buffer[i] = 0;
  }
  buffer_index = 0;
}
