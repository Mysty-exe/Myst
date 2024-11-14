CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -O2

# Target executable name
TARGET = myst.exe

# Source files
SRC_FILES = src/main.cpp src/editor.cpp src/cmd.cpp src/file.cpp

all: $(TARGET)

# Build target
$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET) -lncurses -DNCURSES_STATIC

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean up generated files
clean:
	rm -f $(TARGET)