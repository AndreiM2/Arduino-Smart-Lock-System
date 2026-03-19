#include <Servo.h>



int PINCorect[4]={2,2,3,1};
int PINIntrodus[4];
int indexPIN=0;

enum State{
  LOCKED,
  ENTERING,
  UNLOCKED,
  ALARM
};

State state= LOCKED;

const int btn1 = 2;
const int btn2 = 4;
const int btn3 = 8;
const int btn4 = 11;
const int btnEnter = 13;
const int buzzerPin = 12;
const int servoPin = 3;
unsigned long unlockStartTime = 0;
unsigned long alarmStartTime = 0;
int tries=0;

Servo myservo;

void setup() {
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);
  pinMode(btnEnter, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);        
  myservo.attach(servoPin);
  myservo.write(0);
}



void loop() {

  switch(state){
    case LOCKED:
      myservo.write(0);    
      if (digitalRead(btn1) == LOW || digitalRead(btn2) == LOW || digitalRead(btn3) == LOW || digitalRead(btn4) == LOW || digitalRead(btnEnter) == LOW)
      {
        indexPIN = 0;
        state = ENTERING;
        delay(200);
      }
      break;

   

    case ENTERING:
        if(indexPIN<4)
        {
          if (digitalRead(btn1) == LOW)
          {
            PINIntrodus[indexPIN] = 1;
            indexPIN++;
            tone(buzzerPin, 1000, 80);
            delay(200);
          }

        if (digitalRead(btn2) == LOW)
        {
          PINIntrodus[indexPIN] = 2;
          indexPIN++;
          tone(buzzerPin, 1000, 80);
          delay(200);
        }

        if (digitalRead(btn3) == LOW) {
          PINIntrodus[indexPIN] = 3;
          indexPIN++;
          tone(buzzerPin, 1000, 80);
          delay(200);
        }

        if (digitalRead(btn4) == LOW) {
          PINIntrodus[indexPIN] = 4;
          indexPIN++;
          tone(buzzerPin, 1000, 80);
          delay(200);
        }

      }

      if(indexPIN==4)
      {
        bool ok=true;
        for(int i=0;i<4;i++)
        {
          if(PINIntrodus[i]!=PINCorect[i])
          {
            ok=false;
            break;
          }
        }

        if(ok)
        {
          state=UNLOCKED;
          tries=0;
        }
        else
        {
          tries++;
          if(tries==3) state=ALARM;
          else state=LOCKED;
        }
        indexPIN=0;
        delay(500);
      }
      break;

    case UNLOCKED:
      myservo.write(90);
      if (unlockStartTime == 0)
      {
        unlockStartTime = millis();
        tone(buzzerPin, 1500, 150); // sunet succes
      }
      if (millis() - unlockStartTime >= 5000)
      {
        myservo.write(0); // închis
        unlockStartTime = 0;
        state = LOCKED;
      }
      break;

    case ALARM:
      myservo.write(0); // blocat închis
      if (alarmStartTime == 0) {
        alarmStartTime = millis();
      }
      if ((millis() / 150) % 2 == 0) tone(buzzerPin, 1200);
      else noTone(buzzerPin);

      if (millis() - alarmStartTime >= 10000)
      {
        noTone(buzzerPin);
        alarmStartTime = 0;
        state = LOCKED;
      }
      tries=0;
      break;
  }

}