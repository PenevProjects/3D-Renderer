// This is the main SDL include file
#include <SDL/SDL.h>
// iostream is so we can output error messages to console
#include <iostream>

#include "MCG_GFX_Lib.h"


namespace MCG
{
	SDL_Renderer *_renderer;
	SDL_Window *_window;
	glm::ivec2 _winSize;
	unsigned int _lastTime;
}


bool MCG::Init( glm::ivec2 windowSize )
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		// Something went very wrong in initialisation, all we can do is exit
		std::cout << "MCG Framework: Whoops! Something went very wrong, cannot initialise SDL :(" << std::endl;
		return false;
	}

	_winSize = windowSize;
	// Now we have got SDL initialised, we are ready to create a window!
	// These are some variables to help show you what the parameters are for this function
	// You can experiment with the numbers to see what they do
	int winPosX = 100;
	int winPosY = 100;
	_window = SDL_CreateWindow( "MCG GFX Framework",  // The first parameter is the window title
		winPosX, winPosY,
		_winSize.x, _winSize.y,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	// The last parameter lets us specify a number of options
	// Here, we tell SDL that we want the window to be shown and that it can be resized
	// You can learn more about SDL_CreateWindow here: https://wiki.libsdl.org/SDL_CreateWindow?highlight=%28\bCategoryVideo\b%29|%28CategoryEnum%29|%28CategoryStruct%29
	// The flags you can pass in for the last parameter are listed here: https://wiki.libsdl.org/SDL_WindowFlags

	// The SDL_CreateWindow function returns an SDL_Window
	// This is a structure which contains all the data about our window (size, position, etc)
	// We will also need this when we want to draw things to the window
	// This is therefore quite important we don't lose it!


	if( !_window )
	{
		// Something went very wrong in initialisation, all we can do is exit
		std::cout << "MCG Framework: Whoops! Something went very wrong, cannot create SDL window :(" << std::endl;
		return false;
	}



	// The SDL_Renderer is a structure that handles rendering
	// It will store all of SDL's internal rendering related settings
	// When we create it we tell it which SDL_Window we want it to render to
	// That renderer can only be used for this window
	// (yes, we can have multiple windows - feel free to have a play sometime)
	_renderer = SDL_CreateRenderer( _window, -1, 0 );


	if( !_renderer )
	{
		// Something went very wrong in initialisation, all we can do is exit
		std::cout << "MCG Framework: Whoops! Something went very wrong, cannot obtain SDL rendering context :(" << std::endl;
		return false;
	}



	_lastTime = SDL_GetTicks();

	return true;
}

void MCG::SetBackground( glm::ivec3 colour )
{
	// Set the colour for drawing
	SDL_SetRenderDrawColor( _renderer, colour.r, colour.g, colour.b, 255 );
	// Clear the entire screen to our selected colour
	SDL_RenderClear( _renderer );

}

void MCG::DrawPixel( glm::ivec2 position, glm::ivec3 colour )
{
	// Set the colour for drawing
	SDL_SetRenderDrawColor( _renderer, colour.r, colour.g, colour.b, 255 );
	// Draw our pixel
	SDL_RenderDrawPoint( _renderer, position.x, position.y );
}


