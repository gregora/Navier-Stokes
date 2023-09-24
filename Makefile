main.out: main.cpp
	g++ main.cpp -o main.out -lsfml-graphics -lsfml-window -lsfml-system -pthread -std=c++11
