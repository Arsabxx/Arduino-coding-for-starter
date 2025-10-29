// Define pins: Button connected to pin 2, LED connected to pin 13
int button = 2;
int led = 13;

void setup() {
  // Set pin modes: Button for receiving signal, LED for controlling on/off
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  // Read button state: 1 = pressed, 0 = not pressed
  int buttonState = digitalRead(button);
  delay(5);  // Anti-jitter delay (fixes LED flickering)

  // Press button → LED on; release → LED off
  if (buttonState == 1) {
    digitalWrite(led, HIGH);  // Pressed → LED on
  } else {
    digitalWrite(led, LOW);   // Not pressed → LED off
  }
}