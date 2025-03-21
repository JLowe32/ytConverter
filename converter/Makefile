# Name of the output file
TARGET = yt

# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -std=c++17 -Wall -I./nlohmann

# Libraries to link with
LDFLAGS = -lcurl

# Source Files
SRC = yt.cpp

# Build Target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up the build files
clean:
	rm -f $(TARGET)
