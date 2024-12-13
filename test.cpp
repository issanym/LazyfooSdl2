#include <SDL2/SDL_video.h>
#include <iostream>
#include <SDL2/SDL.h>


using namespace std;

bool init(SDL_Window* win, SDL_Surface* surf)
{
  bool success = true;
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    success = false;
    cout << "Error: " << SDL_GetError() << endl;
  }
  else 
  {
    win = SDL_CreateWindow("Sld test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
    if(win == NULL)
    {
      success = false;
      cout << "Error: " << SDL_GetError() << endl;
    }
    else 
    {
        surf = SDL_GetWindowSurface(win);
    }
  }
  return success;
}

int main (int argc, char *argv[]) 
{
  SDL_Window* initWin;
  SDL_Surface* initSurf;
  if(!init(initWin, initSurf))
  {
    cout << "Failed to init" << endl;
  }
  else 
  {
    cout << "Hello world" << endl;
  }

  SDL_DestroyWindow(initWin);
  SDL_Quit();
  return 0;
}


