CXX := g++
CXXFLAGS := -I src/include -I /usr/include/SDL2 -I game
LDFLAGS := -L src/lib
LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image

# Directories
SRC_DIR := game
LOGIC_DIR := $(SRC_DIR)/logic_game/cpp_files
VUE_DIR := $(SRC_DIR)/vue

# Source files
SRC_FILES := main.cpp \
             $(VUE_DIR)/Grid.cpp \
             $(LOGIC_DIR)/Tower.cpp \
             $(LOGIC_DIR)/Enemy.cpp \
			 $(VUE_DIR)/Tile.cpp \

# Object files
OBJ_FILES := $(SRC_FILES:.cpp=.o)

# Target executable
TARGET := sdl_tower_defense

# Build target
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $^ -o $@ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(TARGET)

.PHONY: all clean
