# Define the compiler
CXX = g++

# Define the compiler flags
CXXFLAGS = -std=c++11 -I src/include -I /opt/homebrew/Cellar/sdl2/2.30.3/include -I /opt/homebrew/Cellar/sdl2_image/2.8.2_1/include -I game

# Define the linker flags
LDFLAGS = -L/opt/homebrew/Cellar/sdl2/2.30.3/lib -L/opt/homebrew/Cellar/sdl2_image/2.8.2_1/lib -lSDL2 -lSDL2_image -Wl,-rpath,/opt/homebrew/Cellar/sdl2/2.30.3/lib -Wl,-rpath,/opt/homebrew/Cellar/sdl2_image/2.8.2_1/lib

# Define the source files
SRCS = main.cpp game/vue/Grid.cpp game/logic_game/cpp_files/Tower.cpp game/logic_game/cpp_files/Enemy.cpp game/vue/Tile.cpp

# Define the object files
OBJS = $(SRCS:.cpp=.o)

# Define the executable
TARGET = main	

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile the object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)
