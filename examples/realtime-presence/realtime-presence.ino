#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESPSupabaseRealtime.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

// Put your supabase URL and Anon key here...
String supabase_url = "https://yourproject.supabase.co";
String anon_key = "anonkey";

// put your WiFi credentials (SSID and Password) here
const char *ssid = "ssid";
const char *psswd = "pass";

SupabaseRealtime realtime;

void HandleChanges(String result)
{
  return;
}

void setup()
{
  Serial.begin(9600);

  WiFi.begin(ssid, psswd);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("\nConnected!");

  realtime.begin(supabase_url, anon_key, HandleChanges);

  // Uncomment this line below, if you activate Presence Authorization
  // https://supabase.com/docs/guides/realtime/authorization#presence

  // realtime.login_email("email", "password");

  // You can also use

  // db.login_phone("phone", "password");

  // Parameter 1 : Your ESP Device Name, to track your device in the Supabase Presence
  realtime.sendPresence("device name");
  realtime.listen();
}

void loop()
{
  realtime.loop();
}