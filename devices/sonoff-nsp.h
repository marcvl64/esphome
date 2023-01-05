#include "esphome.h"

class AC_Control : public Component {
  public:
    AC_Control(int pin, int command)
    {
      AC_signal_genPIN = pin;
      AC_command = command;
    }

    void setup() override {
      pinMode(AC_signal_genPIN, OUTPUT);
    }

    void loop() override {
      if (AC_command==0) {
        AC_off();
        ESP_LOGD("custom", "Turn off AC");
      }
      if (AC_command==1) {
        AC_fan_low();
        ESP_LOGD("custom", "Turn on low fan");
      }
      if (AC_command==2) {
        AC_fan_high();
        ESP_LOGD("custom", "Turn on high fan");
      }
      if (AC_command==3) {
        AC_cool_low();
        ESP_LOGD("custom", "Turn on AC, low fan speed");
      }
      if (AC_command==4) {
        AC_cool_high();
        ESP_LOGD("custom", "Turn on AC, high fan speed");
      }
    }

    void AC_off() override {
      // Add instructions
      digitalWrite(AC_signal_genPIN, LOW);
    }

    void AC_fan_low() override {
      // Add instructions
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(10000);
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(10000);
    }

    void AC_fan_high() override {
      // Add instructions
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5000);
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(5000);
    }

    void AC_cool_low() override {
      // Add instructions
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(10000);
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(2000);
    }

    void AC_cool_high() override {
      // Add instructions
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5000);
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(2000);
    }
};  
