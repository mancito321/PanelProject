//#ifndef Panel_h
#define Panel_h
#include <Filters.h>
#include <Hall.h>
#include <Arduino.h>

#define cmd_motor 0x01
#define cmd_motdone 0x04
#define setM 0x02
#define power 0x03
#define Pi1 A0
#define Pi2 A1
#define Pi3 A2
#define Pi4 A3
#define Pi5 A4


struct frame{
  uint8_t command;
  uint8_t param[4];
};
bool Movemotor(frame& nam,int pin){
    uint8_t position =nam.param[2];
    if (position==0x64){
      analogWrite(pin,255);
    }
    else if(position==0x32){
      analogWrite(pin,255/2);
    }
    nam.command=cmd_motdone;
    return true;
  };
bool setMotor(frame& nam,int pin){
  analogWrite(pin,0);
  nam.command=cmd_motdone;
  return true;
};
bool askPower(frame& nu,frame& nam){
  //uint8_t currnt1=Askforit(Pi1);
  //uint8_t currnt2=Askforit(Pi2);
  //uint8_t currnt3=Askforit(Pi3);
  //uint8_t currnt=Askforit(Pi4);
  //uint8_t Volta=Askforit(Pi5);
  uint8_t currnt1=1;
  uint8_t currnt2=0;
  uint8_t currnt3=0;
  uint8_t currnt=0;
  uint8_t Volta=0;
  nam.command=power;
  nam.param[0]=currnt1;
  nam.param[1]=currnt2;
  nam.param[2]=currnt3;
  nam.param[3]=currnt;
  nam.param[4]=Volta;
  return true;

};
