CC=gcc

CFLAGS=-Wall -Wextra -Werror -fstack-protector-all -pedantic -std=c99
SANITY_FLAGS=-Wfloat-equal -Wshadow -Wpointer-arith

PREFIX ?= /usr

SOURCE=composer.c

OUTPUT=composer

ALL: $(OUTPUT)

debug: CFLAGS += -g -O0
debug: $(OUTPUT)

release: CFLAGS += -static -O3
release: $(OUTPUT)

$(OUTPUT): Makefile $(SOURCE)
	$(CC) $(CFLAGS) $(SANITY_FLAGS) $(SOURCE) -o $(OUTPUT)

install: $(OUTPUT)
	install -Dm755 "composer"	"$(PREFIX)/bin/composer"
	install -Dm755 "docker-compose" "$(PREFIX)/local/bin/docker-compose"
	install -Dm644 "LICENSE"    	"$(PREFIX)/share/licenses/composer/LICENSE"
	#install -Dm644 "composer.8" 	"$(PREFIX)/share/man/man8/composer.8.gz"

uninstall:
	rm -f "$(PREFIX)/bin/composer"
	rm -f "$(PREFIX)/local/bin/docker-compose"
	rm -f "$(PREFIX)/share/licenses/composer/LICENSE"
	#rm -f "$(PREFIX)/share/man/man8/composer.8.gz"
