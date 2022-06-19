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
 * File:    ESP8266_Master.cpp
 * Version: 0.2
 * Purpose: This is the master file that starts and coordinates the services
 * Authors: Frank Niggemann, Francisco Rafael Reyes Carmona
 * 
 * Hardware: ESP8266
 * Dependency Graph:
 * |-- ArduinoJson @ 6.19.4
 * |-- NTPClient @ 3.2.1
 * |-- ESP8266 and ESP32 OLED driver for SSD1306 displays @ 4.3.0
 * |   |-- Wire @ 1.0
 * |-- ESP8266HTTPClient @ 1.2
 * |   |-- ESP8266WiFi @ 1.0
 * |-- ESP8266mDNS @ 1.2
 * |   |-- ESP8266WiFi @ 1.0
 * |-- ESP8266WebServer @ 1.0
 * |   |-- ESP8266WiFi @ 1.0
 * |-- ESP8266WiFi @ 1.0
 * |-- LittleFS @ 0.1.0
 * |-- Wire @ 1.0
 */

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <NTPClient.h>
//#define SPI_DRIVER_SELECT 2  // SoftSpiDriver Define before include.
//#include <SdFat.h>
#include <LittleFS.h>        //#include <SPIFFSEditor.h>
#include <SSD1306Wire.h>
#include <WiFiUdp.h>
#include <Wire.h>
//#include <ThermistorNTC.h>


/***********************************************************************************************************************
 * Methods
 **********************************************************************************************************************/

// Methods Master
void            setStateMaster(int state);

// Methods Client HTTPS
void            clientHttpsSetup();
String          clientHttpsGetContent(String url);
void            clientHttpsRequestPoolConfiguration();
String          clientHttpsGetPoolString();
void            clientHttpsRequestUserBalance();

// Methods Client Pool
void            clientPoolSetup();
void            clientPoolConnectClients();
void            clientPoolRotateStates();
void            clientPoolLogStates();
int             clientPoolClientsOnline();
int             clientPoolClientsOnlineActive();
bool            clientPoolClientIsConnected(int id);
bool            clientPoolConnectClient(int id);
bool            clientPoolRequestNextJobForClient(int id);
String          clientPoolReadJobRequestResultForClient(int id);
void            clientPoolSendClientJobToSlave(int id);
void            clientPoolRequestClientJobResultFromSlave(int id);
bool            clientPoolSendJobResultForClient(int id);
String          clientPoolReadJobResultResultForClient(int id);
String          clientPoolGetContentFromClient(int id);
void            clientPoolGetAndEvaluateContent(int id);
void            setStateClient(int id, int state);
void            clientPoolValidateState(int id);

// Methods Display
void            displaySetup();
void            displayClear();
void            displayScreenHome();

// Methods Helper
String          splitStringAndGetValue(String data, char separator, int index);

// Methods Logging
void            logSetup();
void            logMessage(String partName, String methodName, String type, String message);
void            logMessageSerial(String message); 


// Methods NTP
void            ntpSetup();
unsigned long   ntpGetTimestamp();

// Methods SD card
//void            sdCardSetup();
//bool            sdCardReady();
//String          sdCardReadyString();
//bool            sdCardConfigFileExists();
//String          sdCardConfigFileExistsString();
//void            sdCardReadConfigFile();

// Methods HTTP server
void            serverHttpSetup();
void            serverHttpApiStatus();
void            serverHttpApiLog();

// Methods slaves
void            slavesSetup();
void            slavesWireInit();
void            slavesScan();
void            slavesRefresh();
boolean         slaveExists(byte id);
void            slaveSendMessage(byte id, String message);
void            slavesSendMessage(String message);
void            slaveSendNextJob(byte id, /*String resultType,*/ String lastBlockHash, String nextBlockHash, String difficulty);
void            slaveSendText(byte id, String text);
void            slaveSendLn(byte id, String text);
String          slaveRequestLn(byte id);

// Methods WiFi
void            wifiSetup(String ssid, String password);
bool            wifiConnected();
String          wifiGetIp();

// Temperarute with thermistor
//float           tempGet(Thermistor_connection ConType);

/***********************************************************************************************************************
 * Code Master
 **********************************************************************************************************************/
