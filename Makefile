CXX = g++
CXXFLAGS = -std=c++17 -Wall -c -pipe -O2
PROJ_NAME = main

OBJS_DIR := obj
SRCS_DIR := src
INC_DIR := include
SRCS_FILES := $(SRCS_DIR)/main.cpp $(SRCS_DIR)/dynamic_bitset.cpp \
$(SRCS_DIR)/tests.cpp $(SRCS_DIR)/consoleUtils.cpp
OBJS_FILES = $(patsubst $(SRCS_DIR)/%.cpp,$(OBJS_DIR)/%.o,$(SRCS_FILES))

.PHONY: all clean test

all: main

main: $(OBJS_FILES)
	$(CXX) $(OBJS_FILES) $(LDFLAGS) -o $@


$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) $< -o $@

test:
	@echo "SRC FILES = '$(SRCS_FILES)'"
	@echo "OBJ FILES = '$(OBJS_FILES)'"

clean:
	rm -f $(OBJS_DIR)/*.o
	rm -f main
