// Photoresistor Basic Test Code
// Function: Read ambient light intensity and display on serial monitor

void setup() {
  // Initialize serial communication, set baud rate to 9600
  // This allows us to see the data sent by Arduino on the computer
  Serial.begin(9600);
}

void loop() {
  // Read the value from analog pin A0
  // Photoresistor value range is 0-1023, 0 = darkest, 1023 = brightest
  int lightValue = analogRead(A0);
  
  // Print the light value to serial monitor
  Serial.println(lightValue);
  
  // Wait 500 milliseconds (0.5 seconds) to avoid data refreshing too fast to read clearly
  delay(500);
}