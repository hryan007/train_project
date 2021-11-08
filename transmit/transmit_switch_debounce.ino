boolean switch_debounce(int inputPin) {
  int counter = 0;
  int buttonState = 0;
  int lastButtonState = 0;

  int currentButtonState = 0;
  unsigned long lastDebounceTime = 0;
  unsigned long debounceDelay = 50;
  
  currentButtonState = digitalRead(inputPin);

  if (currentButtonState != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentButtonState != buttonState) {
      buttonState = currentButtonState;
      if (buttonState == LOW) {
        counter++;
        //Serial.println(counter);
      }
    }
  }
  Serial.println("switch = %d, read = %d", inputPin, currentButtonState);
  lastButtonState = currentButtonState;
  return currentButtonState;
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

  if(switch_debounce(red)) {
    signalCode = 2;
  }
  if(switch_debounce(yellow)) {
    signalCode = 3;
  }
  if(switch_debounce(green)) {
    signalCode = 4;
  }
  else signalCode = 0;
  
  radio.write(&signalCode,sizeof(signalCode));
  Serial.println(signalCode);



  delay(10);

}
