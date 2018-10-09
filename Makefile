CFLAGS = -O2 -lX11 -lXss -Wall -Wextra -pedantic -std=c11

xss-inhibit: xss-inhibit.c

clean:
	rm -f xss-inhibit xss-inhibit.o

.phony: clean
