//
//


//! \file game.c
//! \brief game loop functions
//!
//! Includes loop functions ingame and in the menu.
//!


#ifndef GAME_H
#define GAME_H


// system includes
#include <SDL/SDL.h>

// user includes
//#include "input.h"
#include "player.h"
//#include "render.h"
#include "sound.h"
#include "global_vars.h"


#define GAME_NORMAL                1
#define GAME_TOTAL_DESTRUCTION     2


//!
//!
typedef struct
{
  char name[32];
  int score1;
  int score2;
  int time;
} SScore;


//! \struct SGame
//!
//! \param mode define the game mode.
//! \param nb_cars[3] nb_cars[0] = actual total nb of cars.\n
//! nb_cars[1] = actual nb of cars alive.\n
//! nb_cars[2] = total nb of cars after a game restart.\n
typedef struct
{
  int mode;

  int nb_cars[3];

  SScore* scores;

  SFps fps;
} SGame;


#include "render.h"
#include "input.h"


void gameInit( SGame* g );


void gameFree( SGame* g );


//! \fn void gameSetMode( SGame* g, int mode );
//! \brief set game mode : normal or total destruction
void gameSetMode( SGame* g, int mode );


//! \fn void gameSetNbCars( SGame* g, int n );
//! \brief set nb of cars
void gameSetNbCars( SGame* g, int n );


//! \fn void gameLoop( SDL_Event* event, SPlayer* pl, SRender* render, SSound* sound, SFps* fps )
//! \brief main game loop
//!
//! main steps :\n
//!  - fps count \n
//!  - check input \n
//!  - update cars positions \n
//!  - check positions \n
//!  - update camera position \n
//!  - draw everything \n
//!  - calculate delta time.
SPlayer* gameLoop( SGame* g, SDL_Event* event, SLevel* l, SPlayer* pl, SRender* render, SSound* sound );


//! \fn void menuLoop( SDL_Event* event, SPlayer* pl, SRender* render, SSound* sound, SFps* fps )
//! \brief menu loop
//!
//! The game loops in this function while in menu mode.
void menuLoop( SGame* g, SDL_Event* event, SLevel* l, SPlayer* pl, SRender* render, SSound* sound );


//! \fn void pauseLoop( SDL_Event* event, SPlayer* pl, SRender* render, SSound* sound, SFps* fps )
//! \brief pause loop
//!
//! The game loops in this function while in pause mode.
void pauseLoop( SGame* g, SDL_Event* event, SLevel* l, SPlayer* pl, SRender* render, SSound* sound );


//! \fn void gameCarsAlive( SGame* g, SCar* c );
//! \brief count alive cars
void gameCarsAlive( SGame* g, SCar* c );


//! \fn SPlayer* gameRestart( SGame* g, SPlayer* pl, SConfig* conf, SCamera* cam, STexture* t );
//! \brief restart game
SPlayer* gameRestart( SGame* g, SPlayer* pl, SConfig* conf, SCamera* cam, STexture* t );


#endif // GAME_H
