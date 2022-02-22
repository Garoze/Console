# _*_ MakeFile _*_

CC     := g++
CFLAGS := -w -g -Wall

SRC    := src
BIN    := bin
BUILD  := build

SOURCE  := $(shell find $(SRC/**) -type f -regex ".*\.cpp")
HEADERS := $(shell find $(SRC/include/**) -type f -regex ".*\.hpp")
OBJECT  := $(patsubst %, $(BUILD)/%, $(notdir $(SOURCE:.cpp=.cpp.o)))

.PHONY: default config all clean

TARGET := console

all: $(TARGET)

$(BUILD)/%.cpp.o: $(SRC)/%.cpp $(HEADERS)
	@echo "Building: $@"; $(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(TARGET): $(OBJECT)
	@echo "Linking: $@"; $(CC) $^ -o $(TARGET) $(LIB)

config: $(eval SHELL:=/usr/bin/env bash)
	@echo $(shell ./configure.sh)

clean:
	@echo "Cleaning $(TARGET), $(BUILD)"; $(RM) -rf $(OBJECT) $(TARGET)

