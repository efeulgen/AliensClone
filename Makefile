
INCLUDE_PATH = -I"libs"
SRC = src/*.cpp \
      src/Engine/*.cpp \
      src/Engine/Logger/*.cpp \
      src/AliensClone/*.cpp

######################################################################################################
######################################################################################################
build:
	g++ -Wall -std=c++17 $(INCLUDE_PATH) $(SRC) -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o aliensclone
