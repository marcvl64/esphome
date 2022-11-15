#include "esphome.h"

class AC_Turn_on_high_fan : public Component, public Switch {
  public:
   AC_Turn_on_high_fan(int pin)
   {
     AC_signal_genPIN = pin;
   }

   void setup() override {
     pinMode(AC_signal_genPIN, OUTPUT);
   }

   void write_state(bool state) override {
     if (state) {                
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

       publish_state(state);
     }
   }
  private:
   int AC_signal_genPIN;
};

class AC_Turn_on_low_fan : public Component, public Switch {
  public:
   AC_Turn_on_low_fan(int pin)
   {
     AC_signal_genPIN = pin;
   }

   void setup() override {
     pinMode(AC_signal_genPIN, OUTPUT);
   }

   void write_state(bool state) override {
     if (state) { 
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

       publish_state(state);
     }
   }
  private:
   int AC_signal_genPIN;
};

class Fan_Low : public Component, public Switch {
  public:
   Fan_Low(int pin)
   {
     AC_signal_genPIN = pin;
   }

   void setup() override {
     pinMode(AC_signal_genPIN, OUTPUT);
   }

   void write_state(bool state) override {
     if (state) {           
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

       publish_state(state);
     }
   }
  private:
   int AC_signal_genPIN;
};

class Fan_High : public Component, public Switch {
  public:
   Fan_High(int pin)
   {
     AC_signal_genPIN = pin;
   }

   void setup() override {
     pinMode(AC_signal_genPIN, OUTPUT);
   }

   void write_state(bool state) override {
     if (state) {           
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

       publish_state(state);
     }
   }
  private:
   int AC_signal_genPIN;
};

class AC_Off : public Component, public Switch {
  public:
   AC_Off(int pin)
   {
     AC_signal_genPIN = pin;
   }

   void setup() override {
     pinMode(AC_signal_genPIN, OUTPUT);
   }

   void write_state(bool state) override {
     if (state) {
       digitalWrite(AC_signal_genPIN,LOW);
       publish_state(state);
    }
   }
  private:
   int AC_signal_genPIN;
};
