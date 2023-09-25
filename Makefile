main.out: main.cpp Arrow.cpp Arrow.h Fluid.cpp Fluid.h
	g++ main.cpp Arrow.cpp Fluid.cpp -o main.out -lsfml-graphics -lsfml-window -lsfml-system -pthread -std=c++11
