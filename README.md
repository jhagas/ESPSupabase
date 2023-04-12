# ESP32 Supabase

A Arduino Platform Library for connecting ESP32 to Supabase via REST API, including user authentication.
For now, it only supports the architectures espressif32 in PlatformIO targets.

This library is build for microcontroller, 
so I think it is appropriate to not include as much user management features, filters or modifier as in [Official Javascript Library](https://supabase.com/docs/reference/javascript/introduction).

For further information :
- [Supabase Documentation](https://supabase.com/docs)
- [PostgREST API Documentation](https://postgrest.org/en/stable/api.html)

## Examples

See all examples in `examples` folder

## Available Method

| Method                                                | Description                                                                 |
| ----------------------------------------------------- | --------------------------------------------------------------------------- |
| `begin(String url_a, String key_a);`                  | `url_a`  is a Supabase URL and `key_a` is supabase anon key. Returns `void` |
| `login_email(String email_a, String password_a)`      | Returns http response code `int`                                            |
| `login_phone(String phone_a, String password_a)`      | Returns http response code `int`                                            |
| `insert(String table, String json, bool upsert)`      | Returns http response code `int`                                            |
| `get_payload(String table, String json, bool upsert)` | Returns payload from select and rpc method `String`                         |

### Horizontal Filtering Operators

| Abbreviation | Meaning                                                                                                                                                                   |
| ------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| eq           | equals                                                                                                                                                                    |
| gt           | greater than                                                                                                                                                              |
| gte          | greater than or equal                                                                                                                                                     |
| lt           | less than                                                                                                                                                                 |
| lte          | less than or equal                                                                                                                                                        |
| neq          | not equal                                                                                                                                                                 |
| in           | one of a list of values, e.g. `?a=in.(1,2,3)` – also supports commas in quoted strings like `?a=in.("hi,there","yes,you")`                                                |
| is           | checking for exact equality (null,true,false,unknown)                                                                                                                     |
| cs           | contains e.g. `?tags=cs.{example, new}`                                                                                                                                   |
| cd           | contained in e.g. `?values=cd.{1,2,3}`                                                                                                                                    |
| ov           | overlap (have points in common), e.g. `?period=ov.[2017-01-01,2017-06-30]` – also supports array types, use curly braces instead of square brackets e.g.  `?arr=ov.{1,3}` |
| sl           | strictly left of, e.g. `?range=sl.(1,10)`                                                                                                                                 |
| sr           | strictly right of                                                                                                                                                         |
| nxr          | does not extend to the right of, e.g. `?range=nxr.(1,10)`                                                                                                                 |
| nxl          | does not extend to the left of                                                                                                                                            |
| adj          | is adjacent to, e.g. `?range=adj.(1,10)`                                                                                                                                  |
| not          | negates another operator, see [Logical operators](#logical-operators)                                                             |
| or           | logical OR, see [Logical operators](#logical-operators)                                                                           |
| and          | logical AND, see [Logical operators](#logical-operators)                                                                          |

#### Logical operators

Multiple conditions on columns are evaluated using AND by default, but you can combine them using OR with the or operator. For example, to return people under 18 or over 21:

```curl
curl "http://localhost:3000/people?or=(age.lt.18,age.gt.21)"
```

To negate any operator, you can prefix it with not like `?a=not.eq.2` or `?not.and=(a.gte.0,a.lte.100)`.

You can also apply complex logic to the conditions:

```curl
curl "http://localhost:3000/people?grade=gte.90&student=is.true&or=(age.eq.14,not.and(age.gte.11,age.lte.17))"
```

## To-do (sorted by priority)

- [x] Make Select API (GET Request), full with row limits (one by default)
- [ ] Make filtering query builder method in Select, Update and Delete
- [ ] Make order/sort query builder method to in Select
- [ ] Implement Update with PATCH HTTPS Request
- [ ] Implement Delete with DELETE HTTPS Request
- [ ] Implement calling RPC function with HTTPS Request
- [ ] Implement several methods to implement [Supabase Realtime](https://supabase.com/docs/guides/realtime)

