BUILD_DIR_NAME = build
EXEC_NAME_PREFIX = classify

CC = g++
LD = g++
CFLAGS = -std=c++11 -O2
LDFLAGS = 

$(info Building initiated...)

ifeq ($(OS),Windows_NT)

$(info Hello Windows)
BUILD_DIR := .\$(BUILD_DIR_NAME)
MKDIR_P := md
MKDIR_CMD := if not exist $(BUILD_DIR) $(MKDIR_P) $(BUILD_DIR)
RM_Q := del /q
EXEC_NAME = $(EXEC_NAME_PREFIX).exe
FixPath = $(subst /,\,$1)
SEP = $(call FixPath,/)
else

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)

$(info Hello Linux)
BUILD_DIR := ./$(BUILD_DIR_NAME)
MKDIR_P := mkdir -p
MKDIR_CMD := $(MKDIR_P) $(BUILD_DIR)
RM_Q := rm -f
EXEC_NAME = $(EXEC_NAME_PREFIX)
SEP := /

else
	$(error OS not supported)
endif

endif

$(info $$BUILD_DIR is [$(BUILD_DIR)])
$(info $$MKDIR_P is [$(MKDIR_P)])

SRC_FILES_CPP := $(wildcard *.cpp)
OBJ_FILES_CPP := $(patsubst %.cpp,$(BUILD_DIR)$(SEP)%.oxx,$(SRC_FILES_CPP))
SRC_FILES_C := $(wildcard *.c)
OBJ_FILES_C := $(patsubst %.c,$(BUILD_DIR)$(SEP)%.o,$(SRC_FILES_C))
HEADER_FILES := $(wildcard *.h)
HEADER_FILES_TEMPLATE := $(wildcard *.hpp)

OBJ_FILES := $(OBJ_FILES_C) $(OBJ_FILES_CPP)
$(info $$OBJ_FILES is [$(OBJ_FILES)])


.PHONY: dir

all: dir $(BUILD_DIR)$(SEP)$(EXEC_NAME)

dir: $(BUILD_DIR)

$(BUILD_DIR):
	$(MKDIR_CMD)

$(BUILD_DIR)$(SEP)$(EXEC_NAME): $(OBJ_FILES)
	$(LD) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)$(SEP)%.oxx: %.cpp $(HEADER_FILES) $(HEADER_FILES_TEMPLATE)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)$(SEP)%.o: %.c $(HEADER_FILES) $(HEADER_FILES_TEMPLATE)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM_Q) $(BUILD_DIR)$(SEP)*
