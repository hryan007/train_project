int inputPin = 7;
int counter = 0;
int buttonState = 0;
int lastButtonState = 0;

int currentButtonState = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  pinMode(inputPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  currentButtonState = digitalRead(inputPin);

  if (currentButtonState != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentButtonState != buttonState) {
      buttonState = currentButtonState;
      if (buttonState == LOW) {
        counter++;
        Serial.println(counter);
      }
    }
  }
  lastButtonState = currentButtonState;
}
