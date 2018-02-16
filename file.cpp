#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<string>
#include<iostream>

using namespace std;

void G_ErrorLogger(std::string cause){//given a name output the last error of sdl
	std::cout<<cause<<": "<<SDL_GetError()<<std::endl;
}

int main(int argc,char**argv){
	
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0){//init sdl, print error otherwise 
		G_ErrorLogger("init");
		return 3;
	}
	
	if(TTF_Init()!=0){//init sdl, print error otherwise 
		cout<<"ttf init:"<<TTF_GetError();
		return 3;
	}
	
	
	const int G_ScreenWidth=640;
	const int G_ScreenHeight=480;
	
	SDL_Window* Window=SDL_CreateWindow(//create window
	"FelizCumple.o",
	SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED,
	G_ScreenWidth,
	G_ScreenHeight,
	SDL_WINDOW_SHOWN
	);
	if(Window==NULL){//if window fails then output error, quit sdl and exit
		G_ErrorLogger("window create");
		SDL_Quit();
		return 2;
	}
	
	SDL_Renderer* Renderer=SDL_CreateRenderer(//create a renderer
	Window,
	-1,
	SDL_RENDERER_ACCELERATED
	);
	
	if(Renderer==NULL){//if it fails to create a render, output de error and exit the program
		G_ErrorLogger("Renderer create");
		SDL_DestroyWindow(Window);
		SDL_Quit();
		TTF_Quit();
		return 1;
	}
	
	
	//setup TTF
	TTF_Font* font=TTF_OpenFontIndex("font.ttf",50,0);//FELIZ CUMPLE!!
	if(!font){
		cout<<"font:"<<TTF_GetError();
		TTF_Quit();
		SDL_DestroyWindow(Window);
		SDL_DestroyRenderer(Renderer);
		SDL_Quit();
		return 1;
	}
	SDL_Color Color={255,35,1,255};
	SDL_Surface* TextSurface;
	TextSurface=TTF_RenderText_Solid(font,"FELIZ CUMPLE!!",Color);
	int t_w,t_h;
	TTF_SizeText(font,"FELIZ CUMPLE!!",&t_w,&t_h);
	SDL_Texture* TextTexture=SDL_CreateTextureFromSurface(Renderer,TextSurface);
	if(TextTexture==NULL){
		cout<<"TextTexture: "<<SDL_GetError<<endl;
	}
	SDL_Rect TextRect;
	TextRect.w = t_w;
	TextRect.h = t_h;
	TextRect.y = 100;
	TextRect.x = 20;
	SDL_QueryTexture(TextTexture,NULL,NULL,&TextRect.w,&TextRect.h); 
	SDL_Event Event;
	bool Displaying=false;
	bool Done=false;
	
	int n=0;
	int m=0;
	while(!Done){//event handler
		while(SDL_PollEvent(&Event)){
			if(Event.type==SDL_QUIT){
				Done=true;
				continue;
			}
		}
		if(Displaying==true){
			SDL_SetRenderDrawColor(Renderer,255,255,255,255);
			SDL_RenderClear(Renderer);
			SDL_RenderPresent(Renderer);
			SDL_Delay(100);
			Displaying=false;
			continue;
		}
		if(Displaying==false){
			SDL_SetRenderDrawColor(Renderer,255,255,255,255);
			SDL_RenderClear(Renderer);
			SDL_RenderCopy(Renderer,TextTexture,NULL,&TextRect);
			SDL_RenderPresent(Renderer);
			Displaying=true;
			SDL_Delay(100);
			continue;
		}
	}
	/*SDL_Window* Window2=SDL_CreateWindow(//create window
	"FelizCumple.o",
	SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED,
	G_ScreenWidth,
	G_ScreenHeight,
	SDL_WINDOW_SHOWN
	);
	SDL_Surface* Surface=SDL_GetWindowSurface(Window2);
	SDL_BlitSurface(TextSurface,NULL,Surface,NULL);
	SDL_UpdateWindowSurface(Window2);
	
	
	SDL_Delay(1000);
	*/
	SDL_FreeSurface(TextSurface);
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	TTF_CloseFont(font);
	SDL_Quit();
	TTF_Quit();
	
	return 0;
	
	
	
	
	
	
}
