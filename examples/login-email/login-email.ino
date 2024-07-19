// ONLY IF you activate RLS in your Supabase Table

#include <Arduino.h>
#include <ESPSupabase.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

Supabase db;

// Put your supabase URL and Anon key here...
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
  Serial.println("\nConnected!");

  db.begin(supabase_url, anon_key);

  // ONLY IF you activate RLS in your Supabase Table
  db.login_email(email, password);

  // Your Query ...
}

void loop() {
  delay(1000);
}