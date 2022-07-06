/*
ArduinoNano_Slave.cpp - Master file that starts and coordinates the slave for DuinoCluster Master/Slave.
DuinoCluster v1.0

Copyright © 2022 Francisco Rafael Reyes Carmona. This version.
Frank Niggemann, DuinoCoinRig - original version.
All rights reserved.

rafael.reyes.carmona@gmail.com

  This file is part of DuinoCluster.

  DuinoCluster is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  DuinoCluster is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with DuinoCluster.  If not, see <https://www.gnu.org/licenses/>.
*/


/*
 * File:    ArduinoNano_Slave.cpp
 * Version: 0.1.1
 * Author:  Frank Niggemann, Francisco Rafael Reyes Carmona.
 * 
 * This is a modified version of this software: https://github.com/ricaun/DuinoCoinI2C/tree/main/DuinoCoin_Tiny_Slave
 * 
 * Hardware: Arduino Pro Mini / LGT8F328P-SSOP20
 * 
 * Needed files: ArduinoNano_Helper
 *               ArduinoNano_Iic
 *               ArduinoNano_Log
 *               ArduinoNano_Slave
 * 
 * Needed libraries: ArduinoUniqueID
 *                   DuinoCoin
 *                   DuinoCoinSpeed
 *                   StreamJoin
 *                   Wire
 *                   TrueRandomNumbers
 *                   SoftwareSerial
 */

/* 
 * Addittional information to the compiler.
 * By defining SPEED value, the optimization can be changed during macro expansion phase
 *
 * 0 -O0    <- reduce compilation time
 * 1 -Os    <- optimize for size
 * 2 -O2    <- Fast
 * 3 -O3    <- Faster
 * 4 -Ofast <- Fastest
 * g -Og    <- optimize debugging experience
 */
#define SPEED 4

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "Arduino.h"
#include "DuinoCoinSpeed.h"
#include "TrueRandomNumbers.hpp"
#include "ArduinoUniqueID.h"
#include "DuinoCoin.h"
#include "StreamString.h"
#include "Wire.h"
#include <SoftwareSerial.h>


/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

#define PIN_LED_ADDRESS   13
#define PIN_LED_FREE      false
#define PIN_LED_WORKING   13
#define PIN_LED_READY     false

#define SLAVE_STATE_UNKNOWN 0           // The ID for status UNKNOWN (Slave is in an unknown state)
#define SLAVE_STATE_FREE 1              // The ID for status FREE (Slave is free for the next job)
#define SLAVE_STATE_WORKING 2           // The ID for status WORKING (Slave is working on a job)
#define SLAVE_STATE_READY 3             // The ID for status READY (Slave is ready with a job and has a result)
#define SLAVE_STATE_RESULT_READY 4      // The ID for status READY (The result is ready to send)
#define SLAVE_STATE_RESULT_SENT 5       // The ID for status READY (The result has been sent)
#define SLAVE_STATE_ERROR 6             // The ID for status ERROR (Slave has a problem)

#define PIN_IIC_SDA SDA                 // D2 - A4 - GPIO4
#define PIN_IIC_SCL SCL                 // D1 - A5 - GPIO5
#define IIC_SPEED 100000                // The speed

#define IIC_ID_MIN 1                    // The first possible address
#define IIC_ID_MAX 5                    // The last possible address

#define LOGSERIALOUTPUT true            // Define true if config log info to serial.

#define LOGSERIAL Serial                // Define for hardware serial, comment for software serial.

//SoftwareSerial SoftSerial(2, 3);      // Define SoftwareSerial RX, TX at pins defined.
//#define LOGSERIAL SoftSerial          // Uncomment twice lines for Software Serial.

// HASHRATE FORCE for testing only.
//#define HASHRATE_FORCE
//#define HASHRATE_SPEED 258


/***********************************************************************************************************************
 * Variables
 **********************************************************************************************************************/

byte iic_id = 1;
StreamString bufferReceive;
StreamString bufferRequest;
int slaveState = SLAVE_STATE_UNKNOWN;
bool logSerial = LOGSERIALOUTPUT;                   
String ducoId = "";


/***********************************************************************************************************************
 * Methods
 **********************************************************************************************************************/

