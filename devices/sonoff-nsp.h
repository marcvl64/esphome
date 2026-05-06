#include "esphome.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// The Dometic A/C requires a continuous pulse train on the control line — it
// stops the moment the signal stops. Running that train inside ESPHome's
// loop() blocks the main task for ~250 ms per pattern, which starves WiFi /
// MQTT and eventually trips the watchdog (silent reboots every few minutes).
//
// Fix: emit the pattern from a dedicated FreeRTOS task. The task busy-loops
// the pulses, but FreeRTOS preempts at every tick (1 ms), and a vTaskDelay(1)
// between iterations hands the scheduler back to ESPHome / WiFi / MQTT. The
// Dometic still sees an effectively continuous stream.
class AC_Control : public Component {
  public:
    int AC_signal_genPIN;
    volatile int AC_command = 0;   // shared with task; volatile, single 32-bit aligned int is atomic on ESP32

    AC_Control(int pin, esphome::template_::TemplateNumber *&_command)
    {
      AC_signal_genPIN = pin;
      _command->add_on_state_callback([this](int newcommand) {AC_command = newcommand;});
    }

    void setup() override {
      pinMode(AC_signal_genPIN, OUTPUT);
      // Pin to APP_CPU (core 1) so we don't disturb WiFi/BT on PRO_CPU (core 0).
      // Same priority as the Arduino loop task → FreeRTOS round-robin time-slices.
      xTaskCreatePinnedToCore(
        &AC_Control::task_trampoline,
        "ac_ctrl",
        4096,
        this,
        1,
        nullptr,
        1
      );
    }

    void loop() override {
      // Intentionally empty — pulse generation runs in the FreeRTOS task above.
    }

  private:
    static void task_trampoline(void *arg) {
      static_cast<AC_Control*>(arg)->task_run();
    }

    void task_run() {
      for (;;) {
        switch (AC_command) {
          case 0: AC_off();       break;
          case 1: AC_fan_low();   break;
          case 2: AC_fan_high();  break;
          case 3: AC_cool_low();  break;
          case 4: AC_cool_high(); break;
          case 5: AC_heat();      break;
        }
        vTaskDelay(1);  // yield ~1 tick so other tasks always run
      }
    }

  public:

    void AC_off() {
      // Add instructions
      digitalWrite(AC_signal_genPIN, LOW);
    }

