/*
ArduinoNano_Iic.hpp - Communication with the master for DuinoCluster Master/Slave.
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
 * File:    ArduinoNano_Iic.hpp
 * Version: 0.2.1
 * Author:  Frank Niggemann, Francisco Rafael Reyes Carmona
 */



/***********************************************************************************************************************
 * Code Iic
 **********************************************************************************************************************/

void iicSetup() {
  pinMode(PIN_IIC_SDA, INPUT_PULLUP);
  pinMode(PIN_IIC_SCL, INPUT_PULLUP);
  
  Wire.begin();
  for (int id=IIC_ID_MIN; id<=IIC_ID_MAX; id++) {
    Wire.beginTransmission(id);
    int result = Wire.endTransmission();
    if (result != 0) {
      iic_id = id;
      break;
    }
  }
  Wire.end();

  logMessage("Address ID: "+String(iic_id));
  iicInit();
}


void iicHandlerReceive(int numBytes) {
  if (numBytes == 0)
  {
    return;
  }
  while (Wire.available()) {
    char c = Wire.read();
    bufferReceive.write(c);
  }
}

void iicHandlerRequest() {
  char c = '\n';
  if (bufferRequest.available() > 0 && bufferRequest.indexOf('\n') != -1) {
    c = bufferRequest.read();
  }
  Wire.write(c);
}

void iicWorker() {
  if (bufferReceive.available() > 0 && bufferReceive.indexOf('\n') != -1) {

    setState(SLAVE_STATE_WORKING);
    logMessage("Request: "+String(bufferReceive));

    String lastblockhash = bufferReceive.readStringUntil(',');
    String newblockhash = bufferReceive.readStringUntil(',');
    unsigned int difficulty = bufferReceive.readStringUntil('\n').toInt();
    unsigned long startTime = micros();
    unsigned int ducos1result = 0;
    if (difficulty < 655) ducos1result = Ducos1a.work(lastblockhash, newblockhash, difficulty);
    setState(SLAVE_STATE_READY);
    unsigned long endTime = micros();
    #ifdef HASHRATE_FORCE
    unsigned long elapsedTime;
    elapsedTime = (unsigned long)ducos1result * 1000UL;
    elapsedTime /= (HASHRATE_SPEED + random(-5,5));
    #else
    unsigned int elapsedTime = endTime - startTime;
    #endif
    setState(SLAVE_STATE_RESULT_READY);
    //bufferRequest.flush();
    while (bufferRequest.available()) bufferRequest.read();
    size_t leng = bufferRequest.print(String(ducos1result) + "," + String(elapsedTime) + "," + ducoId + "\n");
    setState(SLAVE_STATE_RESULT_SENT);
    if (leng > 0) {
      setState(SLAVE_STATE_FREE);
      logMessage("Result: "+String(ducos1result) + "," + String(elapsedTime) + "," + ducoId);
    } else {
      setState(SLAVE_STATE_ERROR);
      logMessage("ERROR!!!!");
    }
  } else setState(SLAVE_STATE_FREE);
}

void iicInit() {
  Wire.begin(iic_id);
  Wire.onReceive(iicHandlerReceive);
  Wire.onRequest(iicHandlerRequest);  
  ducoId = getDucoId();
  logMessage("DUCO ID: "+ducoId);
  ledBlink(PIN_LED_ADDRESS, 250, 250);
  ledBlink(PIN_LED_ADDRESS, 250, 250);
  setState(SLAVE_STATE_FREE);
}

void iicEnd() {
  Wire.end();
}

void iicReset() {
  iicEnd();
  delay(5);
  iicInit();
}
