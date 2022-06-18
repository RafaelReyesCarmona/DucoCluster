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
 * File:    ESP8266_ClientHttps.hpp
 * Version: 0.2
 * Purpose: Connection and communication with the Duino Coin Server
 * Authors: Frank Niggemann, Francisco Rafael Reyes Carmona
 * 
 */

/***********************************************************************************************************************
 * Code ClientHttps
 **********************************************************************************************************************/


/**
 * Initializes the HTTPS client part of the software
 */
void clientHttpsSetup() {
  logMessage("Master", "clientHttpsSetup", "MethodName", "");
  clientSecure.setInsecure();
  https.setTimeout(30000);
}

/**
 * Reads and returns the content from the given URL
 * 
 * @param String url The URL whose content is to be read and returned
 * 
 * @return String The content
 */
String clientHttpsGetContent(String url) {
  logMessage("ClientHttps", "clientHttpsGetContent", "MethodName", "");
  if (!wifiConnected()) wifiSetup(wifiSsid,wifiPassword);
  String httpsContent;

  if (https.begin(clientSecure, url))
  {
    https.useHTTP10();
    delay(50);
    int httpsCode = https.GET();
    if (httpsCode == HTTP_CODE_OK)
    {
      httpsContent = https.getString();
      logMessage("ClientHttps", "clientHttpsGetContent", "MethodDetail", "HTTPS get content: "+httpsContent);
      https.end();
    }
    else
    {
      logMessage("ClientHttps", "clientHttpsGetContent", "MethodDetail", "HTTPS get content failed with errorcode ("+String(httpsCode)+") -> " + https.errorToString(httpsCode));
    }
  }
  return httpsContent;
}

/**
 * Requests a pool configuration from the pool server
 */ 
void clientHttpsRequestPoolConfiguration() {
  String content;
  content = clientHttpsGetContent(urlRequestPool);
  logMessage("ClientHttps", "clientHttpsRequestPoolConfiguration", "MethodName", "");
  if (masterState != MASTER_STATE_LOADING_POOL) {
    setStateMaster(MASTER_STATE_LOADING_POOL);
  }
  if (content != "") {
    logMessage("ClientHttps", "clientHttpsRequestPoolConfiguration", "MethodDetail", "Return content -> " + content);
    DynamicJsonDocument json(256);
    deserializeJson(json, content);
    serverPoolHost = String((const char*)json["ip"]);
    serverPoolPort = String((long)json["port"]);
    serverPoolName = String((const char*)json["name"]);
    setStateMaster(MASTER_STATE_POOL_LOADED);
    logMessage("ClientHttps", "clientHttpsRequestPoolConfiguration", "MethodDetail", "Updated pool configuration to host " + serverPoolHost + " and port " + serverPoolPort + " with name " + serverPoolName);
    serverPoolError = "";
  } else {
    // ToDo: Create fallback solution!
    logMessage("ClientHttps", "clientHttpsRequestPoolConfiguration", "MethodDetail", "Connection failed!");
  }
  if (serverPoolHost!="" && serverPoolPort!="") {
    if (masterState != MASTER_STATE_POOL_LOADED) {
      setStateMaster(MASTER_STATE_POOL_LOADED);
      logMessage("ClientHttps", "clientHttpsRequestPoolConfiguration", "MethodDetail", "Updated pool configuration to host " + serverPoolHost + " and port " + serverPoolPort + " with name " + serverPoolName);
    }
    serverPoolError = "";
    return;
  }
  logMessage("ClientHttps", "clientHttpsRequestPoolConfiguration", "MethodDetail", "Request pool from " + urlRequestPool);
  
}

/**
 * Requests the user balance for the current user and updates the value in the system
 */ 
void clientHttpsRequestUserBalance() {
  String content;
  String url = urlRequestUserBalance+nameUser;
  content = clientHttpsGetContent(url);
  logMessage("ClientHttps", "clientHttpsRequestUserBalance", "MethodName", "");
  if (content != "") {
    DynamicJsonDocument json(384);
    deserializeJson(json, content);
    float ducoBalance = 0.0;
    ducoBalance = (float)json["result"]["balance"];
    if (balanceFirstValue == 0.0) {
      balanceFirstValue = ducoBalance;
      balanceFirstTimestamp = ntpGetTimestamp();
    }
    balanceLastValue = ducoBalance;
    balanceLastTimestamp = ntpGetTimestamp();
  } else {
  logMessage("ClientHttps", "clientHttpsRequestUserBalance", "MethodDetail", "Connection failed!");
  }
}

/**
 * Returns the pool configuration or 'unknown' as result
 * 
 * @return String The pool configuration or 'unknown'
 */
String clientHttpsGetPoolString() {
  logMessage("ClientHttps", "clientHttpsGetPoolString", "MethodName", "");
  String pool = "Unknown";
  if (serverPoolHost!= "" && serverPoolPort!="") {
    pool = serverPoolHost + ":" + serverPoolPort;
  }
  logMessage("ClientHttps", "clientHttpsGetPoolString", "MethodDetail", "Returns " + pool);
  return pool;
}
