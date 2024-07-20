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
  JsonDocument doc;
  deserializeJson(doc, result);

  // EXAMPLE of what you can do with the result
  String tableName = doc["table"];
  String event = doc["type"];
  String changes = doc["record"];

  Serial.print(tableName);
  Serial.print(" : ");
  Serial.println(event);
  Serial.println(changes);
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

  // Uncomment this line below, if you activate RLS in your Supabase Table
  // realtime.login_email("email", "password");
  
  // You can also use
  // db.login_phone("phone", "password");

  // Parameter 1 : Table name
  // Parameter 2 : Event type ("*" | "INSERT" | "UPDATE" | "DELETE")
  // Parameter 3 : Your Supabase Table Postgres Schema
  // Parameter 4 : Filter
  //   Please read : https://supabase.com/docs/guides/realtime/postgres-changes?queryGroups=language&language=js#available-filters
  //   empty string if you don't want to filter the result
  // EXAMPLE :
  realtime.addChangesListener("table1", "INSERT", "public", "id=eq.0");
  // You can add multiple table listeners
  realtime.addChangesListener("table2", "*", "public", "");

  realtime.listen();
}

void loop()
{
  realtime.loop();
}