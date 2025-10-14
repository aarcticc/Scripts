CC ?= gcc
CFLAGS ?= -std=c99 -Wall -Wextra -O2
LDLIBS ?= -lGL -lGLU -lglut

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
TARGET ?= app

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)