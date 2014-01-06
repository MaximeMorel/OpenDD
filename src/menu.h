//
//


#ifndef MENU_H
#define MENU_H


// system includes
#include <stdio.h>

// user includes
#include "player.h"
#include "render.h"
#include "game.h"


#define MENU_PAGE               0
#define MENU_SELECTION          1
#define MENU_NB_ITEMS           2
#define MENU_ACTIVE             3


#define MENU_ROOT		1
#define MENU_OPTIONS		2
#define MENU_GRAPHICS   	3
#define MENU_CONTROLS	        4
#define MENU_SOUND		5
#define MENU_NETWORK		6
#define MENU_SCORES		7
#define MENU_GAME               8


void menuInit( SRender* r );


void menuFree( SRender* r );


void menuDraw( SRender* r, SPlayer* pl, SGame* g );
   

void menuRoot( SRender* r, SPlayer* pl );


void menuOptions( SRender* r, SPlayer* pl );


void menuGraphics( SRender* r, SPlayer* pl );


void menuControls( SRender* r, SPlayer* pl );


void menuSound( SRender* r, SPlayer* pl );


void menuNetwork( SRender* r, SPlayer* pl );


void menuScores( SRender* r, SPlayer* pl );


void menuGame( SRender* r, SPlayer* pl, SGame* g );


void menuDrawBox( SRender* r, const char* text, GLfloat top_x, GLfloat top_y, GLfloat w, GLfloat h, GLfloat size, bool active );


#endif // MENU_H
