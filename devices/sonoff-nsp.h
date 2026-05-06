#include "esphome.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <vector>

// The Dometic A/C requires a continuous pulse train on its control line — it
// stops the moment the signal stops. Emitting it from ESPHome's loop() blocks
// the main task for ~250 ms per pattern, starving WiFi/MQTT and tripping the
// watchdog (silent reboots).
//
// One FreeRTOS task per instance also fails: two priority-2 tasks on the same
// core round-robin against each other, corrupting both pulse trains so neither
// Dometic decodes when both are commanded on at the same time.
//
// Fix: a SINGLE shared FreeRTOS task drives all AC_Control instances
// sequentially — bedroom pattern, then living-room pattern, then a vTaskDelay
// to let ESPHome's loop run. This mirrors the original loop()'s ordering
// (which never overlapped patterns either) while keeping the main task free.
class AC_Control : public Component {
  public:
    int AC_signal_genPIN;
    volatile int AC_command = 0;   // shared with task; volatile, single 32-bit aligned int is atomic on ESP32

    inline static std::vector<AC_Control*> instances_;
    inline static TaskHandle_t shared_task_ = nullptr;

    AC_Control(int pin, esphome::template_::TemplateNumber *&_command)
    {
      AC_signal_genPIN = pin;
      _command->add_on_state_callback([this](int newcommand) {AC_command = newcommand;});
      // All AC_Control constructors run before any setup() (ESPHome lambda
      // registration phase), so by the time the shared task starts iterating
      // instances_, every instance is already in the vector.
      instances_.push_back(this);
    }

    void setup() override {
      pinMode(AC_signal_genPIN, OUTPUT);
      // Spawn the shared driver task once — first instance's setup() wins.
      // Pin to APP_CPU (core 1) so we don't disturb WiFi/BT on PRO_CPU (core 0).
      // Priority 2 (above Arduino loop's 1) so each pattern runs uninterrupted.
      if (shared_task_ == nullptr) {
        xTaskCreatePinnedToCore(
          &AC_Control::shared_task_run,
          "ac_ctrl",
          4096,
          nullptr,
          2,
          &shared_task_,
          1
        );
      }
    }

    void loop() override {
      // Intentionally empty — pulse generation runs in the shared task below.
    }

  private:
    static void shared_task_run(void *) {
      for (;;) {
        for (auto *inst : instances_) {
          switch (inst->AC_command) {
            case 0: inst->AC_off();       break;
            case 1: inst->AC_fan_low();   break;
            case 2: inst->AC_fan_high();  break;
            case 3: inst->AC_cool_low();  break;
            case 4: inst->AC_cool_high(); break;
            case 5: inst->AC_heat();      break;
          }
        }
        // After both patterns have been emitted, hand ~20 ms back to the
        // priority-1 Arduino loop so MQTT/WiFi/ADC stay responsive.
        vTaskDelay(pdMS_TO_TICKS(20));
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
      // Reverse-engineered from a Saleae capture of the OEM Dometic
      // CCC thermostat — 105 pulse pairs over ~80 ms.
      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(1018);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(516);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(513);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(513);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(513);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(772);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(513);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(519);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(522);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(513);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(513);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(769);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(507);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1027);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(513);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(522);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(513);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(513);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(772);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(513);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(513);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(519);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(519);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(769);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(507);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(513);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(519);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(522);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(519);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(769);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(507);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(513);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(513);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(519);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(522);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(772);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(513);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(513);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(513);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(513);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(513);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(769);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(507);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(513);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(519);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(513);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(510);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(513);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(989);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(540);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(509);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(505);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(514);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(505);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(505);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(506);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(502);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(509);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(527);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(506);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(502);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(509);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(505);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(514);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(506);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(502);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(509);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(505);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(527);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(506);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(502);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(509);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(5);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(506);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(506);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(502);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(1018);

      digitalWrite(AC_signal_genPIN, LOW);
      delayMicroseconds(505);
      digitalWrite(AC_signal_genPIN, HIGH);
      delayMicroseconds(2063);

      delay(175);  // inter-frame idle gap
    }
};  
