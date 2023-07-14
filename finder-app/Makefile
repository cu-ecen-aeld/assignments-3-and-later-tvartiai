
CROSS_COMPILE=aarch64-none-linux-gnu-
CC := $(CROSS_COMPILE)gcc

APPOBJS := writer.o

.PHONY: clean

INCLUDES :=

CFLAGS := -g -Wall -Wextra -pedantic -std=gnu99 $(INCLUDES)

LDFLAGS :=

all: writer

writer: $(APPOBJS)
	$(CC) -o writer  $(APPOBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -f writer *.o *.lob
