main.out: main.cpp Arrow.cpp Arrow.h Fluid.cpp Fluid.h misc.cpp misc.h examples.cpp examples.h
	g++ main.cpp Arrow.cpp Fluid.cpp misc.cpp examples.cpp -o main.out -lsfml-graphics -lsfml-window -lsfml-system -pthread -std=c++11
