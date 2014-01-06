//
//


#include "menu.h"


void menuInit( SRender* r )
{
  r->menu[0] = MENU_ROOT;
  r->menu[1] = 0;
  r->menu[2] = 0;
  r->menu[3] = 0;

  printf( "Struct menu : OK.\n" );
}


void menuFree( SRender* r )
{
  printf( "Struct menu : free.\n" );
}


void menuDraw( SRender* r, SPlayer* pl, SGame* g )
{
  
  clearScreen();
  orthoMode( pl->conf->res );  
  glDisable( GL_DEPTH_TEST );
  glDisable( GL_LIGHTING );
  glDisable( GL_TEXTURE_2D );

  screenFilter( r, pl );
  restoreScreen( r, pl );

  glLineWidth( 3.0f );

  alphaModeOn();  
  glEnable( GL_TEXTURE_2D );
  
  switch( r->menu[MENU_PAGE] )
    {
    case 0:      
      break;
      
    case MENU_ROOT:
      menuRoot( r, pl );
      break;
      
    case MENU_OPTIONS:
      menuOptions( r, pl );
      break;
      
    case MENU_GRAPHICS:
      menuGraphics( r, pl );
      break;
      
    case MENU_CONTROLS:
      menuControls( r, pl );
      break;

    case MENU_NETWORK:
      menuNetwork( r, pl );
      break;

    case MENU_SCORES:
      menuScores( r, pl );
      break;
			
    case MENU_SOUND:
      menuSound( r, pl );
      break;

    case MENU_GAME:
      menuGame( r, pl, g );
      break;
    }

  glLineWidth( 1.0f );
  alphaModeOff();
  swapBuffers();
}


void menuRoot( SRender* r, SPlayer* pl )
{
  r->menu[MENU_NB_ITEMS] = 6;

  menuDrawBox( r, "MENU", 0.2f*pl->conf->res[0], 0.95f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.035f*pl->conf->res[0],
	       0 );

  menuDrawBox( r, "RESUME", 0.2f*pl->conf->res[0], 0.82*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==0?1:0 );

  menuDrawBox( r, "RESTART", 0.2f*pl->conf->res[0], 0.69*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==1?1:0 );
  
  menuDrawBox( r, "OPTIONS", 0.2f*pl->conf->res[0], 0.56f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==2?1:0 );

  menuDrawBox( r, "NETWORK", 0.2f*pl->conf->res[0], 0.43f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==3?1:0 );

  menuDrawBox( r, "SCORES", 0.2f*pl->conf->res[0], 0.30f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==4?1:0 );

  menuDrawBox( r, "QUIT", 0.2f*pl->conf->res[0], 0.17f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==5?1:0 );

  if( r->menu[MENU_ACTIVE] == 1 )
    {
      switch( r->menu[MENU_SELECTION] )
	{
	case 0 :
	  pl->state &= ~MENU;
	  break;
	  
	case 1 :
	  pl->state |= RESTART;
	  pl->state &= ~MENU;
	  break;

	case 2 :
	  r->menu[MENU_PAGE] = MENU_OPTIONS;
	  break;

	case 3 :
	  r->menu[MENU_PAGE] = MENU_NETWORK;
	  break;

	case 4 :
	  r->menu[MENU_PAGE] = MENU_SCORES;
	  break;
	  
	case 5 :
	  pl->state |= QUIT;
	  pl->state &= ~MENU;
	  break;

	default :
	  break;	  
	}

      r->menu[MENU_ACTIVE] = 0;
      r->menu[MENU_SELECTION] = 0;
    }
}


void menuOptions( SRender* r, SPlayer* pl )
{
  r->menu[MENU_NB_ITEMS] = 5;

  menuDrawBox( r, "OPTIONS", 0.2f*pl->conf->res[0], 0.95f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.035f*pl->conf->res[0],
	       0 );

  menuDrawBox( r, "GAME", 0.2f*pl->conf->res[0], 0.80f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==0?1:0 );

  menuDrawBox( r, "CONTROLS", 0.2f*pl->conf->res[0], 0.65f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==1?1:0 );
  
  menuDrawBox( r, "VIDEO", 0.2f*pl->conf->res[0], 0.50f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==2?1:0 );

  menuDrawBox( r, "SOUND", 0.2f*pl->conf->res[0], 0.35f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==3?1:0 );

  menuDrawBox( r, "BACK", 0.2f*pl->conf->res[0], 0.20f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==4?1:0 );

  if( r->menu[MENU_ACTIVE] == 1 )
    {
      switch( r->menu[MENU_SELECTION] )
	{
	case 0 :
	  r->menu[MENU_PAGE] = MENU_GAME;
	  break;

	case 1 :
	  r->menu[MENU_PAGE] = MENU_CONTROLS;
	  break;
	  
	case 2 :
	  r->menu[MENU_PAGE] = MENU_GRAPHICS;
	  break;
	  
	case 3 :
	  r->menu[MENU_PAGE] = MENU_SOUND;
	  break;

	case 4 :
	  r->menu[MENU_PAGE] = MENU_ROOT;
	  break;

	default :
	  break;	  
	}

      r->menu[MENU_ACTIVE] = 0;
      r->menu[MENU_SELECTION] = 0;
    }
}


