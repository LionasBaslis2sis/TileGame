INCS = -I "C:\libs\SDL2\include" -L "C:\libs\SDL2\lib\x64" -I "C:\libs\glm"

LIBS = -lm -lSDL2_image -lSDL2main -lSDL2

CPP = src/*.cpp

CXX = g++

CXXFLAGS = -std=c++20 -Wall -static-libgcc -static-libstdc++

all:
	@ $(CXX) $(CXXFLAGS) main.cpp $(CPP) -o main.exe $(INCS) $(LIBS)