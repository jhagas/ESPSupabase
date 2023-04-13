#include <Arduino.h>
#include <ESP32_Supabase.h>
#include <WiFi.h>

Supabase db;

// Put your supabase URL and Anon key here...
// Because Login already implemented, there's no need to use secretrole key
String supabase_url = "https://bzdazgjthqumbxiexchy.supabase.co";
String anon_key = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6ImJ6ZGF6Z2p0aHF1bWJ4aWV4Y2h5Iiwicm9sZSI6ImFub24iLCJpYXQiOjE2ODExNjAwNTcsImV4cCI6MTk5NjczNjA1N30.nQb4GMqJY9DGt-i7gsd4DSSHmBwo7ucUOJHqhp5OlHE";

// put your WiFi credentials (SSID and Password) here
const char* ssid = "FALKO 1";
const char* psswd = "12345678";

// Put Supabase account credentials here
const String email = "jhagas@e.email";
const String password = "thisispassword";

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