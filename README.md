# ESP32 Supabase

An Arduino Platform Library for connecting ESP32 to Supabase via REST API, including user authentication.
For now, it only supports the architectures espressif32 in PlatformIO targets.

This library is build for microcontroller, 
so I think it is appropriate to not include as much user management features, filters or modifier as in [Official Javascript Library](https://supabase.com/docs/reference/javascript/introduction).

For further information :
- [Supabase Documentation](https://supabase.com/docs)
- [PostgREST API Documentation](https://postgrest.org/en/stable/api.html)

## Table of Contents

- [ESP32 Supabase](#esp32-supabase)
  - [Table of Contents](#table-of-contents)
  - [Using This Library](#using-this-library)
  - [Examples](#examples)
  - [Available Method](#available-method)
    - [Directly Makes Connection to Database](#directly-makes-connection-to-database)
    - [Building The Queries](#building-the-queries)
      - [Horizontal Filtering (comparison) Operator](#horizontal-filtering-comparison-operator)
      - [Ordering, Limiting or Offseting the Result](#ordering-limiting-or-offseting-the-result)
      - [Getting the Query URL (for debugging)](#getting-the-query-url-for-debugging)
      - [Reset the Query URL](#reset-the-query-url)
  - [To-do (sorted by priority)](#to-do-sorted-by-priority)

## Using This Library

This library is available at Arduino's Library Manager, as well as PlatformIO Library Manager
- [Arduino Library Manager Guide](http://arduino.cc/en/guide/libraries)

## Examples

See all examples in `examples` folder

## Available Method

### Directly Makes Connection to Database

| Method                                           | Description                                                                                                                          |
| ------------------------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------ |
| `begin(String url_a, String key_a);`             | `url_a`  is a Supabase URL and `key_a` is supabase anon key. Returns `void`                                                          |
| `login_email(String email_a, String password_a)` | Returns http response code `int`                                                                                                     |
| `login_phone(String phone_a, String password_a)` | Returns http response code `int`                                                                                                     |
| `insert(String table, String json, bool upsert)` | Returns http response code `int`. If you want to do upsert, set thirt parameter to `true`                                            |
| `.doSelect()`                                    | Called at the end of select query chain, see [Examples](#examples). Returns http response payload (your data) from Supabase `String` |
| `.doUpdate(String json)`                         | Called at the end of update query chain, see [Examples](#examples). Returns http response code from Supabase `int`                   |

### Building The Queries

When building the queries, you can chaining the method like this example.

> Remember in `.select()` method, it is mandatory to put some low amount of `.limit()`, so you can avoid your microcontroller's memory get overflowed

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

## To-do (sorted by priority)

- [x] Make Select API (GET Request), full with row limits (one by default)
- [x] Make filtering query builder method in Select and update
- [x] Make order/sort query builder method to in Select
- [x] Implement Update with PATCH HTTPS Request
- [x] Port to ESP8266
- [ ] Implement calling RPC function with HTTPS Request
- [ ] Implement several methods to implement [Supabase Realtime](https://supabase.com/docs/guides/realtime)

Better documentation is always a welcoming change 😄️😄️
