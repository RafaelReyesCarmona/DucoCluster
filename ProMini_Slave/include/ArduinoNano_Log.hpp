/*
ArduinoNano_Log.hpp - Central log management slave for DuinoCluster Master/Slave.
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
 * File:    ArduinoNano_Log.hpp
 * Version: 0.1.1
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
    LOGSERIAL.begin(115200);
    LOGSERIAL.println("\n");
  }
}

/**
 * Writes the message to the configured log destination(s)
 */
void logMessage(String message) {
  if (logSerial) {
    logMessageSerial(message);
  }
}

/**
 * Writes the log message to the serial stream
 */
void logMessageSerial(String message) {
  LOGSERIAL.println(message);
}
