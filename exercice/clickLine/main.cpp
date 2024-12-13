#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstddef>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 520;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

bool init();
void close();
bool loadRend();

SDL_Window* gWin = NULL;
SDL_Renderer* gRend = NULL;
SDL_Renderer* itmRend[KEY_PRESS_SURFACE_TOTAL];

// ======================================================================================================================

int main()
{
  if (!init()) {
    std::cout << "Couldnt init SDL" << std::endl;
  }
  else {
    bool quit=true;
    SDL_Event e;

    while (quit) {
      while (SDL_PollEvent(&e) !=0 ) {
        if (e.type==SDL_QUIT) {
          quit = false;
        }
        else {
          switch (e.key.keysym.sym) {
            case SDLK_UP:
              
          }
        }
      }
    }
  }

	return 0;
}


// ====================================================================================================================

bool init()
{
  bool success = true;

  if(SDL_Init(SDL_INIT_VIDEO)<0)
  {
    std::cout << "Couldnt init SDL. Error: " << SDL_GetError() << std::endl;
    success=false;
  }
  else {
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
      std::cout << "Warning: no linear texture renderr" << std::endl;
    }

    gWin=SDL_CreateWindow("CLICKSS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWin==NULL) {
      std::cout << "Couldnt create window. Error: " << SDL_GetError() << std::endl;
      success=false;
    }
    else {
      gRend = SDL_CreateRenderer(gWin, -1, SDL_RENDERER_ACCELERATED);
      if (gRend==NULL) {
        std::cout << "Couldnt create renderer. Error: " << SDL_GetError() << std::endl;
        success=false;
      }
      else {
        SDL_SetRenderDrawColor(gRend, 10, 10, 10, 0xff);
      }
    }
  }
  return success;
}

bool loadRend()
{
  bool success = true;

  itmRend[KEY_PRESS_SURFACE_DEFAULT] = SDL_CreateRenderer(gWin, -1, SDL_RENDERER_ACCELERATED);
  if (itmRend[KEY_PRESS_SURFACE_DEFAULT]==NULL) {
    std::cout << "Couldnt create renderer default. Error: " << SDL_GetError() << std::endl;
    success=false;
  }
  else {
    SDL_SetRenderDrawColor(gRend, 0, 0, 0, 0xff);
    SDL_RenderDrawLine(itmRend[KEY_PRESS_SURFACE_DEFAULT], 0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2);
  }

  itmRend[KEY_PRESS_SURFACE_UP] = SDL_CreateRenderer(gWin, -1, SDL_RENDERER_ACCELERATED);
  if (itmRend[KEY_PRESS_SURFACE_UP]==NULL) {
    std::cout << "Couldnt create renderer up. Error: " << SDL_GetError() << std::endl;
    success=false;
  }
  else {

    SDL_Rect stadium = {SCREEN_WIDTH/7, SCREEN_HEIGHT/7, SCREEN_WIDTH*2/3, SCREEN_HEIGHT*2/3};
    SDL_SetRenderDrawColor(gRend, 0, 230, 0, 0xff);
    SDL_RenderFillRect(itmRend[KEY_PRESS_SURFACE_UP], &stadium);

  }

  return success;
}

void close()
{
  SDL_DestroyWindow(gWin);
  SDL_DestroyRenderer(gRend);
  gWin = NULL;
  gRend = NULL;

  SDL_Quit();
}
