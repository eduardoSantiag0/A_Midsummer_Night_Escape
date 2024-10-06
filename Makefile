# all:  
#	g++ -Isrc/include -o main main.cpp Game.cpp TextureManager.cpp Player.cpp Obstacles.cpp Score.cpp ParallaxBG.cpp $(shell pkg-config --cflags --libs sdl2 SDL2_image SDL2_mixer SDL2_ttf)

# Compiler settings
CC = g++

# Common sources
SRC = main.cpp Game.cpp TextureManager.cpp Player.cpp Obstacles.cpp Score.cpp ParallaxBG.cpp
INCLUDE = -Isrc/include

# OS detection
UNAME_S := $(shell uname -s)

# Set platform-specific settings
ifeq ($(UNAME_S), Linux)
    # Linux settings
    LIBS = $(shell pkg-config --cflags --libs sdl2 SDL2_image SDL2_mixer SDL2_ttf)
    OUTPUT = main
else
    # Windows settings (using MinGW)
    LIBS = -Lsrc/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
    OUTPUT = main.exe
endif

# Default target
all: $(OUTPUT)

# Compile and link
$(OUTPUT): $(SRC)
	$(CC) $(INCLUDE) -o $(OUTPUT) $(SRC) $(LIBS)

# Clean the build
clean:
	rm -f main main.exe

