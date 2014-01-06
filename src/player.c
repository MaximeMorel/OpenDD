//
//


//! \file player.c
//! \brief player.c
//!
//!


#include "player.h"


void playerInit( SPlayer* pl, int type, int mode )
{
  pl->id = 0;
  pl->name[0] = '\0';

  pl->key_press = 0;
  pl->mouse_press = 0;
  pl->other_press = 0;
  pl->state = MENU;
  pl->score[0] = 0;
  pl->score[1] = 0;
  
  //pl->exit = false;

  pl->conf = NULL;

  //pl->camera = NULL;

  if( type == PL_AI )
    {
      pl->ai = malloc( sizeof(SPlayerAI) );
      aiInit( pl->ai, mode );
      pl->ai->car = &pl->car;
    }
  else
    {
      pl->ai = NULL;
    }
  
  carInit( &pl->car );
  
  printf( "Struct player : OK.\n" );
}


void playerFree( SPlayer* pl )
{
  if( pl->ai != NULL )
    {
      aiFree( pl->ai );
      free( pl->ai );
      pl->ai = NULL;
    }

  carFree( &pl->car );

  printf ( "Struct player %d : free.\n", pl->id );
}


SPlayer* playersInit( SPlayer* pl, SConfig* conf, int mode, int nb_cars )
{
  int i;
  // players array
  //SPlayer pl[20];
  //nb_car = 2;
  //g_nb_car = &nb_car;
  if( pl != NULL )
    {
      for( i = 0; i < *g_nb_car; i++ )
	{
	  playerFree( &pl[i] );
	}
      free( pl );
    }

  pl = malloc( nb_cars * sizeof( SPlayer ) );
  if( pl == NULL )
    {
      printf( "malloc error !!!\n" );
    }
  //printf( "malloc pl %p\n", pl );

  // human player  
  playerInit( &pl[0], PL_HUMAN, mode );
  pl[0].id = 0;
  pl[0].car.id = pl[0].id;
  strcpy( pl[0].name, "popux" );
  pl[0].conf = conf;
  //pl[0].camera = &cam;
  //cam->player = &pl[0]; // outside
  if( nb_cars >= 1 )
    {
      pl[0].next = &pl[1]; 
      pl[0].car.next = &pl[0].next->car;
    }
  carSetPos( &pl[0].car, 80, 0, M_PI );

  // ai player
  for( i = 1; i < nb_cars; i++ )
    {      
      playerInit( &pl[i], PL_AI, mode );
      pl[i].id = i;
      pl[i].car.id = pl[i].id;
      carSetPos( &pl[i].car, 80*cosf((M_PIx2 * i)/ nb_cars), 80*sinf((M_PIx2 * i)/ nb_cars), M_PI+(M_PIx2 * i)/ nb_cars );
      // stcuk test
      //carSetPos( &pl[i].car, 0, 0, M_PI+(M_PIx2 * i)/ *g_nb_car );

      if( i <= nb_cars-2 )
	{
	  pl[i].next = &pl[i+1];
	  pl[i].car.next = &pl[i].next->car;
	}
      else
	{
	  pl[i].next = &pl[0];
	  pl[i].car.next = &pl[i].next->car;
	}
    }
  
  // circle linked list test
  /*for( i = 0; i < nb_cars; i++ )
  {
    printf( "car %d:%p  car next:%p\n", i, &pl[i].car, pl[i].car.next );
  }

  for( i = 0; i < nb_cars; i++ )
  {
    printf( "player %d:%p  player next:%p\n", i, &pl[i], pl[i].next );
    }*/

  return pl;
}


void playersLoadTexture( SPlayer* pl, STexture* t )
{
  int i;

  for( i = 0; i < *g_nb_car; i++ )
    {
      pl[i].car.pTexture = t;
      carLoadTexture( &pl[i].car );
    }
}


void playerSetPos( SPlayer* pl, float x, float y, float z, float angle_x, float angle_y )
{
  
}


void playerAddAI( SPlayer* pl,float x, float z, float angle )
{
  //playerInit( pl );
  //carSetPos( &pl->car, x, z, angle );
}


void playerUpdatePos( SPlayer* pl )
{
  
} 


void toggleGod( SPlayer* pl )
{
    
}


void toggleMenu( SPlayer* pl )
{
  // menu off
  if ( pl->state & MENU )
    {
      pl->state ^= MENU;
      //SDL_ShowCursor ( 0 );
    }
  // menu on
  else
    {
      pl->state |= MENU;
      //SDL_ShowCursor ( 1 );
    }
}


void toggleConsole( SPlayer* pl )
{
  // console off
  if( pl->state & CONSOLE )
    {
      pl->state ^= CONSOLE;
    }
  // console on
  else
    {
      pl->state |= CONSOLE;
    }
}


void togglePause( SPlayer* pl )
{
  // pause off
  if( pl->state & PAUSE )
    {
      pl->state ^= PAUSE;
    }
  // pause on
  else
    {
      pl->state |= PAUSE;
    }
}
