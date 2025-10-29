// Light-Controlled Servo - Core Code
// Function: Control servo angle based on ambient light intensity

#include <Servo.h>  // Include servo library

Servo myServo;      // Create servo object
int servoPin = 9;   // Servo signal pin
int photoPin = A0;  // Photoresistor pin

void setup() {
  // Attach servo to specified pin
  myServo.attach(servoPin);
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read photoresistor value (0-1023)
  int lightValue = analogRead(photoPin);
  
  // Map light value to servo angle (0-1023 → 0-180 degrees)
  // Brighter environment = larger servo angle; Darker environment = smaller servo angle
  int angle = map(lightValue, 0, 1023, 0, 180);
  
  // Control servo to move to calculated angle
  myServo.write(angle);
  
  // Display detailed information on serial monitor
  Serial.print("Ambient Light: ");
  Serial.print(lightValue);
  Serial.print(" → Servo Angle: ");
  Serial.print(angle);
  Serial.println("°");
  
  // Short delay
  delay(100);
}