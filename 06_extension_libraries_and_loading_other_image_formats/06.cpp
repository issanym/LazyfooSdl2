/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

/*
-------------------------------------------------------------------------------------------------------------------------------------------------
To use any SDL_image function or data types, we need to include the SDL_image header. We'd have to do the same for SDL_ttf, or SDL_mixer.
-------------------------------------------------------------------------------------------------------------------------------------------------
*/

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface* gPNGSurface = NULL;

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
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if( !( IMG_Init( imgFlags ) & imgFlags ) )
			{
				printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );  // +++
				success = false;
			}
			else
			{
				//Get window surface
				gScreenSurface = SDL_GetWindowSurface( gWindow );
			}
		}
	}

	return success;
}

/*
-------------------------------------------------------------------------------------------------------------------------------------------------
Now that we're using SDL_image, we need to initialize it. Here we want to initialize SDL_image with PNG loading, 
so we pass in the PNG loading flags into IMG_Init. IMG_Init returns the flags that loaded successfully. 
If the flags that are returned do not contain the flags we requested, that means there's an error.

When there's an error with SDL_image, you get error string with IMG_GetError as opposed to SDL_GetError.

Also:
STOP E-MAILING ME TELLING ME THAT THAT CALL TO IMG_Init IS A BUG!
STOP E-MAILING ME TELLING ME THAT THAT CALL TO IMG_Init IS A BUG!
STOP E-MAILING ME TELLING ME THAT THAT CALL TO IMG_Init IS A BUG!
STOP E-MAILING ME TELLING ME THAT THAT CALL TO IMG_Init IS A BUG!
STOP E-MAILING ME TELLING ME THAT THAT CALL TO IMG_Init IS A BUG!

It's not. IMG_INIT_PNG is 2. If you init with IMG_INIT_PNG and get back IMG_INIT_PNG you get 2 & 2 which is 2. 
2 will evaluate to true, the ! will negate it which means it will evaluate to false which will cause the SDL_GetWindowSurface line to execute.

If you were to get back 4 back from IMG_Init when you wanted 2, 4 & 2 is 0, which evaluates to false, which is negated by the ! 
to evaluate to true which will cause the error printing code to execute.

If you were to get back 6 back from IMG_Init (both the 4 and 2 bit) when you wanted 2, 6 & 2 is 2, 
which evaluates to true, which is negated by the ! to evaluate to false which will cause SDL_GetWindowSurface line to execute.

The reason the code is like that is because we only care about the PNG loading bit. If we get that, that means we can continue. 
In other cases this code would be different, but we're not dealing with that here.

So make sure to brush up on your binary math and STOP E-MAILING ME TELLING ME THAT THAT CALL TO IMG_Init IS A BUG!. 
Seriously it's like 25% of the bug reports I get. 
--------------------------------------------------------------------------------------------------------------------------------------------------
*/

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG surface
	gPNGSurface = loadSurface( "lamine.jpg" );
	if( gPNGSurface == NULL )
	{
		printf( "Failed to load PNG image!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded image
	SDL_FreeSurface( gPNGSurface );
	gPNGSurface = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}

/*
----------------------------------------------------------------------------------------------------------------------------------------------
Our image loading function is pretty much the same as before, only now it uses IMG_Load as opposed to SDL_LoadBMP. 
IMG_Load can load many different types of format which you can find out about in the SDL_image documentation. Like with IMG_Init, 
when there's an error with IMG_Load, we call IMG_GetError to get the error string. 
-----------------------------------------------------------------------------------------------------------------------------------------------
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

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				//Apply the PNG image
				SDL_BlitSurface( gPNGSurface, NULL, gScreenSurface, NULL );
			
				//Update the surface
				SDL_UpdateWindowSurface( gWindow );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
