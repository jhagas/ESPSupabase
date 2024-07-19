#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP_Supabase_Realtime.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

SupabaseRealtime realtime;

void DevicesTableHandler(String result)
{
  JsonDocument doc;
  deserializeJson(doc, result);

  // Example of what you can do with the result
  String state = doc["state"];
  Serial.println(state);
}

void setup()
{
  Serial.begin(9600);

  WiFi.begin("ssid", "password");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  realtime.begin("https://project.supabase.co", "apikey");
  realtime.login_email("email", "password"); // Only if you activate RLS in your Supabase Postgres Table

  // Parameter 1 : Table name
  // Parameter 2 : Event type ("*" | "INSERT" | "UPDATE" | "DELETE")
  // Parameter 3 : Filter
  //   Please read : https://supabase.com/docs/guides/realtime/postgres-changes?queryGroups=language&language=js#available-filters
  //   empty string if you don't want to filter the result
  // Parameter 4 : Callback function, how to handle the result (message)
  realtime.listen("table", "*", "", DevicesTableHandler);
}

void loop()
{
  realtime.loop();
}