CC = g++
LD = g++
CFLAGS = -std=c++11 -O2
LDFLAGS = 
BUILD_DIR = ./build
SRC_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
MKDIR_P = mkdir -p

.PHONY: dir

all: dir $(BUILD_DIR)/main

dir: $(BUILD_DIR)

$(BUILD_DIR):
	$(MKDIR_P) $(BUILD_DIR)

$(BUILD_DIR)/main: $(OBJ_FILES)
	if [[ -f $(BUILD_DIR) ]]
	then
		mkdir -p $(BUILD_FIR)
	fi
	$(LD) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<