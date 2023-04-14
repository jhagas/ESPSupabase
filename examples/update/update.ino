#include <Arduino.h>
#include <ESP32_Supabase.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

Supabase db;

// Put your target table here
String table = "";

// Put your JSON that you want to insert rows
// You can also use library like ArduinoJson generate this
String JSON = "";

bool upsert = false;

void setup() {
  Serial.begin(9600);

  Serial.print("Connecting to WiFi");
  WiFi.begin("ssid", "password");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Connected!");

  int code = db.update("table").eq("column", "value").doUpdate(JSON);
  Serial.println(code);
  db.urlQuery_reset();
}

void loop() {
  delay(10);
}