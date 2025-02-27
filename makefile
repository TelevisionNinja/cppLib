CXX := g++
CPPFLAGS := -std=c++23 -Wall
TARGET_EXEC := test.exe

SRC_DIRS := ./src ./tests
BUILD_DIR := ./

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(OBJS) ./test.exe
