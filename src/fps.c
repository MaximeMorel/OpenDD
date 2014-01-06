//
//


//! \file fps.c
//! \brief fps.c
//!
//!


#include "fps.h"


void fpsInit( SFps* f )
{
  f->time_start = 0;

  f->time_now = 0;
  f->time_old = 0;
  f->time_delta = 0;
  f->fps_timer = 0;
  f->frame = 0;
  f->frame_old = 0;
  f->fps_per_sec = 0;
  f->fps_per_frame = 0;
  f->fps_per_frame_old = 0;

  f->time_now_save = 0;
  f->time_old_save = 0;

  f->time_start_pause = 0;
  f->time_stop_pause = 0;
  
  printf ( "Struct fps : OK.\n" );
}


void fpsFree( SFps* f )
{
  printf( "Struct fps : free.\n" );
}

void fpsCount( SFps* f )
{
  f->frame_old = f->frame; 
  f->frame++;
  
  if( f->time_now - f->fps_timer >= 1000 )
    {
      f->fps_per_sec = f->frame;
      f->frame = 0;
      f->fps_timer = f->time_now;
    }
  
  f->fps = 1000.0f / f->time_delta;
  f->fps_per_frame = ( f->fps + f->fps_per_frame_old )/2;
  f->fps_per_frame_old = f->fps;
  
  
  f->time_now = SDL_GetTicks();
  f->time_delta = f->time_now - f->time_old;
  f->time = f->time_delta / 1000.0f;
}


void fpsWait( SFps* f )
{
  if( f->time_delta < MAX_FRAME_TIME )
    {
      SDL_Delay( MAX_FRAME_TIME - f->time_delta );    // frame limit
    }
}	


void fpsEndframe( SFps* f )
{
  f->time_old = f->time_now;
}


void fpsSaveTime( SFps* f )
{
  f->time_start_pause = SDL_GetTicks();
}


void fpsRestoreTime( SFps* f )
{
  f->time_start += SDL_GetTicks() - f->time_start_pause;
}


void fpsResetTime( SFps* f )
{
  f->time_start = SDL_GetTicks();
}


void fpsSleep( int delay )
{
  SDL_Delay( delay );
}
