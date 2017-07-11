#include <Arduino.h>

#include "avionica-readers.h"

namespace Avionica {

EdgeReader::EdgeReader(Port& port, byte line)
  : port(port), line(line), prev_level(LOW) {
  port.setupLine(line, AVIONICA_INPUT);
}

bool EdgeReader::hasRaised() {
  byte level = port.readLevel(line);
  bool result = (prev_level == LOW && level == HIGH);
  prev_level = level;
  return result;
}

bool EdgeReader::hasFallen() {
  byte level = port.readLevel(line);
  bool result = (prev_level == HIGH && level == LOW);
  prev_level = level;
  return result;
}


SerialReader::SerialReader(Port& port, byte line)
  : port(port), line(line) {
  port.setupLine(line, AVIONICA_SERIAL_INPUT);
}

} // namespace Avionica
