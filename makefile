CXX = g++
CXXFLAGS = -std=c++20 -Iinclude -Ilib -Wall -Wextra -O2

# Target executable name
TARGET = build/myst.exe

# Source files
SRC_FILES = src/main.cpp src/app.cpp src/editor.cpp src/status.cpp src/history.cpp src/file.cpp src/menu.cpp src/buttons.cpp src/settings.cpp src/scanner.cpp lib/ini.c

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