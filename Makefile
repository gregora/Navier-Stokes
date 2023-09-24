main.out: main.cpp Arrow.cpp Arrow.h
	g++ main.cpp Arrow.cpp -o main.out -lsfml-graphics -lsfml-window -lsfml-system -pthread -std=c++11
