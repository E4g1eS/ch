CC = g++
CFLAGS = -g -Wall -pedantic
TARGET := app.out
BUILD := build
BIN := bin
SRC := src

SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS) | $(BIN)
	$(CC) -o $(addprefix $(BIN)/,$@) $(addprefix $(BUILD)/,$^)

%.o: %.cpp | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $(addprefix $(BUILD)/,$@)

$(BIN):
	mkdir $(BIN)

$(BUILD):
	mkdir $(BUILD)