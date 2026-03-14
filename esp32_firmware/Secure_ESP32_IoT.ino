#include <WiFi.h>
#include <BluetoothSerial.h>

#include "cloud_upload.h"
#include "encryption.h"

BluetoothSerial SerialBT;

String ssid="";
String password="";
String macAddress="";

String readInput()
{
  while(!Serial.available()) delay(10);

  String s = Serial.readStringUntil('\n');
  s.trim();

  return s;
}

void connectWiFi()
{
  Serial.println("\nScanning WiFi...\n");

  int n = WiFi.scanNetworks();

  for(int i=0;i<n;i++)
  {
    Serial.print(i+1);
    Serial.print(": ");
    Serial.println(WiFi.SSID(i));
  }

  Serial.println("\nSelect WiFi number:");

  int choice = readInput().toInt();

  ssid = WiFi.SSID(choice-1);

  Serial.print("SSID: ");
  Serial.println(ssid);

  Serial.println("Enter password:");

  password = readInput();

  Serial.println("Connecting...");

  WiFi.begin(ssid.c_str(),password.c_str());

  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  macAddress = WiFi.macAddress();

  Serial.print("ESP32 MAC: ");
  Serial.println(macAddress);
}

void sendMessage(String msg)
{
  String data =
  "ESP32["+macAddress+"]("+ssid+","+WiFi.localIP().toString()+"):"+msg;

  Serial.println(data);

  String encrypted = encryptMessage(data);

  Serial.println("Encrypted message sent");

  uploadToCloud(encrypted);
}

void setup()
{
  Serial.begin(115200);

  delay(2000);

  connectWiFi();

  SerialBT.begin("ESP32_NODE");

  Serial.println("\nBluetooth Ready");
  Serial.println("Connect mobile to ESP32_NODE");
}

void loop()
{
  if(SerialBT.available())
  {
    String msg = SerialBT.readStringUntil('\n');
    msg.trim();

    if(msg.length()>0)
      sendMessage(msg);
  }

  if(Serial.available())
  {
    String msg = Serial.readStringUntil('\n');
    msg.trim();

    if(msg.length()>0)
      sendMessage(msg);
  }
}