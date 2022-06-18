/*
ArduinoNano_Helper.hpp - Contains all helper functions for the slave DuinoCluster Master/Slave.
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
 * File:    ArduinoNano_Helper.hpp
 * Version: 0.1.1
 * Author:  Frank Niggemann, Francisco Rafael Reyes Carmona
 */



/***********************************************************************************************************************
 * Code Helper
 **********************************************************************************************************************/

String getDucoId() {
  String ID = "DUCOID"+getPseudoUniqueIdString();
  return ID;
}

String getPseudoUniqueIdString() {
  String result = "";
  byte value[8];
  String hexvalue = "0123456789ABCDEF";  

  for (int i=0 ; i<8 ; i++) {
    value[i] = boot_signature_byte_get(i);
  }
  for (int i=8 ; i<128 ; i++) {
    byte value_before = value[(i%8)];
    value[(i%8)] = (value_before+boot_signature_byte_get(i))%256;
  }
  for (int i=0 ; i<8 ; i++) {
    byte low = value[i] % 16;
    byte high = (value[i]-low) / 16;
    logMessage("low: "+String(low));
    logMessage("high: "+String(high));
    result.concat(hexvalue[high]);  
    result.concat(hexvalue[low]);  
  }
  return result;
}

unsigned long getStartupDelay() {
  /*
  byte value[8];
  unsigned long milliseconds = 0;
  for (int i=0 ; i<8 ; i++) {
    value[i] = boot_signature_byte_get(i);
  }
  for (int i=8 ; i<128 ; i++) {
    byte value_before = value[(i%8)];
    value[(i%8)] = (value_before+boot_signature_byte_get(i))%256;
  }
  for (int i=0 ; i<8 ; i++) {
    milliseconds += value[i]*(8^i);
  }
  milliseconds = (milliseconds%1000)*10;
  logMessage("Startupdelay: "+String(milliseconds)+"ms");
  return milliseconds;
  */
  unsigned long time = 0;
  time = (unsigned long) getTrueRotateRandomByte() * 1000 + (unsigned long) getTrueRotateRandomByte();
  logMessage("Startupdelay: "+String(time)+"µs");
  return time;
}

void ledBlink(int pin, int msOn, int msOff) {
  digitalWrite(pin, HIGH);
  delay(msOn);
  digitalWrite(pin, LOW);
  delay(msOff);
}

void ledSet(bool ledAddress, bool ledFree, bool ledWorking, bool ledReady) {
  if (PIN_LED_ADDRESS) {
    if (ledAddress) {
      digitalWrite(PIN_LED_ADDRESS, HIGH);
      logMessage("PIN_LED_ADDRESS: ON");
    } else {
      digitalWrite(PIN_LED_ADDRESS, LOW);
      logMessage("PIN_LED_ADDRESS: OFF");
    }
  }
  if (PIN_LED_FREE) {
    if (ledFree) {
      digitalWrite(PIN_LED_FREE, HIGH);
      logMessage("PIN_LED_FREE: ON");
    } else {
      digitalWrite(PIN_LED_FREE, LOW);
      logMessage("PIN_LED_FREE: OFF");
    }
  }
  if (PIN_LED_WORKING) {
    if (ledWorking) {
      digitalWrite(PIN_LED_WORKING, HIGH);
      logMessage("PIN_LED_WORKING: ON");
    } else {
      digitalWrite(PIN_LED_WORKING, LOW);
      logMessage("PIN_LED_WORKING: OFF");
    }
  }
  if (PIN_LED_READY) {
    if (ledReady) {
      digitalWrite(PIN_LED_READY, HIGH);
      logMessage("PIN_LED_READY: ON");
    } else {
      digitalWrite(PIN_LED_READY, LOW);
      logMessage("PIN_LED_READY: OFF");
    }
  }
}
