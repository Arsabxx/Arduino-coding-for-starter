// Define RGB LED pins
int redPin = 9;    // Red pin connected to digital pin 9
int greenPin = 10; // Green pin connected to digital pin 10
int bluePin = 11;  // Blue pin connected to digital pin 11

void setup() {
  // Set all RGB pins as OUTPUT mode
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void setColor(int r, int g, int b) {
  analogWrite(redPin, r);    // Set red LED intensity using PWM
  analogWrite(greenPin, g);  // Set green LED intensity using PWM
  analogWrite(bluePin, b);   // Set blue LED intensity using PWM
}

void loop() {
  // Example 1: Pink color
  setColor(255, 100, 150);  // High red, medium green, medium blue
  delay(1000);              // Wait for 1 second

  // Example 2: Purple color
  setColor(150, 0, 255);    // Medium red, no green, high blue
  delay(1000);              // Wait for 1 second

  // Example 3: Dark yellow color
  setColor(200, 150, 0);    // High red, medium green, no blue
  delay(1000);              // Wait for 1 second

  // Example 4: Orange color
  setColor(255, 120, 0);    // Maximum red, medium green, no blue
  delay(1000);              // Wait for 1 second

  // Example 5: Cyan color
  setColor(0, 200, 200);    // No red, high green, high blue
  delay(1000);              // Wait for 1 second

  // Example 6: Light gray color
  setColor(100, 100, 100);  // Equal low intensity for all colors
  delay(1000);              // Wait for 1 second
}
