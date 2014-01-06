// MOREL Maxime
//


//! \file config.c
//! \brief Config for a player.
//!
//!


#include "config.h"


void configInit( SConfig* c )
{
  printf( "Load default config.\n" );

  c->particle_nb = 256;
  c->tire_nb = 256;
  c->smoke_nb = 256;

  c->cl_wireframe = false;
  //c->cl_fullscreen = false;
  //c->cl_invert_y_axis = true;
  //c->noclip = false;
  c->grab_mouse = true;
  //c->cl_resx = 640;
  //c->cl_resy = 480;
  //c->cl_resx_full = 1024;
  //c->cl_resy_full = 768;
  //c->resx = 640;
  //c->resy = 480;
  //c->cl_bpp = 24;

  c->res[0] = 640;
  c->res[1] = 480;
  c->res[2] = 640;
  c->res[3] = 480;
  c->res[4] = 1024;
  c->res[5] = 768;
  c->res[6] = 24;
  c->res[7] = 0;
  c->res[8] = 0;

  //c->cl_mouse_x_sensib = 0.5;
  //c->cl_mouse_y_sensib = 0.5;
  c->cl_mouse_pitch = -200;
  c->cl_mouse_yaw = 200;
  c->cl_fov = FOV_NORMAL;
  //c->sdl_disp_flags = 0;

  strcpy( c->data_path, "../data" );
  //strcpy( c->data_path, "data" );
  
  c->keyconf[KEY_FORWARD] = SDLK_UP;
  c->keyconf[KEY_BACKWARD] = SDLK_DOWN;
  c->keyconf[KEY_LEFT] = SDLK_LEFT;
  c->keyconf[KEY_RIGHT] = SDLK_RIGHT;
  c->keyconf[KEY_HANDBRAKE] = SDLK_SPACE;
  c->keyconf[KEY_FASTSTEER] = SDLK_z;
  c->keyconf[KEY_REAR_VIEW] = SDLK_v;
  c->keyconf[KEY_HORN] = SDLK_g;
  c->keyconf[KEY_CAM_FORWARD] = SDLK_u;
  c->keyconf[KEY_CAM_BACKWARD] = SDLK_j;
  c->keyconf[KEY_CAM_LEFT] = SDLK_h;
  c->keyconf[KEY_CAM_RIGHT] = SDLK_k;
  c->keyconf[KEY_CAM_UP] = SDLK_o;
  c->keyconf[KEY_CAM_DOWN] = SDLK_l;
  c->keyconf[KEY_CAM_RESET] = SDLK_i;
  c->keyconf[KEY_CAM_MODE] = SDLK_c;
  c->keyconf[KEY_CAM_FOLLOW_NEXT] = SDLK_n;
  c->keyconf[KEY_CAM_FOLLOW_PREV] = SDLK_b;
  c->keyconf[KEY_CAM_FOLLOW_PLAYER] = SDLK_x;
  c->keyconf[KEY_PAUSE] = SDLK_p;
  c->keyconf[KEY_SCREENSHOT] =  SDLK_F9;
  c->keyconf[KEY_CONSOLE] = SDLK_KP4;
  c->keyconf[KEY_CAR_RESET] = SDLK_r;
  
  c->keyconf[KEY_FORWARD2] = SDLK_UNKNOWN;
  c->keyconf[KEY_BACKWARD2] = SDLK_UNKNOWN;
  c->keyconf[KEY_LEFT2] = SDLK_UNKNOWN;
  c->keyconf[KEY_RIGHT2] = SDLK_UNKNOWN;
  c->keyconf[KEY_HANDBRAKE2] = SDLK_UNKNOWN;
  c->keyconf[KEY_FASTSTEER2] = SDLK_UNKNOWN;
  c->keyconf[KEY_REAR_VIEW2] = SDLK_UNKNOWN;
  c->keyconf[KEY_HORN2] = SDLK_UNKNOWN;
  c->keyconf[KEY_CAM_FORWARD2] = SDLK_UNKNOWN;
  c->keyconf[KEY_CAM_BACKWARD2] = SDLK_UNKNOWN;
  c->keyconf[KEY_CAM_LEFT2] = SDLK_UNKNOWN;
  c->keyconf[KEY_CAM_RIGHT2] = SDLK_UNKNOWN;
  c->keyconf[KEY_CAM_UP2] = SDLK_UNKNOWN;
  c->keyconf[KEY_CAM_DOWN2] = SDLK_UNKNOWN;
  c->keyconf[KEY_CAM_RESET2] = SDLK_UNKNOWN;
  c->keyconf[KEY_CAM_MODE2] = SDLK_UNKNOWN;
  c->keyconf[KEY_CAM_FOLLOW_NEXT2] = SDLK_UNKNOWN;
  c->keyconf[KEY_CAM_FOLLOW_PREV2] = SDLK_UNKNOWN;
  c->keyconf[KEY_CAM_FOLLOW_PLAYER2] = SDLK_UNKNOWN;
  c->keyconf[KEY_PAUSE2] = SDLK_UNKNOWN;
  c->keyconf[KEY_SCREENSHOT2] =  SDLK_UNKNOWN;
  c->keyconf[KEY_CONSOLE2] = SDLK_UNKNOWN;
  c->keyconf[KEY_CAR_RESET2] = SDLK_UNKNOWN;

  printf( "Load user config.\n" );
  configLoad( c );

  configCheckConflicts( c );
  
  printf( "Struct config : OK.\n" );
}


