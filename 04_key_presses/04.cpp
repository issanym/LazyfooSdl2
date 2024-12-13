/*T his source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

// --------------------------------------------------|| 04 Key presses ||------------------------------------------------------


//Using SDL, standard IO, and strings
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Key press surfaces constants
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

/*
----------------------------------------------------------------------------------------------------------------------------------------------
Near the top of the source code we declare an enumeration of the different surfaces we have. 
Enumerations are a shorthand way to do symbolic constants instead of having to do 
const int KEY_PRESS_SURFACE_DEFAULT = 0;  const int KEY_PRESS_SURFACE_UP = 1; const int KEY_PRESS_SURFACE_DOWN = 2; and such. 
They default to start counting at 0 and go up by one for each enumeration you declare. 
This means KEY_PRESS_SURFACE_DEFAULT is 0, KEY_PRESS_SURFACE_UP is 1, KEY_PRESS_SURFACE_DOWN is 2, KEY_PRESS_SURFACE_LEFT is 3, 
KEY_PRESS_SURFACE_RIGHT is 4, and KEY_PRESS_SURFACE_TOTAL is 5, It's possible to give them explicit integer values, 
but we won't be covering that here. A quick Google search on enumerations should cover that.

One bad habit beginning programmers have is using abritary numbers instead of symbolic constants. 
For example they'll have 1 mean main menu, 2 mean options, etc which is fine for small programs. 
When you're dealing with thousands of lines of code (which video games usually have), having a line that says "if( option == 1 )" 
will produce much more headaches than using "if( option == MAIN_MENU )". 
-----------------------------------------------------------------------------------------------------------------------------------------------
*/

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//+++++++++++

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

/*
------------------------------------------------------------------------------------------------------------------------------------------------
Along with our usual function prototypes, we have a new function called loadSurface. 
There's a general rule that if you're copy/pasting code, you're doing something wrong. Rather than copy/paste loading code every time,
we're going to use a function to handle that.

What's important to this specific program is that we have an array of pointers to SDL surfaces called gKeyPressSurfaces to contain 
all the images we'll be using. Depending on which key the user presses, we'll set gCurrentSurface (which is the image 
that will be blitted to the screen) to one of these surfaces.
------------------------------------------------------------------------------------------------------------------------------------------------
*/

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set default current surface
			gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

			//While application is running
			while( !quit )
			{

// In the main function before entering the main loop, we set the default surface to display. 

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					//User presses a key
					else if( e.type == SDL_KEYDOWN )
					{
						//Select surfaces based on key press
						switch( e.key.keysym.sym )
						{
							case SDLK_UP:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
							break;

							case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
							break;

							case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
							break;

							case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
							break;

							default:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
							break;
						}
					}
				}

/*
--------------------------------------------------------------------------------------------------------------------------------------------------
Here is our event loop. As you can see we handle closing the window as we did in the previous tutorial, then we handle an SDL_KEYDOWN event. 
This event happens when ever you press a key on the keyboard.

Inside of the SDL Event is an SDL Keyboard event which contains the information for the key event. 
Inside of that is a SDL Keysym which contains the information about the key that was pressed. 
That Keysym contains the SDL Keycode which identifies the key that was pressed.

As you can see, what this code does is set the surfaces based on which key was pressed. Look in the SDL documentation if you want 
to see what the other keycodes are for other keys. 
--------------------------------------------------------------------------------------------------------------------------------------------------
*/

				//Apply the current image
				SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
			
				//Update the surface
				SDL_UpdateWindowSurface( gWindow );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}


// ===============================================================================================================================================

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}


bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load default surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "press.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load up surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "up.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
	{
		printf( "Failed to load up image!\n" );
		success = false;
	}

	//Load down surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "down.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
	{
		printf( "Failed to load down image!\n" );
		success = false;
	}

	//Load left surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "left.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
	{
		printf( "Failed to load left image!\n" );
		success = false;
	}

	//Load right surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "right.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
	{
		printf( "Failed to load right image!\n" );
		success = false;
	}

	return success;
}

// Here in the loadMedia function we load all of the images we're going to render to the screen

void close()
{
	//Deallocate surfaces
	for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	{
		SDL_FreeSurface( gKeyPressSurfaces[ i ] );
		gKeyPressSurfaces[ i ] = NULL;
	}

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}

	return loadedSurface;
}

/*
-------------------------------------------------------------------------------------------------------------------------------------------------
Here's the loadSurface function which loads an images and reports an error if something goes wrong. 
It's pretty much that same as before, but having the image loading and error reporting contained in one function makes it easy to add to 
and debug image loading.

And since I get this question a lot by new C++ programmers, no this function does not leak memory. 
It does allocate memory to load a new SDL surface and return it without freeing the allocated memory, 
but what would be the point of allocating the surface and immediately deallocating it? 
What this function does is load the surface and return the newly loaded surface so what ever called this function can deallocate it 
after it's done using it. In this program, the loaded surface is deallocated in the close function.
------------------------------------------------------------------------------------------------------------------------------------------------- 
*/

