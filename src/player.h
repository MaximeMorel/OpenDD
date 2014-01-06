//
//


//! \file player.h
//! \brief player.h
//!
//!


#ifndef PLAYER_H
#define PLAYER_H


// system includes
#include <stdio.h>
#include <math.h>

// user includes
#include "config.h"
#include "fps.h"
#include "car.h"
#include "vector.h"
#include "texture.h"
//#include "camera.h"
#include "math_ext.h"
#include "ai_player.h"


// player type
#define PL_HUMAN 0
#define PL_AI    1

// key_press
#define KEYPRESS_FORWARD    1
#define KEYPRESS_BACKWARD   2
#define KEYPRESS_LEFT       4
#define KEYPRESS_RIGHT 	    8
#define KEYPRESS_FASTSTEER  16
#define KEYPRESS_HANDBRAKE  32

// mouse_press
#define MOUSEPRESS_LEFT     1
#define MOUSEPRESS_RIGHT    2
#define MOUSEPRESS_MIDDLE   4

// client_state
#define IDLE    0
#define MOVE    1
#define RUN     2
#define PAUSE   4
#define MENU    8
#define CONSOLE 16
#define RESTART 32
#define QUIT    64


//! \struct SPlayer
//! \brief Player structure.
//!
//! Contains camera info, player state, key info...
//! 
//! \parame id id of the player
//! \param score[2] Score of the player
//! \param car The car of the player
//! \param conf player's config
//! \param ai AI struct if computer player
typedef struct _SPlayer
{  
  int id;
  char name[32];
  int key_press, mouse_press, other_press, state;
  //bool exit;
  int score[2];
  SCar car; // every player has a car
  SConfig* conf; // only human players have a config
  //SCamera* camera; // only human players have a camera
  SPlayerAI* ai; // only ai players have a AI struct

  struct _SPlayer* next;
} SPlayer;


//#include "camera.h"
//#include "render.h"


extern void playerInit( SPlayer* pl, int type, int mode );
extern void playerFree( SPlayer* pl );


//! \fn SPlayer* playersInit( SPlayer* pl, SConfig* conf, int mode, int nb_cars );
//! \brief Init all the players
SPlayer* playersInit( SPlayer* pl, SConfig* conf, int mode, int nb_cars );


//! \fn void playersLoadTexture( SPlayer* pl, STexture* t );
//! \brief Load player's texture.
void playersLoadTexture( SPlayer* pl, STexture* t );


//! \fn void playerSetPos( SPlayer* pl, float x, float y, float z, float angle_x, float angle_y )
//! \brief Set player pos (camera)
//!
void playerSetPos( SPlayer* pl, float x, float y, float z, float angle_x, float angle_y );


//! \fn void playerUpdatePos( SPlayer* pl )
//! \brief Update player pos (camera)
//!
void playerUpdatePos( SPlayer* pl );
//void player_update_pos_noclip( SPlayer* pl );


void playerAddAI( SPlayer* pl,float x, float z, float angle );


// toggle
void toggleNoclip( SPlayer* pl );
void toggleGod( SPlayer* pl );
void toggleMenu( SPlayer* pl );
void toggleConsole( SPlayer* pl );
void togglePause( SPlayer* pl );


#endif // PLAYER_H
