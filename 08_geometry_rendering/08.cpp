/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

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
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

/*
------------------------------------------------------------------------------------------------------------------------------------------------
So as you can see in our media loading function, we load no media. 
SDL's primitive rendering allows you to render shapes without loading special graphics. 
------------------------------------------------------------------------------------------------------------------------------------------------
*/

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

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

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );


/*
----------------------------------------------------------------------------------------------------------------------------------------------
At the top of the main loop we handle the quit event like before and clear the screen. 
Also notice that we're setting the clearing color to white with SDL_SetRenderDrawColor every frame as opposed to setting it once 
in the initialization function. We'll cover why this happens when we get to the end of the main loop. 
------------------------------------------------------------------------------------------------------------------------------------------------
*/


				//Render red filled quad
				SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );		
				SDL_RenderFillRect( gRenderer, &fillRect );

/*
------------------------------------------------------------------------------------------------------------------------------------------------
The first primitive we're going to draw is a fill rectangle, which is a solid rectangle.

First we define a rectangle to define the area we want to fill with color. If you never seen a struct initialized like this, 
know that the member variables that make up an SDL rect are x, y, w, and h for the x position, y position, width, and height respectively. 
You can initialize a struct by giving it an array of variables in the order they are in the struct. 
Here we're setting the rectangle one quarter of the screen width in the x direction, one quarter of the screen height in the y direction, 
and with half the screen's width/height.

After defining the rectangle area, we set the rendering color with SDL_SetRenderDrawColor. 
This function takes in the renderer for the window we're using and the RGBA values for the color we want to render with. 
R is the red component, G is green, B is blue, and A is alpha. Alpha controls how opaque something is and we'll cover that in the 
transparency tutorial. These values go from 0 to 255 (or FF hex as you see above) and are mixed together to create all the 
colors you see on your screen. This call to SDL_SetRenderDrawColor sets the drawing color to opaque red.

After the rectangle and color have been set, SDL_RenderFillRect is called to draw the rectangle. 
--------------------------------------------------------------------------------------------------------------------------------------------------
*/


				//Render green outlined quad
				SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );		
				SDL_RenderDrawRect( gRenderer, &outlineRect );

/*
--------------------------------------------------------------------------------------------------------------------------------------------------
You can also draw a rectangle outline with an empty center using SDL_RenderDrawRect. As you can see it pretty much works the same as a solid 
filled rectangle as this piece of code is almost the same as the one above it. The major difference is that this rectangle is 2 thirds of 
the screen in size and that the color we're using here is green.
--------------------------------------------------------------------------------------------------------------------------------------------------
*/

				
				//Draw blue horizontal line
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );		
				SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

/*
-------------------------------------------------------------------------------------------------------------------------------------------------
Here is the code to draw a pixel thin line using SDL_RenderDrawLine. First we set the color to blue, and then give 
the rendering calls the starting x/y position and ending x/y position. These positions cause it to go horizontally straight across the screen.
-------------------------------------------------------------------------------------------------------------------------------------------------
*/

				//Draw vertical line of yellow dots
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
				for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
				{
					SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
				}

				//Update screen
				SDL_RenderPresent( gRenderer );
			}

/*
--------------------------------------------------------------------------------------------------------------------------------------------------
The last bit of geometry we render is a sequence of dots using SDL_RenderDrawPoint. 
We're just taking a set of points and drawing them from top to bottom. Again notice the y coordinate and the inverted y axis. 
After we're finished drawing all our geometry, we update the screen.

Notice the call to SDL_SetRenderDrawColor. We're using 255 red and 255 green which combine together to make yellow. 
Remember that call to SDL_SetRenderDrawColor at the top of the loop? If that wasn't there, the screen would be cleared with whatever color 
was last set with SDL_SetRenderDrawColor, resulting in a yellow background in this case. 
--------------------------------------------------------------------------------------------------------------------------------------------------
*/


		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
