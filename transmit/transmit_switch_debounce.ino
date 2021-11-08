boolean switch_debounce(int inputPin) {
const int buttonPin = inputPin;    // the number of the pushbutton pin
//const int ledPin = 13;      // the number of the LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;  

  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }

  // set the LED:
  //digitalWrite(ledPin, ledState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  return ledState;

}



#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(8, 7);
int red=2,yellow=3,green=4;
const byte address[6] = "00005";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  pinMode(red,INPUT);
  
  pinMode(yellow,INPUT);
  pinMode(green,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  //char text[]="Hello Rimo";
  int signalCode=0;
  //radio.write(&text,sizeof(text));

  /*if(digitalRead(red)==HIGH){
    signalCode=2;
  }else if(digitalRead(yellow)==HIGH){
    signalCode=3;
  }else if(digitalRead(green)==HIGH){
    signalCode=4;
  }else{
    signalCode=0;
  }*/

  if(switch_debounce(red) == 1) {
    signalCode = 2;
  }
  if(switch_debounce(yellow) == 1) {
    signalCode = 3;
  }
  if(switch_debounce(green) == 1) {
    signalCode = 4;
  }
  else signalCode = 0;
  
  radio.write(&signalCode,sizeof(signalCode));
  Serial.println(signalCode);



  delay(10);

}
