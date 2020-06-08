all: pg2json

pg2json: pg2json.c libpg_query/libpg_query.a
	gcc -I./libpg_query -o $@ -static -g $^

clean:
	rm -f pg2json

distclean: clean
	rm -rf libpg_query

libpg_query/libpg_query.a:
	@[ -d $(@D) ] || git clone -b 10-latest --depth 2 https://github.com/lfittl/libpg_query.git
	make build -C libpg_query

test: pg2json
	./$<
