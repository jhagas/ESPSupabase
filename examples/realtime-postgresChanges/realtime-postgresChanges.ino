#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP_Supabase.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

enum DEBUGTYPES {
  DEBUG_ERROR,
  DEBUG_INFO,
  DEBUG_MOTOR,
  DEBUG_VERBOSE,
  DEBUG_LED,
  DEBUG_FEED,
  DEBUG_SYNC
};

typedef enum DEBUGTYPES DEBUGTYPES;


DEBUGTYPES APP_DEBUG_LEVEL[4] = {
  DEBUG_ERROR,
  DEBUG_FEED,
  DEBUG_INFO,
  DEBUG_SYNC
};

void DEBUG_PRINT(String str, DEBUGTYPES debuglevel) {
  for (int i = 0; i < 4; i++) {
    if (APP_DEBUG_LEVEL[i] == debuglevel) {
      Serial.println(String(APP_DEBUG_LEVEL[i]) + " " + str);
      return;
    }
  }

  return;
}


void wifiConnected() {
  DEBUG_PRINT("WiFi Connected: " + WiFi.SSID(), DEBUG_INFO);
  DEBUG_PRINT("IP Address: ", DEBUG_INFO);
  DEBUG_PRINT(String(WiFi.localIP()), DEBUG_INFO);
}

bool waitForWifi(int timeout = 0, String method = "") {
  int cnt = 0;
  ProgressBar status = ProgressBar(timeout);
  DEBUG_PRINT("", DEBUG_INFO);

  DEBUG_PRINT("Attempting Connection: " + method, DEBUG_INFO);
  status.start();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    status.step();
    cnt++;

    if (cnt >= timeout && timeout > 0) {
      status.end();
      return false;
    }
  }
  status.end();

  return true;
}

Supabase db;

void DevicesTableHandler(JsonDocument result) {
  serializeJson(result, Serial);
}

void setup() {
  Serial.begin(9600);

  WiFi.begin("ssid", "password");
  if (waitForWifi(50, ".ENV")) {
    wifiConnected();
  };

  db.setupRealtime(SUPABASEURL, SUPABASEANONKEY);
  int numqueries = 0;
  SUPABASEQuery queries[numqueries] = {};
  db.realtime.addEntry("Devices", "*", queries, numqueries, DevicesTableHandler);
}

void loop() {
  db.realtime.loop();
}