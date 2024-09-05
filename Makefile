all:
	g++ -I src/HPP -I src/include -L src/lib -o main main.cpp src/CPP/* -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -std=c++23

run:
	./main

