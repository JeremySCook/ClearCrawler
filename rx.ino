    //servo setup
    #include <Servo.h>   
    Servo headX;
    Servo headY;
    
    //LED setup
    #include "LedControl.h"
    LedControl lc = LedControl(4,2,3,1); //1 matrix selcted - both act the same way
    unsigned long delayTime = 500; //wait between updates

    //NRF setup
    #include <SPI.h>
    #include <nRF24L01.h>
    #include <RF24.h>
    RF24 radio(9, 10); // CE, CSN
    const byte address[6] = "00001";
    
    //input variable setup
    int buttonState = HIGH; //state input button

    void setup() {
      Serial.begin(9600);

      headX.attach(6);
      headY.attach(5);
      headX.write(50);
      headY.write(95);
      
      //radio setup
      radio.begin();
      radio.openReadingPipe(0, address);
      radio.setPALevel(RF24_PA_MIN); //set as: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
      //radio.setDataRate(RF24_250KBPS); //set as: F24_250KBPS, F24_1MBPS, F24_2MBPS ==>250KBPS = longest range
      //radio.setChannel(80); //sets channel from 2.4 to 2.524 GHz in 1 MHz increments 2.483.5 GHz is normal legal limit
      radio.startListening();

      //LED setup
      lc.shutdown(0,false);
      lc.setIntensity(0,2);
      lc.clearDisplay(0);
      lookCenter();

      //input setup
      pinMode(0, INPUT_PULLUP); //button for when Tx/Rx not communicating

      //output setup
      pinMode(A0, OUTPUT); //activate motor IN1
      pinMode(A1, OUTPUT); //activate motor IN2
      pinMode(A2, OUTPUT); //activate motor IN3
      pinMode(A3, OUTPUT); //activate motor IN4

      //beep
      tone(7, 1000, 250);
      
    }
    void loop() {
      buttonState = digitalRead(0);

      if (buttonState == LOW) {
        lookBig();
        headY.write(105);
        forward();
        delay(1000);
        headY.write(95);
        stopLegs();
        lookCenter();
      }
      
      if (radio.available()) {
        char text[32] = "";
        radio.read(&text, sizeof(text));
        String Data = String(text);
        Serial.println(text);
        if(Data == "L") {
          Serial.println("is L - connected");
          //digitalWrite(13, HIGH); //need to change?
          delay(5);
        }
        if(Data == "A") {
          forward();
          lookCenter();
          Serial.println("A");
        }
        if(Data == "B") {
          right();
          lookRight();
          Serial.println("B");
        }
        if(Data == "C") {
          back();
          lookCenter();
          Serial.println("C");
        }
        if(Data == "D") {
          left();
          lookLeft();
          Serial.println("D");
        }
        if(Data == "S") {
          stopLegs();
          lookCenter();
          Serial.println("S");
        }
        if(Data == "J") {
          tone(7, 1000, 100);
          Serial.println("J - Joystick");
        }

        //Head analog data
        //headX
          if(Data == "0") {
          headX.write(70);
          Serial.println("0");
        }
          if(Data == "1") {
          headX.write(60);
          Serial.println("1");
        }
          if(Data == "2") {
          headX.write(50);
          Serial.println("2");
        }
          if(Data == "3") {
          headX.write(40);
          Serial.println("3");
        }
          if(Data == "4") {
          headX.write(30);
          Serial.println("4");
        }

        
        //headY
          if(Data == "5") {
          headY.write(105);
          Serial.println("5");
        }
          if(Data == "6") {
          headY.write(100);
          Serial.println("5");
        }
          if(Data == "7") {
          headY.write(95);
          Serial.println("7");
        }
          if(Data == "8") {
          headY.write(90);
          Serial.println("9");
        } 
          if(Data == "9") {
          headY.write(85);
          Serial.println("9");
        }      
        
      }
      else Serial.println("no radio available");
      delay(5);
    }

    void forward(){
      Serial.println("Forward");
      //lookCenter();
      digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, LOW);

    }
    void back(){
      Serial.println("Back");
      digitalWrite(A0, LOW);
      //lookCenter();
      digitalWrite(A1, HIGH);
      digitalWrite(A2, LOW);
      digitalWrite(A3, HIGH);

    }
    void left(){
      Serial.println("Left");
      //lookLeft();
      digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
      digitalWrite(A2, LOW);
      digitalWrite(A3, HIGH);
    }
    void right(){
      Serial.println("Right");
      //lookRight();
      digitalWrite(A0, LOW);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, LOW);

    }
    void stopLegs(){
      Serial.println("Stop");
      //lookCenter();
      digitalWrite(A0, LOW);
      digitalWrite(A1, LOW);
      digitalWrite(A2, LOW);
      digitalWrite(A3, LOW);

    }

 //LED routines
  void lookCenter(){
  //look center
  lc.clearDisplay(0);
  lc.setColumn(0,2,B00111100);
  lc.setColumn(0,3,B00111100);
  lc.setColumn(0,4,B00110100);  
  lc.setColumn(0,5,B00111100);
  }
   void lookRight(){
  //look right
  lc.clearDisplay(0);
  lc.setColumn(0,2,B01111000);
  lc.setColumn(0,3,B01111000);
  lc.setColumn(0,4,B01101000);  
  lc.setColumn(0,5,B01111000);
  }
   void lookLeft(){
  //look left
  lc.clearDisplay(0);
  lc.setColumn(0,2,B00011110);
  lc.setColumn(0,3,B00011110);
  lc.setColumn(0,4,B00011010);  
  lc.setColumn(0,5,B00011110);
  }
  void lookBig(){
  lc.clearDisplay(0);
  lc.setColumn(0,1,B01111110);
  lc.setColumn(0,2,B01111110);
  lc.setColumn(0,3,B01110010);
  lc.setColumn(0,4,B01110010);  
  lc.setColumn(0,5,B01111110);
  lc.setColumn(0,6,B01111110);
  }
