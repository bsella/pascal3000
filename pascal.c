#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>

const unsigned int width=1080, height=720;//3840 2400 //1080 720

int main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	SDL_Surface *screen=SDL_SetVideoMode(width,height,32,SDL_HWSURFACE);
	
	//Calculating Pascal
	unsigned int pascal[height*(height+1)/2];
	for(int y=0; y<height; y++)
		for(int x=0; x<=y;x++)
			if(x==0 || x==y)
				pascal[y*(y+1)/2+x]=1;
			else
				pascal[y*(y+1)/2+x]= pascal[y*(y-1)/2+x]+pascal[y*(y-1)/2+x-1];
	//Drawing
	Uint32 * p= screen->pixels;
	unsigned ratio = 4;
	for(int y=0; y<height; y++)
		for(int x=0; x<=y; x++)
			if(pascal[y*(y+1)/2+x]%2==0)
				p[x+y*width]=SDL_MapRGB(screen->format,0,255,0);
			else
				p[x+y*width]=SDL_MapRGB(screen->format,0,0,0);
	
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
			default: break;
		}
	}

	SDL_SaveBMP(screen, "pascal.bmp");
	SDL_FreeSurface(screen);
	SDL_Quit();
	return 0;
}
