all:  
	g++ -Isrc/include -Lsrc/lib -o main main.cpp Game.cpp TextureManager.cpp Player.cpp Obstacles.cpp Score.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf