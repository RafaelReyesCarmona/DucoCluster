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
 * File:    ESP8266_Config.hpp
 * Version: 0.1
 * Purpose: Global variables. Change for your own situation.
 * Author:  Francisco Rafael Reyes Carmona
 */

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

// Possible states for the master node
#define         MASTER_STATE_UNKNOWN                                  0                                           // The ID for status UNKNOWN (Master is in an unknown state)
#define         MASTER_STATE_BOOTING                                  1                                           // The ID for status BOOTING (System is booting)
#define         MASTER_STATE_SCANNING                                 2                                           // The ID for status SCANNING (Master scanns for slaves)
#define         MASTER_STATE_LOADING_CONFIG                           3                                           // The ID for status LOADING_CONFIG (Master loads configuration)
#define         MASTER_STATE_CONFIG_LOADED                            4                                           // The ID for status LOADING_CONFIG (Master loads configuration)
#define         MASTER_STATE_CONNECTING_WIFI                          5                                           // The ID for status CONNECTING_WIFI (Master connects to WiFi)
#define         MASTER_STATE_WIFI_CONNECTED                           6                                           // The ID for status CONNECTING_WIFI (Master connects to WiFi)
#define         MASTER_STATE_LOADING_POOL                             7                                           // The ID for status LOADING_POOL (Master loads pool configuration)
#define         MASTER_STATE_POOL_LOADED                              8                                           // The ID for status POOL_LOADED (Master successfully loaded pool configuration)
#define         MASTER_STATE_CONNECTING_CLIENTS                       9                                           // The ID for status CONNECTING_CLIENTS (Master connects clients to the pool server)
#define         MASTER_STATE_CLIENTS_CONNECTED                        10                                          // The ID for status CLIENTS_CONNECTED (Master connected clients to the pool server)
#define         MASTER_STATE_RUNNING                                  11                                          // The ID for status RUNNING (Master and slaves are up and running)

// Possible states for the pool server clients
#define         CLIENT_STATE_UNKNOWN                                  0                                           // The ID for status UNKNOWN (Client is in an unknown state)
#define         CLIENT_STATE_OFFLINE                                  1                                           // The ID for status OFFLINE (Client is offline)
#define         CLIENT_STATE_CONNECTING                               2                                           // The ID for status CONNECTING (Client is connecting to pool server)
#define         CLIENT_STATE_ONLINE                                   3                                           // The ID for status ONLINE (Client is connected to pool server)
#define         CLIENT_STATE_JOB_REQUEST_SENT_TO_SERVER               4                                           // The ID for status JOB_REQUEST_SENT_TO_SERVER (Client has sent a job request to the server)
#define         CLIENT_STATE_JOB_REQUEST_RESULT_FROM_SERVER           5                                           // The ID for status JOB_REQUEST_RESULT_FROM_SERVER (Server has answered the request for a job)
#define         CLIENT_STATE_JOB_SENT_TO_SLAVE                        6                                           // The ID for status JOB_SENT_TO_SLAVE (Job has been sent to the slave)
#define         CLIENT_STATE_JOB_RESULT_FROM_SLAVE                    7                                           // The ID for status JOB_RESULT_FROM_SLAVE (Slave has sent the result for the job)
#define         CLIENT_STATE_JOB_RESULT_SENT_TO_SERVER                8                                           // The ID for status JOB_RESULT_SENT_TO_SERVER (Client has sent the job result to the server for verification)
#define         CLIENT_STATE_JOB_RESULT_RESULT_FROM_SERVER            9                                           // The ID for status JOB_RESULT_RESULT_FROM_SERVER (Server has answered the request for verification)
#define         CLIENT_STATE_ERROR                                    10                                          // The ID for status ERROR (The client has an error)

// Slaves
#define         SLAVE_ID_MIN                                          1                                           // The first possible address for a slave
#define         SLAVE_ID_MAX                                          5                                           // The last possible address for a slave
#define         WIRE_PIN_SDA                                          D1                                          // The communication pin for SDA (D2 on ESP8266)
#define         WIRE_PIN_SCL                                          D2                                          // The communication pin for SCL (D1 on ESP8266)
#define         WIRE_CLOCK                                            100000                                      // The I2C communication frequency

// Display
#define         OLED_PIN_SDA                                          WIRE_PIN_SDA                                // The communication pin for SDA (D2 on ESP8266) This is inverted on Wemos Deauther ESP8266 + OLED + 18650 SDA -> D1.
#define         OLED_PIN_SCL                                          WIRE_PIN_SCL                                // The communication pin for SCL (D1 on ESP8266) This is inverted on Wemos Deauther ESP8266 + OLED + 18650 SCL -> D2.
#define         OLED_ADDR                                             0x3C                                        // The address of the OLED display
#define         OLED_FLIP_VERTICALLY                                  0                                           // With 1 the content of the display will be flipped vertically

