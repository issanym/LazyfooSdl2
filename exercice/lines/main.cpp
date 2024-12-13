#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstddef>
#include <iostream>
#include <SDL2/SDL.h>
#include <ostream>
#include <string>

bool init();
void close();

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWin = NULL;
SDL_Renderer* gRend = NULL; 

// ==================================================================================================================

int main()
{
  if (!init()) {
    std::cout<<"Couldnt initialise SDL "<< std::endl;
  }
  else {
    bool quit = false;

    SDL_Event e;

    while (!quit) {
      while (SDL_PollEvent(&e)!=0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
      }
      
      // color control
      SDL_SetRenderDrawColor(gRend, 0, 0, 0, 0xff);
      SDL_RenderClear(gRend);

      // vertical line
      SDL_SetRenderDrawColor(gRend, 250, 250, 250, 0xff);
      SDL_RenderDrawLine(gRend, SCREEN_WIDTH/3, 0, SCREEN_WIDTH/3, SCREEN_HEIGHT);

      SDL_SetRenderDrawColor(gRend, 250, 250, 250, 0xff);
      SDL_RenderDrawLine(gRend, (SCREEN_WIDTH*2)/3, 0, (SCREEN_WIDTH*2)/3, SCREEN_HEIGHT);

      // horizontal line
      SDL_SetRenderDrawColor(gRend, 250, 250, 250, 0xff);
      SDL_RenderDrawLine(gRend, 0, SCREEN_HEIGHT/3, SCREEN_WIDTH, SCREEN_HEIGHT/3);

      SDL_SetRenderDrawColor(gRend, 250, 250, 250, 0xff);
      SDL_RenderDrawLine(gRend, 0, (SCREEN_HEIGHT*2)/3, SCREEN_WIDTH, (SCREEN_HEIGHT*2)/3);


      SDL_RenderPresent(gRend);

    }
  }

	return 0;
}

// ===================================================================================================================

bool init()
{
  bool success=true;

  if (SDL_Init(SDL_INIT_VIDEO)<0) {
    std::cout << "Failed to initialise SDL! error: " << SDL_GetError() << std::endl;
    success = false;
  }
  else {
    if (!(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))) {
      std::cout << "warning: no linear rendering" << std::endl;
    }

    gWin=SDL_CreateWindow("Lines", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWin==NULL) {
      std::cout<< "COuldnt create window. Error: " << SDL_GetError() << std::endl;
      success = false;
    }
    else {

      gRend=SDL_CreateRenderer(gWin, -1, SDL_RENDERER_ACCELERATED);
      if (gRend==NULL) {
        std::cout << "COuldnt create renderer. error: " << SDL_GetError() << std::endl;
        success=false;
      }
      else {
        SDL_SetRenderDrawColor(gRend, 255, 255, 255, 0xFF);
      }
    }
  }
  return success;
}


void close()
{
  SDL_DestroyRenderer(gRend);
  SDL_DestroyWindow(gWin);
  gRend = NULL;
  gWin = NULL;

  SDL_Quit();
}
