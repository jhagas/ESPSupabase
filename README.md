# ESPSupabase

Simple library to connect ESP32/8266 to Supabase via REST API and WebSockets (for Realtime), including user authentication

## Installation

This library is available at Arduino's Library Manager, as well as PlatformIO Library Manager

- [Arduino Library Manager Guide](http://arduino.cc/en/guide/libraries)

## Examples

See all examples in `examples` folder

## Supabase PostgREST API (`#include <ESPSupabase.h>`)

### Directly Makes Connection to Database

| Method                                                                                     | Description                                                                                                                                                                                                                                                                                                                                                                                                               |
| ------------------------------------------------------------------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `login_email(String email_a, String password_a)`                                           | **(OPTIONAL, ONLY IF USING RLS)**, Returns http response code `int`                                                                                                                                                                                                                                                                                                                                                       |
| `login_phone(String phone_a, String password_a)`                                           | **(OPTIONAL, ONLY IF USING RLS)**, Returns http response code `int`                                                                                                                                                                                                                                                                                                                                                       |
| `begin(String url_a, String key_a);`                                                       | `url_a` is a Supabase URL and `key_a` is supabase anon key. Returns `void`                                                                                                                                                                                                                                                                                                                                                |
| `insert(String table, String json, bool upsert)`                                           | Returns http response code `int`. If you want to do upsert, set thirt parameter to `true`                                                                                                                                                                                                                                                                                                                                 |
| `upload(String bucket, String filename, String mime_type, Stream *stream, uint32_t size)`  | `bucket` is the name of the Supabase Storage bucket without any `/`. `filename` is the name to upload the file with, should have extension but no `/`. Takes a `Stream*` pointer as an argument, this can be Arduino SD `File*` or SPIFFS `File*` types. Returns http response code `int`. `mime_type` is for eg. `image/jpg`. `size` is the total size in bytes of the file to upload. Returns http response code `int`. |
| `upload(String bucket, String filename, String mime_type, uint8_t *buffer, uint32_t size)` | Same function as the previous one but takes a `uint8_t*` buffer instead of a `Stream*`. Can be used for files stored in RAM.                                                                                                                                                                                                                                                                                              |
| `.doSelect()`                                                                              | Called at the end of select query chain, see [Examples](#examples). Returns http response payload (your data) from Supabase `String`                                                                                                                                                                                                                                                                                      |
| `.doUpdate(String json)`                                                                   | Called at the end of update query chain, see [Examples](#examples). Returns http response code from Supabase `int`                                                                                                                                                                                                                                                                                                        |

### Building The Queries

When building the queries, you can chain the method like in this example.

> Remember in `.select()` method, you have to put `.limit()`, so your microcontroller's memory don't get overflowed

```arduino
String read = db.from("table").select("*").eq("column", "value").order("column", "asc", true).limit(1).doSelect();
```

| Methods                  | Description                                                                             |
| ------------------------ | --------------------------------------------------------------------------------------- |
| `.from(String table);`   | Specify which table you want to query. It will append `?table_name` in Request URL      |
| `.select(String colls);` | Specify that you want to do select query. It will append `&select=colls` in Request URL |
| `.update(String table);` | Specify that you want to do update query. It will append `&update` in Request URL       |

#### Horizontal Filtering (comparison) Operator

| Methods                            | Description                                                                                                |
| ---------------------------------- | ---------------------------------------------------------------------------------------------------------- |
| `.eq(String colls, String value)`  | Equals                                                                                                     |
| `.gt(String colls, String value)`  | Greater than                                                                                               |
| `.gte(String colls, String value)` | Greater than or equal                                                                                      |
| `.lt(String colls, String value)`  | Less than                                                                                                  |
| `.lte(String colls, String value)` | Less than or equal                                                                                         |
| `.neq(String colls, String value)` | Not equal                                                                                                  |
| `.in(String colls, String value)`  | One of a list of values, e.g. `1,2,3` – also supports commas in quoted strings like `"hi,there","yes,you"` |
| `.is(String colls, String value)`  | Checking for exact equality `<null, true, false, unknown>`                                                 |
| `.cs(String colls, String value)`  | Contains e.g. `example, new`                                                                               |
| `.cd(String colls, String value)`  | Contained in e.g. `1, 2, 3`                                                                                |
| `.ov(String colls, String value)`  | Overlap (have points in common), e.g. `2017-01-01, 2017-06-30`                                             |
| `.sl(String colls, String value)`  | Strictly left of, e.g. `1,10`                                                                              |
| `.sr(String colls, String value)`  | Strictly right of                                                                                          |
| `.nxr(String colls, String value)` | Does not extend to the right of, e.g. `1,10`                                                               |
| `.nxl(String colls, String value)` | Does not extend to the left of                                                                             |
| `.adj(String colls, String value)` | Is adjacent to, e.g. `1,10`                                                                                |

#### Ordering, Limiting or Offseting the Result

| Methods                                       | Description                                                                                                                                                                                 |
| --------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `.order(String coll, String by, bool nulls);` | This reorders the response rows. `coll` parameter is column name, `by` parameter is either `asc` or `desc`. The last parameter specifies the position of nulls, `nullsfirst` or `nullslast` |
| `.limit(unsigned int by);`                    | Limit the amount of response rows. THIS IS MANDATORY FOR SELECT METHOD!!!                                                                                                                   |
| `.offset(int by);`                            | Request response rows with offset is with its parameters.                                                                                                                                   |

#### Getting the Query URL (for debugging)

```arduino
db.urlQuery_reset();
```

#### Reset the Query URL

This method calls in mandatory, must be called after one opetation (let's say `doSelect()`, or `doUpdate()`) before doing anything else.

```arduino
db.urlQuery_reset();
```

## Supabase Realtime API (`#include <ESPSupabaseRealtime.h>`)

To use Realtime (Postgres Changes), please see the `examples/realtime-postgresChanges` and `examples/realtime-presence` folder. The broadcast feature are not implemented yet.

| Method                                                                         | Description                                                                                                         |
| ------------------------------------------------------------------------------ | ------------------------------------------------------------------------------------------------------------------- |
| `login_email(String email_a, String password_a)`                               | **(OPTIONAL, ONLY IF USING RLS)**, Returns http response code `int`                                                 |
| `login_phone(String phone_a, String password_a)`                               | **(OPTIONAL, ONLY IF USING RLS)**, Returns http response code `int`                                                 |
| `begin(String hostname, String key, void (*func)(String))`                     | Setup the Realtime connection with Supabase URL and Anon key, also put the handle function for the incoming message |
| `sendPresence(String device_name)`                                             | Track the presence (online status) of your ESP device. Track presence on realtime channel "ESP"                     |
| `addChangesListener(String table, String event, String schema, String filter)` | Listen to Postgres Database changes, you can add multiple of this if you want to track changes form multiple tables |
| `listen()`                                                                     | Start websocket connection                                                                                          |
| `loop()`                                                                       | Put this in your loop() function, this will handle the websocket connection and send heartbeats to Supabase         |

## To-do (sorted by priority)

- [x] Implement Postgres Changes in [Supabase Realtime](https://supabase.com/docs/guides/realtime)
- [x] Implement Presence in [Supabase Realtime](https://supabase.com/docs/guides/realtime)
- [ ] Implement Broadcast in [Supabase Realtime](https://supabase.com/docs/guides/realtime)

## Project Using This Library

- [Monitoring dan Data Logging Sensor dengan Platform Database Supabase dan Aplikasi Web React.js](https://www.jhagas.space/posts/monitoring-data-logging-sensor-iot-supabase)

## References:

- [Supabase Documentation](https://supabase.com/docs)
- [Official Javascript Library](https://supabase.com/docs/reference/javascript/introduction)
- [PostgREST API Documentation](https://postgrest.org/en/stable/api.html)
