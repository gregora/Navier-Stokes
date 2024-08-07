CUDA_PATH = /usr/local/cuda
all: main.out mainCUDA.out

main.out: main.cpp Arrow.o Fluid.o misc.o examples.o
	g++ main.cpp Arrow.o Fluid.o misc.o examples.o -o main.out -lsfml-graphics -lsfml-window -lsfml-system -pthread -std=c++11

mainCUDA.out: main.cpp Arrow.o FluidCUDA.o misc.o examples.o
	g++ main.cpp Arrow.o FluidCUDA.o misc.o examples.o -o mainCUDA.out -lsfml-graphics -lsfml-window -lsfml-system -L$(CUDA_PATH)/lib64 -lcudart -std=c++11

Arrow.o: Arrow.cpp Arrow.h
	g++ -c Arrow.cpp -lsfml-graphics -lsfml-window -lsfml-system -std=c++11

Fluid.o: Fluid.cpp Fluid.h
	g++ -c Fluid.cpp -lsfml-graphics -lsfml-window -lsfml-system -std=c++11

FluidCUDA.o: FluidCUDA.cu Fluid.h
	nvcc -c FluidCUDA.cu -std=c++11

misc.o: misc.cpp misc.h
	g++ -c misc.cpp

examples.o: examples.cpp examples.h
	g++ -c examples.cpp

