CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -O2
SRC=$(wildcard backend/*.c)
TARGET=student_system
all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
clean:
	rm -f $(TARGET)
