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

/*
 Breathing light function - creates smooth fade effect
 pin - Target pin to control
 start - Starting brightness (0-255)
 end - Ending brightness (0-255)
 */
 
void breathe(int pin, int start, int end) {
  int step = (start < end) ? 1 : -1;  // Determine step direction (fade in or fade out)
  
  // Loop through brightness values from start to end
  for (int i = start; (step > 0 && i <= end) || (step < 0 && i >= end); i += step) {
    analogWrite(pin, i);  // Analog write (PWM) to control brightness
    delay(10);            // Delay to control breathing speed
  }
}

/*
 Function to set RGB LED color using PWM
 r - Red intensity (0-255, where 255 is maximum brightness)
 g - Green intensity (0-255, where 255 is maximum brightness) 
 b - Blue intensity (0-255, where 255 is maximum brightness)
 */
 
void setColor(int r, int g, int b) {
  analogWrite(redPin, r);    // Set red LED intensity
  analogWrite(greenPin, g);  // Set green LED intensity
  analogWrite(bluePin, b);   // Set blue LED intensity
}

void loop() {
  // Breathing light effect (using red as example, can be extended to green and blue)
  breathe(redPin, 0, 255);  // Red fades from dark to bright
  breathe(redPin, 255, 0);  // Red fades from bright to dark

  // Color cycle (Red → Green → Blue → Red)
  setColor(255, 0, 0);    // Red color
  delay(1000);           // Hold for 1 second
  setColor(0, 255, 0);    // Green color
  delay(1000);
  setColor(0, 0, 255);    // Blue color
  delay(1000);
}
