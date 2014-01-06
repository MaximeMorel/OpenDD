//
//


//! \file debug.h
//! \brief debug.h
//!
//! Some functions for debugging.
//!


#ifndef DEBUG_H
#define DEBUG_H


// system includes
#include <stdio.h>

// user includes
#include "player.h"
#include "vector.h"
#include "global_vars.h"


void debug();


//! \fn void debugMenu( SPlayer* pl )
//! \brief debug in the menu.
//!
void debugMenu( SPlayer* pl );


//! \fn void debugGame( SPlayer* pl )
//! \brief debug ingame.
//!
void debugGame( SPlayer* pl );


#endif // DEBUG_H
