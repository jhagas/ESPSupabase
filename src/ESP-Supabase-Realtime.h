#ifndef ESP_Supabase_Realtime_h
#define ESP_Supabase_Realtime_h

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

class SupabaseRealtime
{
private:
  WebSocketsClient webSocket;

  String key;
  String hostname;

  String phone_or_email;
  String password;
  String data;
  String loginMethod;
  bool useAuth;
  int _login_process();
  unsigned int authTimeout = 0;
  unsigned long loginTime;
  String configAUTH;

  // Initial config
  const char *config = "{\"event\":\"phx_join\",\"topic\":\"realtime:ESP\",\"payload\":{\"config\":{\"postgres_changes\":[]}},\"ref\":\"sentRef\"}";
  JsonDocument postgresChanges;
  JsonDocument jsonRealtimeConfig;
  String configJSON;

  // Heartbeat
  unsigned int last_ms = millis();
  const char *jsonRealtimeHeartbeat = R"({"event": "heartbeat","topic": "phoenix","payload": {},"ref": "sentRef"})";
  const char *tokenConfig = R"({"topic": "realtime:ESP","event": "access_token","payload": {
    "access_token": ""
  },"ref": "sendRef"})";

  void processMessage(uint8_t *payload);
  void webSocketEvent(WStype_t type, uint8_t *payload, size_t length);

  std::function<void(String)> handler;

public:
  SupabaseRealtime() {}
  void begin(String hostname, String key, void (*func)(String));
  void addChangesListener(String table, String event, String schema, String filter);
  void listen();
  void loop();
  int login_email(String email_a, String password_a);
  int login_phone(String phone_a, String password_a);
};

#endif