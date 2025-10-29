const int lightPin = A0; // photoresistor must connect to A0
const int ledPin = 13; // ledPin must connect to 13
int threshold = 900; // set a middle threshold(when the analogread result meet this value, the LED will change)

void setup() {
  pinMode(ledPin, OUTPUT); // output singel mode
  Serial.begin(9600); // oprn the serial port
}

void loop() {
  int lightVal = analogRead(lightPin); // the ligth value is equal to the analogRead from the photoresistor
  Serial.println(lightVal); // can check the collect data from the photoresistor

  if (lightVal < threshold) { // if the light value smaller that threshold
    digitalWrite(ledPin, HIGH); //then light up
  } else { //otherwise
    digitalWrite(ledPin, LOW); //light down
  }
  delay(100); //delay for the loop, to avoid repectition
}
