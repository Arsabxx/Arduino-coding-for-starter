// Function: Only change LED state in very dark or very bright conditions, 
// with quick transitions in intermediate states

int lastBrightness = 0; // Record previous brightness

void setup() {
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int lightValue = analogRead(A0);
  int brightness;

  // Use thresholds and exaggerated contrast
  if (lightValue > 600) {
    // Very bright environment: LED almost off
    brightness = 5;
  } else if (lightValue > 500) {
    // Medium-bright: low brightness
    brightness = 60;
  } else if (lightValue > 400) {
    // Medium-dark: medium brightness
    brightness = 150;
  } else {
    // Very dark environment: maximum brightness
    brightness = 255;
  }

  // Only update when brightness change is significant to avoid minor fluctuations
  if (abs(brightness - lastBrightness) > 30) {
    analogWrite(9, brightness);
    lastBrightness = brightness;

    // Display status changes
    Serial.print("Light: ");
    Serial.print(lightValue);
    Serial.print(" → Brightness: ");
    Serial.print(brightness);

    // Use emojis to represent states
    if (brightness == 255) {
      Serial.println(" 🌟 Super Bright!");
    } else if (brightness >= 150) {
      Serial.println(" 💡 Very Bright");
    } else if (brightness >= 80) {
      Serial.println(" 💡 Medium");
    } else {
      Serial.println(" 🌙 Dim Light");
    }
  }

  delay(150);
}