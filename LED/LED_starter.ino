// Tell Arduino: LED in pin 13
int led = 13;

void setup() {
  // Set rules: LED is a "device to be turned on/off"
  pinMode(led, OUTPUT);
  // Turn LED on at startup (after writing this line, the light stays on)
  digitalWrite(led, 1);
}

void loop() {
  // Nothing to write here! Because the light is already on in setup, no need to repeat in loop
}