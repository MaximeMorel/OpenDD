//
//


//! \file hud.h
//! \brief onscreen info drawing


#ifndef HUD_H
#define HUD_H


// system includes
#include <GL/gl.h>

// user includes
#include "player.h"
#include "config.h"
#include "render.h"
#include "game.h"
#include "global_vars.h"


//! \fn void hudDraw( SRender* r, SPlayer* p, SGame* g );
//! \brief print all onscreen info
void hudDraw( SRender* r, SPlayer* p, SGame* g );


void hudCarState( SRender* r, SPlayer* p );


void hudScore( SRender* r, SPlayer* p );


void hudSpeed( SRender* r, SPlayer* p );


void hudFps( SRender* r, SPlayer* p );


void hudTimer( SRender* r, SPlayer* p );


void hudCarDead( SRender* r, SGame* g, SPlayer* p );


void hudGameStatus( SRender* r, SGame* g, SPlayer* p );


void hudDebug( SRender* r, SPlayer* p );


#endif // HUD_H
