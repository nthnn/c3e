CC = gcc
CFLAGS = -Wall -std=c17 -Os -static -I../include

SRCS = $(wildcard ../src/c3e/*.c) full_test.c
OBJS = $(SRCS:.c=.o)

TARGET = ../dist/full_test
LIBS = -lm

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p ../dist
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

.PHONY: all clean
