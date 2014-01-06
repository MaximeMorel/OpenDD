//
//


//! \file game.c
//! \brief game loop functions
//!
//! Includes loop functions ingame and in the menu.
//!


#include "game.h"


void gameInit( SGame* g )
{
  g->nb_cars[0] = 0;
  g->nb_cars[1] = 0;

  g->scores = NULL;

  fpsInit( &g->fps );

  printf( "Struct game : OK.\n" );
}



void gameFree( SGame* g )
{
  fpsFree( &g->fps );

  printf( "Struct game : free.\n" );
}


void gameSetMode( SGame* g, int mode )
{
  if( mode == GAME_NORMAL || mode == GAME_TOTAL_DESTRUCTION )
    {
      g->mode = mode;
    }
}


void gameSetNbCars( SGame* g, int n )
{
  g->nb_cars[2] = n;
}


SPlayer* gameLoop( SGame* g, SDL_Event* event, SLevel* l, SPlayer* pl, SRender* render, SSound* sound )
{
  Vector3f tmp, color;//, null_vector;
  static float* pos;
  static int i,j;

  g->fps.time_start = SDL_GetTicks();

  setVector3f( color, 1.0f, 1.0f, 0.0f );

  while( !(pl->state & QUIT) )
    {
      fpsCount( &g->fps );
      fpsWait( &g->fps );

      // sound test
      //oggPlay( &sound->oggsound[0], "data/sound/music/1.ogg" );

      // check input.
      inputGame( event, pl, render->cam );

      // update all car position and check wall collisions.
      for( i = 0; i < *g_nb_car; i++ )
	{
	  // ai update
	  if( pl[i].ai && !(pl[i].car.state & CAR_DEAD) )
	    {
	      if( pl[i].ai->timeout < g_fps->time_now )
		{
		  aiUpdate( pl[i].ai, l );
		  pl[i].ai->timeout = g_fps->time_now + 100;
		}
	    }

	  carUpdate( &pl[i].car );

	  if( (pos=checkCollisionWorld( &pl[i].car, l )) != NULL )
	    {
	      //Vector3f color;
	      //setVector3f( color, 1.0f, 1.0f, 0.0f );

	      pl[i].car.collision++;

	      // generate particles
	      particleAdd( &render->particle, pos, pl[i].car.v, color );

	      // set damage
	      carSetDamage( &pl[i].car );
	    }

	  // horn test
	  /*if( pl[i].car.state & CAR_HORN )
	    {
	    oggPlay( &sound->oggsound[1], "data/sound/music/horn.ogg" );
	    }*/	  
	}

      // real score ( rotation ) count
      for( i = 0; i < *g_nb_car; i++ )
	{
	  if( pl[i].car.score_timeout > g_fps->time_now )
	    {
	      carCheckScore( &pl[i].car );
	    }
	}
  
      // tire traces
      if( render->tire.timeout < g_fps->time_now )
	{
	  for( i = 0; i < *g_nb_car; i++ )
	    {
	      if( pl[i].car.adherence > 0.9f && pl[i].car.speed > 2.0f*CAR_THRESHOLD )
		{
		  carGetWheelPos( &pl[i].car );
		  tireTraceAdd( &render->tire, pl[i].car.wheel_pos );
		}
	    }
	  render->tire.timeout = g_fps->time_now + 50;
	}
      
      // smoke
      if( render->smoke.timeout < g_fps->time_now )
	{
	  for( i = 0; i < *g_nb_car; i++ )
	    {	 
	      if( ((pl[i].car.state & CAR_DAMAGED)&& !(pl[i].car.state & CAR_DEAD)) || (pl[i].car.adherence > 0.98f && pl[i].car.speed > 10.0f*CAR_THRESHOLD) )
		{
		  smokeAdd( &render->smoke, pl[i].car.pos, 0.9f );
		}
	      
	      // dead smoke
	      if( pl[i].car.state & CAR_DEAD )
		{
		  setVector3fv( tmp, pl[i].car.dir_vect );
		  //mulVector3f( tmp, 2.0f );
		  sumVector3fv( tmp, pl[i].car.pos );
		  smokeAdd( &render->smoke, tmp, 0.1f );
		}
	    }
	  render->smoke.timeout = g_fps->time_now + 100;
	}
	      
      // collision check between cars.
      // must do all possibilities.
      for( j = 0; j < *g_nb_car; j++ )
	{
	  for( i = j+1; i < *g_nb_car; i++)
	    {
	      if( (pos=checkCollisionCar( &pl[j].car, &pl[i].car )) != NULL )
		{
		  //Vector3f color;
		  //setVector3f( color, 1.0f, 1.0f, 0.0f );
		  
		  //printf("pos=%p\n", pos );
		  pl[j].car.collision++;
		  pl[i].car.collision++;

		  // generate particles
		  particleAdd( &render->particle, pos, pl[i].car.v, color );
		  particleAdd( &render->particle, pos, pl[j].car.v, color );

		  // score
		  if( !(pl[i].car.state & CAR_DEAD) && !(pl[i].car.state & CAR_DEAD) )
		    {
		      pl[i].score[0] += (int)(10.0f*pl[i].car.hit_power);
		      pl[j].score[0] += (int)(10.0f*pl[j].car.hit_power);
		    }

		  // set damage
		  carSetDamage( &pl[i].car );
		  carSetDamage( &pl[j].car );
		}
	    }
	}

      // save last good position : without collisions.
      for( j = 0; j < *g_nb_car; j++ )
	{
	  if( pl[j].car.collision == 0 )
	    {
	      //printf( "car %d pos saved.\n", j );
	      carSavePos( &pl[j].car );
	    }
	  else
	    {
	      //printf( "car %d pos not saved.\n", j );
	    }
	}

      
      // update camera position.
      cameraUpdate( render->cam );

      //printf( "rotation : %f\n", pl[0].car.rotation );
      //printf( "adherence : %f\n", pl[0].car.adherence );
      //printf( "speed=%f  accel=%f  sens=%d  state=%d  frame=%d  collision=%d\n", 
      //pl[0].car.speed, pl[0].car.accel, pl[0].car.sens, pl[0].car.state, g_fps->frame, pl[0].car.collision );

      // particle update
      particleUpdate( &render->particle );

      // smoke update
      smokeUpdate( &render->smoke );

      // sound update
      if( sound->timeout < g_fps->time_now )
	{
	  //soundUpdate( sound );
	  sound->timeout = g_fps->time_now + 50;
	}
         
      // render everything
      if( render->timeout < g_fps->time_now )
	{
	  gameCarsAlive(g, &pl[0].car );
	  display( render , pl, g, l );
	  render->timeout = g_fps->time_now + 16;
	}

      /*if( g_fps->frame == 0)
	setTitle( render, g_fps->frame_old );*/
      
      if( pl->state & MENU )
	{
	  menuLoop( g, event, l, pl, render, sound );
	}

      if( pl->state & PAUSE )
	{
	  pauseLoop( g, event, l, pl, render, sound );
	}

      if( pl->state & RESTART )
	{
	  pl = gameRestart( g, pl, pl->conf, render->cam, &render->texture );
	  pl[0].state = 0;	  
	}
      
      fpsEndframe( &g->fps );
    }
  return pl;
}



