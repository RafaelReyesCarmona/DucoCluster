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
 * File:    ESP8266_ServerHttp.hpp
 * Version: 0.2
 * Purpose: The local HTTP server for the user front end
 * Author:  Frank Niggemann, Francisco Rafael Reyes Carmona
 */

/***********************************************************************************************************************
 * Code ServerHttp
 **********************************************************************************************************************/
/**
 * Returns the current rig status as JSON
 */
void serverHttpApiStatus() {
  logMessage("ServerHttp", "serverHttpApiStatus", "MethodName", "");
  String apiStatus = "";
  if (nodes_online > 0) {
    apiStatus += "{";
    apiStatus += "\"rig_name\":\""+nameRig+"\",";
    apiStatus += "\"rig_ip\":\""+wifiIp+"\",";
    apiStatus += "\"user_name\":\""+nameUser+"\",";
    apiStatus += "\"pool_address\":\""+serverPoolHost+":"+serverPoolPort+"\",";
    apiStatus += "\"up_and_running_since\":\""+String(workingSeconds)+"\",";
    apiStatus += "\"balance_first_value\":"+String(balanceFirstValue, 10)+",";
    apiStatus += "\"balance_first_timestamp\":"+String(balanceFirstTimestamp)+",";
    apiStatus += "\"nodes\":\""+String(nodes_sum)+"\",";
    apiStatus += "\"nodes_online\":\""+String(nodes_online)+"\",";
    apiStatus += "\"number_of_jobs\":\""+String(jobs_sum)+"\",";
    apiStatus += "\"number_of_blocks\":\""+String(jobs_blocks)+"\",";
    apiStatus += "\"jobs_good\":\""+String(jobs_good)+"\",";
    apiStatus += "\"jobs_bad\":\""+String(jobs_bad)+"\"}";
    //apiStatus += "\"core_details\":[";

    // ToDo ...

    //apiStatus += "]";
    //apiStatus += "}";
  }
  server.send(200, "text/plain", apiStatus);

  //return apiStatus;
}

/**
 * Returns the log files
 */
void serverHttpApiLog() {
  logMessage("ServerHttp", "serverHttpApiLog", "MethodName", "");
  String content = "Log";
  server.send(200, "text/plain", content);

  //return content;
}

/**
 * Initializes the HTTP server part of the software
 */
void serverHttpSetup() {
  logMessage("ServerHttp", "serverHttpSetup", "MethodName", "");
  //SPIFFS.begin();
  LittleFS.begin();

  /*
  server.on("/api/status", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", serverHttpApiStatus());
  });

  server.on("/api/log", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", serverHttpApiLog());
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html");
  });
  */

  server.on("/api/status", HTTP_GET, serverHttpApiStatus);

  server.on("/api/log", HTTP_GET, serverHttpApiLog);

  //server.on("/", HTTP_GET, server.send(200, LittleFS, "/index.html"));
  
  server.serveStatic("/", LittleFS, "/"); 
  
  server.begin();
}
