#include <ArduinoJson.h>
#include <Panel.h>

int MotorPin=2;
int currP=3;
int currP1=4;
int currP2=5;
int currP3=6;
int VolP=7;
String command;
frame inmsg;
frame outmsg;

void setup(){
  Serial.begin(9600);
  //setMotor(MotorPin);
}
void loop(){
  if(readMessage()){
    if(command==power){
      askPower(inmsg, outmsg);
      sendMessage(Serial,outmsg);
    }
  }
}
bool readMessage(){
  if(Serial.available() > 0){
    StaticJsonBuffer<200> jsonBuffer;
    String inp = Serial.readStringUntil('\n');
    JsonObject& root = jsonBuffer.parseObject(inp);
    if(root.success()){
      command = root["command"].asString();
      current = root["current"];
      volt = root["voltage"];
      return true;
    }
  }
  return false;
}
bool sendMessage(Stream& uart, frame nam){
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["command"] = nam.command;
  root["current"] = nam.param[0];
  root["voltage"] = nam.param[1];
  root.printTo(Serial);
  return true;
}
