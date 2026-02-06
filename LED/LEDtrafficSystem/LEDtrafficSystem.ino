// Pedestrian Crossing System


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int redPin = 11;
int yellowPin = 12;
int greenPin = 13;
int buttonPin = 2;
int pedestrianPin = 9;

const unsigned long MAX_GREEN_TIME = 25000;   
const unsigned long PEDESTRIAN_TIME = 10000;   
const unsigned long YELLOW_TIME = 3000;        
const unsigned long MIN_AFTER_BUTTON = 5000;   
const unsigned long COUNTDOWN_START = 15000;   

enum SystemState {
  VEHICLE_GREEN,
  VEHICLE_YELLOW,
  PEDESTRIAN_WALK
};
SystemState currentState = VEHICLE_GREEN;

unsigned long stateStartTime = 0;
unsigned long buttonPressTime = 0;
bool buttonPressed = false;
bool countdownActive = false;
unsigned long plannedSwitchTime = MAX_GREEN_TIME;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(pedestrianPin, OUTPUT);
 
  lcd.init();
  lcd.backlight();
  
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(pedestrianPin, LOW);
  
  startVehicleGreen();
}

void loop() {
  checkButton();
  switch (currentState) {
    case VEHICLE_GREEN:
      handleVehicleGreen();
      break;
    case VEHICLE_YELLOW:
      handleVehicleYellow();
      break;
    case PEDESTRIAN_WALK:
      handlePedestrianWalk();
      break;
  }
}

void checkButton() {
  int buttonState = digitalRead(buttonPin);
  if (currentState == VEHICLE_GREEN && !countdownActive) {
    if (buttonState == LOW) {
      if (!buttonPressed) {
        buttonPressed = true;
        unsigned long currentGreenTime = millis() - stateStartTime;
        if (currentGreenTime < COUNTDOWN_START) {
          plannedSwitchTime = (currentGreenTime + MIN_AFTER_BUTTON > COUNTDOWN_START) ? 
                             (currentGreenTime + MIN_AFTER_BUTTON) : COUNTDOWN_START;
          plannedSwitchTime = (plannedSwitchTime < MAX_GREEN_TIME) ? plannedSwitchTime : MAX_GREEN_TIME;
        } else {
          plannedSwitchTime = currentGreenTime + MIN_AFTER_BUTTON;
          plannedSwitchTime = (plannedSwitchTime < MAX_GREEN_TIME) ? plannedSwitchTime : MAX_GREEN_TIME;
          countdownActive = true;
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Button Pressed!");
        lcd.setCursor(0, 1);
        lcd.print("Processing...  ");
        delay(1500);
        updateDisplay();
      }
    } else {
      buttonPressed = false;
    }
  }
}

void handleVehicleGreen() {
  unsigned long currentTime = millis() - stateStartTime;
  static unsigned long lastDisplayUpdate = 0;
  if (millis() - lastDisplayUpdate >= 500) {
    updateDisplay();
    lastDisplayUpdate = millis();
  }
  if (currentTime >= plannedSwitchTime) {
    startVehicleYellow();
  }
}

void handleVehicleYellow() {
  unsigned long currentTime = millis() - stateStartTime;
  if (currentTime >= YELLOW_TIME) {
    startPedestrianWalk();
  }
}

void handlePedestrianWalk() {
  unsigned long currentTime = millis() - stateStartTime;
  updatePedestrianDisplay(currentTime);
  if (currentTime >= PEDESTRIAN_TIME) {
    startVehicleGreen();
  }
}

void startVehicleGreen() {
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(pedestrianPin, LOW);

  stateStartTime = millis();
  currentState = VEHICLE_GREEN;
  buttonPressed = false;
  countdownActive = false;
  plannedSwitchTime = MAX_GREEN_TIME;

  lcd.clear();
  updateDisplay();
}

void startVehicleYellow() {
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(redPin, LOW);

  stateStartTime = millis();
  currentState = VEHICLE_YELLOW;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cars: YELLOW    ");
  lcd.setCursor(0, 1);
  lcd.print("Prepare to Stop ");
}

void startPedestrianWalk() {
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, HIGH);
  digitalWrite(pedestrianPin, HIGH);

  stateStartTime = millis();
  currentState = PEDESTRIAN_WALK;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WALK NOW!       ");
}

void updateDisplay() {
  if (currentState == VEHICLE_GREEN) {
    unsigned long currentTime = millis() - stateStartTime;
    unsigned long remainingTime = plannedSwitchTime - currentTime;
    int secondsLeft = remainingTime / 1000;
    
    lcd.setCursor(0, 0);
    lcd.print("Cars: GREEN     ");
    
    lcd.setCursor(0, 1);
    
    if (countdownActive) {
      lcd.print("Countdown: ");
      if (secondsLeft < 10) lcd.print(" ");
      lcd.print(secondsLeft);
      lcd.print("s  ");
    } else {
      lcd.print("Time:");
      if (secondsLeft < 10) lcd.print(" ");
      lcd.print(secondsLeft);
      lcd.print("s ");

      static bool blinkState = false;
      static unsigned long lastBlink = 0;
      
      if (millis() - lastBlink > 800) {
        blinkState = !blinkState;
        lastBlink = millis();
      }
      
      if (blinkState && currentTime < COUNTDOWN_START) {
        lcd.print("PRESS BTN");
      } else {
        lcd.print("         ");
      }
    }
  }
}

void updatePedestrianDisplay(unsigned long currentTime) {
  unsigned long remainingTime = PEDESTRIAN_TIME - currentTime;
  int secondsLeft = remainingTime / 1000;

  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  if (secondsLeft < 10) lcd.print(" ");
  lcd.print(secondsLeft);
  lcd.print("s       ");

  if (remainingTime <= 3000) {
    digitalWrite(pedestrianPin, (millis() / 500) % 2);
    lcd.setCursor(0, 0);
    if (remainingTime > 2000) {
      lcd.print("HURRY! 3s      ");
    } else if (remainingTime > 1000) {
      lcd.print("QUICK! 2s      ");
    } else {
      lcd.print("FAST! 1s       ");
    }
  } else {
    lcd.setCursor(0, 0);
    lcd.print("WALK NOW!       ");
  }
}
