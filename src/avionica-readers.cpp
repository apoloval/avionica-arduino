#include <Arduino.h>

#include "avionica-readers.h"

Avionica::ParallelReader::ParallelReader(
  Avionica::Port& port, byte dav_line, byte data_line)
  : port(port),
    dav_line(dav_line),
    data_line(data_line),
    prev_dav(LOW) {
  port.setupLine(dav_line, AVIONICA_INPUT);
  port.setupLine(data_line, AVIONICA_P2S);
}

bool Avionica::ParallelReader::dataAvailable() {
  byte dav = port.readLevel(dav_line);
  bool result = (prev_dav == LOW && dav == HIGH);
  prev_dav = dav;
  return result;
}

word Avionica::ParallelReader::data() {
  return port.read(data_line);
}
