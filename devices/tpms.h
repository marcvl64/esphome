#include "esphome.h"

class UartReadLineSensor : public Component, public UARTDevice, public TextSensor {
 public:
  UartReadLineSensor(UARTComponent *parent) : UARTDevice(parent) {}

  const byte STX = 0x02; // start of text
  const byte ETX = 0x03; // end of text
  const byte AA = 0xAA;
  const byte EIGHTEEN = 0x18;
  const byte ZERO = 0x00;
  const byte NINE_THREE = 0x93;
  const byte NINE_FOUR = 0x94;
  const byte TWENTY = 0x20;
  const int MAX_LENGTH = 180;
  const int SENSOR_DATA = 10;

  bool validateChecksum(char* data, int length) {
    byte sum=0;
    for (int i=0; i < length -1; i++) {
      sum += data[i];
    }
    return sum == data[length - 1];
  }

  bool validateMessage(char* data) {
    if (data[0] != AA && data[0] != EIGHTEEN) return false;
    if (data[1] != ZERO) return false;
    if (data[2] != NINE_THREE && data[2] != NINE_FOUR) return false;
    if (data[3] != TWENTY) return false;
    ESP_LOGD("custom","message validated");
    return true;
  }

  String createJSON(char* data) {
    DynamicJsonDocument doc(1024);
    int shift = 0;
    int sensorloop = 16;
    if(data[0] == AA) {       // this is a sensor update message
      doc["alarm"] = 0;
    } else if (data[0] =  EIGHTEEN) {  //this is an alarm message
      doc["alarm"] = data[6];
      shift = 1;             // all sensor data are shifted by 1 byte
      sensorloop = data[6];
    }
    // go through all the sensor data
    for (int i = 0; i < sensorloop; i++) {
      DynamicJsonDocument sensor(1024);
      sensor["position"] = data[6+shift+i*10];
      sensor["psi"] = data[10+shift+i*10];
      sensor["timeout"] = data[11+shift+i*10];
      if (data[12+shift+i*10] < 127) {
        sensor["temperature"] = data[12+shift+i*10];
      } else {
        sensor["temperature"] = data[12+shift+i*10] - 256;
      }
      sensor["rfQuality"] = data[13+shift+i*10];
      sensor["alarm"] = data[14+shift+i*10];
      sensor["reference"] = data[15+shift+i*10];
      // add sensor to the doc Json, with the proper tyre label
      switch (data[6+i*10]) {
        case 11:
          doc["fl"] = sensor;
          break;
        case 12:
          doc["fr"] = sensor;
          break;
        case 21:
          doc["dlo"] = sensor;
          break;
        case 22:
          doc["dli"] = sensor;
          break;
        case 23:
          doc["dri"] = sensor;
          break;
        case 24:
          doc["dro"] = sensor;
          break;
        case 31:
          doc["tl"] = sensor;
          break;
        case 32:
          doc["tr"] = sensor;
          break;
        case 41:
          doc["spare"] = sensor;
          break;
      }
    }
    // convert JSON object to string
    String json_str;
    serializeJson(doc, json_str);
    return json_str;
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
          String json_str = createJSON(data);
          publish_state(json_str.c_str());
          ESP_LOGD("custom","message content: %s", json_str);
        }
      }  
    }
  }
};

