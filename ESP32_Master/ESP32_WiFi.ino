/*
 * Project: DuinoCoinRig
 * File:    ESP32_WiFi
 * Version: 0.1
 * Purpose: Communication with the wireless network
 * Author:  Frank Niggemann
 */

#include <WiFi.h>

/**
 * Initializes the WiFi part of the software
 * 
 * @param String ssid The SSID of the WiFi networt
 * @param String password The password for the WiFi network with the given SSID
 */
void wifiSetup(String ssid, String password) {
  if (ssid!="") {
    setState(MASTER_STATE_CONNECTING_WIFI);
    logMessage("Connecting to: " + String(ssid));
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.status() != WL_CONNECTED) {
      delay(200);
    }
    logMessage("Connected to: " + String(ssid));
    setState(MASTER_STATE_WIFI_CONNECTED);
    logMessage("Connected with IP address: " + wifiGetIp());
  } else {
    logMessage("Can't connect to WiFi without SSID");
  }
  displayScreenHome();
}

/**
 * Returns the WiFi connection status
 * 
 * @return bool Returns the connection status 
 */
bool wifiConnected() {
  if (WiFi.status() != WL_CONNECTED) {
    return false;
  }
  return true;
}

/**
 * Returns the IP of the WiFi connection
 * 
 * @return String Returns the IP of the current WiFi connection or "Not connected"
 */
String wifiGetIp() {
  if (!wifiConnected()) {
    return "Not connected";
  }
  return WiFi.localIP().toString();
}