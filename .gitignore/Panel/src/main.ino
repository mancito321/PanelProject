#include "Panel.h"
#include "Hall.h"
#include "Filters.h"

frame inmsg;
frame outmsg;
int MotorPin=2;

uint8_t PRtt;

void setup(){
  Serial.begin(9600);
  //setMotor(MotorPin);
  //Sensor usa 57600;
}
void loop(){
  if(readMessage(Serial,inmsg)){
    if(inmsg.command==cmd_motor){
      Movemotor(inmsg,MotorPin);
      sendMessage(Serial,inmsg);
    }
    else if(inmsg.command==setM){
      setMotor(inmsg,MotorPin);
      sendMessage(Serial,inmsg);
    }
    else if(inmsg.command==power){
      askPower(inmsg, outmsg);
      sendMessage(Serial,outmsg);
    }
  }
}
bool readMessage(Stream& uart ,frame& nam){
  if(uart.available()){
    PRtt=uart.read();
    if(PRtt == 0x7E){

      uint8_t inbuffer[6];
      uint16_t check=0;
      uart.readBytes(inbuffer,7);
      for(int i=0; i<=5; i++){
        check += inbuffer[i];
        }
      check = (0xFF-byte(check));
      if(check == byte(inbuffer[6])){
        nam.command = inbuffer[0];
        for(int i=0; i<=4; i++){
          nam.param[i] = inbuffer[i+1];
        }
        return true;
        //Correccion del checksum
      }else{uart.write(1);
        //------------------------------------------
          uart.write(inbuffer[6]);
        //------------------------------------------
      }
      //Correccion delchecksum
   }else{uart.write(2);}

 }
 return false;
}
bool sendMessage(Stream& uart, frame& nam){
  uint16_t output[8];
  output[0]=0x7E;
  output[1]=nam.command;
  uint16_t sum=nam.command;
  for(int i=0;i<=4;i++){
    output[i+2]=nam.param[i];
    sum += nam.param[i];
  }
  output[7]=(0xFF -byte(sum));

  for(int i=0; i<=7; i++){
    uart.write(output[i]);
  }
return true;
}
