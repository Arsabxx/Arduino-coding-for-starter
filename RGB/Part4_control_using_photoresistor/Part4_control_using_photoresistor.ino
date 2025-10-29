// RGB LED pin definitions
int redPin = 9;     // Red LED connected to digital pin 9 (PWM)
int greenPin = 10;  // Green LED connected to digital pin 10 (PWM)
int bluePin = 11;   // Blue LED connected to digital pin 11 (PWM)
// Light sensor analog input pin
int lightSensorPin = A0;  // Photoresistor connected to analog pin A0

void setup() {
  // Set RGB pins as OUTPUT
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Initialize serial communication for debugging (optional)
  Serial.begin(9600);
}

/*
Function to set RGB LED color using PWM
 r - Red intensity (0-255)
 g - Green intensity (0-255)
b - Blue intensity (0-255)
 */
void setColor(int r, int g, int b) {
  analogWrite(redPin, r);    // Set red LED brightness
  analogWrite(greenPin, g);  // Set green LED brightness
  analogWrite(bluePin, b);   // Set blue LED brightness
}

/*
 Color cycle function - displays red, green, blue in sequence
 Each color lasts for 1 second
 */
void colorCycle() {
  setColor(255, 0, 0);  // Red color
  delay(1000);          // Display for 1 second
  setColor(0, 255, 0);  // Green color
  delay(1000);          // Display for 1 second
  setColor(0, 0, 255);  // Blue color
  delay(1000);          // Display for 1 second
}

void loop() {
  // Read photoresistor value (0-1023, lower value = darker environment)
  int lightValue = analogRead(lightSensorPin);

  // Map sensor value to RGB brightness (0-255, darker environment = higher brightness)
  int brightness = map(lightValue, 0, 1023, 255, 0);

  // Optional: Print values for debugging
  Serial.print("Light: ");
  Serial.print(lightValue);
  Serial.print(" -> Brightness: ");
  Serial.println(brightness);

  // Ambient light sensing control - adjust RGB brightness automatically
  setColor(brightness, brightness, brightness);  // White light (equal RGB values)
  delay(100);                                    // Short delay for stability

  // Timer-based color cycle trigger (executes every 5 seconds)
  static unsigned long lastColorTime = 0;
  if (millis() - lastColorTime > 5000) {
    colorCycle();
    lastColorTime = millis();
  }
}
