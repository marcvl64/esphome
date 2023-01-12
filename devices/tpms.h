#include "esphome.h"

class UartReadLineSensor : public Component, public UARTDevice, public TextSensor {
 public:
  UartReadLineSensor(UARTComponent *parent) : UARTDevice(parent) {}

  const byte STX = 0x02; // start of text
  const byte ETX = 0x03; // end of text
  const byte AA = 0xAA;
  const byte ZERO = 0x00;
  const byte NINE_THREE = 0x93;
  const byte TWENTY = 0x20;
  const int MAX_LENGTH = 110;
  const int SENSOR_DATA = 10;

  bool validateChecksum(char* data, int length) {
    byte sum=0;
    for (int i=0; i < length -1; i++) {
      sum += data[i];
    }
    return sum == data[length - 1];
  }

  bool validateMessage(char* data) {
    if (data[0] != AA) return false;
    if (data[1] != ZERO) return false;
    if (data[2] != NINE_THREE) return false;
    if (data[3] != TWENTY) return false;
    return true;
  }

  void setup() override {
    // nothing to do here
  }

  void loop() override {
    while (available()) {
      char data[MAX_LENGTH];
      int length = 0;
      byte inByte = read();
      if (inByte == STX) {
        while (available() && inByte != ETX) {
          data[length++] = inByte;
          inByte = read();
        }
        data[length++] = inByte; // add ETX to data
        if (validateChecksum(data, length) && validateMessage(data+1)) {
          publish_state(data);
        }
      }  
    }
  }
//  int readline(int readch, char *buffer, int len)
//  {
//    static int pos = 0;
//    int rpos;
//
//    if (readch > 0) {
//      switch (readch) {
//        case '\n': // Ignore new-lines
//          break;
//        case '\r': // Return on CR
//          rpos = pos;
//          pos = 0;  // Reset position index ready for next time
//          return rpos;
//        default:
//          if (pos < len-1) {
//            buffer[pos++] = readch;
//            buffer[pos] = 0;
//          }
//      }
//    }
//    // No end of line has been found, so return -1.
//    return -1;
//  }
//
//  void loop() override {
//    const int max_line_length = 80;
//    static char buffer[max_line_length];
//    while (available()) {
//      if(readline(read(), buffer, max_line_length) > 0) {
//        publish_state(buffer);
//      }
//    }
//  }
};

