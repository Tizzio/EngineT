CC = g++
CXXFLAGS = -w -std=gnu++14

# paths 
SRC_DIR = src
BUILD_DIR = obj

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

vpath %.cpp $(SRC_DIR)

# includes
SDL_INCLUDES = `sdl-config --cflags --libs`
BULLET_INCLUDES =  `pkg-config --cflags bullet`
GLEW_INCLUDES = `pkg-config --cflags glew`  
INCLUDES = $(SDL_INCLUDES) $(BULLET_INCLUDES) $(GLEW_INCLUDES)

# libraries
BULLET_LIBS = `pkg-config --libs bullet`
ASSIMP_LIBS = `pkg-config --libs assimp`

LIBS = -lSDL2 -lGLEW -lGLU -lGL -I  $(BULLET_LIBS) $(ASSIMP_LIBS)
EXEC = build/executable.x

# main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(LIBS)


# object files
$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(INCLUDES) -c $(CXXFLAGS) $< -o $@ 

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $@
    
clean:
	rm -rf $(BUILD_DIR)/*

