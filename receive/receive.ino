
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(8, 7);
int red = 2, yellow = 3, green = 4;
const byte address[6] = "00005";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int signalCode = 0;
  if (radio.available()) {
    radio.read(&signalCode, sizeof(signalCode));
    Serial.println(signalCode);
    if(signalCode!=0){
      digitalWrite(signalCode, HIGH);
    }else{
      digitalWrite(green, LOW);
      digitalWrite(red, LOW);
      digitalWrite(yellow, LOW);
    }
    
    
    //Serial.println(text);
  }

}
