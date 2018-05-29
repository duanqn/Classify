CC = g++
LD = g++
CFLAGS = -std=c++11 -O2
LDFLAGS = 

$(info HELLO2)

ifeq ($(OS),Windows_NT)

$(info Hello Windows)
BUILD_DIR := .\build
MKDIR_P := md
MKDIR_CMD := if not exist $(BUILD_DIR) $(MKDIR_P) $(BUILD_DIR)
RM_Q := del /q
FixPath = $(subst /,\,$1)
SEP = $(call FixPath,/)
else

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)

$(info Hello Linux)
BUILD_DIR := ./build
MKDIR_P := mkdir -p
MKDIR_CMD := $(MKDIR_P) $(BUILD_DIR)
RM_Q := rm -f
SEP := /

else
	$(error OS not supported)
endif

endif

$(info $$BUILD_DIR is [$(BUILD_DIR)])
$(info $$MKDIR_P is [$(MKDIR_P)])

SRC_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp,$(BUILD_DIR)$(SEP)%.o,$(SRC_FILES))
EXEC_NAME = main

.PHONY: dir

all: dir $(BUILD_DIR)$(SEP)$(EXEC_NAME)

dir: $(BUILD_DIR)

$(BUILD_DIR):
	$(MKDIR_CMD)

$(BUILD_DIR)$(SEP)$(EXEC_NAME): $(OBJ_FILES)
	$(LD) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)$(SEP)%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM_Q) $(BUILD_DIR)$(SEP)*.o
	$(RM_Q) $(BUILD_DIR)$(SEP)$(EXEC_NAME)
