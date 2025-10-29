// PWM Controlled LED Brightness Test Code
// Function: Create a breathing light effect (gradually brightens then gradually dims)

void setup() {
  // Set digital pin 9 to output mode
  // Note: Must use PWM pins with ~ symbol (3,5,6,9,10,11) to adjust brightness
  pinMode(9, OUTPUT);
}

void loop() {
  // Part 1: Make LED gradually brighten
  // Use for loop to increase brightness value from 0 to 255 step by step
  for(int i = 0; i < 255; i++) {
    // analogWrite value range is 0-255, 0 = darkest, 255 = brightest
    analogWrite(9, i);
    // Short delay to make brightness changes visible
    delay(10);
  }
  
  // Part 2: Make LED gradually dim
  // Use for loop to decrease brightness value from 255 to 0 step by step
  for(int i = 255; i > 0; i--) {
    analogWrite(9, i);
    delay(10);
  }
}