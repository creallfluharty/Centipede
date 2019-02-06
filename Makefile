.PHONY: all

all:
	g++ -w -o bin/Centipede source/*.cpp -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
