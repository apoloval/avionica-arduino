#ifndef AVIONICA_PORTS_H
#define AVIONICA_PORTS_H

#include <Arduino.h>

#define AVIONICA_CLOCK_PIN 2
#define AVIONICA_LATCH_PIN 3
#define AVIONICA_PORT_COUNT 12

namespace Avionica {
  class Port {
  public:

    //! Create a port with the given pin assignment
    Port(byte pin0, byte pin1, byte pin2, byte pin3);

    //! Setup the given line in the given IO mode
    void setupLine(byte line, byte io_mode);

    //! Read the content of the given line
    //! This must be called after `Avionica::swap()` to take effect.
    word read(byte line);

    //! Write the content of the given line
    //! This must be called before `Avionica::swap()` to take effect.
    void write(byte line, word value);

  private:

    friend void Avionica::swap();

    bool enabled[4];
    byte mode[4];
    byte pin[4];
    word buffer[4];

    //! Check if the given line is valid (is enabled)
    bool validLine(byte line);

    //! Check if the given line is valid for the given IO mode
    bool validLine(byte line, byte io_mode);

    //! Send one bit of each line in OUTPUT mode
    void send_bit();

    //! Receive one bit of each line in INPUT mode
    void receive_bit();
  };

  //! Setup Avionica library
  //! Initializes its internal state and prepares the global signal IO
  void setup();

  //! Swap data between the internal buffers and the devices
  //! This have to be called after `write()` and before `read()`.
  void swap();

  // Above we declare some aliases of the available ports
  extern Port& P1;
  extern Port& P2;
  extern Port& P3;
  extern Port& P4;
  extern Port& P5;
  extern Port& P6;
  extern Port& P7;
  extern Port& P8;
  extern Port& P9;
  extern Port& P10;
  extern Port& P11;
  extern Port& P12;

  extern Port& PortA;
  extern Port& PortB;
  extern Port& PortC;
  extern Port& PortD;
  extern Port& PortE;
  extern Port& PortF;
  extern Port& PortG;
  extern Port& PortH;
  extern Port& PortI;
  extern Port& PortJ;
  extern Port& PortK;
  extern Port& PortL;
}

#endif
