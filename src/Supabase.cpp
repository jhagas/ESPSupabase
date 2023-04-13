#include "ESP32_Supabase.h"

WiFiClientSecure client;
HTTPClient https;

void Supabase::begin(String url_a, String key_a)
{
  client.setInsecure();
  url = url_a;
  key = key_a;
}

void Supabase::add_filter(String column, String condition, String value)
{

}

void Supabase::clear_filter()
{
  filter = "";
}

int Supabase::insert(String table, String json, bool upsert)
{
  int httpCode;
  if (https.begin(client, url + "/rest/v1/" + table))
  {
    https.addHeader("apikey", key);
    https.addHeader("Content-Type", "application/json");
    if (upsert)
    {
      https.addHeader("Authorization", "resolution=merge-duplicates");
    }
    if (useAuth)
    {
      unsigned long t_now = millis();
      if (t_now - loginTime >= 3500000)
      {
        login_process();
      }
      https.addHeader("Authorization", "Bearer " + USER_TOKEN);
    }
    httpCode = https.POST(json);
    https.end();
  }
  else
  {
    return -100;
  }
  return httpCode;
}

int Supabase::select(String table, String column, int limit)
{
  column.replace(",", "%2C");
  String url_select = url + "/rest/v1/" + table + "?select=" + column + "&limit=" + limit;
  https.begin(client, url_select);
  https.addHeader("apikey", key);
  https.addHeader("Content-Type", "application/json");

  if (useAuth)
  {
    unsigned long t_now = millis();
    if (t_now - loginTime >= 60 * 60 * 1000)
    {
      login_process();
    }
    https.addHeader("Authorization", "Bearer " + USER_TOKEN);
  }

  int httpCode = 0;
  while (httpCode <= 0)
  {
    httpCode = https.GET();
  }

  if (httpCode > 0)
  {
    payload = https.getString();
  }
  https.end();

  return httpCode;
}

String Supabase::getPayload()
{
  return payload;
}

int Supabase::login_email(String email_a, String password_a)
{
  useAuth = true;
  loginMethod = "email";
  phone_or_email = email_a;
  password = password_a;

  int httpCode = 0;
  while (httpCode <= 0)
  {
    httpCode = login_process();
  }
  return httpCode;
}

int Supabase::login_phone(String phone_a, String password_a)
{
  useAuth = true;
  loginMethod = "phone";
  phone_or_email = phone_a;
  password = password_a;

  int httpCode = 0;
  while (httpCode <= 0)
  {
    httpCode = login_process();
  }
  return httpCode;
}

int Supabase::login_process()
{
  int httpCode;
  StaticJsonDocument<1024> doc;
  Serial.println("Beginning to login..");

  if (https.begin(client, url + "/auth/v1/token?grant_type=password"))
  {
    https.addHeader("apikey", key);
    https.addHeader("Content-Type", "application/json");

    String query = "{\"" + loginMethod + "\": \"" + phone_or_email + "\", \"password\": \"" + password + "\"}";
    httpCode = https.POST(query);

    if (httpCode > 0)
    {
      String payload = https.getString();
      deserializeJson(doc, payload);
      USER_TOKEN = doc["access_token"].as<String>();
      Serial.println("Login Success");
      Serial.println(USER_TOKEN);
    }
    else
    {
      Serial.println(phone_or_email);
      Serial.println(password);

      Serial.print("Login Failed : ");
      Serial.println(httpCode);
    }

    https.end();
    loginTime = millis();
  }
  else
  {
    return -100;
  }
  return httpCode;
}