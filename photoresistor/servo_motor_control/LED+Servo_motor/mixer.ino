// Enhanced Light-Controlled System - Servo & LED with Visual Feedback
// Function: Control servo angle and LED brightness based on ambient light with enhanced visualization
#include <Servo.h>  // Include the Servo library to control the servo motor

// Create objects and variables to store our components
Servo myServo;      // This creates a "servo object" that we can command to move
int servoPin = 9;   // The pin where servo signal wire is connected (PWM pin)
int photoPin = A0;  // The pin where photoresistor is connected (Analog pin)
int ledPin = 3;     // The pin where LED is connected (PWM pin for brightness control)

void setup() {
  // SETUP FUNCTION: Runs once when Arduino starts
  myServo.attach(servoPin);  // Tell the servo which pin it's connected to
  pinMode(ledPin, OUTPUT);   // Set LED pin as OUTPUT (we send signals TO it)
  
  Serial.begin(9600);        // Start communication with computer at 9600 bits per second
  
  // Print welcome messages to the Serial Monitor (like a text screen)
  Serial.println("=== Enhanced Light Control System ===");
  Serial.println("Control servo angle & LED brightness with visual feedback");
  Serial.println("NOTE: Photoresistor is REVERSED - covering it INCREASES readings");
  Serial.println("LED Behavior: High readings (covered) = BRIGHT, Low readings (light) = DIM");
}

void loop() {
  // LOOP: Runs repeatedly forever, like an infinite loop
  // This is where the main action happens!
  
  // Read light sensor value (REVERSED BEHAVIOR!)
  int lightValue = analogRead(photoPin);  // Read light level 
  // PHOTORESISTOR IS REVERSED:
  // - Low values (700) = BRIGHT LIGHT
  // - High values (900-950) = DARK (covered)
  
  // Calculate servo position based on REVERSED light readings
  int angle = 0;  // This will store the servo angle (0-180 degrees)
  
  // REVERSED Servo logic: higher readings (darker) = bigger angle
  if (lightValue > 900) {
    angle = 180;    // Very dark (covered): servo goes to maximum position (180°)
  } else if (lightValue < 700) {
    angle = 0;      // Very bright: servo goes to minimum position (0°)
  } else {
    // Medium range: map proportionally between 0-180 degrees
    // REVERSED mapping: 700-900 range maps to 0-180
    angle = map(lightValue, 700, 900, 0, 180);
  }
  
  //Calculate LED brightness based on REVERSED light readings
  int brightness = 0;  // This will store LED brightness (0=off, 255=full brightness)
  
  // REVERSED LED logic:
  // High readings (900-950 when covered) = BRIGHT LED
  // Low readings (700 when light) = DIM LED
  
  if (lightValue > 850) {
    // 1: DARK ENVIRONMENT (covered photoresistor = high readings > 850)
    // LED gets BRIGHTER when photoresistor is covered (higher readings)
    brightness = map(lightValue, 850, 1023, 200, 255);
    // This means: 850 = 200, 1023 = 255 (very bright)
    
  } else if (lightValue < 750) {
    // 3: BRIGHT ENVIRONMENT (light on photoresistor = low readings < 750)
    // LED gets DIMMER when there's light (lower readings)
    brightness = map(lightValue, 0, 750, 50, 10);
    // This means: 0 = 50, 750 = 10 (very dim)
    
  } else {
    // 2: TRANSITION ZONE (light between 750-850)
    // Smooth transition between bright and dim modes
    brightness = map(lightValue, 750, 850, 10, 200);
    // This means: 750 = 10, 850 = 200 (big range)
  }
  
  // Safety check: make sure brightness is always between 0-255
  brightness = constrain(brightness, 0, 255);
  
  // Send commands to hardware
  myServo.write(angle);           // Move servo to calculated angle
  analogWrite(ledPin, brightness); // Set LED to calculated brightness
  
  //Display information on Serial Monitor with REVERSED labels
  Serial.print("Light Reading:");
  Serial.print(lightValue);
  
  // Show what the reading actually means
  if (lightValue > 850) {
    Serial.print(" (COVERED/DARK)");
  } else if (lightValue < 750) {
    Serial.print(" (LIGHT/BRIGHT)");
  } else {
    Serial.print(" (TRANSITION)");
  }
  
  // Create a visual progress bar for light intensity
  Serial.print(" [");
  int lightBars = map(lightValue, 0, 1023, 0, 20);  // Convert to 20 bars
  for (int i = 0; i < 20; i++) {
    if (i < lightBars) {
      Serial.print("█");  // Filled block for current light level
    } else {
      Serial.print(" ");  // Empty space for remaining
    }
  }
  Serial.print("] ");
  
  Serial.print("→ Angle:");
  Serial.print(angle);
  Serial.print("° ");
  
  // Create visual indicator for servo position
  Serial.print("[");
  int angleBars = map(angle, 0, 180, 0, 10);  // Convert to 10 bars
  for (int i = 0; i < 10; i++) {
    if (i < angleBars) {
      Serial.print("▶");  // Triangle shows servo position
    } else {
      Serial.print("-");  // Dash for unused positions
    }
  }
  Serial.print("] ");
  
  Serial.print("LED:");
  Serial.print(brightness);
  
  // Create visual indicator for LED brightness
  Serial.print(" ["); 
  int ledBars = map(brightness, 0, 255, 0, 10);  // Convert to 10 bars
  for (int i = 0; i < 10; i++) {
    if (i < ledBars) {
      Serial.print("●");  // Filled circle for LED brightness
    } else {
      Serial.print("·");  // Dot for unused brightness
    }
  }
  Serial.print("]");
  
  // Add descriptive status message that matches REVERSED behavior
  if (lightValue > 850) {
    Serial.println(" 💡💡 BRIGHT LED! (Photoresistor COVERED)");
  } else if (lightValue < 750) {
    Serial.println(" 🌙🌙 DIM LED! (Photoresistor in LIGHT)");
  } else {
    Serial.println(" 🔄 TRANSITION ZONE");
  }
  
  //Wait a bit before next reading (150 milliseconds = 0.15 seconds)
  delay(150);
}

/*
FOR PHOTORESISTOR:

photoresistor behavior:
- LIGHT on sensor → LOW readings (around 700)
- COVERED sensor → HIGH readings (900-950)

logic:
- When readings are HIGH (900-950 = covered/dark) → LED BRIGHT
- When readings are LOW (700 = light/bright) → LED DIM

Servo behavior:
- HIGH readings (covered) → 180° 
- LOW readings (light) → 0°

- Cover photoresistor → LED gets bright, servo moves to 180°
- Shine light on photoresistor → LED gets dim, servo moves to 0°
*/