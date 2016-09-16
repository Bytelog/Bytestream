OUT = game
CC = gcc
CFLAGS = -O2 -pipe -Wall -o $(OUT)
LDFLAGS =

src = $(wildcard common/*.c) $(wildcard client/*.c)
obj = $(src:.c=.o)

all: $(obj)
	$(CC) $(CFLAGS) $^ $(LDFLAGS)

clean:
	rm -f $(obj) $(OUT)