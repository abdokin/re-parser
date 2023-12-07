CXX = g++
CXXFLAGS = -std=c++11 -Wall
BUILD_DIR = build

TARGET = $(BUILD_DIR)/re
SRCS = main.cpp 
OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: clean run

run: $(TARGET)
	$(TARGET) "(1|0)"
	$(TARGET) "(1|0)*"

