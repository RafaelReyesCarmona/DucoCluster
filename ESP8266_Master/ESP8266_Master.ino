/*
 * Project: DuinoCoinRig
 * File:    ESP8266_Master
 * Version: 0.1
 * Purpose: This is the master file that starts and coordinates the services
 * Author:  Frank Niggemann
 * 
 * Hardware: ESP8266
 * 
 * Needed files: ESP8266_ClientHttp
 *               ESP8266_ClientPool
 *               ESP8266_Display
 *               ESP8266_Helper
 *               ESP8266_Log
 *               ESP8266_Master
 *               ESP8266_SD
 *               ESP8266_ServerHttp
 *               ESP8266_Slaves
 *               ESP8266_WiFi
 * 
 * Needed libraries: ArduinoJson
 *                   ESP8266HTTPClient
 *                   ESP8266mDNS
 *                   ESP8266WiFi
 *                   ESPAsyncTCP
 *                   ESPAsyncWebServer
 *                   SdFat
 *                   SPIFFSEditor
 *                   SSD1306Wire
 *                   WiFiClient
 *                   Wire
 */

#define MASTER_STATE_UNKNOWN 0              // The ID for status UNKNOWN (Master is in an unknown state)
#define MASTER_STATE_BOOTING 1              // The ID for status BOOTING (System is booting)
#define MASTER_STATE_SCANNING 2             // The ID for status SCANNING (Master scanns for slaves)
#define MASTER_STATE_LOADING_CONFIG 3       // The ID for status LOADING_CONFIG (Master loads configuration)
#define MASTER_STATE_CONFIG_LOADED 4        // The ID for status LOADING_CONFIG (Master loads configuration)
#define MASTER_STATE_CONNECTING_WIFI 5      // The ID for status CONNECTING_WIFI (Master connects to WiFi)
#define MASTER_STATE_WIFI_CONNECTED 6       // The ID for status CONNECTING_WIFI (Master connects to WiFi)
#define MASTER_STATE_LOADING_POOL 7         // The ID for status LOADING_POOL (Master loads pool configuration)
#define MASTER_STATE_CONNECTING_CLIENTS 8   // The ID for status CONNECTING_CLIENTS (Master connects clients to pool)
#define MASTER_STATE_RUNNING 9              // The ID for status RUNNING (Master and slaves are up and running)

// Configuration
String softwareName             = "DuinoCoinRig";
String softwareVersion          = "0.1";
String configStatus             = "";
String wifiSsid                 = "";                         // Your WiFi SSID
String wifiPassword             = "";                         // Your WiFi password
String nameUser                 = "";                         // Your Duino Coin username
String nameRig                  = "";                         // Your name for this rig
String serverMainHost           = "server.duinocoin.com";     // The host of the main server
String serverMainPort           = "2812";                     // The port to connect to
String serverMainName           = "Main-Server";              // The name
String serverPoolRequestHost    = "server.duinocoin.com";     // The host of the pool request server
String serverPoolRequestPort    = "4242";                     // The port to connect to
String serverPoolRequestName    = "Pool-Server";              // The name
String serverPoolHost           = "";                         // The host of the pool server
String serverPoolPort           = "";                         // The port to connect to
String serverPoolName           = "";                         // The name

// Current state of the rig
int masterState = MASTER_STATE_UNKNOWN;                       // The current state of the master
String serverPoolError          = "";                         // The last pool error
int cores_sum = 0;                                            // The number of connected cores
int cores_online = 0;                                         // The number of cores with a connection to the pool
int jobs_good = 0;                                            // The number of cores with a connection to the pool
int jobs_bad = 0;                                             // The number of cores with a connection to the pool
  
// Methods Logging
void logSetup();
void logMessage(String message);
void logMessageSerial(String message);
void logMessageSdCard(String message);
void logMessageWebsite(String message);

// Methods Display
void displaySetup();
void displayClear();
void displayScreenHome();

// Methods SD-Card
void sdCardSetup();
bool sdCardReady();
String sdCardReadyString();
bool sdCardConfigFileExists();
String sdCardConfigFileExistsString();
void sdCardReadConfigFile();

// Methods WiFi
void wifiSetup(String ssid, String password);
String wifiGetIp();

/**
 * Initializes the software
 */
void setup() {
  delay(100);
  logSetup();
  delay(100);
  setState(MASTER_STATE_BOOTING);
  logMessage("");
  logMessage("DuinoCoinRig V0.1");
  displaySetup();
  delay(2000);
  slavesSetup();
  displayScreenHome();
  sdCardSetup();
}

/**
 * The main loop for the software
 */
void loop() {
  // put your main code here, to run repeatedly:
  if (sdCardReady() && !wifiConnected()) {
    sdCardReadConfigFile();
    wifiSetup(wifiSsid, wifiPassword);
  }
  if (serverPoolHost=="" && wifiConnected()) {
    clientHttpsRequestPoolConfiguration();
  }
  displayScreenHome();
  
  if (masterState == MASTER_STATE_LOADING_POOL) {
    setState(MASTER_STATE_CONNECTING_CLIENTS);
  }
  if (masterState == MASTER_STATE_LOADING_POOL) {
    setState(MASTER_STATE_CONNECTING_CLIENTS);
  }
  if (masterState == MASTER_STATE_CONNECTING_CLIENTS) {
    setState(MASTER_STATE_RUNNING);
  }
  delay(100);
}

void setState(int state) {
  masterState = state;
  logMessage("Set state ID: "+String(state));
}