// SD
//#define         SD_PIN_CS                                             (uint8_t)10U                                          // The CS pin (D8 on ESP8266)
//#define         SD_PIN_MOSI                                           (uint8_t)11U
//#define         SD_PIN_MISO                                           (uint8_t)7U
//#define         SD_PIN_CLK                                            (uint8_t)6U

/***********************************************************************************************************************
 * Variables
 **********************************************************************************************************************/

// Configuration
String          softwareName                                        = "DucoCluster";                              // The name of this software          
String          softwareVersion                                     = "1.0";                                      // The version of this software
String          minerName                                           = "AVR I2C 3.1";                              // The name of the miner
String          wifiSsid                                            = "xxxxxxxxxxx";                                 // Your WiFi SSID
String          wifiPassword                                        = "xxxxxxxxxxxx";                           // Your WiFi password
String          wifiIp                                              = "";                                         // Your WiFi IP
String          nameUser                                            = "xxxxxxxxxxx";                                    // Your Duino Coin username
String          nameRig                                             = "DucoClusterAVR";                           // Your name for this rig
String          urlRequestPool                                      = "https://server.duinocoin.com/getPool";     // The url to request the pool server
String          urlRequestUserBalance                               = "https://server.duinocoin.com/balances/";   // The url to request the balance
String          serverPoolHost                                      = "";                                         // The host of the pool server
String          serverPoolPort                                      = "";                                         // The port to connect to
String          serverPoolName                                      = "";                                         // The name of the pool server

/* For testing
 * String          serverPoolHost                                      = "162.55.103.174";                         // The host of the pool server
 * String          serverPoolPort                                      = "6000";                                   // The port to connect to
 * String          serverPoolName                                      = "diskos-pool-1";                          // The name of the pool server
*/

// Unsupported for future implementations
//bool            loadConfigFromSdCard                                = false;                                      // With true loads config from SD card and overwrites this config here

// Communication HTTPS
WiFiClientSecure clientSecure;
HTTPClient      https;                                                                                            // The used instance of HTTPClient to request content from a HTTPS source (ClientHttps)
String          serverBalanceError                                  = "";                                         // The last balance server error

// Communication pool server
WiFiClient      poolClientInstance[SLAVE_ID_MAX];                                                                 // The used instancec of WiFiClient to communicate with the pool server (ClientPool)
String          poolClientBuffer[SLAVE_ID_MAX];                                                                   // The communication buffer to ensure that only complete datasets will be processed (ClientPool)
String          poolClientServerVersion[SLAVE_ID_MAX];                                                            // The server version for the clients node, reported by the pool server (ClientPool)
String          poolClientLastBlockHash[SLAVE_ID_MAX];                                                            // The last block hash for the clients node, reported by the pool server (ClientPool)
String          poolClientNextBlockHash[SLAVE_ID_MAX];                                                            // The next block hash for the clients node, reported by the pool server (ClientPool)
String          poolClientDifficulty[SLAVE_ID_MAX];                                                               // The difficulty for the clients node, reported by the pool server (ClientPool)
int             poolClientState[SLAVE_ID_MAX];                                                                    // The state of the client (ClientPool)
unsigned long   poolClientTimeRequestStart[SLAVE_ID_MAX];                                                         // The time when the last request was sent to the pool server (ClientPool)
String          poolClientDucos1aResult[SLAVE_ID_MAX];                                                            // The result of the Ducos1a class reported by the slave (ClientPool)
String          poolClientDucoId[SLAVE_ID_MAX];                                                                   // The ID of the slave (ClientPool)
String          poolClientMicrotimeDifference[SLAVE_ID_MAX];                                                      // The time used to calculate the result reported by the slave (ClientPool)
int             poolClientLoopsWithoutStateChange[SLAVE_ID_MAX];                                                  // The number of loops without changing the state (ClientPool)
unsigned long   poolClientJobsSum[SLAVE_ID_MAX];                                                                  // The number of jobs sent to the slave (ClientPool)
unsigned long   poolClientJobsBlocks[SLAVE_ID_MAX];                                                               // The number of found blocks for the slave (ClientPool)
unsigned long   poolClientJobsGood[SLAVE_ID_MAX];                                                                 // The number of correct results for the slave (ClientPool)
unsigned long   poolClientJobsBad[SLAVE_ID_MAX];                                                                  // The number of wrong results for the slave (ClientPool)
String          serverPoolError          = "";                                                                    // The last pool server error

