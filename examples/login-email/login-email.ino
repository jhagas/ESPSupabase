#include <Arduino.h>
#include <ESP32_Supabase.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

Supabase db;

// Put your supabase URL and Anon key here...
// Because Login already implemented, there's no need to use secretrole key
String supabase_url = "";
String anon_key = "";

// put your WiFi credentials (SSID and Password) here
const char* ssid = "your wifi ssid";
const char* psswd = "your wifi password";

// Put Supabase account credentials here
const String email = "";
const String password = "";

void setup() {
  Serial.begin(9600);

  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, psswd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Connected!");

  db.begin(supabase_url, anon_key);
  db.login_email(email, password);
}

void loop() {
  delay(10);
}