# Define compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Define the target executable
TARGET = restaurant

# Define source files
SRC = main.cpp Restaurant.cpp

# Define object files
OBJ = $(SRC:.cpp=.o)

# Rule to create the target executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Rule to create object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean target for removing compiled files
clean:
	rm -f $(TARGET) $(OBJ)

# Declare phony targets
.PHONY: clean
