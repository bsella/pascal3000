all:
	gcc `sdl-config --cflags --libs` -lm pascal.c -o eliPascal