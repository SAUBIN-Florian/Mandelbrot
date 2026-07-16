CC= g++
PKG= sfml-graphics
CFLAGS= -Wall -Wextra `pkg-config --cflags $(PKG)`
LIBS= `pkg-config --libs $(PKG)`
SRC= ./main.cpp
OUT= ./build/Mandelbrot

compile:
	@ $(CC) $(CFLAGS) -o $(OUT) $(SRC) $(LIBS)

run: compile
	@ $(OUT)
