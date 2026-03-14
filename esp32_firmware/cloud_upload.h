#ifndef CLOUD_UPLOAD_H
#define CLOUD_UPLOAD_H

#include <HTTPClient.h>

String serverURL = "http://IPv4_Address:3000";
String deviceKey = "ESP32_SECRET_123";

void uploadToCloud(String message)
{
  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi not connected");
    return;
  }

  HTTPClient http;

  Serial.println("Sending data to bridge server...");

  http.begin(serverURL);

  http.addHeader("Content-Type","text/plain");
  http.addHeader("Device-Key",deviceKey);

  int httpCode = http.POST(message);

  Serial.print("HTTP Response: ");
  Serial.println(httpCode);

  http.end();
}

#endif