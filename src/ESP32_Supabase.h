#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

class Supabase
{
public:
  String url;
  String key;
  String USER_TOKEN;

  void begin(String url_a, String key_a);

  int login_email(String email_a, String password_a);
  int login_phone(String phone_a, String password_a);

  int insert(String table, String json, bool upsert);
  int select(String table, String column, int limit = 1);
  void add_filter(String column, String condition, String value);
  void clear_filter();
  void sort();
  String getPayload();

private:
  bool useAuth;
  unsigned long loginTime;
  String phone_or_email;
  String password;
  String payload;
  String loginMethod;
  String filter;

  int login_process();
};