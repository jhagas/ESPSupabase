#include <Arduino.h>
#include <Supabase.h>
#include <WiFi.h>

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
  WiFi.begin("Jhagas H.", "tibetanplateau");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Connected!");

  int code = db.insert(table, JSON, upsert);
  Serial.println(code);
}

void loop() {
  delay(10);
}