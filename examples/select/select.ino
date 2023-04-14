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
const char *ssid = "";
const char *psswd = "";

// Put Supabase account credentials here
const String email = "";
const String password = "";

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
  Serial.println("Connected!");

  // Beginning Supabase Connection
  db.begin(supabase_url, anon_key);

  // Logging in with your account you made in Supabase
  db.login_email(email, password);

  // Select query with filter and order, limiting the result is mandatory here
  String read = db.from("examples").select("*").eq("column", "value").order("column", "asc", true).limit(1).doSelect();
  Serial.println(read);

  // Reset Your Query before doing everything else
  db.urlQuery_reset();

  // Join operation with other table that connected via PK or FK
  String read = db.from("examples").select("*, other_table(other_table_column1, other_table_column2, another_table(*))").order("column", "asc", true).limit(1).doSelect();
  Serial.println(read);
  db.urlQuery_reset();
}

void loop()
{
  delay(10);
}