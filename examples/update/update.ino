#include <Arduino.h>
#include <ESPSupabase.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

Supabase db;

// Put your supabase URL and Anon key here...
String supabase_url = "https://yourproject.supabase.co";
String anon_key = "anonkey";

// put your WiFi credentials (SSID and Password) here
const char *ssid = "ssid";
const char *psswd = "pass";

// Put your target table here
String table = "tablename";

// Put your JSON that you want to insert rows
// You can also use library like ArduinoJson generate this
String JSON = "";

bool upsert = false;

void setup()
{
  Serial.begin(9600);

  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, psswd);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("\nConnected!");

  // Beginning Supabase Connection
  db.begin(supabase_url, anon_key);

  // Uncomment this line below, if you activate RLS in your Supabase Table
  // db.login_email("email", "password");
  
  // You can also use
  // db.login_phone("phone", "password");

  int code = db.update("table").eq("column", "value").doUpdate(JSON);
  Serial.println(code);
  db.urlQuery_reset();
}

void loop()
{
  delay(1000);
}