// Display
SSD1306Wire     display(OLED_ADDR, OLED_PIN_SDA, OLED_PIN_SCL);                                                   // The used instance of SSD1306Wire with configuraion for the used display
//SH1106Wire      display(OLED_ADDR, OLED_PIN_SDA, OLED_PIN_SCL);

// Log
bool logSerial                                                      = false;                                       // true -> The log will be sent to the serial communication
bool logClientHttps                                                 = false;                                       // true -> Writes the logs for Part ClientHttps
bool logClientPool                                                  = false;                                       // true -> Writes the logs for Part ClientPool
bool logDisplay                                                     = false;                                       // true -> Writes the logs for Part Display
bool logHelper                                                      = false;                                       // true -> Writes the logs for Part Helper
bool logMaster                                                      = false;                                       // true -> Writes the logs for Part Master
bool logNtp                                                         = false;                                       // true -> Writes the logs for Part Ntp
bool logSdCard                                                      = false;                                       // true -> Writes the logs for Part SdCard
bool logServerHttp                                                  = false;                                       // true -> Writes the logs for Part ServerHttp
bool logSlaves                                                      = false;                                       // true -> Writes the logs for Part Slaves
bool logWiFi                                                        = false;                                       // true -> Writes the logs for Part WiFi
bool logMethodNames                                                 = false;                                       // true -> Writes the logs for method names
bool logMethodDetails                                               = false;                                       // true -> Writes the logs for method details
bool logStateChanges                                                = false;                                       // true -> Writes the logs for state changes 

// NTP
WiFiUDP         ntpUDP;                                                                                           // The used instance of WiFiUDP for UDP communication with NTP server
NTPClient       timeClient(ntpUDP, "pool.ntp.org", 0);                                                            // The used instance of NTPClient with configuration

// SD card
//SdFat           sd;                                                                                               // The used instance of SdFat for accessing the SD card
//SdFile          file;                                                                                             // The used instance of SdFile for reading a file from SD card
//const size_t    LINE_DIM                                            = 100;                                        // The max length of a line in the configuration file
//char            line[LINE_DIM];                                                                                   // The array for the lines in the configuration file

// Local HTTP server
ESP8266WebServer server(80);                                                                                       // The used instance of AsyncWebServer for serving a website on port 80
bool            webserverStarted                                    = false;                                       // Set to true once the local web server has started

// Slaves
bool            slaveFound[SLAVE_ID_MAX];                                                                         // An array with all possible IDs and the information if there is a slave with this ID

// Current state of the rig
int             masterState                                         = MASTER_STATE_UNKNOWN;                       // The current state of the master
int             nodes_sum                                           = 0;                                          // The number of connected nodes
int             nodes_online                                        = 0;                                          // The number of nodes with a connection to the pool
unsigned long   jobs_sum                                            = 0;                                          // The number of jobs (complete)
unsigned long   jobs_blocks                                         = 0;                                          // The number of blocks found
unsigned long   jobs_good                                           = 0;                                          // The number of good jobs
unsigned long   jobs_bad                                            = 0;                                          // The number of bad jobs
unsigned long   timestampFirst                                      = 0;                                          // First received timestamp
unsigned long   timestampNow                                        = 0;                                          // Current timestamp
unsigned long   timestampUpdateLast                                 = 0;                                          // Timestamp for last update
unsigned long   timestampUpdateEvery                                = 30000;                                      // Update every 30000ms
unsigned long   workingSeconds                                      = 0;                                          // The number of seconds the rig has been running
unsigned long   balanceFirstTimestamp                               = 0;                                          // Timestamp when the first balance has been received
float           balanceFirstValue                                   = 0.0;                                          // The first received balance
unsigned long   balanceLastTimestamp                                = 0;                                          // Timestamp when the last balance has been received
float           balanceLastValue                                    = 0.0;                                          // The last received balance

// Temperature NTC
// Declaration for NTC thermistor beta. 
//Thermistor thermistor(/* PIN */       A0,
//                      /* RESISTOR */  21900L,
//                      /* NTC 25ºC */  9950L,
//                      /* BETA */      4190.0,
//                      /* Vref */      3.30);

//Thermistor thermistor(/* PIN */      A0,
//                       /* RESISTOR */  22170L,
//                       /* NTC_T1 */    355000L,
//                       /* T1 (ºC) */   0.0,  // 273,15 ºK
//                       /* NTC_T2 */    157500L,
//                       /* T2 (ºC) */   14.0, // 287,15 ºK
//                       /* NTC_T3 */    79300L,
//                       /* T3 (ºC) */   28.0, // 301,15 ºK
//                       /* NTC_T4 */    58300L,
//                       /* T4 (ºC) */   35.0, // 308,15 ºK
//                       /* Vref */      3.30);