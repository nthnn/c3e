CC = gcc
CFLAGS = -Os -static -I../src

SRCS = $(wildcard ../src/c3e/*.cpp) full_test.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = ../dist/full_test
LIBS = -lm

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p ../dist
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

.PHONY: all clean
