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

void setup()
{
  Serial.begin(9600);

  // Connecting to Wi-Fi
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

  // MAKE SURE YOU HAVE YOUR SUPABASE DATABASE SETUP FIRST, THIS LIBRARY CANNOT SET THE DATABASE FOR YOU
  // Basic select query
  String read = db.from("examples").select("*").doSelect();
  Serial.println(read);

  // Reset Your Query before doing everything else
  db.urlQuery_reset();

  // More advanced query, FOR DEMONSTRATION PURPOSES ONLY
  String read = db.from("examples").select("*").eq("column", "value").order("column", "asc", true).limit(1).doSelect();
  Serial.println(read);
  db.urlQuery_reset();

  // Join operation with other table that connected via PK or FK, FOR DEMONSTRATION PURPOSES ONLY
  String read = db.from("examples").select("*, other_table(other_table_column1, other_table_column2, another_table(*))").order("column", "asc", true).limit(1).doSelect();
  Serial.println(read);
  db.urlQuery_reset();
}

void loop()
{
  delay(1000);
}