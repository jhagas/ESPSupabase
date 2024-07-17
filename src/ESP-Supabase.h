#ifndef ESP_Supabase_h
#define ESP_Supabase_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <WebSocketsClient.h>

#if defined(ESP8266)
#include <ESP8266HTTPClient.h>
#elif defined(ESP32)
#include <HTTPClient.h>
#else
#error "This library is not supported for your board! ESP32 and ESP8266"
#endif

struct SupabaseQuery
{
  String key;
  String comparator;
  String value;
};

class Supabase
{
private:
  String hostname;
  String key;
  String USER_TOKEN;

  String url_query;

  WiFiClientSecure client;
  HTTPClient https;

  bool useAuth;
  unsigned long loginTime;
  String phone_or_email;
  String password;
  String data;
  String loginMethod;
  String filter;

  unsigned int authTimeout = 0;

  void _check_last_string();
  int _login_process();

public:
  SupabaseRealtime realtime;
  Supabase() {}
  ~Supabase() {}

  void setupRealtime(String hostname_a, String key_a);
  void begin(String hostname_a, String key_a);
  String getQuery();
  // query reset
  void urlQuery_reset();

  // membuat Query Builder
  Supabase &from(String table);
  int insert(String table, String json, bool upsert);
  Supabase &select(String colls);
  Supabase &update(String table);
  int upload(String bucket, String filename, String mime_type, Stream *stream, uint32_t size);
  int upload(String bucket, String filename, String mime_type, uint8_t *buffer, uint32_t size);

  // Comparison Operator
  Supabase &eq(String coll, String conditions);
  Supabase &gt(String coll, String conditions);
  Supabase &gte(String coll, String conditions);
  Supabase &lt(String coll, String conditions);
  Supabase &lte(String coll, String conditions);
  Supabase &neq(String coll, String conditions);
  Supabase &in(String coll, String conditions);
  Supabase &is(String coll, String conditions);
  Supabase &cs(String coll, String conditions);
  Supabase &cd(String coll, String conditions);
  Supabase &ov(String coll, String conditions);
  Supabase &sl(String coll, String conditions);
  Supabase &sr(String coll, String conditions);
  Supabase &nxr(String coll, String conditions);
  Supabase &nxl(String coll, String conditions);
  Supabase &adj(String coll, String conditions);

  // Ordering
  Supabase &order(String coll, String by, bool nulls);
  Supabase &limit(unsigned int by);
  Supabase &offset(int by);

  // do select. execute this after building your query
  String doSelect();

  // do update. execute this after querying your update
  int doUpdate(String json);

  int login_email(String email_a, String password_a);
  int login_phone(String phone_a, String password_a);

  String rpc(String func_name, String json_param = "");
};

class SupabaseRealtimeTableEntry
{
private:
  WiFiClientSecure client;
  WebSocketsClient webSocket;
  std::function<void(JsonDocument)> handleEvent; // Changed to std::function
  String jsonRealtimeConfig;
  String key;
  String hostname;

public:
  void setupHandler(std::function<void(JsonDocument)> handler);

  SupabaseRealtimeTableEntry(String key, String hostname)
  {
    hostname.replace("https://", "");
    this->key = key;
    this->hostname = hostname;
  }

  void setupListener(String table, String event, SupabaseQuery queries[], int numqueries);
  void processMessage(uint8_t *payload, size_t length, JsonDocument result);
  void webSocketEvent(WStype_t type, uint8_t *payload, size_t length);
  void loop();
};

class SupabaseRealtime
{
private:
  String hostname;
  String key;
  // Define an array to store SUPABASERealtimeTableEntry objects
  std::vector<SupabaseRealtimeTableEntry> entries;

public:
  SupabaseRealtime(){}
  void setupConnection(String hostname, String key);
  // Function to add a SUPABASERealtimeTableEntry object to the array
  void addEntry(String table, String event, SupabaseQuery queries[], int numqueries, std::function<void(JsonDocument)> handler);\
  void loop();
};

#endif