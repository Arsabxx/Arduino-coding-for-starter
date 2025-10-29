// 增强版光控舵机 - 带进度条和状态反馈
// 功能：更直观地显示光线与角度的关系

#include <Servo.h>

Servo myServo;
int servoPin = 9;
int photoPin = A0;

void setup() {
  myServo.attach(servoPin);
  Serial.begin(9600);
  Serial.println("=== 增强版光控舵机 ===");
  Serial.println("光线控制舵机角度 - 带可视化反馈");
}

void loop() {
  int lightValue = analogRead(photoPin);
  
  // 使用非线性映射，让响应更明显
  int angle = 0;
  if (lightValue > 800) {
    angle = 180;  // 很亮时转到最大角度
  } else if (lightValue < 200) {
    angle = 0;    // 很暗时转到最小角度
  } else {
    // 中等范围使用正常映射
    angle = map(lightValue, 200, 800, 0, 180);
  }
  
  // 控制舵机
  myServo.write(angle);
  
  // 增强的串口输出，带可视化进度条
  Serial.print("光线:");
  Serial.print(lightValue);
  
  // 光线强度进度条（20个字符宽度）
  Serial.print(" [");
  int lightBars = map(lightValue, 0, 1023, 0, 20);
  for (int i = 0; i < 20; i++) {
    if (i < lightBars) {
      Serial.print("█");
    } else {
      Serial.print(" ");
    }
  }
  Serial.print("] ");
  
  Serial.print("→ 角度:");
  Serial.print(angle);
  Serial.print("° ");
  
  // 角度进度条（10个字符宽度）
  Serial.print("[");
  int angleBars = map(angle, 0, 180, 0, 10);
  for (int i = 0; i < 10; i++) {
    if (i < angleBars) {
      Serial.print("▶"); // 用三角形表示角度位置
    } else {
      Serial.print("-");
    }
  }
  Serial.print("]");
  
  // 状态描述
  if (angle > 150) {
    Serial.println(" 🔥 最大角度");
  } else if (angle > 100) {
    Serial.println(" 🔆 大角度");
  } else if (angle > 50) {
    Serial.println(" 💡 中角度");
  } else {
    Serial.println(" 🌙 小角度");
  }
  
  delay(150);
}