bool MCG::ProcessFrame()
{
	// This tells the renderer to actually show its contents to the screen
	// This is specific to the SDL drawing commands. When we start with OpenGL we will need to use a different command here
	// This is to do with something called 'double buffering', where we have an off-screen buffer that we draw to and then swap once we finish (this function is the 'swap')
	SDL_RenderPresent( _renderer );


	SDL_Event incomingEvent;
	// SDL_PollEvent will check if there is an event in the queue
	// If there's nothing in the queue it won't sit and wait around for an event to come along (there are functions which do this, and that can be useful too!)
	// For an empty queue it will simply return 'false'
	// If there is an event, the function will return 'true' and it will fill the 'incomingEvent' we have given it as a parameter with the event data
	while( SDL_PollEvent( &incomingEvent ) )
	{
		// If we get in here, we have an event and need to figure out what to do with it
		// For now, we will just use a switch based on the event's type
		switch( incomingEvent.type )
		{
		case SDL_QUIT:
			// The event type is SDL_QUIT
			// This means we have been asked to quit - probably the user clicked on the 'x' at the top right corner of the window
			// To quit we need to set our 'go' bool to false so that we can escape out of the game loop
			return false;


		case SDL_KEYUP:
			// The event type is SDL_KEYUP
			// This means that the user has released a key
			// Let's figure out which key they pressed
			switch( incomingEvent.key.keysym.sym )
			{
				case SDLK_ESCAPE:
					return false;
			}


			// If you want to learn more about event handling and different SDL event types, see:
			// https://wiki.libsdl.org/SDL_Event
			// and also: https://wiki.libsdl.org/SDL_EventType
		}
	}





	// Update our world
	// We are going to work out the time between each frame now
	// First, find the current time
	// again, SDL_GetTicks() returns the time in milliseconds since SDL was initialised
	// We can use this as the current time
	unsigned int current = SDL_GetTicks();
	// Next, we want to work out the change in time between the previous frame and the current one
	// This is a 'delta' (used in physics to denote a change in something)
	// So we call it our 'deltaT' and I like to use an 's' to remind me that it's in seconds!
	// (To get it in seconds we need to divide by 1000 to convert from milliseconds)
	float deltaTs = (float)( current - _lastTime ) / 1000.0f;
	// Now that we've done this we can use the current time as the next frame's previous time
	_lastTime = current;


	// Limiter in case we're running really quick
	if( deltaTs < ( 1.0f / 60.0f ) )	// not sure how accurate the SDL_Delay function is..
	{
		SDL_Delay( (unsigned int)( ( ( 1.0f / 60.0f ) - deltaTs )*1000.0f ) );
	}


	return true;

}

void MCG::Cleanup()
{
	SDL_DestroyWindow( _window );
	SDL_Quit();
}


int MCG::ShowAndHold()
{
	// Show

	// This tells the renderer to actually show its contents to the screen
	// This is specific to the SDL drawing commands. When we start with OpenGL we will need to use a different command here
	// This is to do with something called 'double buffering', where we have an off-screen buffer that we draw to and then swap once we finish (this function is the 'swap')
	SDL_RenderPresent( _renderer );




	// Hold

	// We are now preparing for our main loop (also known as the 'game loop')
	// This loop will keep going round until we exit from our program by changing the bool 'go' to the value false
	// This loop is an important concept and forms the basis of most games you'll be writing
	// Within this loop we generally do the following things:
	//   * Check for input from the user (and do something about it!)
	//   * Update our world
	//   * Draw our world
	// We will come back to this in later lectures
	bool go = true;
	while( go )
	{

		// Here we are going to check for any input events
		// Basically when you press the keyboard or move the mouse, the parameters are stored as something called an 'event'
		// SDL has a queue of events
		// We need to check for each event and then do something about it (called 'event handling')
		// the SDL_Event is the datatype for the event
		SDL_Event incomingEvent;
		// SDL_WaitEvent will check if there is an event in the queue
		// If there's nothing in the queue it will sit and wait around for an event to come along (there are functions which don't wait which can be useful too!)
		// When there is an event, the function will fill the 'incomingEvent' we have given it as a parameter with the event data
		SDL_WaitEvent( &incomingEvent );
		switch( incomingEvent.type )
		{
		case SDL_QUIT:
			// The event type is SDL_QUIT
			// This means we have been asked to quit - probably the user clicked on the 'x' at the top right corner of the window
			// To quit we need to set our 'go' bool to false so that we can escape out of the game loop
			go = false;
			break;


		case SDL_KEYUP:
			// The event type is SDL_KEYUP
			// This means that the user has released a key
			// Let's figure out which key they pressed
			switch( incomingEvent.key.keysym.sym )
			{
			case SDLK_ESCAPE: // This is the escape key
				return 0;
			}

			// If you want to learn more about event handling and different SDL event types, see:
			// https://wiki.libsdl.org/SDL_Event
			// and also: https://wiki.libsdl.org/SDL_EventType
			// but don't worry, we'll be looking at handling user keyboard and mouse input soon
		}



	}

	// If we get outside the main game loop, it means our user has requested we exit

	Cleanup();
	return 0;
}

