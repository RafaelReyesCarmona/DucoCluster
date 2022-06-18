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
 * File:    ESP8266_Display.hpp
 * Version: 0.2
 * Purpose: Control of the display
 * Author:  Frank Niggemann, Francisco Rafael Reyes Carmona
 */

/***********************************************************************************************************************
 * Code Display
 **********************************************************************************************************************/

/**
 * Initializes the display part of the software
 */
void displaySetup() {
  logMessage("Display", "displaySetup", "MethodName", "");
  display.init();
  if (OLED_FLIP_VERTICALLY) {
    display.flipScreenVertically();
  }
  display.setFont(ArialMT_Plain_10);
  display.resetDisplay();
  display.displayOn();
  display.setContrast(255);
  display.setI2cAutoInit(true);
  displayClear();
  displayScreenHome();
}

/**
 * Clears the LCD display
 */
void displayClear() {
  logMessage("Display", "displayClear", "MethodName", "");
  display.clear();
  display.display();
  delay(10);
}

/**
 * Displays the home screen on the LCD display
 */
void displayScreenHome() {
  logMessage("Display", "displayScreenHome", "MethodName", "");
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  String text = "";
  if (masterState == MASTER_STATE_BOOTING) {
    text = softwareName+" V"+softwareVersion+"\n";
    text+= "Booting";
  } else {
    if (!wifiConnected()) {
      text = softwareName+" V"+softwareVersion+"\n";
      text+= "Searching Wifi...";
      /*
      if (!sdCardReady()) {
        text = softwareName+" V"+softwareVersion+"\n";
        text+= "No SD card found!";
      } else {
        text = softwareName+" V"+softwareVersion+"\n";
        text+= "WiFi: "+wifiGetIp();
      }
      */
    } else {
      text = "WiFi: "+wifiGetIp()+"\n";
      if (serverPoolHost!= "" && serverPoolPort!="") {
        text+= "Pool: "+clientHttpsGetPoolString()+"\n"; 
      } else {
        text+= "Pool: Unknown \n";
      }
      text+= "Nodes: "+String(nodes_sum)+" / Online: "+String(nodes_online)+"\n";
      text+= "Jobs: "+String(jobs_sum)+" / Blocks: "+String(jobs_blocks)+"\n";
      text+= "Good: "+String(jobs_good)+" / Bad: "+String(jobs_bad);
    }
  }
  display.drawString(0, 0, text);
  display.display();
  delay(10);
}