    void AC_fan_low() {
      // Add instructions
      digitalWrite(AC_signal_genPIN, LOW);// sets the digital pin 13 on
      delayMicroseconds(1000);// waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);// sets the digital pin 13 AC_signal_genPIN
      delayMicroseconds(500);// waits for half a second
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(4119);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(789);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1556);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(2000);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(795);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(503);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(3090);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(755);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(538);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(503);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1000);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1556);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(750);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(528);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(540);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(503);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(539);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(503);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1054);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(533);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(750);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(529);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(503);
      
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(539);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1000);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1550);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(750);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(539);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(4148);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(750);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(2000);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1550);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1000);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);//
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);       //4
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);           //4
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);            //4
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);        //7
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);//
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delay(175);


    }

    void AC_fan_high() {
      // Add instructions
      digitalWrite(AC_signal_genPIN, LOW);// sets the digital pin 13 on
      delayMicroseconds(1041);// waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);// sets the digital pin 13 AC_signal_genPIN
      delayMicroseconds(500);// waits for half a second
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(4119);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(755);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(520);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1000);
      //
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1000);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(2000);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(762);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(520);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1519);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(3000);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(770);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(525);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(528);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1000);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1554);////////////////////*
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(750);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(525);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(528);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(529);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1043);///////////////*
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(755);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(527);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
      
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1554);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1042);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(763);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(528);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(4118);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(769);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(529);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1520);//////////////**********
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1000);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1555);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1000);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(510);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    ////////////////////////////////////////////////////////////////
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    ///7
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    ////////////////////////////////////
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
      
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(2574);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);            
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);        
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    ///////////////////////////////////////////////
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(510);
    ///////////////////////////
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);//
    ////////////////////////////////////////////////////==
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1000);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delay(175);

    }

    void AC_cool_low() {
      // Add instructions
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin 13 on
      delayMicroseconds(1000); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin 13 off
      delayMicroseconds(500);            // waits for half a second
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(4119);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(789);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1556);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(2000);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(795);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1000);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(3607);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(795);
    //77777777777777777777777777777777777777
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1000);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1555);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(800);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1000);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    //77777777777777777777777777777
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(789);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1520);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1042);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(866);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(4119);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(797);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    //777777777777777777777777777777777777777
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1555);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1000);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1555);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1044);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(513);
    //////////////////////////////////////////////////////
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    /////////////////////////////////////////////////////
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(510);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(513);
    //////////////////////////////////////////
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    ////////////////////////////////////////////////
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(510);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(510);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(510);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(543);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(518);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(518);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(510);
    //777777777777777777777777777777777777777777
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(510);
    /////////////////////////////////////////////////////////
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    ////////////////////////////////////////////////////
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(510);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(513);
    //////////////////////////////////////////////
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    ////////////////////////////////////////////
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(510);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1000);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1033);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delay(175);
    }

    void AC_cool_high() {
      // Add instructions
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(1000); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(500);            // waits for a second
      
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(4000); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(800);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(1000);            //3.6 waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on 3.7
      delayMicroseconds(1000); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(500);            // waits for a second 3.8
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on 3.9
      delayMicroseconds(2000); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(789);            // waits for a second
      
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on 290.1
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off 29.2
      delayMicroseconds(1000);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on 290.3
      delayMicroseconds(3600); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off 290.6
      delayMicroseconds(779);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on 3.7
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(500);            // waits for a second 290.75
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(1000); // waits for a second  290.8
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(500);            // waits for a second 290.9
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(1500); // waits for a second 300
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(500);            // waits for a second 300.1
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(788);            // waits for a second 300.2
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second 300.3
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(500);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on 300.4
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(500);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // 300.5 waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(500);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(1000); // waits for a second 300.6
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off 300.7
      delayMicroseconds(500);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(781);            // waits for a second 300.8
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second 300.9
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(500);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on 310
      delayMicroseconds(1000); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(1000);            // waits for a second 310.1
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(1000); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(500);            // waits for a second 310.3
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(795);    // 310.4       // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); //  300.5 waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(500);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(4000); // waits for a second 310.6
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off 320
      delayMicroseconds(780);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(1500);            // waits for a second 320.2
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second 300.3
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(1000);            // waits for a second 300.4
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on 300.5
      delayMicroseconds(1500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(1000);            // waits for a second 300.6
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on 300.7
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(500);            // waits for a second 500
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second 300.8
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off 330.2
      delayMicroseconds(500);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(500);  // 330.3          // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off 330.8
      delayMicroseconds(500);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(1500);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(500);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(500);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second 340.4
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(500);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off 340.9
      delayMicroseconds(500);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off 350
      delayMicroseconds(500);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off 350.5
      delayMicroseconds(500);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off 350.6
      delayMicroseconds(500);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(5);            // waits for a second
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delayMicroseconds(2000);            // waits for a second 350.8
    
      digitalWrite(AC_signal_genPIN, LOW); // sets the digital pin AC_signal_genPIN on
      delayMicroseconds(500); // waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);  // sets the digital pin AC_signal_genPIN off
      delay(175);            // waits for a second
    }

    void AC_heat() {
      // Add instructions
      digitalWrite(AC_signal_genPIN, LOW);// sets the digital pin 13 on
      delayMicroseconds(1000);// waits for a second
      digitalWrite(AC_signal_genPIN, HIGH);// sets the digital pin 13 AC_signal_genPIN
      delayMicroseconds(500);// waits for half a second
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(4120);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(789);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(520);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
      
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      //
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(2000);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(780);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(3090);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(793);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(528);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1000);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1550);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(778);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1000);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
      //
      
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(790);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(528);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(2068);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(780);
    
      //
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(4119);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(790);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(530);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1000);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(2068);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1000);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1000);/////////////
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    //
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    ///7
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    /////////////////////////////////
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    //7
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(2000);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1000);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    ///
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);            
    //////////******************
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);        
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    ///////////////////////////////////****7
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    ///////////////
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);//
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    //7///////////////////////////////////////////////////////////////////////////////////
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    /////////**********************
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(500);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);
    
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(500);
      digitalWrite(AC_signal_genPIN, HIGH);
      delay(175);
    }
};  
