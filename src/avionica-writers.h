#ifndef AVIONICA_WRITERS_H
#define AVIONICA_WRITERS_H

#include "avionica-ports.h"

#define AVIONICA_MAX7219_BUFFER_SIZE 16

//! The decode modes for MAX7219
#define AVIONICA_MAX7219_NO_DECODE  0
#define AVIONICA_MAX7219_MODE_B     1

//! The digits of MAX7219
#define AVIONICA_MAX7219_DIGIT0     0
#define AVIONICA_MAX7219_DIGIT1     1
#define AVIONICA_MAX7219_DIGIT2     2
#define AVIONICA_MAX7219_DIGIT3     3
#define AVIONICA_MAX7219_DIGIT4     4
#define AVIONICA_MAX7219_DIGIT5     5
#define AVIONICA_MAX7219_DIGIT6     6
#define AVIONICA_MAX7219_DIGIT7     7

namespace Avionica {

  //! A writer object that can be used to write commands to a MAX7219 device.
  class Max7219Writer {
  public:
    //! Create a MAX7219 writer for the given port and line.
    Max7219Writer(Avionica::Port& port, byte line);

    //! Set the normal operation mode (not shutdown).
    void setNormalOperation();

    //! Set the given decode mode for the given digit.
    void setDecodeMode(byte digit, byte mode);

    //! Set the given decode mode for all digits
    void setDecodeModeForAll(byte mode);

    //! Set the intensity of the LEDs (from 0.0 to 1.0).
    void setIntensity(float value);

    //! Set the last digit that will be scanned.
    void setScanLimit(byte limit);

    //! Set the value for the given digit in no-decode mode.
    void setNoDecodeDigit(byte digit, byte value);

    //! Put a new command in the buffer.
    void send(byte addr, byte data);

    //! Flush one byte of the buffer into the port.
    void flush();

  private:

    Avionica::Port& port;
    byte line;
    word buffer[AVIONICA_MAX7219_BUFFER_SIZE];
    byte buffer_index;
    byte decode_modes;

    void resetBuffer();
  };
}

#endif
