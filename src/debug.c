//
//


//! \file debug.c
//! \brief debug.c
//!
//! Some functions for debugging.
//!


#include "debug.h"


void debug()
{
}


void debugMenu( SPlayer* pl )
{
  printf( "menu\n" );
}


void debugGame( SPlayer* pl )
{
  //printf( "fps : %f \n", pl->pl_fps->fps );
  //printf( "keypress : %d\n", pl->key_press );
  //printf( "car state : %d\n", pl->car.state );
  //printf( "px : %f \t py : %f \t pz : %f \n", pl->px, pl->py, pl->pz );
  //printf( "vx : %f \t vy : %f \t vz : %f \n", pl->vx, pl->vy, pl->vz );
  //printf( "rx : %f \t cos_rx : %f \t sin_rx : %f \n", pl->rx, pl->cos_rx, pl->sin_rx );
  //printf( "ry : %f \t cos_ry : %f \t sin_ry : %f \n", pl->ry, pl->cos_ry, pl->sin_ry );
  //printf( "keypress : %d\n", pl->key_press );
  printf( "car state : %d\n", pl->car.state );
  //printf( "car px : %f \t car pz : %f \n", pl->car.pos_x, pl->car.pos_z );
  printf("car pos:%f,%f\n",pl->car.pos[0],pl->car.pos[2]);
  printf( "car speed : %f \t accel : %f \t rpm : %f\n", pl->car.speed, \
	  pl->car.accel, pl->car.rpm );
  printf( "car accel_x : %f \t accel_z : %f \n", pl->car.a[0], pl->car.a[2] );
  printf( "sens : %d\n", pl->car.sens );
  //printf( "car vx : %f \t car vz : %f \n", pl->car.vx, pl->car.vz );
  //printf( "car dir : %f \t car cos_dir : %f \t car sin_dir : %f \n", pl->car.dir, pl->car.cos_dir, pl->car.sin_dir );
  //printf( "wheel : %f \t car time : %f \n", pl->car.wheel_angle, pl->car.time );
  //printf( "cam dist : %f \n", 
  //	  module2f( pl->px_norm - pl->car.pos_x, pl->pz_norm - pl->car.pos_z) );
  //printf( "cam : %d \n", pl->camera );
  //printf( "cam press : %d\n", pl->camera->key_press );
  printf( "fps time: %f\n", g_fps->time );

  printf( "\n" );
}
