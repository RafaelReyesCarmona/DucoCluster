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
 * File:    ESP8266_WiFi.hpp
 * Version: 0.2
 * Purpose: Communication with the wireless network
 * Author:  Frank Niggemann, Francisco Rafael Reyes Carmona
 */

/***********************************************************************************************************************
 * Code WiFi
 **********************************************************************************************************************/

/**
 * Initializes the WiFi part of the software
 * 
 * @param String ssid The SSID of the WiFi networt
 * @param String password The password for the WiFi network with the given SSID
 */ 
void wifiSetup(String ssid, String password) {
  logMessage("WiFi", "wifiSetup", "MethodName", "");
  if (ssid!="") {
    setStateMaster(MASTER_STATE_CONNECTING_WIFI);
    logMessage("WiFi", "wifiSetup", "MethodDetail", "Connecting to: " + String(ssid));
    WiFi.mode(WIFI_STA);
    WiFi.setSleepMode(WIFI_NONE_SLEEP);
    WiFi.begin(ssid, password);
    
    int wait_passes = 0;
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      if (++wait_passes >= 10) {
        WiFi.begin(ssid, password);
        wait_passes = 0;
      }
    }
/*
    while (WiFi.status() != WL_CONNECTED) {
      delay(200);
    }
*/
    setStateMaster(MASTER_STATE_WIFI_CONNECTED);
    wifiIp = wifiGetIp();
    logMessage("WiFi", "wifiSetup", "MethodDetail", "Connected with IP address: " + wifiIp);
  } else {
    logMessage("WiFi", "wifiSetup", "MethodDetail", "Can't connect to WiFi without SSID");
  }
  //displayScreenHome();
}

/**
 * Returns the WiFi connection status
 * 
 * @return bool Returns the connection status 
 */
bool wifiConnected() {
  logMessage("WiFi", "wifiConnected", "MethodName", "");
  if (WiFi.status() != WL_CONNECTED) {
    logMessage("WiFi", "wifiConnected", "MethodDetail", "Return false");
    return false;
  }
  logMessage("WiFi", "wifiConnected", "MethodDetail", "Return true");
  return true;
}

/**
 * Returns the IP of the WiFi connection
 * 
 * @return String Returns the IP of the current WiFi connection or "Not connected"
 */
String wifiGetIp() {
  logMessage("WiFi", "wifiGetIp", "MethodName", "");
  if (!wifiConnected()) {
    logMessage("WiFi", "wifiGetIp", "MethodDetail", "Return 'Not connected'");
    return "Not connected";
  }
  String ip = WiFi.localIP().toString();
  logMessage("WiFi", "wifiGetIp", "MethodDetail", "Return " + ip);
  return ip;
}
