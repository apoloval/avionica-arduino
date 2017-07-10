#ifndef AVIONICA_READERS_H
#define AVIONICA_READERS_H

#include "avionica-ports.h"

namespace Avionica {
  class ParallelReader {
  public:

    ParallelReader(Avionica::Port& port, byte dav_line, byte data_line);

    bool dataAvailable();

    word data();

  private:
    Avionica::Port& port;
    byte dav_line;
    byte data_line;
    word prev_dav;
  };
}

#endif
