// Pins definition: 1 button, 3 LEDs
int button = 2;
int led1 = 13;
int led2 = 12;
int led3 = 11;

// Only track if LEDs are on (2 states: off / on)
bool lightsOn = false;
// Track last button state to avoid repeated trigger
int lastBtnState = 1;

void setup() {
  pinMode(button, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  // All LEDs off at start
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}

void loop() {
  // Read current button state (1=pressed, 0=not pressed)
  int currentBtnState = digitalRead(button);

  // React only when button is pressed (state changes from 0 to 1)
  if (currentBtnState == 1 && lastBtnState == 0) {
    if (!lightsOn) {
      // 1st press: Turn on in order
      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led3, HIGH);
      lightsOn = true;
    } else {
      // 2nd press: Turn off in order
      digitalWrite(led1, LOW);
      delay(500);
      digitalWrite(led2, LOW);
      delay(500);
      digitalWrite(led3, LOW);
      lightsOn = false;
    }
  }

  // Update last button state
  lastBtnState = currentBtnState;
}
