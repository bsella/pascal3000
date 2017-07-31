EXE=eliPascal

all:
	gcc `sdl-config --cflags --libs` -lm pascal.c -o $(EXE)

clean:
	rm $(EXE)