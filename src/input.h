// MOREL Maxime
//


//! \file input.h
//!  \brief Look for input events.


#ifndef INPUT_H
#define INPUT_H


// system includes

// user includes
#include "player.h"
#include "car.h"
#include "menu.h"
#include "render.h"
#include "camera.h"
#include "screenshot.h"
#include "debug.h"


//! \fn void inputMenu( SDL_Event* event, SPlayer* pl, int* menu );
//! \brief events check in menu
void inputMenu( SDL_Event* event, SPlayer* pl, int* menu );


//! \fn void inputGame( SDL_Event* event, SPlayer* pl, SCamera* cam );
//! \brief events check in game
void inputGame( SDL_Event* event, SPlayer* pl, SCamera* cam );


void inputConsole( SDL_Event* event, SPlayer* pl );


//! \fn void inputPause( SDL_Event* event, SPlayer* pl );
//! \brief events check in pause
void inputPause( SDL_Event* event, SPlayer* pl );

//ingame
void keyboardDown( const SDL_KeyboardEvent* event, SPlayer* pl, SCamera* cam );
void keyboardUp( const SDL_KeyboardEvent* event, SPlayer* pl, SCamera* cam );
void mouseMotion( const SDL_MouseMotionEvent* event, SPlayer* pl, SCamera* cam );
void mouseButtonDown( const SDL_MouseButtonEvent* event, SPlayer* pl );
void mouseButtonUp( const SDL_MouseButtonEvent* event, SPlayer* pl );
	
// menu
void keyboardDownMenu( const SDL_KeyboardEvent* event, int* menu );
void keyboardUpMenu( const SDL_KeyboardEvent* event, int* menu );
void mouseMotionMenu( const SDL_MouseMotionEvent* event, int* menu );
void mouseButtonDownMenu( const SDL_MouseButtonEvent* event, int* menu );
void mouseButtonUpMenu( const SDL_MouseButtonEvent* event, int* menu );


#endif // INPUT_H
