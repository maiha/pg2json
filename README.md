# pg2json [![Build Status](https://travis-ci.org/maiha/pg2json.svg?branch=master)](https://travis-ci.org/maiha/pg2json)

Extract SQL ASTs from PostgreSQL queries as JSON text.
* parser: https://github.com/lfittl/libpg_query

## Usage

Execute the command with the postgresql SQL file as an argument.

```console
$ pg_dump -t users -s > users.sql

$ pg2json users.sql | jq .
...
  {
    "RawStmt": {
      "stmt": {
        "CreateStmt": {
          "relation": {
...

$ pg2json users.sql | jq -r -c '.[].RawStmt.stmt.CreateStmt | select (.!=null).tableElts | .[].ColumnDef | [.colname, .typeName.TypeName.names[1].String.str] | @tsv'
id      int8
login   varchar
name    varchar
...
```

## Development

```console
$ make
```

## Contributing

1. Fork it (<https://github.com/maiha/pg2json/fork>)
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create a new Pull Request

## Contributors

- [maiha](https://github.com/maiha) - creator and maintainer
