/*
DucoCluster v1.0

Copyright © 2022 Francisco Rafael Reyes Carmona. This version.
Frank Niggemann, DuinoCoinRig - original version.
All rights reserved.

rafael.reyes.carmona@gmail.com

  This file is part of DucoCluster.

  DucoCluster is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  DucoCluster is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with DucoCluster.  If not, see <https://www.gnu.org/licenses/>.
*/

/*
 * Project: DucoCluster
 * File:    ESP8266_Slaves.hpp
 * Version: 0.2
 * Purpose: Communication with the slaves
 * Author:  Frank Niggemann, Francisco Rafael Reyes Carmona
 */

/***********************************************************************************************************************
 * Code Slaves
 **********************************************************************************************************************/

/**
 * Initializes communication with the slaves
 */
void slavesSetup() {
  logMessage("Slaves", "slavesSetup", "MethodName", "");
  slavesWireInit();
  slavesScan();
}

/**
 * Initializes the I²C data bus
 */
void slavesWireInit() {
  logMessage("Slaves", "slavesWireInit", "MethodName", "");
  pinMode(WIRE_PIN_SDA, INPUT_PULLUP);
  pinMode(WIRE_PIN_SCL, INPUT_PULLUP);
  Wire.begin(WIRE_PIN_SDA, WIRE_PIN_SCL);
  Wire.setClock(WIRE_CLOCK);
}

/**
 * Searches for existing slaves
 */
void slavesScan() {
  logMessage("Slaves", "slavesScan", "MethodName", "");
  setStateMaster(MASTER_STATE_SCANNING);
  logMessage("Slaves", "slavesScan", "MethodDetail", "Start scanning for slaves");
  int counter = 0;
  for (byte id=0 ; id<SLAVE_ID_MAX ; id++) {
    if (slaveExists(id)) {
      logMessage("Slaves", "slavesScan", "MethodDetail", "Slave found with ID " + String(id));
      String text = slaveRequestLn(id);
      counter++;
      slaveFound[id] = true;
    } else {
      slaveFound[id] = false;
    }
  }
  nodes_sum = counter;
  logMessage("Slaves", "slavesScan", "MethodDetail", "Found "+String(counter)+" slave(s)");
}

/**
 * Refresh for existing slaves
 */
void slavesRefresh() {
  logMessage("Slaves", "slavesRefresh", "MethodName", "");
  logMessage("Slaves", "slavesRefresh", "MethodDetail", "Refreshing for slaves");
  int counter = 0;
  for (byte id=0 ; id<SLAVE_ID_MAX ; id++) {
    if (slaveExists(id)) {
      logMessage("Slaves", "slavesRefresh", "MethodDetail", "Slave found with ID " + String(id));
      String text = slaveRequestLn(id);
      counter++;
      slaveFound[id] = true;
    } else {
      slaveFound[id] = false;
    }
  }
  nodes_sum = counter;
  logMessage("Slaves", "slavesRefresh", "MethodDetail", "Found "+String(counter)+" slave(s)");
}

/**
 * Checks if the slave with the given ID exists
 * 
 * @param byte id The ID of the slave whose existence is to be checked
 * 
 * @return bool Returns true if slave exists
 */
boolean slaveExists(byte id) {
  logMessage("Slaves", "slaveExists", "MethodName", "");
  slavesWireInit();
  Wire.beginTransmission(id);
  byte result = Wire.endTransmission();
  return (result == 0);
}

/**
 * Sends a message to the slave with the given ID
 * 
 * @param byte id The ID of the slave to which the message is to be sent
 * @param String message The message to be sent to the slave
 */
void slaveSendMessage(byte id, String message) {
  logMessage("Slaves", "slaveSendMessage", "MethodName", "");
  logMessage("Slaves", "slaveSendMessage", "MethodDetail", "Send message to ID " + String(id));
  slaveSendLn(id, message);
}

/**
 * Sends a message to all slaves
 * 
 * @param String message The message to be sent to all slaves
 */
void slavesSendMessage(String message) {
  logMessage("Slaves", "slavesSendMessage", "MethodName", "");
  logMessage("Slaves", "slavesSendMessage", "MethodDetail", "Send message to all slaves");
  for (byte id=0 ; id<SLAVE_ID_MAX ; id++) {
    if (slaveExists(id)) {
      logMessage("Slaves", "slavesSendMessage", "MethodDetail", "Send message to ID " + String(id) + " -> " + message);
      slaveSendText(id, message);
    }
  }
}

/**
 * Sends the next job to the slave with the given ID
 * 
 * @param byte id The ID of the slave to which the text is to be sent
 * @param String hashLastBlock The hash for the last block
 * @param String hashNextBlock The hash for the next block
 * @param int difficulty The difficulty
 */
void slaveSendNextJob(byte id, String lastBlockHash, String nextBlockHash, String difficulty) {
  logMessage("Slaves", "slaveSendNextJob", "MethodName", "");
  String job = lastBlockHash + "," + nextBlockHash + "," + difficulty;
  slaveSendLn(id, job);
}

/**
 * Sends a text to the slave with the given ID
 * 
 * @param byte id The ID of the slave to which the text is to be sent
 * @param String text The text to be sent to the slave
 */
void slaveSendText(byte id, String text) {
  logMessage("Slaves", "slaveSendText", "MethodName", "");
  logMessage("Slaves", "slaveSendText", "MethodDetail", "Send text to ID " + String(id) + " -> " + text);
  slavesWireInit();
  for (int pos=0 ; ((unsigned int)pos)<text.length() ; pos++) {
     Wire.beginTransmission(id);
     Wire.write(text.charAt(pos));
     Wire.endTransmission();
  }
}

/**
 * Sends a text to the slave with the given ID and adds a \n to the end of the text
 * 
 * @param byte id The ID of the slave to which the text is to be sent
 * @param String text The text to be sent to the slave
 */
void slaveSendLn(byte id, String text) {
  logMessage("Slaves", "slaveSendLn", "MethodName", "");
  slaveSendText(id, text + "\n");
}

/**
 * Requests a text line from a slive
 * 
 * @param byte id The ID of the slave from which a line of text is to be requested
 * 
 * @return String Returns the answer line sent by the slave as a result 
 */
String slaveRequestLn(byte id) {
  logMessage("Slaves", "slaveRequestLn", "MethodName", "");
  char end = '\n';
  String text = "";
  boolean done = false;
  slavesWireInit();
  while (!done) {
    Wire.requestFrom((int)id, 1);
    if (Wire.available()) {
      char c = Wire.read();
      if (c == end) {
        break;
        done = true;
      }
      text += c;
    }
  }
  logMessage("Slaves", "slaveRequestLn", "MethodDetail", "Slave returns text -> " + text);
  return text;
}
