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
 * File:    ESP8266_SDCard.hpp
 * Version: 0.2
 * Purpose: Communication with the SD card (Unused code, implementation for future versions)
 * Author:  Frank Niggemann, Francisco Rafael Reyes Carmona
 */

/***********************************************************************************************************************
 * Code SD
 **********************************************************************************************************************/

/**
 * Initializes the SD part of the software
 */
//void sdCardSetup() {
//  logMessage("SdCard", "sdCardSetup", "MethodName", "");
//}

/**
 * Returns true if the SD card is inserted and ready
 * 
 * @return bool Returns true if the SD card is inserted and ready
 */
//bool sdCardReady() {
//  logMessage("SdCard", "sdCardReady", "MethodName", "");
//  if (!sd.begin(SD_PIN_CS, SPI_HALF_SPEED)) {
//  if (!sd.begin(SD_CONFIG)) {
//    return false;  
//  }
//  return true;
//}

/**
 * Returns a describing string for the ready status of the SD card
 * 
 * @return String The describing string for the ready status of the SD card
 */
//String sdCardReadyString() {
//  logMessage("SdCard", "sdCardReadyString", "MethodName", "");
//  if (!sdCardReady()) {
//    return "SD card not ready";  
//  }
//  return "SD card ready";
//}

/**
 * Returns true if the config file exists on the SD card
 * 
 * @return bool Returns true if the config file exists on the SD card
 */
//bool sdCardConfigFileExists() {
//  logMessage("SdCard", "sdCardConfigFileExists", "MethodName", "");
//  if (!sdCardReady()) {
//    return false; 
//  }
//  if (!file.open("config.rig", O_READ)) {
//    return false;
//  }
//  return true;
//}

/**
 * Returns a describing string for the existence of the config file on the SD card
 * 
 * @return String The describing string for the existence of the config file on the SD card
 */
//String sdCardConfigFileExistsString() {
//  logMessage("SdCard", "sdCardConfigFileExistsString", "MethodName", "");
//  if (sdCardConfigFileExists()) {
//    return "Config file 'config.rig' found on SD card";  
//  }
//  return "Config file 'config.rig' not found on SD card";
//}

/**
 * Reads the config file and sets the local configuration
 */
//void sdCardReadConfigFile() {
//  logMessage("SdCard", "sdCardReadConfigFile", "MethodName", "");
//  size_t n;
//  if (!sdCardReady()) {
//    logMessage("SdCard", "sdCardReadConfigFile", "MethodDetail", "No SD card found");
//  } else if (!sdCardConfigFileExists()) {
//    logMessage("SdCard", "sdCardReadConfigFile", "MethodDetail", "No config file 'config.rig' found on SD card");
//  } else {
//    setStateMaster(MASTER_STATE_LOADING_CONFIG);
//    logMessage("SdCard", "sdCardReadConfigFile", "MethodDetail", "Loading config file 'config.rig'");
//    String config = "";
//    while ((n = file.fgets(line, sizeof(line))) > 0) {
//      config = String(line);
//      config.trim();
//      if (config.substring(0, 10) == "wifi_ssid=") {
//        wifiSsid = config.substring(10);
//        logMessage("SdCard", "sdCardReadConfigFile", "MethodDetail", "Config for WiFi SSID loaded");
//      } else if (config.substring(0, 14) == "wifi_password=") {
//        wifiPassword = config.substring(14);
//        logMessage("SdCard", "sdCardReadConfigFile", "MethodDetail", "Config for WiFi password loaded");
//      } else if (config.substring(0, 10) == "name_user=") {
//        nameUser = config.substring(10);
//        logMessage("SdCard", "sdCardReadConfigFile", "MethodDetail", "Config for user name loaded");
//      } else if (config.substring(0, 9) == "name_rig=") {
//        nameRig = config.substring(9);
//        logMessage("SdCard", "sdCardReadConfigFile", "MethodDetail", "Config for rig name loaded");
//      } 
//    }
//    setStateMaster(MASTER_STATE_CONFIG_LOADED);
//    logMessage("SdCard", "sdCardReadConfigFile", "MethodDetail", "Config file 'config.rig' loaded");
//  }
//}
