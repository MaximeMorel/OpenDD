//
//


//! \file main.h
//! \brief main.h
//!
//! Includes and inits almost everything.
//!


#ifndef MAIN_H
#define MAIN_H


//system includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>

//user includes
#include "bool.h"
#include "game.h"
#include "camera.h"
#include "car.h"
#include "player.h"
#include "config.h"
#include "fps.h"
#include "render.h"
#include "version.h"
#include "math_ext.h"
#include "global_vars.h"
#include "sound.h"


//! \fn bool sdlInit()
//! \brief Init SDl for video.
//! \return true if there is no error, else false.
//!
//! Must do it in before opengl init.
//!
bool sdlInit();


//! \fn void cmdline( int argc, char **argv )
//! \brief Command line parser. TODO
//!
void cmdline( int argc, char **argv );


//! \fn int quit( int code )
//! \brief Exit the app.
//! \param code exit code.
//! \return the exit \a code.
//!
int quit( int code );


#endif // MAIN_H