void menuGraphics( SRender* r, SPlayer* pl )
{
  r->menu[MENU_NB_ITEMS] = 2;

  menuDrawBox( r, "VIDEO", 0.2f*pl->conf->res[0], 0.95f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.035f*pl->conf->res[0],
	       0 );
  
  menuDrawBox( r, "TOGGLE FULLSCREEN", 0.2f*pl->conf->res[0], 0.75f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==0?1:0 );
  
  menuDrawBox( r, "BACK", 0.2f*pl->conf->res[0], 0.35f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==1?1:0 );

  if( r->menu[MENU_ACTIVE] == 1 )
    {
      switch( r->menu[MENU_SELECTION] )
	{
	case 0 :
	  if( r->screen != NULL )
	    {
	      free( r->screen );
	      r->screen = NULL;
	    }
	  toggleFullscreen( pl->conf->res );	  
	  break;

	case 1 :	  
	  r->menu[MENU_PAGE] = MENU_OPTIONS;
	  break;

	default :
	  break;	  
	}

      r->menu[MENU_ACTIVE] = 0;
      r->menu[MENU_SELECTION] = 0;
    }
}


void menuControls( SRender* r, SPlayer* pl )
{
  r->menu[MENU_NB_ITEMS] = 1;

  menuDrawBox( r, "CONTROLS", 0.2f*pl->conf->res[0], 0.95f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.035f*pl->conf->res[0],
	       0 );

  menuDrawBox( r, "Maybe", 0.2f*pl->conf->res[0], 0.65f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       0 );

  menuDrawBox( r, "BACK", 0.2f*pl->conf->res[0], 0.35f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==0?1:0 );

  if( r->menu[MENU_ACTIVE] == 1 )
    {
      switch( r->menu[MENU_SELECTION] )
	{
	case 0 :
	  r->menu[MENU_PAGE] = MENU_OPTIONS;
	  break;

	default :
	  break;	  
	}

      r->menu[MENU_ACTIVE] = 0;
      r->menu[MENU_SELECTION] = 0;
    }
}


void menuNetwork( SRender* r, SPlayer* pl )
{
  r->menu[MENU_NB_ITEMS] = 1;

  menuDrawBox( r, "NETWORK", 0.2f*pl->conf->res[0], 0.95f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.035f*pl->conf->res[0],
	       0 );

  menuDrawBox( r, "Maybe", 0.2f*pl->conf->res[0], 0.65f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       0 );

  menuDrawBox( r, "BACK", 0.2f*pl->conf->res[0], 0.35f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==0?1:0 );

  if( r->menu[MENU_ACTIVE] == 1 )
    {
      switch( r->menu[MENU_SELECTION] )
	{
	case 0 :
	  r->menu[MENU_PAGE] = MENU_ROOT;
	  break;

	default :
	  break;	  
	}

      r->menu[MENU_ACTIVE] = 0;
      r->menu[MENU_SELECTION] = 0;
    }
}


void menuScores( SRender* r, SPlayer* pl )
{
  r->menu[MENU_NB_ITEMS] = 1;

  menuDrawBox( r, "SCORES", 0.2f*pl->conf->res[0], 0.95f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.035f*pl->conf->res[0],
	       0 );

  menuDrawBox( r, "Maybe", 0.2f*pl->conf->res[0], 0.65f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       0 );

  menuDrawBox( r, "BACK", 0.2f*pl->conf->res[0], 0.35f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==0?1:0 );

  if( r->menu[MENU_ACTIVE] == 1 )
    {
      switch( r->menu[MENU_SELECTION] )
	{
	case 0 :
	  r->menu[MENU_PAGE] = MENU_ROOT;
	  break;

	default :
	  break;	  
	}

      r->menu[MENU_ACTIVE] = 0;
      r->menu[MENU_SELECTION] = 0;
    }
}


