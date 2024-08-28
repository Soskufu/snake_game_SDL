# Variables
CXX = g++
CXXFLAGS = -std=c++2a -g -Wall -m64 -I include -I C:/SDL2-w64/include
LDFLAGS = -L C:/SDL2-w64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin/debug
EXECUTABLE = $(BIN_DIR)/main
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Default target
.PHONY: all
all: BuildDebug

# Custom target equivalent to "Build Debug" in Sublime Text
BuildDebug: $(EXECUTABLE)
	@echo "Build Debug complete."

# Link object files into the final executable
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "Running program..."

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Run target
run: BuildDebug
	./$(EXECUTABLE)

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)\main.exe
	@echo "Clean complete."

# Phony targets
.PHONY: BuildDebug clean

# just doing this
#g++ -c src/*.cpp -std=c++2a -g -Wall -m64 -I include -I C:/SDL2-w64/include && g++ *.o -o bin/debug/main -L C:/SDL2-w64/lib -lmingw32 -LSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf && start bin/debug/main