#include <LiquidCrystal.h>

#define Motor_forward         0
#define Motor_return          1
#define Motor_L_dir_pin       7
#define Motor_R_dir_pin       8
#define Motor_L_pwm_pin       9
#define Motor_R_pwm_pin       10
#define joyX A8
#define joyY A9
float xMap, yMap, xValue, yValue;
const int buttonPin = 19;
volatile int buttonState;
int count = 0;

float arrayOfSpeed[2];

LiquidCrystal lcd(37, 36, 35, 34, 33, 32);
#define trimmer A3
#define power A4
void setup()
{
  Serial.begin(9600);
  delay(200);
  Serial.print("JollyCooperation\n");
 
  pinMode(buttonPin, INPUT);
  lcd.begin(20, 4);     // Display size definition 20 char  4 row
  lcd.setCursor(0, 0);
}

void loop()
{
////// Direction
      xValue = analogRead(joyX);
      yValue = analogRead(joyY);

      value_to_speed(xValue, yValue);
      int dir = value_to_dir(xValue);

      digitalWrite(Motor_R_dir_pin, dir);
      digitalWrite(Motor_L_dir_pin, dir);
      analogWrite(Motor_R_pwm_pin, arrayOfSpeed[0]);
      analogWrite(Motor_L_pwm_pin, arrayOfSpeed[1]);
       delay(200);
       lcd.clear();
       xValue = 512;

}

int value_to_dir(int value){
  //1023 0 518
  int result;
  if (value > 550) {
    result = 0;
  } else if (value < 500) {
    result = 1;
  } else {
    result = 1;
  }
  return result;
}

float value_to_speed(float value){
  if (value > 550) {
    return map(value,550,1023,10,250);
  } else if (value < 500) {
    return map(value,500,0,10,250);
  } else {
    return 0;
  }
}

void value_to_speed(float xValue, float yValue) {
  if (yValue > 550) {
    arrayOfSpeed[0] = map(yValue, 550, 1023, 10, 250);
  } else if (yValue < 500) {
    arrayOfSpeed[1] = map(yValue, 500, 0, 10, 250);
  } else {
    if (xValue > 550) {
      arrayOfSpeed[0] = arrayOfSpeed[1] = map(xValue, 550, 1023, 10, 250);
    } 
    if (xValue < 500) {
      arrayOfSpeed[0] = arrayOfSpeed[1] = map(xValue, 500, 0, 10, 250);
    }
  }
}


float ad_volts(int input)
{
  int meas = analogRead(input); //Reading analog input
  float volts;
  volts = meas*5.0;
  volts = volts/1023.0; // Transform it into voltage

  return volts;
}
