CCFLAGS = -Wall -Wno-missing-braces
CC = gcc
STD = -std=c99
INP = src/main.c
OUT = GoL
FINC = -I/src
FLIB = -L. -L/home/loren/Repos/raylib/src  -L/usr/local/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -latomic -DPLATFORM_DESKTOP

all: compile run 

compile: 
	$(CC) $(INP) $(STD) $(CCFLAGS) -o $(OUT) $(FINC) $(FLIB) 

run:
	./$(OUT)

rem: 
	rm $(OUT) 
