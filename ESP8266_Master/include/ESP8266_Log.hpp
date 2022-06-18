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
 * File:    ESP8266_Log.hpp
 * Version: 0.2
 * Purpose: Central log management
 * Author:  Frank Niggemann, Francisco Rafael Reyes Carmona
 */

/***********************************************************************************************************************
 * Code Log
 **********************************************************************************************************************/

/**
 * Initializes the log part of the software
 */
void logSetup() {
  if (logSerial) {
    Serial.begin(115200);
    Serial.println("\n");
  }
}

/**
 * Writes the message to the configured log destination(s)
 */
void logMessage(String partName, String methodName, String type, String message) {
  bool partOk = false;
  bool typeOk = false;
  
  if (partName=="ClientHttps" && logClientHttps) {
    partOk = true;
  } else if (partName=="ClientPool" && logClientPool) {
    partOk = true;
  } else if (partName=="Display" && logDisplay) {
    partOk = true;
  } else if (partName=="Helper" && logHelper) {
    partOk = true;
  } else if (partName=="Master" && logMaster) {
    partOk = true;
  } else if (partName=="Ntp" && logNtp) {
    partOk = true;
  } else if (partName=="SdCard" && logSdCard) {
    partOk = true;
  } else if (partName=="ServerHttp" && logServerHttp) {
    partOk = true;
  } else if (partName=="Slaves" && logSlaves) {
    partOk = true;
  } else if (partName=="WiFi" && logWiFi) {
    partOk = true;
  }
  
  if (type=="MethodName" && logMethodNames) {
    typeOk = true;
  } else if (type=="MethodDetail" && logMethodDetails) {
    typeOk = true;
  } else if (type=="StateChange" && logStateChanges) {
    typeOk = true;
  }

  if (partOk && typeOk && logSerial) {
    if (message != "") {
      logMessageSerial(partName+"::"+methodName+"() -> "+message);
    } else {
      logMessageSerial(partName+"::"+methodName+"()");
    }
  }
}

/**
 * Writes the log message to the serial stream
 */
void logMessageSerial(String message) {
  Serial.println(message);
}
