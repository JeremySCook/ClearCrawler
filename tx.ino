    //
    //Radio setup
    //
    #include <SPI.h>
    #include <nRF24L01.h>
    #include <RF24.h>
    RF24 radio(9, 10); // CE, CSN
    const byte address[6] = "00001";
    //
    //Button setup
    //
    const byte PIN_BUTTON_A = 2;
    const byte PIN_BUTTON_B = 3;
    const byte PIN_BUTTON_C = 4;
    const byte PIN_BUTTON_D = 5;
    const byte PIN_BUTTON_E = 6;
    const byte PIN_BUTTON_F = 7;
    const byte PIN_BUTTON_J = 8;
    const byte PIN_ANALOG_X = 0;
    const byte PIN_ANALOG_Y = 1;
    boolean pressed_a = false;
    boolean pressed_b = false;
    boolean pressed_c = false;
    boolean pressed_d = false;
    boolean pressed_e = false;
    boolean pressed_f = false;
    boolean pressed_j = false;
    int analog_x = 350;
    int analog_y = 350;
    //
    //
    void setup() {
      //
      Serial.begin(9600);
      //
      //Radio setup
      radio.begin();
      radio.openWritingPipe(address);
      radio.setPALevel(RF24_PA_MIN); //can set: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
      //radio.setDataRate(RF24_250KBPS); //set as: F24_250KBPS, F24_1MBPS, F24_2MBPS ==>250KBPS = longest range
      //radio.setChannel(80); //sets channel from 2.4 to 2.524 GHz in 1 MHz increments 2.483.5 GHz is normal legal limit
      radio.stopListening();
      //
      //input setup
      pinMode(PIN_BUTTON_A, INPUT);
      digitalWrite(PIN_BUTTON_A, HIGH);
      pinMode(PIN_BUTTON_B, INPUT);
      digitalWrite(PIN_BUTTON_B, HIGH);
      pinMode(PIN_BUTTON_C, INPUT);
      digitalWrite(PIN_BUTTON_C, HIGH);
      pinMode(PIN_BUTTON_D, INPUT);
      digitalWrite(PIN_BUTTON_D, HIGH);
      pinMode(PIN_BUTTON_E, INPUT);
      digitalWrite(PIN_BUTTON_E, HIGH);
      pinMode(PIN_BUTTON_F, INPUT);
      digitalWrite(PIN_BUTTON_F, HIGH);
      pinMode(PIN_BUTTON_J, INPUT);
      digitalWrite(PIN_BUTTON_J, HIGH);
    }
    void loop() {
      //
      //radio test
      const char text[] = "L"; //heartbeat to make sure comms are working
      radio.write(&text, sizeof(text));
      delay(5);
      //
      //button Tx
      if(pressed_a == digitalRead(PIN_BUTTON_A)){
      Serial.print("a pressed");
      Serial.println();
      const char text[] = "A"; //forward
      radio.write(&text, sizeof(text));
      }
      if(pressed_b == digitalRead(PIN_BUTTON_B)){
      Serial.print("b pressed");
      Serial.println();
      const char text[] = "B"; //right
      radio.write(&text, sizeof(text));
      }
      if(pressed_c == digitalRead(PIN_BUTTON_C)){
      Serial.print("c pressed");
      Serial.println();
      const char text[] = "C"; //back
      radio.write(&text, sizeof(text));
      }
      if(pressed_d == digitalRead(PIN_BUTTON_D)){
      Serial.print("d pressed");
      Serial.println();
      const char text[] = "D"; //left
      radio.write(&text, sizeof(text));
      }
      if((pressed_a != digitalRead(PIN_BUTTON_A)) && (pressed_b != digitalRead(PIN_BUTTON_B)) && (pressed_c != digitalRead(PIN_BUTTON_C)) && (pressed_d != digitalRead(PIN_BUTTON_D))){
      Serial.print("no directional presses - stop Clear Crawler");
      Serial.println();
      const char text[] = "S"; //stop
      radio.write(&text, sizeof(text));
      }
      if(pressed_e == digitalRead(PIN_BUTTON_E)){
      Serial.print("e pressed"); //NOT YET ASSIGNED
      Serial.println();
      }
      if(pressed_f == digitalRead(PIN_BUTTON_F)){
      Serial.print("f pressed"); //NOT YET ASSIGNED
      Serial.println();
      }
      if(pressed_j == digitalRead(PIN_BUTTON_J)){
      Serial.print("j (joystick) pressed");
      Serial.println();
      const char text[] = "J"; //joystick button
      radio.write(&text, sizeof(text));
      }

      //analog sticks
      analog_x = analogRead(PIN_ANALOG_X);
      analog_y = analogRead(PIN_ANALOG_Y);
      
      //x axis
      if(analog_x > 1000){
        const char text[] = "4"; radio.write(&text, sizeof(text));
        Serial.println("4");
        }
      if((analog_x <1000) && (analog_x >600)){
        const char text[] = "3"; radio.write(&text, sizeof(text));
        Serial.println("3");
        }
      if((analog_x < 600) && (analog_x >400)){
        const char text[] = "2"; radio.write(&text, sizeof(text));
        Serial.println("2");
        delay(1);
        }
      if((analog_x <400) && (analog_x >200)){
        const char text[] = "1"; radio.write(&text, sizeof(text));
        Serial.println("1");
        }  
      if(analog_x < 200){
        const char text[] = "0"; radio.write(&text, sizeof(text));
        Serial.println("0");    
        }
      
      //y axis
      if(analog_y > 1000){
        const char text[] = "9"; radio.write(&text, sizeof(text));
        Serial.println("9");
        delay(1);
        }
      if((analog_y <1000) && (analog_y >600)){
        const char text[] = "8"; radio.write(&text, sizeof(text));
        Serial.println("8");
        }
      if((analog_y <600) && (analog_y >400)){
        const char text[] = "7"; radio.write(&text, sizeof(text));
        Serial.println("7");
        delay(1);
        }
      if((analog_y <400) && (analog_y >200)){
        const char text[] = "6"; radio.write(&text, sizeof(text));
        Serial.println("6");
        }
      if(analog_y < 200){
        const char text[] = "5"; radio.write(&text, sizeof(text));
        Serial.println("5");    
        }
//}
delay(5);
}
