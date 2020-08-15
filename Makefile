INCS = -I "C:\libs\SDL2\include" -L "C:\libs\SDL2\lib\x64"

LIBS = -lm -lSDL2_image -lSDL2main -lSDL2

CPP = src/*.cpp

CXX = g++

CXXFLAGS = -std=c++20 -Wall

all:
	@ $(CXX) $(CXXFLAGS) main.cpp $(CPP) -o main.exe $(INCS) $(LIBS)