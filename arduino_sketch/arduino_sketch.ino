
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
int previousState = LOW;
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    if (previousState == LOW) {
      Serial.print("tmut");
      previousState = HIGH;
    }
    digitalWrite(ledPin, HIGH);
  } else {
    if (previousState == HIGH) {
      previousState = LOW;
    }
    digitalWrite(ledPin, LOW);
  }
}
