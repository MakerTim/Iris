#include <AccelStepper.h>
#include <MultiStepper.h>

#define motor1Pin1 8
#define motor1Pin2 9
#define motor1Pin3 10
#define motor1Pin4 11

#define motor2Pin1 46
#define motor2Pin2 48
#define motor2Pin3 50
#define motor2Pin4 52

#define motor3Pin1 47
#define motor3Pin2 49
#define motor3Pin3 51
#define motor3Pin4 53

#define button1 22
#define button2 33
#define button3 24
#define button4 25

#define coinDetector 39

const int stepPin = 3; 
const int dirPin = 4; 

int stepsPerRevolution = 64;
int degreePerRevolution = 5.625;
int buttonPressed;

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

AccelStepper stepper1(AccelStepper::HALF4WIRE,motor1Pin1, motor1Pin3, motor1Pin2, motor1Pin4);
AccelStepper stepper2(AccelStepper::HALF4WIRE,motor2Pin1, motor2Pin3, motor2Pin2, motor2Pin4);
AccelStepper stepper3(AccelStepper::HALF4WIRE,motor3Pin1, motor3Pin3, motor3Pin2, motor3Pin4); 
void setup() {

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

  pinMode(coinDetector, INPUT);
   lcd.init();                 
  lcd.backlight();       
  
}

void loop() {
 lcd.clear();              
  screen1();   
  
  while (true) {
    if (digitalRead(coinDetector) == LOW) { 
      break;
    }
  }
lcd.clear();
screen2(); 

   while (true) {
    if (digitalRead(button1) == LOW) {
      buttonPressed = 1;
      break;
    }
    if (digitalRead(button2) == LOW) {
      buttonPressed = 2;
      break;
    }
    if (digitalRead(button3) == LOW) {
      buttonPressed = 3;
      break;
    }
    if (digitalRead(button4) == LOW) {
      buttonPressed = 4;
      break;
    }
  }
lcd.clear();
screen3();

//stappenmotors 1,2,3 zijn een andre motor dan 4
   switch (buttonPressed) {
    case 1:
    Serial.begin(9600);
  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(400.0);
  stepper1.setSpeed(1000);
  stepper1.moveTo(degToSteps(50));
  stepper1.run();
    break;

    case 2:
     Serial.begin(9600);
  stepper2.setMaxSpeed(1000);
  stepper2.setAcceleration(400.0);
  stepper2.setSpeed(1000);
  stepper2.moveTo(degToSteps(50));
  stepper2.run();
  break;

  case 3:
     Serial.begin(9600);
  stepper3.setMaxSpeed(1000);
  stepper3.setAcceleration(400.0);
  stepper3.setSpeed(1000);
  stepper3.moveTo(degToSteps(50));
  stepper3.run();
  break;
  
  case 4:
    for(int x = 0; x < 229; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(4000); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(4000);
     break;
}
   }
 }
 void screen1() {
  lcd.setCursor(0, 0);                  
  lcd.print("Werp een munt in"); 
}
void screen2() {              
  lcd.setCursor(0, 0);      
  lcd.print("Maak uw keuze ");            
}

void screen3() {
  lcd.setCursor(0, 0);
  lcd.print("Geniet ervan"); 
}

float degToSteps(float deg){
  return (stepsPerRevolution / degreePerRevolution)*deg;
}
