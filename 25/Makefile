SRCS = $(wildcard e*.c)

CFLAGS = -g -Wall -std=c99 -pedantic
PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<
