#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include "palette.h"

const unsigned int width=1024, height=512;//3840 2400 //1080 720

//Calculating Pascal
void calcPascal(unsigned int *pscl, double mx){
	for(int y=0; y<height; y++)
		for(int x=0; x<=y;x++){
			if(x==0 || x==y)
				pscl[y*(y+1)/2+x]=1;
			else
				pscl[y*(y+1)/2+x]= pscl[y*(y-1)/2+x]+pscl[y*(y-1)/2+x-1];
			if(pscl[y*(y+1)/2+x]>mx)
				pscl[y*(y+1)/2+x]=0;
		}
}

void drawPascal(unsigned int *pscl,double max, SDL_Surface *s, Palette p){
	Uint32 * pixels= s->pixels;
	for(int y=0; y<height; y++)
		for(int x=0; x<=y; x++){
			pixels[x*2+width/2-y+y*width]=pltGet(p,pscl[y*(y+1)/2+x]/max);
			pixels[x*2+1+width/2-y+y*width]=pltGet(p,pscl[y*(y+1)/2+x]/max);
		}
}

int main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	SDL_Surface *screen=SDL_SetVideoMode(width,height,32,SDL_HWSURFACE);
	
	double max=1;

	Palette *colors=pltInit(screen);
	pltAdd(colors,SDL_MapRGB(screen->format,0,0,0),0.0);
	pltAdd(colors,SDL_MapRGB(screen->format,255,0,0),0.25);
	pltAdd(colors,SDL_MapRGB(screen->format,255,0,0),0.5);
	pltAdd(colors,SDL_MapRGB(screen->format,0,255,0),0.625);
	pltAdd(colors,SDL_MapRGB(screen->format,0,0,255),0.75);
	pltAdd(colors,SDL_MapRGB(screen->format,255,255,255),1.0);
	
	unsigned int pascal[height*(height+1)/2];
	calcPascal(pascal,max);

	//Drawing
	
			//if((int)(pascal[y*(y+1)/2+x])%2!=0)
			//	p[x+y*width]=SDL_MapRGB(screen->format,255,0,0);
			//else
			//	if((int)(pascal[y*(y+1)/2+x])%4!=0)
			//		p[x+y*width]=SDL_MapRGB(screen->format,0,255,0);
			//	else
			//		if((int)(pascal[y*(y+1)/2+x])%8!=0)
			//			p[x+y*width]=SDL_MapRGB(screen->format,0,0,255);
			//		else p[x+y*width]=SDL_MapRGB(screen->format,0,0,0);
	drawPascal(pascal, max, screen,*colors);
	
	//Input
	int run=1;
	while(run){
		SDL_Event event;
		SDL_Flip(screen);
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE: run=0;break;
					default: break;
				}
				break;
			case SDL_QUIT: run=0; break;
			default: max+=1;
		}
		calcPascal(pascal,max);
		drawPascal(pascal, max, screen,*colors);

	}
	pltFree(colors);
	SDL_SaveBMP(screen, "pascal.bmp");
	SDL_FreeSurface(screen);
	SDL_Quit();
	printf("%f\n", max);
	return 0;
}
