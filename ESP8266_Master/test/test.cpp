#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

String          urlRequestPool                                      = "https://server.duinocoin.com/getPool";     // The url to request the pool server
WiFiClient      client;
// Change the part in brackets to your WiFi name
String SSID = "recaf_2G";
// Change the part in brackets to your WiFi password
String PASSWORD = "dece423dece423";
String serverPoolHost = "";
String serverPoolPort = "";
String serverPoolName = "";

void SetupWifi() {
  Serial.println("Connecting to: " + String(SSID));
  WiFi.mode(WIFI_STA); // Setup ESP in client mode
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.begin(SSID, PASSWORD);

  int wait_passes = 0;
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (++wait_passes >= 10) {
      WiFi.begin(SSID, PASSWORD);
      wait_passes = 0;
    }
  }

  Serial.println("\n\nnSuccessfully connected to WiFi");
  Serial.println("Local IP address: " + WiFi.localIP().toString());
  Serial.println();
}

String httpGetString(String URL) {
  String payload = "";
  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient http;
  
  if (http.begin(client, URL)) {
    int httpCode = http.GET();
    
    if (httpCode == HTTP_CODE_OK) payload = http.getString();
    else Serial.printf("Error fetching node from poolpicker: %s\n", http.errorToString(httpCode).c_str());

    http.end();
  }
  return payload;
}

void gethttp() {
    String httpstring;
    httpstring = httpGetString(urlRequestPool);
    DynamicJsonDocument json(1024);
    deserializeJson(json, httpstring);
    serverPoolHost = String((const char*)json["ip"]);
    serverPoolPort = String(json["port"]);
    serverPoolName = String((const char*)json["name"]);
    Serial.println(httpstring);
}

void setup() {
    Serial.begin(115200);
    Serial.println("\n");
    SetupWifi();
}

void loop() {
  gethttp();
    Serial.println("Host: "+serverPoolHost);
    Serial.println("Port: "+serverPoolPort);
    Serial.println("Name : "+serverPoolName);
}