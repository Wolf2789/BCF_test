TARGET = persons

SRC_DIR = src/
SRC = $(SRC_DIR)main.cpp

CFLAGS = -I/usr/local/include -I./$(SRC_DIR)
LDFLAGS = -L/usr/local/lib -lyaml-cpp

CC = g++

build: $(TARGET)

all: clean build run

$(TARGET): $(SRC)
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

clean:
ifneq (,$(wildcard ./$(TARGET)))
	rm $(TARGET)
endif

run:
	./$(TARGET)
