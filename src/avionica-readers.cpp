#include <Arduino.h>

#include "avionica-readers.h"

Avionica::EdgeReader::EdgeReader(Avionica::Port& port, byte line)
  : port(port), line(line), prev_level(LOW) {
  port.setupLine(line, AVIONICA_INPUT);
}

bool Avionica::EdgeReader::hasRaised() {
  byte level = port.readLevel(line);
  bool result = (prev_level == LOW && level == HIGH);
  prev_level = level;
  return result;
}

bool Avionica::EdgeReader::hasFallen() {
  byte level = port.readLevel(line);
  bool result = (prev_level == HIGH && level == LOW);
  prev_level = level;
  return result;
}


Avionica::SerialReader::SerialReader(Avionica::Port& port, byte line)
  : port(port), line(line) {
  port.setupLine(line, AVIONICA_P2S);
}
