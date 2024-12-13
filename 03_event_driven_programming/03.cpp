/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

// --------------------------------------------------|| 03 Event driven programming ||------------------------------------------------------

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gXOut = NULL;


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

/*
--------------------------------------------------------------------------------------------------------------------------------------------------
In our code after SDL is initialized and the media is loaded (as mentioned in the previous tutorial), we declare a quit flag that keeps 
track of whether the user has quit or not. Since we just started the application at this point, it is obviously initialized to false.

We also declare an SDL_Event union. A SDL event is some thing like a key press, mouse motion, joy button press, etc. 
In this application we're going to look for quit events to end the application. 
--------------------------------------------------------------------------------------------------------------------------------------------------
*/

			//While application is running
			while( !quit )
			{

/*
-------------------------------------------------------------------------------------------------------------------------------------------------
In the previous tutorials, we had the program wait for a few seconds before closing. 
In this application we're having the application wait until the user quits before closing.

So we'll have the application loop while the user has not quit. This loop that keeps running while the application is active 
is called the main loop, which is sometimes called the game loop. It is the core of any game application.
-------------------------------------------------------------------------------------------------------------------------------------------------
*/

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}
/*
--------------------------------------------------------------------------------------------------------------------------------------------------
At the top of our main loop we have our event loop. What this does is keep processing the event queue until it is empty.

When you press a key, move the mouse, or touch a touch screen you put events onto the event queue.

The event queue will then store them in the order the events occurred waiting for you to process them. 
When you want to find out what events occured so you can process them, you poll the event queue 
to get the most recent event by calling SDL_PollEvent. 
What SDL_PollEvent does is take the most recent event from the event queue and puts the data from the event into 
the SDL_Event we passed into the function. 

SDL_PollEvent will keep taking events off the queue until it is empty. When the queue is empty, SDL_PollEvent will return 0. 
So what this piece of code does is keep polling events off the event queue until it's empty. 
If an event from the event queue is an SDL_QUIT event (which is the event when the user Xs out the window), 
we set the quit flag to true so we can exit the application. 
-------------------------------------------------------------------------------------------------------------------------------------------------
*/
				//Apply the image
				SDL_BlitSurface( gXOut, NULL, gScreenSurface, NULL );
			
				//Update the surface
				SDL_UpdateWindowSurface( gWindow );
			}
/*
-------------------------------------------------------------------------------------------------------------------------------------------------
After we're done processing the events for our frame, we draw to the screen and update it (as discussed in the previous tutorial). 
If the quit flag was set to true, the application will exit at the end of the loop. 
If it is still false it will keep going until the user Xs out the window.
-------------------------------------------------------------------------------------------------------------------------------------------------
*/
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

// ===================================================================================================================================================

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
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

	//Load splash image
	gXOut = SDL_LoadBMP( /*03_event_driven_programming*/"x.bmp" );
	if( gXOut == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "03_event_driven_programming/x.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface( gXOut );
	gXOut = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}