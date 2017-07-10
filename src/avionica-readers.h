#ifndef AVIONICA_READERS_H
#define AVIONICA_READERS_H

#include "avionica-ports.h"

namespace Avionica {

  //! A reader object that can be used to read signal edges
  class EdgeReader {
  public:

    //! Create a edge reader for the given port and line.
    EdgeReader(Avionica::Port& port, byte line);

    //! True if a raising edge was detected, false otherwise.
    bool hasRaised();

    //! True if a falling edge was detected, false otherwise.
    bool hasFallen();

  private:

    Avionica::Port& port;
    byte line;
    byte prev_level;
  };

  class SerialReader {
  public:

    SerialReader(Avionica::Port& port, byte line);

    inline word read() { return port.read(line); }

    inline byte readLowerByte() { return port.read(line); }

    inline byte readUpperByte() { return port.read(line) >> 8; }

  private:

    Avionica::Port& port;
    byte line;
  };
}

#endif