void configFree( SConfig* c )
{
  configSave( c );

  printf( "Struct config : free.\n" );
}


void configLoad( SConfig* c )
{
  char var[64];

  FILE* file = fopen( "data/config.cfg", "rb" );
  if( file == NULL )
    {
      printf( "Error loading config!!!\n" );
      return;
    }

  while( !feof( file ) )
    {
      fscanf( file, "%s", var );

      if( strcmp( var, "key_forward" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_FORWARD] );
	}
      else
      if( strcmp( var, "key_backward" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_BACKWARD] );
	}
      else
      if( strcmp( var, "key_left" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_LEFT] );
	}
      else
      if( strcmp( var, "key_right" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_RIGHT] );
	}
      else
      if( strcmp( var, "key_handbrake" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_HANDBRAKE] );
	}
      else
      if( strcmp( var, "key_faststeer" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_FASTSTEER] );
	}
      else
      if( strcmp( var, "key_rearview" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_REAR_VIEW] );
	}
      else
      if( strcmp( var, "key_horn" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_HORN] );
	}
      else
      if( strcmp( var, "key_cam_forward" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_FORWARD] );
	}
      else
      if( strcmp( var, "key_cam_backward" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_BACKWARD] );
	}
      else
      if( strcmp( var, "key_cam_left" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_LEFT] );
	}
      else
      if( strcmp( var, "key_cam_right" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_RIGHT] );
	}
      else
      if( strcmp( var, "key_cam_up" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_UP] );
	}
      else
      if( strcmp( var, "key_cam_down" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_DOWN] );
	}
      else
      if( strcmp( var, "key_cam_reset" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_RESET] );
	}
      else
      if( strcmp( var, "key_cam_mode" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_MODE] );
	}
      else
      if( strcmp( var, "key_cam_follow_prev" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_FOLLOW_PREV] );
	}
      else
      if( strcmp( var, "key_cam_follow_next" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_FOLLOW_NEXT] );
	}
      else
      if( strcmp( var, "key_cam_follow_player" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_FOLLOW_PLAYER] );
	}
      else
      if( strcmp( var, "key_pause" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_PAUSE] );
	}
      else
      if( strcmp( var, "key_console" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CONSOLE] );
	}
      else
      if( strcmp( var, "key_screenshot" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_SCREENSHOT] );
	}
      else
      if( strcmp( var, "key_car_reset" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAR_RESET] );
	}
      else
      if( strcmp( var, "key_forward2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_FORWARD2] );
	}
      else
      if( strcmp( var, "key_backward2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_BACKWARD2] );
	}
      else
      if( strcmp( var, "key_left2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_LEFT2] );
	}
      else
      if( strcmp( var, "key_right2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_RIGHT2] );
	}
      else
      if( strcmp( var, "key_handbrake2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_HANDBRAKE2] );
	}
      else
      if( strcmp( var, "key_faststeer2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_FASTSTEER2] );
	}
      else
      if( strcmp( var, "key_rearview2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_REAR_VIEW2] );
	}
      else
      if( strcmp( var, "key_horn2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_HORN2] );
	}
      else
      if( strcmp( var, "key_cam_forward2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_FORWARD2] );
	}
      else
      if( strcmp( var, "key_cam_backward2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_BACKWARD2] );
	}
      else
      if( strcmp( var, "key_cam_left2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_LEFT2] );
	}
      else
      if( strcmp( var, "key_cam_right2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_RIGHT2] );
	}
      else
      if( strcmp( var, "key_cam_up2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_UP2] );
	}
      else
      if( strcmp( var, "key_cam_down2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_DOWN2] );
	}
      else
      if( strcmp( var, "key_cam_reset2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_RESET2] );
	}
      else
      if( strcmp( var, "key_cam_mode2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_MODE2] );
	}
      else
      if( strcmp( var, "key_cam_follow_prev2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_FOLLOW_PREV2] );
	}
      else
      if( strcmp( var, "key_cam_follow_next2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_FOLLOW_NEXT2] );
	}
      else
      if( strcmp( var, "key_cam_follow_player2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAM_FOLLOW_PLAYER2] );
	}
      else
      if( strcmp( var, "key_pause2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_PAUSE2] );
	}
      else
      if( strcmp( var, "key_console2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CONSOLE2] );
	}
      else
      if( strcmp( var, "key_screenshot2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_SCREENSHOT2] );
	}
      else
      if( strcmp( var, "key_car_reset2" ) == 0 )
	{
	  fscanf( file, "%d", (int*)&c->keyconf[KEY_CAR_RESET2] );
	}
      else
      if( strcmp( var, "wireframe" ) == 0 )
	{
	  int i;
	  fscanf( file, "%d", &i );
	  c->cl_wireframe = i;
	}
      else
      if( strcmp( var, "res_x_fullscreen" ) == 0 )
	{
	  fscanf( file, "%d", &c->res[4] );
	}
      else
      if( strcmp( var, "res_y_fullscreen" ) == 0 )
	{
	  fscanf( file, "%d", &c->res[5] );
	}
      else
      if( strcmp( var, "res_x_window" ) == 0 )
	{
	  fscanf( file, "%d", &c->res[2] );
	}
      else
      if( strcmp( var, "res_y_window" ) == 0 )
	{
	  fscanf( file, "%d", &c->res[3] );
	}
      else
      if( strcmp( var, "bpp" ) == 0 )
	{
	  fscanf( file, "%d", &c->res[6] );
	}
      else
      if( strcmp( var, "fullscreen" ) == 0 )
	{
	  fscanf( file, "%d", &c->res[8] );
	}
      else
      if( strcmp( var, "particle_nb" ) == 0 )
	{
	  fscanf( file, "%d", &c->particle_nb );
	}
      else
      if( strcmp( var, "tire_nb" ) == 0 )
	{
	  fscanf( file, "%d", &c->tire_nb );
	}
      else
      if( strcmp( var, "smoke_nb" ) == 0 )
	{
	  fscanf( file, "%d", &c->smoke_nb );
	}
    }

  fclose( file );
}


void configSave( SConfig* c )
{
  FILE* file = fopen( "data/config.cfg", "wb" );
  if( file == NULL )
    {
      printf( "Error saving config!!!\n" );
      return;
    }

  fprintf( file, "key_forward %d\n", c->keyconf[KEY_FORWARD] );
  fprintf( file, "key_backward %d\n", c->keyconf[KEY_BACKWARD] );
  fprintf( file, "key_left %d\n", c->keyconf[KEY_LEFT] );
  fprintf( file, "key_right %d\n", c->keyconf[KEY_RIGHT] );
  fprintf( file, "key_handbrake %d\n", c->keyconf[KEY_HANDBRAKE] );
  fprintf( file, "key_faststeer %d\n", c->keyconf[KEY_FASTSTEER] );
  fprintf( file, "key_rearview %d\n", c->keyconf[KEY_REAR_VIEW] );
  fprintf( file, "key_horn %d\n", c->keyconf[KEY_HORN] );
  fprintf( file, "key_cam_forward %d\n", c->keyconf[KEY_CAM_FORWARD] );
  fprintf( file, "key_cam_backward %d\n", c->keyconf[KEY_CAM_BACKWARD] );
  fprintf( file, "key_cam_left %d\n", c->keyconf[KEY_CAM_LEFT] );
  fprintf( file, "key_cam_right %d\n", c->keyconf[KEY_CAM_RIGHT] );
  fprintf( file, "key_cam_up %d\n", c->keyconf[KEY_CAM_UP] );
  fprintf( file, "key_cam_down %d\n", c->keyconf[KEY_CAM_DOWN] );
  fprintf( file, "key_cam_reset %d\n", c->keyconf[KEY_CAM_RESET] );
  fprintf( file, "key_cam_mode %d\n", c->keyconf[KEY_CAM_MODE] );
  fprintf( file, "key_cam_follow_prev %d\n", c->keyconf[KEY_CAM_FOLLOW_PREV] );
  fprintf( file, "key_cam_follow_next %d\n", c->keyconf[KEY_CAM_FOLLOW_NEXT] );
  fprintf( file, "key_cam_follow_player %d\n", c->keyconf[KEY_CAM_FOLLOW_PLAYER] );
  fprintf( file, "key_pause %d\n", c->keyconf[KEY_PAUSE] );
  fprintf( file, "key_console %d\n", c->keyconf[KEY_CONSOLE] );
  fprintf( file, "key_screenshot %d\n", c->keyconf[KEY_SCREENSHOT] );
  fprintf( file, "key_car_reset %d\n", c->keyconf[KEY_CAR_RESET] );

  
  fprintf( file, "key_forward2 %d\n", c->keyconf[KEY_FORWARD2] );
  fprintf( file, "key_backward2 %d\n", c->keyconf[KEY_BACKWARD2] );
  fprintf( file, "key_left2 %d\n", c->keyconf[KEY_LEFT2] );
  fprintf( file, "key_right2 %d\n", c->keyconf[KEY_RIGHT2] );
  fprintf( file, "key_handbrake2 %d\n", c->keyconf[KEY_HANDBRAKE2] );
  fprintf( file, "key_faststeer2 %d\n", c->keyconf[KEY_FASTSTEER2] );
  fprintf( file, "key_rearview2 %d\n", c->keyconf[KEY_REAR_VIEW2] );
  fprintf( file, "key_horn2 %d\n", c->keyconf[KEY_HORN2] );
  fprintf( file, "key_cam_forward2 %d\n", c->keyconf[KEY_CAM_FORWARD2] );
  fprintf( file, "key_cam_backward2 %d\n", c->keyconf[KEY_CAM_BACKWARD2] );
  fprintf( file, "key_cam_left2 %d\n", c->keyconf[KEY_CAM_LEFT2] );
  fprintf( file, "key_cam_right2 %d\n", c->keyconf[KEY_CAM_RIGHT2] );
  fprintf( file, "key_cam_up2 %d\n", c->keyconf[KEY_CAM_UP2] );
  fprintf( file, "key_cam_down2 %d\n", c->keyconf[KEY_CAM_DOWN2] );
  fprintf( file, "key_cam_reset2 %d\n", c->keyconf[KEY_CAM_RESET2] );
  fprintf( file, "key_cam_mode2 %d\n", c->keyconf[KEY_CAM_MODE2] );
  fprintf( file, "key_cam_follow_prev2 %d\n", c->keyconf[KEY_CAM_FOLLOW_PREV2] );
  fprintf( file, "key_cam_follow_next2 %d\n", c->keyconf[KEY_CAM_FOLLOW_NEXT2] );
  fprintf( file, "key_cam_follow_player2 %d\n", c->keyconf[KEY_CAM_FOLLOW_PLAYER2] );
  fprintf( file, "key_pause2 %d\n", c->keyconf[KEY_PAUSE2] );
  fprintf( file, "key_console2 %d\n", c->keyconf[KEY_CONSOLE2] );
  fprintf( file, "key_screenshot2 %d\n", c->keyconf[KEY_SCREENSHOT2] );
  fprintf( file, "key_car_reset2 %d\n", c->keyconf[KEY_CAR_RESET2] );

  fprintf( file, "wireframe %d\n", c->cl_wireframe );
  fprintf( file, "res_x_fullscreen %d\n", c->res[4] );
  fprintf( file, "res_y_fullscreen %d\n", c->res[5] );
  fprintf( file, "res_x_window %d\n", c->res[2] );
  fprintf( file, "res_y_window %d\n", c->res[3] );
  fprintf( file, "bpp %d\n", c->res[6] );
  fprintf( file, "fullscreen %d\n", c->res[8] );
  fprintf( file, "particle_nb %d\n", c->particle_nb );
  fprintf( file, "tire_nb %d\n", c->tire_nb );
  fprintf( file, "smoke_nb %d\n", c->smoke_nb );

  fclose( file );
}


void configCheckConflicts( SConfig* c )
{
  int i, j;

  for( j = 0; j < 46; j++ )
    {
      for( i = j+1; i < 46; i++ )
	{
	  if( c->keyconf[i] == c->keyconf[j] )
	    {
	      if( c->keyconf[i] != SDLK_UNKNOWN )
		{
		  printf( "Config : conflict keys %d & %d!!!\n", i, j );
		}
	    }
	}
    }  
}