void menuLoop( SGame* g, SDL_Event* event, SLevel* l, SPlayer* pl, SRender* render, SSound* sound )
{
  copyScreen( render, pl );

  fpsSaveTime( &g->fps );

  if( pl->conf->grab_mouse )
    {
      toggleGrabmouse( &pl->conf->grab_mouse );
    }
  //orthoMode( pl->conf->res );
  //alphaModeOn();
  
  pl->state |= MENU;
  
  while( pl->state & MENU )
    {
      fpsCount( &g->fps );
      fpsWait( &g->fps );

      // check input
      inputMenu( event, pl, render->menu );

      // sound update
      if( sound->timeout < g_fps->time_now )
	{
	  //soundUpdate( sound );
	  sound->timeout = g_fps->time_now + 50;
	}

      // render everything
      if( render->timeout < g_fps->time_now )
	{
	  if( render->screen == NULL )
	    {
	      //printf( "re menu\n" );
	      display( render, pl, g, l );display( render, pl, g, l );
	      copyScreen( render, pl );
	    }
	  menuDraw( render , pl, g );
	  render->timeout = g_fps->time_now + 75;
	}
      
      fpsEndframe( &g->fps );
    }
  alphaModeOff();
  //perspectiveMode( pl->conf->cl_fov, pl->conf->res[0]/pl->conf->res[1] );
  
  //setFov( pl->conf->cl_fov  );
  render->menu[MENU_PAGE] = MENU_ROOT;
  toggleGrabmouse( &pl->conf->grab_mouse );
  fpsRestoreTime( &g->fps );
}


void pauseLoop( SGame* g, SDL_Event* event, SLevel* l, SPlayer* pl, SRender* render, SSound* sound )
{
  fpsSaveTime( &g->fps );
      
  pl->state |= PAUSE;
  
  while( pl->state & PAUSE )
    {
      fpsCount( &g->fps );
      fpsWait( &g->fps );
      
      // check input
      inputGame( event, pl, render->cam );

      // update camera position.
      cameraUpdate( render->cam );

      // sound update
      if( sound->timeout < g_fps->time_now )
	{
	  //soundUpdate( sound );
	  sound->timeout = g_fps->time_now + 50;
	}

      // render everything
      if( render->timeout < g_fps->time_now )
	{
	  display( render, pl, g, l );
	  render->timeout = g_fps->time_now + 15;
	}
      
      fpsEndframe( &g->fps );
    }

  fpsRestoreTime( &g->fps );
}


void gameCarsAlive( SGame* g, SCar* c )
{
  int i;
  SCar* car = c;

  g->nb_cars[1] = g->nb_cars[0];

  for( i = 0; i < g->nb_cars[0]; i++ )
    {
      if( car->state & CAR_DEAD )
	{
	  g->nb_cars[1]--;
	}
      car = car->next;
    }
}


SPlayer* gameRestart( SGame* g, SPlayer* pl, SConfig* conf, SCamera* cam, STexture* t )
{
  printf( "Game retarting.\n" );
  
  pl = playersInit( pl, pl->conf, g->mode, g->nb_cars[2] );
  g->nb_cars[0] = g->nb_cars[2];
  cam->player = &pl[0];
  playersLoadTexture( pl, t );
  fpsResetTime( &g->fps );
  
  pl->state &= ~RESTART;

  printf( "Game restarted.\n" );

  return pl;
}
