#include <FlexiTimer2.h>
#include <Keyboard.h>
#include <Mouse.h>

const int movePixel = 2;

volatile int state = LOW;
volatile int intState = LOW;
volatile int moveState = LOW;

volatile unsigned long timeNow = 0;
volatile unsigned long timePrev = 0;

unsigned long timeChat = 500;
unsigned long moveDelay = 1000*30;

void mouseMove() {
  if(moveState == LOW) {
    Mouse.move(movePixel, 0, 0);
  }else{
    Mouse.move(-movePixel, 0, 0);
  }
  moveState = !moveState;
}

void switchOn() {
  intState = HIGH;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(0, switchOn, FALLING);

  FlexiTimer2::set(moveDelay, mouseMove);
  FlexiTimer2::start();

  Keyboard.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  timeNow = millis();
  if(intState == HIGH){
    if(timeNow - timePrev > timeChat){
      if(state == HIGH){
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('l');
        delay(10);
        Keyboard.releaseAll();

        FlexiTimer2::stop(); 
      }else{
        Keyboard.press(' ');
        delay(10);
        Keyboard.releaseAll();

        FlexiTimer2::start();
      }
      digitalWrite(LED_BUILTIN, state); 
      state = !state;
      timePrev = timeNow;
    }
    intState = LOW;
  }
}
