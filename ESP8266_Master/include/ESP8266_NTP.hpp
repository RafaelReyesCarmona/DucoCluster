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
 * File:    ESP8266_NTP.hpp
 * Version: 0.2
 * Purpose: Central NTP management
 * Author:  Frank Niggemann, Francisco Rafael Reyes Carmona
 */

/***********************************************************************************************************************
 * Code NTP
 **********************************************************************************************************************/

/**
 * Initializes the NTP part of the software
 */
void ntpSetup() {
  logMessage("Ntp", "ntpSetup", "MethodName", "");
  timeClient.begin();
}

/**
 * Returns the current UNIX timestamp
 * 
 * @return unsigned long The current UNIX timestamp
 */
unsigned long ntpGetTimestamp() {
  logMessage("Ntp", "ntpGetTimestamp", "MethodName", "");
  timeClient.update();
  unsigned long timestamp = timeClient.getEpochTime();
  logMessage("Ntp", "ntpGetTimestamp", "MethodDetail", "Return timestamp " + String(timestamp));
  return timestamp;
}
