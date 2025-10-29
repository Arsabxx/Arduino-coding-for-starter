// Define RGB LED pins
int red = 9;      // Red pin connected to digital pin 9
int green = 10;   // Green pin connected to digital pin 10  
int blue = 11;    // Blue pin connected to digital pin 11

void setup() {
  // Set all RGB pins as OUTPUT mode
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

/*
 * Function to set RGB LED color
 r - Red intensity (0-255, where 255 is brightest)
 g - Green intensity (0-255, where 255 is brightest)  
 b - Blue intensity (0-255, where 255 is brightest)
 */
 
void setColor(int r, int g, int b) {
  analogWrite(red, r);      // Set red LED intensity using PWM
  analogWrite(green, g);    // Set green LED intensity using PWM
  analogWrite(blue, b);     // Set blue LED intensity using PWM
}

void loop() {
  // Display RED color
  setColor(255, 0, 0);  // Maximum red, no green, no blue
  delay(1000);          // Wait for 1 second
  
  // Display GREEN color 
  setColor(0, 255, 0);  // No red, maximum green, no blue
  delay(1000);          // Wait for 1 second
  
  // Display BLUE color
  setColor(0, 0, 255);  // No red, no green, maximum blue
  delay(1000);          // Wait for 1 second
  
  // Display WHITE color (Red + Green + Blue)
  setColor(255, 255, 255);  // Maximum red, green and blue
  delay(1000);              // Wait for 1 second
}
