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

.PHONY: test
test: $(patsubst %,run/%,$(wildcard test/*/sql))

run/%: pg2json
	@mkdir -p tmp
	@printf "%-15s : " "$(*D)"
	@if ./$< $* > tmp/json && cmp $(*D)/json tmp/json; then \
	  printf "\033[1;32mOK\033[0m\n"; \
	else \
	  printf "\033[1;31mNG\033[0m\n"; \
	  diff $(*D)/json tmp/json; \
	fi