void menuSound( SRender* r, SPlayer* pl )
{
  r->menu[MENU_NB_ITEMS] = 1;

  menuDrawBox( r, "SOUND", 0.2f*pl->conf->res[0], 0.95f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.035f*pl->conf->res[0],
	       0 );

  menuDrawBox( r, "Maybe", 0.2f*pl->conf->res[0], 0.65f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       0 );

  menuDrawBox( r, "BACK", 0.2f*pl->conf->res[0], 0.35f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==0?1:0 );

  if( r->menu[MENU_ACTIVE] == 1 )
    {
      switch( r->menu[MENU_SELECTION] )
	{
	case 0 :
	  r->menu[MENU_PAGE] = MENU_OPTIONS;
	  break;

	default :
	  break;	  
	}

      r->menu[MENU_ACTIVE] = 0;
      r->menu[MENU_SELECTION] = 0;
    }
}


void menuGame( SRender* r, SPlayer* pl, SGame* g )
{
  r->menu[MENU_NB_ITEMS] = 6;

  menuDrawBox( r, "GAME OPTIONS", 0.2f*pl->conf->res[0], 0.95f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.035f*pl->conf->res[0],
	       0 );

  menuDrawBox( r, "CARS", 0.2f*pl->conf->res[0], 0.75f*pl->conf->res[1], 
	       0.15f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       0 );

  menuDrawBox( r, " 2", 0.40f*pl->conf->res[0], 0.75f*pl->conf->res[1], 
	       0.10f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==0?1:0 );

  menuDrawBox( r, "10", 0.55f*pl->conf->res[0], 0.75f*pl->conf->res[1], 
	       0.10f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==1?1:0 );

  menuDrawBox( r, "20", 0.70f*pl->conf->res[0], 0.75f*pl->conf->res[1], 
	       0.10f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==2?1:0 );

  menuDrawBox( r, "GAME MODE", 0.2f*pl->conf->res[0], 0.55f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       0 );

  menuDrawBox( r, "NORMAL", 0.2f*pl->conf->res[0], 0.43f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==3?1:0 );

  menuDrawBox( r, "TOTAL DESTRUCTION", 0.2f*pl->conf->res[0], 0.31f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==4?1:0 );

  menuDrawBox( r, "BACK", 0.2f*pl->conf->res[0], 0.15f*pl->conf->res[1], 
	       0.6f*pl->conf->res[0], 0.1f*pl->conf->res[1], 0.025f*pl->conf->res[0],
	       r->menu[MENU_SELECTION]==5?1:0 );

  if( r->menu[MENU_ACTIVE] == 1 )
    {
      switch( r->menu[MENU_SELECTION] )
	{
	case 0 :
	  gameSetNbCars( g, 2 );
	  r->menu[MENU_SELECTION] = 5;
	  break;

	case 1 :
	  gameSetNbCars( g, 10 );
	  r->menu[MENU_SELECTION] = 5;
	  break;

	case 2 :
	  gameSetNbCars( g, 20 );
	  r->menu[MENU_SELECTION] = 5;
	  break;

	case 3 :
	  gameSetMode( g, GAME_NORMAL );
	  r->menu[MENU_SELECTION] = 5;
	  break;

	case 4 :
	  gameSetMode( g, GAME_TOTAL_DESTRUCTION );
	  r->menu[MENU_SELECTION] = 5;
	  break;
	  
	case 5 :
	  r->menu[MENU_PAGE] = MENU_OPTIONS;
	  r->menu[MENU_SELECTION] = 0;
	  break;

	default :
	  break;	  
	}

      r->menu[MENU_ACTIVE] = 0;
      //r->menu[MENU_SELECTION] = 0;
    }
}


void menuDrawBox( SRender* r, const char* text, GLfloat top_x, GLfloat top_y, GLfloat w, GLfloat h, GLfloat size, bool active )
{
  if( active )
    {
      glColor4f( 0.0f, 0.0f, 0.0f, 0.75f );
    }
  else
    {
      glColor4f( 1.0f, 0.0f, 0.0f, 0.75f );
    }

  glDisable( GL_TEXTURE_2D );
  glBegin( GL_LINE_LOOP );

  glVertex2f ( top_x , top_y );
  glVertex2f ( top_x , top_y - h );
  glVertex2f ( top_x + w , top_y - h );
  glVertex2f ( top_x + w , top_y );

  glEnd();
  glEnable( GL_TEXTURE_2D );

  glPrintf( &r->font, text, -size*(strlen(text)/2)+((top_x)+w/2), top_y-h, size );
}
