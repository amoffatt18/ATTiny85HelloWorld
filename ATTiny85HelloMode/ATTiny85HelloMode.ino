int but = 0; // button pin location
int led = 1; // led pin location

boolean butState = false; // sets the button state to false
boolean prevState = false; // sets the previous state to false

int switchVal = 2; // initializes the switch cases

unsigned long startTime; // begins the timer
unsigned long endTime; // ends the timer
unsigned long interval = 100; // sets the interval to 100ms


void setup() {

  Serial.begin(9600);
  pinMode (but, INPUT);
  pinMode (led, OUTPUT);

  startTime = millis(); // initializes the start timer
}

void loop() {

  butState = debounce(but, prevState); // debounces the button state

  if (butState == HIGH && prevState == LOW) {
    switchVal = switchVal + 1;

    if (switchVal == 3) { // resets the cases if it exceeds past case 2
      switchVal = 0;
    }
  }
  switch (switchVal) {
    case 0: // keeps the led off
      digitalWrite (led, LOW);
      break;

    case 1: // this case turns the led on
      digitalWrite (led, HIGH);
      break;

    case 2: // the last case makes the led flash
      endTime = millis();
      if (endTime - startTime >= interval) {
        digitalWrite (led, HIGH);

        startTime = millis();
        digitalWrite (led, LOW);
      }
      break;

  }

  prevState = butState;
}

boolean debounce(int aRandomButtonPin, boolean aPrevButtonState) {

  boolean aButtonState = digitalRead(aRandomButtonPin);

  if (aButtonState != aPrevButtonState) {
    delay(5);
    aButtonState = digitalRead(aRandomButtonPin);
  }

  return aButtonState;



}
