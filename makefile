CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Ilib -Wall -Wextra -O2

# Target executable name
TARGET = build/myst.exe

# Source files
SRC_FILES = src/main.cpp src/editor.cpp src/cmd.cpp src/file.cpp lib/ini.c

all: build_dir $(TARGET)

# Build target
$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET) -lncurses

# Create build directory if it doesn't exist
build_dir:
	mkdir -p build

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean up generated files
clean:
	rm -f $(TARGET)