#include "ESP8266_Config.hpp"
#include "ESP8266_Log.hpp"
#include "ESP8266_ClientHttps.hpp"
#include "ESP8266_ClientPool.hpp"
#include "ESP8266_Display.hpp"
#include "ESP8266_Helper.hpp"
#include "ESP8266_NTP.hpp"
#include "ESP8266_SdCard.hpp"
#include "ESP8266_ServerHttp.hpp"
#include "ESP8266_Slaves.hpp"
#include "ESP8266_Wifi.hpp"
//#include "ESP8266_Temp.hpp"


/**
 * Sets the master state
 * 
 * @param int setStateMaster The id of the state
 */
void setStateMaster(int state) {
  logMessage("Master", "setStateMaster", "MethodName", "");
  if (masterState != state) {
    masterState = state;
    logMessage("Master", "setStateMaster", "StateChange", "Master changed state to " + String(state));
  }
}

/**
 * Initializes the software
 */
void setup() {
  delay(100);
  logSetup();
  delay(100);
  setStateMaster(MASTER_STATE_BOOTING);
  logMessage("Master", "setStateMaster", "MethodName", "\n"+softwareName+" "+softwareVersion+"\n"+"\n");
  displaySetup();
  delay(12000);
  slavesSetup();
  displayScreenHome();
  //if (loadConfigFromSdCard) {
  //  sdCardSetup();
  //}
}

/**
 * The main loop for the software
 */
void loop() {
  displayScreenHome();
  /*
  if (loadConfigFromSdCard && !wifiConnected()) {
    if (sdCardReady()) sdCardReadConfigFile();
    displayScreenHome();
  } else if (!loadConfigFromSdCard && !wifiConnected()) {
    setStateMaster(MASTER_STATE_CONFIG_LOADED);
    displayScreenHome();
  }
  */
  if (!wifiConnected()) {
    setStateMaster(MASTER_STATE_CONFIG_LOADED);
    displayScreenHome();
  }
  
  if (masterState == MASTER_STATE_CONFIG_LOADED) {
    wifiSetup(wifiSsid, wifiPassword);
    displayScreenHome();
  }
  
  if (masterState == MASTER_STATE_WIFI_CONNECTED) {
    ntpSetup();
    if (timestampFirst == 0) {
      timestampFirst = ntpGetTimestamp();
      timestampNow = timestampFirst;
      timestampUpdateLast = millis();
    }
    clientHttpsSetup();
    clientHttpsRequestUserBalance();
    clientHttpsRequestPoolConfiguration();
    displayScreenHome();
  }
  
  if (masterState == MASTER_STATE_POOL_LOADED) {
    clientPoolConnectClients();
    nodes_online = clientPoolClientsOnline();
    displayScreenHome();
  }
  
  if (masterState == MASTER_STATE_CLIENTS_CONNECTED) {
    setStateMaster(MASTER_STATE_RUNNING);
    displayScreenHome();
    balanceFirstTimestamp = ntpGetTimestamp();
  }

  if (masterState == MASTER_STATE_RUNNING) {
    clientPoolRotateStates();
    displayScreenHome();
    if (!webserverStarted) {
      serverHttpSetup();
      webserverStarted = true;
    }
    server.handleClient();
  }

  if ((millis() - timestampUpdateLast) > timestampUpdateEvery) {
    timestampNow = ntpGetTimestamp();
    timestampUpdateLast = millis();
    workingSeconds = timestampNow - timestampFirst;
    logMessage("Master", "setStateMaster", "MethodDetail", "workingSeconds = " + String(timestampNow) + " - " + String(timestampFirst) + " = " + String(workingSeconds));
    if (serverPoolHost=="" || serverPoolPort=="" || nodes_online==0) { // change && for ||.
      clientHttpsRequestPoolConfiguration();
    }
  } else {
    workingSeconds = timestampNow - timestampFirst + (millis()/1000) - (timestampUpdateLast/1000);
    logMessage("Master", "setStateMaster", "MethodDetail", "workingSeconds = " + String(timestampNow) + " - " + String(timestampFirst) + " + " + String((millis()/1000)) + " - " + String((timestampUpdateLast/1000)) + " = " + String(workingSeconds));
  }
  if (clientPoolClientsOnlineActive() < nodes_online) {
    byte count = 0;
    for (int id=SLAVE_ID_MIN ; id<SLAVE_ID_MAX ; id++) {
      if (clientPoolConnectClient(id)) count++;
    }
    nodes_online = count;
    displayScreenHome();
  }
  delay(50);
}
