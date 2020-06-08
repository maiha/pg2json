#define VERSION "0.2.0"

#include <pg_query.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file(char *path) {
  FILE *f = fopen(path, "rb");
  if ( f != NULL ) {
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, f);
    fclose(f);
    string[fsize] = 0;
    return string;
  } else {
    return NULL;
  }
}

int main(int argc, char *argv[]){
  if (argc == 2 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)) {
    fprintf(stdout, "pg2json version %s\n", VERSION);
    return 0;
  }

  if (argc != 2) {
    fprintf(stderr,"usage: pg2json <SQL_FILE>\n");
    return 1;
  }

  char *path = argv[1];
  char *data = read_file(path);

  if (data == NULL) {
    fprintf(stderr,"read error: %s\n", path);
    return 2;
  }

  PgQueryParseResult result = pg_query_parse(data);

  if (result.error) {
    fprintf(stderr,"error: %s at %d\n", result.error->message, result.error->cursorpos);
    pg_query_free_parse_result(result);
    return 2;
  } else {
    printf("%s\n", result.parse_tree);
    pg_query_free_parse_result(result);
    return 0;
  }
}
