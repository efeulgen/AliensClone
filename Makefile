
build:
	g++ -Wall -std=c++17 src/*.cpp src/Engine/*.cpp src/Engine/Logger/*.cpp src/AliensClone/*.cpp -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o aliensclone
