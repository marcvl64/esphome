#include "esphome.h"

class UartReadLineSensor : public Component, public UARTDevice, public TextSensor {
 public:
  UartReadLineSensor(UARTComponent *parent) : UARTDevice(parent) {}

  const byte STX = 0x02;          // start of text
  const byte ETX = 0x03;          // end of text
  const byte NINE_THREE = 0x93;   // sensor update message
  const byte NINE_FOUR = 0x94;    // sensor alarm message
  const byte TWENTY = 0x20;
  const int MAX_LENGTH = 180;
  const int SENSOR_DATA = 10;

  bool validateChecksum(char* data, int length) {      // verify that checksum is ok
    ESP_LOGD("tpms", "checking checksum");
    byte sum=0;
    for (int i=1; i < length -2; i++) {
      sum += data[i];
    }
    byte checksum = sum % 256;
    return checksum == data[length - 2];
  }

  bool validateMessage(char* data) {                   // verify that this is a sensor update or sensorm alarm message
    ESP_LOGD("tpms", "validating message");
    if (data[3] != NINE_THREE && data[3] != NINE_FOUR) return false;
    if (data[4] != TWENTY) return false;
    return true;
  }

  String createJSON(char* data) {
    ESP_LOGD("tpms", "creating JSON");
    DynamicJsonDocument doc(2048);
    int shift = 0;
    int sensorloop = 16;
    if(data[3] == NINE_THREE) {         // this is a sensor update message
      doc["alarm"] = 0;
    } else if (data[3] == NINE_FOUR) {  // this is an alarm message
      doc["alarm"] = data[6];
      shift = 1;                        // all sensor data are shifted by 1 byte
      sensorloop = data[6];
    }
    // go through all the sensor data
    for (int i = 0; i < sensorloop; i++) {
      DynamicJsonDocument sensor(1024);
      // storing the hex value of position as a string
      char hex[3];
      sprintf(hex, "%02X", data[6+shift+i*10]);
      sensor["position"] = hex;
      sensor["psi"] = data[10+shift+i*10];
      sensor["timeout"] = data[11+shift+i*10];
      if (data[12+shift+i*10] < 127) {
        sensor["temperature"] = data[12+shift+i*10];
      } else {
        sensor["temperature"] = data[12+shift+i*10] - 256;
      }
      sensor["rfQuality"] = data[13+shift+i*10];
      // storing the hex value of alarm as a string
      char hex1[3];
      sprintf(hex1, "%02X", data[14+shift+i*10]);
      sensor["alarm"] = hex1;
      sensor["reference"] = data[15+shift+i*10];
      // add sensor to the doc Json, with the proper tire label
      switch (data[6+shift+i*10]) {
        case 0x11:
          doc["fl"] = sensor;
          break;
        case 0x14:
          doc["fr"] = sensor;
          break;
        case 0x21:
          doc["dlo"] = sensor;
          break;
        case 0x22:
          doc["dli"] = sensor;
          break;
        case 0x23:
          doc["dri"] = sensor;
          break;
        case 0x24:
          doc["dro"] = sensor;
          break;
        case 0x31:
          doc["tl"] = sensor;
          break;
        case 0x34:
          doc["tr"] = sensor;
          break;
        case 0x41:
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
        data[length++] = inByte;                                          // storing STX
        inByte = read();
        data[length++] = inByte;                                          // storing Message Length 
        for (int i = 1; i <= data[1]+2; i++) {                            // reading bytes for message length + checksum + ETX
          inByte = read();
          data[length++] = inByte;
        }
          data[length++] = inByte;                                        // add ETX to data
        if (validateChecksum(data, length) && validateMessage(data)) {    // if checksum is ok and message format is ok, create JSON
          String json_str = createJSON(data);
          publish_state(json_str.c_str());
        }
      }  
    }
  }
};

