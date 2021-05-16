/* Car Haptic Feedback Simulator

  Reads value of pressure applied on force resistive sensor and applies
  moving average. Detects short or long press and delivers haptic 
  feedback through linear resonant actuator
  
  For 2021 Imperial HCDE Design Engineering project

  v1.0

  Maintained by Jack Beaumont
*/

// Includes
#include "movingAvg.h"
#include <Wire.h>
#include "Adafruit_DRV2605.h"

// Constants
int fsrPin = A0;     // the FSR and 3.3K pulldown are connected to a0
int fsrReading;     // analog reading from the FSR resistor divider
int sensorMovingAvg = 0; // moving average from the FSR
const int SHORT_PRESS_TIME = 1000; 
const int LONG_PRESS_TIME  = 1000; 

// Variables
bool currentState; // the current state of the button
bool lastState = false; // the previous state of the button
bool isPressing = false;
bool isLongDetected = false;
long pressDuration = 0;
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;

// Setup moving average
int average;
movingAvg mySensor(50);

Adafruit_DRV2605 drv;

void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);
  mySensor.begin();
  drv.begin();

  drv.selectLibrary(1);

  // I2C trigger by sending 'go' command
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG);
  fsrReading = analogRead(fsrPin);

}

void loop(void) {
  
  currentState = ((fsrReading - sensorMovingAvg) > 500);

  if (lastState == false && currentState == true) {       // button is pressed
    
    pressedTime = millis();
    haptic_feedback();
    isPressing = true;
    isLongDetected = false;
    
  } else if (lastState == true && currentState == false) { // button is released
    
    isPressing = false;
    releasedTime = millis();
    
    long pressDuration = releasedTime - pressedTime;

    if ( pressDuration < SHORT_PRESS_TIME )  // short press is detected
      Serial.println("Short press");
  }

  if (isPressing == true && isLongDetected == false) {  // lcheck if long is detected
    long pressDuration = millis() - pressedTime;

    if ( pressDuration > LONG_PRESS_TIME ) {  // long is detected
      Serial.println("Long press");
      haptic_feedback();
      isLongDetected = true;
    }
  }
  
  // save the the last state
  lastState = currentState;


  readSensor();

  delay(100);
}


// Read value from sensor and apply moving average
void readSensor() {

  fsrReading = analogRead(fsrPin);
  if (sensorMovingAvg > fsrReading) {
    for (int i = 0; i < 10; i++) {
      mySensor.reading(fsrReading);
    }
  }

  sensorMovingAvg = mySensor.reading(fsrReading);
}

// Generate haptic feedback
void haptic_feedback() {

  drv.setWaveform(0, 17);  // play effect
  drv.setWaveform(1, 0);       // end waveform
  drv.go();
  delay(200);
}
