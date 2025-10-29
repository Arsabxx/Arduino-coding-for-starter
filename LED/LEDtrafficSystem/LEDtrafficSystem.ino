// Pedestrian Crossing System


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// 引脚定义
int redPin = 11;
int yellowPin = 12;
int greenPin = 13;
int buttonPin = 2;
int pedestrianPin = 9;

// 时间设置
const unsigned long MAX_GREEN_TIME = 25000;    // 最大绿灯时间2秒5
const unsigned long PEDESTRIAN_TIME = 10000;   // 行人通行时间10秒
const unsigned long YELLOW_TIME = 3000;        // 黄灯时间3秒
const unsigned long MIN_AFTER_BUTTON = 5000;   // 按钮按下后至少5秒绿灯
const unsigned long COUNTDOWN_START = 15000;   // 从15秒开始倒数

// 系统状态
enum SystemState {
  VEHICLE_GREEN,
  VEHICLE_YELLOW,
  PEDESTRIAN_WALK
};
SystemState currentState = VEHICLE_GREEN;

// 系统变量
unsigned long stateStartTime = 0;
unsigned long buttonPressTime = 0;
bool buttonPressed = false;
bool countdownActive = false;
unsigned long plannedSwitchTime = MAX_GREEN_TIME;

void setup() {
  // 设置引脚模式
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(pedestrianPin, OUTPUT);
  
  // 初始化LCD
  lcd.init();
  lcd.backlight();
  
  // 开始时关闭所有灯
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(pedestrianPin, LOW);
  
  // 开始车辆绿灯
  startVehicleGreen();
}

void loop() {
  // 检查按钮状态
  checkButton();
  
  // 根据当前状态处理
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
  
  // 只有在绿灯阶段才检测按钮
  if (currentState == VEHICLE_GREEN && !countdownActive) {
    if (buttonState == LOW) {
      // 按钮按下
      if (!buttonPressed) {
        buttonPressed = true;
        unsigned long currentGreenTime = millis() - stateStartTime;
        
        // 计算计划切换时间
        if (currentGreenTime < COUNTDOWN_START) {
          // 如果当前时间少于15秒，确保至少还有5秒绿灯
          plannedSwitchTime = (currentGreenTime + MIN_AFTER_BUTTON > COUNTDOWN_START) ? 
                             (currentGreenTime + MIN_AFTER_BUTTON) : COUNTDOWN_START;
          plannedSwitchTime = (plannedSwitchTime < MAX_GREEN_TIME) ? plannedSwitchTime : MAX_GREEN_TIME;
        } else {
          // 如果当前时间超过15秒，开始5秒倒数
          plannedSwitchTime = currentGreenTime + MIN_AFTER_BUTTON;
          plannedSwitchTime = (plannedSwitchTime < MAX_GREEN_TIME) ? plannedSwitchTime : MAX_GREEN_TIME;
          countdownActive = true;
        }
        
        // 显示按钮反馈
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Button Pressed!");
        lcd.setCursor(0, 1);
        lcd.print("Processing...  ");
        delay(1500);
        
        // 回到正常显示
        updateDisplay();
      }
    } else {
      // 按钮释放
      buttonPressed = false;
    }
  }
}

void handleVehicleGreen() {
  unsigned long currentTime = millis() - stateStartTime;
  
  // 更新显示
  static unsigned long lastDisplayUpdate = 0;
  if (millis() - lastDisplayUpdate >= 500) {
    updateDisplay();
    lastDisplayUpdate = millis();
  }
  
  // 检查切换条件
  if (currentTime >= plannedSwitchTime) {
    startVehicleYellow();
  }
}

void handleVehicleYellow() {
  unsigned long currentTime = millis() - stateStartTime;
  
  // 检查黄灯时间是否结束
  if (currentTime >= YELLOW_TIME) {
    startPedestrianWalk();
  }
}

void handlePedestrianWalk() {
  unsigned long currentTime = millis() - stateStartTime;
  
  // 更新行人显示
  updatePedestrianDisplay(currentTime);
  
  // 检查是否结束行人阶段
  if (currentTime >= PEDESTRIAN_TIME) {
    startVehicleGreen();
  }
}

void startVehicleGreen() {
  // 设置灯光 - 车辆绿灯，行人红灯
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(pedestrianPin, LOW);
  
  // 重置状态
  stateStartTime = millis();
  currentState = VEHICLE_GREEN;
  buttonPressed = false;
  countdownActive = false;
  plannedSwitchTime = MAX_GREEN_TIME;
  
  // 更新显示
  lcd.clear();
  updateDisplay();
}

void startVehicleYellow() {
  // 设置灯光 - 车辆黄灯
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(redPin, LOW);
  
  // 重置状态时间
  stateStartTime = millis();
  currentState = VEHICLE_YELLOW;
  
  // 更新显示
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cars: YELLOW    ");
  lcd.setCursor(0, 1);
  lcd.print("Prepare to Stop ");
}

void startPedestrianWalk() {
  // 设置灯光 - 车辆红灯，行人绿灯
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, HIGH);
  digitalWrite(pedestrianPin, HIGH);
  
  // 重置状态时间
  stateStartTime = millis();
  currentState = PEDESTRIAN_WALK;
  
  // 更新显示
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
      // 倒数模式显示
      lcd.print("Countdown: ");
      if (secondsLeft < 10) lcd.print(" ");
      lcd.print(secondsLeft);
      lcd.print("s  ");
    } else {
      // 正常模式显示
      lcd.print("Time:");
      if (secondsLeft < 10) lcd.print(" ");
      lcd.print(secondsLeft);
      lcd.print("s ");
      
      // 按钮提示闪烁
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
  
  // 显示剩余时间
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  if (secondsLeft < 10) lcd.print(" ");
  lcd.print(secondsLeft);
  lcd.print("s       ");
  
  // 最后3秒闪烁警告
  if (remainingTime <= 3000) {
    // 闪烁行人LED
    digitalWrite(pedestrianPin, (millis() / 500) % 2);
    
    // 显示紧急信息
    lcd.setCursor(0, 0);
    if (remainingTime > 2000) {
      lcd.print("HURRY! 3s      ");
    } else if (remainingTime > 1000) {
      lcd.print("QUICK! 2s      ");
    } else {
      lcd.print("FAST! 1s       ");
    }
  } else {
    // 正常显示
    lcd.setCursor(0, 0);
    lcd.print("WALK NOW!       ");
  }
}