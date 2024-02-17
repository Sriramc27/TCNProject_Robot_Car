/*
 * @Author: ELEGOO
 * @Date: 2019-10-22 11:59:09
 * @LastEditTime: 2020-12-18 14:14:35
 * @LastEditors: Changhua
 * @Description: Smart Robot Car V4.0
 * @FilePath: 
 */
#include <avr/wdt.h>
#include "ApplicationFunctionSet_xxx0.h"
#include "DeviceDriverSet_xxx0.h"

DeviceDriverSet_Motor AppMotor2;

void start_obstacle_avoidance(){
    while(true){
      char check = Serial.read();
      if(check=='n'){
        Application_FunctionSet.ApplicationFunctionSet_Obsstop();
        break;
      }
      //Application_SmartRobotCarxxx0.Functional_Mode = ObstacleAvoidance_mode;
      Application_FunctionSet.ApplicationFunctionSet_ObsAvoid();
      Application_FunctionSet.ApplicationFunctionSet_Obstacle();    
    }
}

void setup()
{
  // put your setup code here, to run once:
  Application_FunctionSet.ApplicationFunctionSet_Init();
  wdt_enable(WDTO_2S);
  //AppMotor2.DeviceDriverSet_Motor_Init();
  //espSerial.begin(9600);
  //mySerial.begin(600);

  Serial.begin(9600);
  
  pinMode(PIN_Motor_PWMA, OUTPUT);
  pinMode(PIN_Motor_PWMB, OUTPUT);
  pinMode(PIN_Motor_AIN_1, OUTPUT);
  pinMode(PIN_Motor_BIN_1, OUTPUT);
  pinMode(PIN_Motor_STBY, OUTPUT); 
}

void loop()
{
  if (Serial.available() > 0) {
  char myChar = Serial.read();
  // Serial.print("Message: ");
  // Serial.println(myChar);
  switch(myChar){
    case 'w':
      Serial.print("Moving forward");
     // AppMotor2.DeviceDriverSet_Motor_forward(); 
      for(int i=0;i<200;i++){
      digitalWrite(PIN_Motor_AIN_1, HIGH);
      analogWrite(PIN_Motor_PWMA, 200);
      digitalWrite(PIN_Motor_BIN_1, HIGH);
      analogWrite(PIN_Motor_PWMB, 200);
      delay(10); 
      }
    break;
    case 'a':
      Serial.print("Left");
      //AppMotor2.DeviceDriverSet_Motor_left();
       for(int i=0;i<200;i++){
      digitalWrite(PIN_Motor_AIN_1, HIGH);
      analogWrite(PIN_Motor_PWMA, 200);
      digitalWrite(PIN_Motor_BIN_1, LOW);
      analogWrite(PIN_Motor_PWMB, 200);
      delay(10);
       }
    break;

    case 'd':
      Serial.print("Right");
      //AppMotor2.DeviceDriverSet_Motor_right();
       for(int i=0;i<200;i++){
      digitalWrite(PIN_Motor_AIN_1, LOW);
      analogWrite(PIN_Motor_PWMA, 200);
      digitalWrite(PIN_Motor_BIN_1, HIGH);
      analogWrite(PIN_Motor_PWMB, 200);
      delay(10);
      }
    break;

    case 's':
      Serial.print("Back");
      //AppMotor2.DeviceDriverSet_Motor_back();
      for(int i=0;i<200;i++){
      digitalWrite(PIN_Motor_AIN_1, LOW);
      analogWrite(PIN_Motor_PWMA, 200);
      digitalWrite(PIN_Motor_BIN_1, LOW);
      analogWrite(PIN_Motor_PWMB, 200);
      delay(10);
      }
    break;

    case 'o':
      Serial.print("Obstacle avoidance start");
      start_obstacle_avoidance();
      Serial.print("Obstacle avoidance stop");
    break;

    default:
      Serial.print("Stop");
      //AppMotor2.DeviceDriverSet_Motor_stop();
      digitalWrite(PIN_Motor_AIN_1, LOW);
      analogWrite(PIN_Motor_PWMA, 0);
      digitalWrite(PIN_Motor_BIN_1, HIGH);
      analogWrite(PIN_Motor_PWMB, 0);
    delay(10);
   }
  }
  //put your main code here, to run repeatedly :
  wdt_reset();
  Application_FunctionSet.ApplicationFunctionSet_SensorDataUpdate();
  Application_FunctionSet.ApplicationFunctionSet_KeyCommand();
  Application_FunctionSet.ApplicationFunctionSet_RGB();
  Application_FunctionSet.ApplicationFunctionSet_Follow();
  Application_FunctionSet.ApplicationFunctionSet_Obstacle();
  Application_FunctionSet.ApplicationFunctionSet_Tracking();
  Application_FunctionSet.ApplicationFunctionSet_Rocker();
  Application_FunctionSet.ApplicationFunctionSet_Standby();
  Application_FunctionSet.ApplicationFunctionSet_IRrecv();
  Application_FunctionSet.ApplicationFunctionSet_SerialPortDataAnalysis();

  Application_FunctionSet.CMD_ServoControl_xxx0();
  Application_FunctionSet.CMD_MotorControl_xxx0();
  Application_FunctionSet.CMD_CarControlTimeLimit_xxx0();
  Application_FunctionSet.CMD_CarControlNoTimeLimit_xxx0();
  Application_FunctionSet.CMD_MotorControlSpeed_xxx0();
  Application_FunctionSet.CMD_LightingControlTimeLimit_xxx0();
  Application_FunctionSet.CMD_LightingControlNoTimeLimit_xxx0();
  Application_FunctionSet.CMD_ClearAllFunctions_xxx0();

  Serial.print("Car");
  delay(1500);

}
