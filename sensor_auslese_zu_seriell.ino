
/*********************************************************
This is a library for the MPR121 12-channel Capacitive touch sensor
Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/
These sensors use I2C communicate, at least 2 pins are required 
to interface
Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!
Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
**********************************************************/

#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();
Adafruit_MPR121 cap2 = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
uint16_t currtouched2 = 0;


void setup() {
  Serial.begin(115200);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
  
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  while (!cap.begin(0x5A)) {
    Serial.println("MPR121 1 not found, check wiring?");
    
  }



  while (!cap2.begin(0x5B)) {
    Serial.println("MPR121 2 not found, check wiring?");
    
  }

  Serial.println("MPR121 found!");
}

void loop() {
  // Get the currently touched pads
  currtouched = cap.touched();
  currtouched2 = cap2.touched();
  
 /* for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
    }
  }*/

  // reset our state

  // comment out this line for detailed data from the sensor!
  //return;
  
  // debugging info, what
//  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
 // Serial.print("Filt: ");
  
  for (uint8_t i=0; i<10; i++) {
  //  Serial.print("Variable_");
  //  Serial.print(i);
  //  Serial.print(":");
   Serial.print(cap.filteredData(i)); Serial.print(",");
  }
    for (uint8_t i=10; i<20; i++) {
  //  Serial.print("Variable_");
  //  Serial.print(i);
  //  Serial.print(":");
   Serial.print(cap2.filteredData(i-10)); Serial.print(",");
  }
   Serial.println();
  
  //Serial.print("Base: ");
  //for (uint8_t i=0; i<12; i++) {
  //  Serial.print(cap.baselineData(i)); Serial.print("\t");
  //}
 // Serial.println();
  
  // put a delay so it isn't overwhelming
  delay(250);
}