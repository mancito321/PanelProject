#ifndef Hall_h
#define Hall_h
#include <Arduino.h>
#include <Filters.h>

float testFrequency = 60;                     // test signal frequency (Hz)
float windowLength = 20.0/testFrequency;     // how long to average the signal, for statistist
int sensorValue = 0;
float intercept = -0.1129; // to be adjusted based on calibration testing
float slope = 0.0405; // to be adjusted based on calibration testing
float current_amps; // estimated actual current in amps

unsigned long printPeriod = 1000; // in milliseconds
// Track time in milliseconds since last reading
unsigned long previousMillis = 0;


uint8_t Askforit(uint8_t Anapin) {
  RunningStatistics inputStats;                 // create statistics to look at the raw test signal
  inputStats.setWindowSecs( windowLength );
  float i=0;
  float stack=0;
  while( i<=5 ) {
    sensorValue = analogRead(Anapin);  // read the analog in value:
    inputStats.input(sensorValue);  // log to Stats function

    if((unsigned long)(millis() - previousMillis) >= printPeriod) {
      previousMillis = millis();   // update time

      // display current values to the screen

      // output sigma or variation values associated with the inputValue itsel

      // convert signal sigma value to current in amps
      current_amps = intercept + slope * inputStats.sigma();

      i++;
    }
  }
  return (current_amps);
}
#endif
