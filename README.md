# ESP32 Supabase

A Arduino Platform Library for connecting ESP32 to Supabase via REST API, including user authentication.
For now, it only supports the architectures espressif32 in PlatformIO targets.

For further information :
- [Supabase Documentation](https://supabase.com/docs)
- [PostgREST API Documentation](https://postgrest.org/en/stable/api.html)

## Examples

See all examples in `examples` folder

## Available Method

| Method                                           | Description                                                                 |
| ------------------------------------------------ | --------------------------------------------------------------------------- |
| `begin(String url_a, String key_a);`             | `url_a`  is a Supabase URL and `key_a` is supabase anon key. Returns `void` |
| `login_email(String email_a, String password_a)` | Returns http response code `int`                                            |
| `login_phone(String phone_a, String password_a)` | Returns http response code `int`                                            |
| `insert(String table, String json, bool upsert)` | Returns http response code `int`                                            |

To get the payload from `select` method. use `object.payload`

## To-do

- [x] Make Select API (GET Request), full with row limits (one by default)
- [ ] Implement Update with PATCH HTTPS Request
- [ ] Implement Delete with DELETE HTTPS Request
- [ ] Make order/sort query builder method to in Select
- [ ] Make filtering query builder method in Select, Update and Delete

