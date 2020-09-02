TARGET = cstring

SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)

CC = gcc
CPPFLAGS += -Iinclude -pedantic
CFLAGS += -Wall -std=c99 -O3
LDFLAGS += -Llib
#LDLIBS += 

MOVE = mv
MKDIR_P = mkdir -p

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

run:
	./$(TARGET)

clean:
	$(RM) $(OBJ) $(TARGET)