// Methods Helper
String getDucoId();
String getPseudoUniqueIdString();
unsigned long getStartupDelay();
void ledBlink(int pin, int msOn, int msOff);
void ledSet(bool ledAddress, bool ledFree, bool ledWorking, bool ledReady);

// Methods Iic
void iicSetup();
void iicHandlerReceive(int numBytes);
void iicHandlerRequest();
void iicWorker();
void iicInit();
void iicEnd();
void iccReset();

// Methods Log
void logSetup();
void logMessage(String message);
void logMessageSerial(String message);

// Methods TrueRandomNumbers
byte rotate(byte b, int r);
void pushLeftStack(byte bitToPush);
void pushRightStackRight(byte bitToPush);
byte getTrueRotateRandomByte();

void setState(int state);

/***********************************************************************************************************************
 * Code Main
 **********************************************************************************************************************/

#include "ArduinoNano_Helper.hpp"
#include "ArduinoNano_Iic.hpp"
#include "ArduinoNano_Log.hpp"

void setState(int state) {
  if (slaveState != state) {
    slaveState = state;
    if (slaveState == SLAVE_STATE_UNKNOWN) {
      logMessage("Set state ID: "+String(state)+ " (UNKNOWN)");
      ledSet(false, false, false, false);
    } else if (slaveState == SLAVE_STATE_FREE) {
      logMessage("Set state ID: "+String(state)+ " (FREE)");
      ledSet(false, true, false, false);
    } else if (slaveState == SLAVE_STATE_WORKING) {
      logMessage("Set state ID: "+String(state)+ " (WORKING)");
      ledSet(false, false, true, false);
    } else if (slaveState == SLAVE_STATE_READY) {
      logMessage("Set state ID: "+String(state)+ " (READY)");
      ledSet(false, false, false, true);
    } else if (slaveState == SLAVE_STATE_RESULT_READY) {
      logMessage("Set state ID: "+String(state)+ " (RESULT_READY)");
      ledSet(false, false, false, true);
    } else if (slaveState == SLAVE_STATE_RESULT_SENT) {
      logMessage("Set state ID: "+String(state)+ " (RESULT_SENT)");
      ledSet(false, true, false, false);
    } else if (slaveState == SLAVE_STATE_ERROR) {
      logMessage("Set state ID: "+String(state)+ " (ERROR)");
      ledSet(false, false, false, false);
    } else {
      logMessage("Set state ID: "+String(state)+ " (ERROR)");
      ledSet(false, false, false, false);
    }
  }
}

//void(* resetFunc) (void) = 0;//declare reset function at address 0


void setup() {
  delay(100);
  if (PIN_LED_ADDRESS) {
    pinMode(PIN_LED_ADDRESS, OUTPUT);
    digitalWrite(PIN_LED_ADDRESS, LOW);
  }
  if (PIN_LED_FREE) {
    pinMode(PIN_LED_FREE, OUTPUT);
    digitalWrite(PIN_LED_FREE, LOW);
  }
  if (PIN_LED_WORKING) {
    pinMode(PIN_LED_WORKING, OUTPUT);
    digitalWrite(PIN_LED_WORKING, LOW);
  }
  if (PIN_LED_READY) {
    pinMode(PIN_LED_READY, OUTPUT);
    digitalWrite(PIN_LED_READY, LOW);
  }
  logSetup();
  delayMicroseconds(getStartupDelay());
  setState(SLAVE_STATE_UNKNOWN);
  iicSetup();
}

uint8_t cycles = 0;

void loop() {
  if (slaveState == SLAVE_STATE_ERROR || slaveState == SLAVE_STATE_UNKNOWN) {
    logMessage("Resetting...");
    iicReset();
    logMessage("Reset OK.");
  }
  if (slaveState == SLAVE_STATE_FREE) iicWorker();
  delay(5);
  cycles++;
  if(cycles > 255) {
    setState(SLAVE_STATE_FREE);
    //bufferReceive.flush();
    while (bufferReceive.available()) bufferReceive.read();
    //bufferRequest.flush();
    while (bufferRequest.available()) bufferRequest.read();
    cycles = 0;
  }
  

// For tessting only.
//  if(Serial.available()){
//    int c = Serial.read();
//    setState(c-48);
//  }
}
