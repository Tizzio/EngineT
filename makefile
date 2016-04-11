CC = g++
CXXFLAGS = -w -std=gnu++14

# paths 
SRC_DIR = src
BUILD_DIR = obj

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

vpath %.cpp $(SRC_DIR)

# flags
SDL_FLAGS = `sdl-config --cflags`
BULLET_FLAGS =  `pkg-config --cflags bullet`
GLEW_FLAGS = `pkg-config --cflags glew`  
FLAGS = $(SDL_FLAGS) $(BULLET_FLAGS) $(GLEW_FLAGS)

# libraries
GL_LIBS = -lGLEW -lGLU -lGL
SDL_LIBS = -lSDL2
BULLET_LIBS = `pkg-config --libs bullet`
ASSIMP_LIBS = `pkg-config --libs assimp`

LIBS = $(SDL_LIBS)  $(GL_LIBS) $(BULLET_LIBS) $(ASSIMP_LIBS)
EXEC = build/executable.x

# main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(LIBS)


# object files
$(BUILD_DIR)/%.o: %.cpp
	$(CC) -c $(CXXFLAGS) $(FLAGS) $< -o $@ 

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $@
    
clean:
	rm -rf $(BUILD_DIR)/*

force:
	rm -rf $(BUILD_DIR)/*

