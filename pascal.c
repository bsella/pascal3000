#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include "palette.h"

const unsigned int width=1024, height=512;//3840 2400 //1080 720

//Calculating Pascal
void calcPascal(unsigned int *pscl, double mx, double d){
	for(int y=0; y<height; y++)
		for(int x=0; x<=y;x++){
			if(x==0 || x==y)
				pscl[y*(y+1)/2+x]=1;
			else
				pscl[y*(y+1)/2+x]= pscl[y*(y-1)/2+x]+pscl[y*(y-1)/2+x-1];
			//if(pscl[y*(y+1)/2+x]>mx)
			//	pscl[y*(y+1)/2+x]/=d;
		}
}

static int prime(unsigned n){
	if(n<2) return 0;
	for(int x=2; x<sqrt(n)+1;x++)
		if(n%x==0) return 0;
	return 1;
}

static unsigned devides(unsigned n){
	unsigned c=0;
	while(n%2==0){
		n/=2;
		c++;
	}
	return c;
}

static void draw2Pixels(unsigned x, unsigned y, SDL_Surface *s, Palette p, float alpha){
	Uint32 * pixels= s->pixels;
	pixels[x*2+width/2-y+y*width]=pltGet(p,alpha);
	pixels[x*2-1+width/2-y+y*width]=pltGet(p,alpha);
}

static unsigned getPascal(unsigned *pascal, unsigned xCoord, unsigned yCoord){
	return pascal[yCoord*(yCoord+1)/2+xCoord]; //yCoord's triangle number plus xCoord
}

void drawPascal(unsigned int *pscl,double max, SDL_Surface *s, Palette p){
	for(int y=0; y<height; y++)
		for(int x=0; x<=y; x++){
			//if(pscl[y*(y+1)/2+x]%2!=0)
			//draw2Pixels(x,y,s,p,0); //pscl[y*(y+1)/2+x]/max);
			//else if(pscl[y*(y+1)/2+x]%4!=0)
			//	draw2Pixels(x,y,s,p,0.5);
			//else if(pscl[y*(y+1)/2+x]%8!=0)
			//	draw2Pixels(x,y,s,p,1);
			//if(prime(getPascal(pscl,x,y)))
				// draw2Pixels(x,y,s,p,0);
			draw2Pixels(x,y,s,p,devides(getPascal(pscl,x,y))/max);

		}
}

int main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	SDL_Surface *screen=SDL_SetVideoMode(width,height,32,SDL_HWSURFACE);
	
	double max=6;

	double d=1;

	Palette *colors=pltInit();
	//pltAdd(colors,SDL_MapRGB(screen->format,0,0,0),0.0);
	//pltAdd(colors,SDL_MapRGB(screen->format,255,0,0),0.165);
	//pltAdd(colors,SDL_MapRGB(screen->format,255,255,0),0.33);
	//pltAdd(colors,SDL_MapRGB(screen->format,0,255,0),0.495);
	//pltAdd(colors,SDL_MapRGB(screen->format,0,255,255),0.66);
	//pltAdd(colors,SDL_MapRGB(screen->format,0,0,255),0.825);
	//pltAdd(colors,SDL_MapRGB(screen->format,255,0,255),1);

	//pltAdd(colors,SDL_MapRGB(screen->format,255,0,0),0.0);
	//pltAdd(colors,SDL_MapRGB(screen->format,0,255,0),0.5);
	//pltAdd(colors,SDL_MapRGB(screen->format,0,0,255),1.0);
	
	pltAdd(colors,SDL_MapRGB(screen->format,255,0,0),0);
	pltAdd(colors,SDL_MapRGB(screen->format,0,0,255),.2);
	pltAdd(colors,SDL_MapRGB(screen->format,255,128,0),0.201);
	pltAdd(colors,SDL_MapRGB(screen->format,0,255,0),0.5);
	pltAdd(colors,SDL_MapRGB(screen->format,0,0,0),1);

	unsigned int pascal[height*(height+1)/2];
	calcPascal(pascal,max, d);

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
	Uint32 *pixels = screen->pixels;
		for(int x=0;x<200;x++){
			for(int y=0;y<10;y++)
				pixels[x+y*width]=pltGet(*colors,x/200.0);
			pixels[x+10*width]=SDL_MapRGB(screen->format,255,255,255);
		}
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
			default: max*=1.002;
		}
		calcPascal(pascal,max,d);
		drawPascal(pascal, max, screen,*colors);

	}
	pltFree(colors);
	SDL_SaveBMP(screen, "pascal.bmp");
	SDL_FreeSurface(screen);
	SDL_Quit();
	printf("max=%f\n", max);
	return 0;
}
