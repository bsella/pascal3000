#ifndef SHOWFRACTAL
#define SHOWFRACTAL
#include <SDL/SDL.h>

typedef struct{
	struct paletteColor *first;
	SDL_PixelFormat *format;
}Palette;

int pltEmpty(Palette *plt);

Palette* pltInit(SDL_Surface* s);

void pltAdd(Palette *p, Uint32 color, double i);

Uint32 pltGet(Palette p, double i);

void pltFree(Palette *p);

void pltPrint(Palette *p);

#endif