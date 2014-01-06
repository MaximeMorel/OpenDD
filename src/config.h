// MOREL Maxime
//

//! \file config.h
//! \brief Config for a player.
//!


#ifndef CONFIG_H
#define CONFIG_H


//system includes
#include <stdio.h>
#include <SDL/SDL.h>

//user includes
#include "bool.h"


#define FOV_NORMAL         75
#define FOV_ZOOM           15

#define KEY_FORWARD             0
#define KEY_BACKWARD            1
#define KEY_LEFT                2
#define KEY_RIGHT               3
#define KEY_HANDBRAKE           4
#define KEY_FASTSTEER           5
#define KEY_REAR_VIEW           6
#define KEY_HORN                7
#define KEY_CAM_FORWARD         8
#define KEY_CAM_BACKWARD        9
#define KEY_CAM_LEFT            10
#define KEY_CAM_RIGHT           11
#define KEY_CAM_UP              12
#define KEY_CAM_DOWN            13
#define KEY_CAM_RESET           14
#define KEY_CAM_MODE            15
#define KEY_CAM_FOLLOW_NEXT     16
#define KEY_CAM_FOLLOW_PREV     17
#define KEY_CAM_FOLLOW_PLAYER   18
#define KEY_PAUSE               19
#define KEY_SCREENSHOT          20
#define KEY_CONSOLE             21
#define KEY_CAR_RESET           22

#define KEY_FORWARD2            23
#define KEY_BACKWARD2           24
#define KEY_LEFT2               25
#define KEY_RIGHT2              26
#define KEY_HANDBRAKE2          27
#define KEY_FASTSTEER2          28
#define KEY_REAR_VIEW2          29
#define KEY_HORN2               30
#define KEY_CAM_FORWARD2        31
#define KEY_CAM_BACKWARD2       32
#define KEY_CAM_LEFT2           33
#define KEY_CAM_RIGHT2          34
#define KEY_CAM_UP2             35
#define KEY_CAM_DOWN2           36
#define KEY_CAM_RESET2          37
#define KEY_CAM_MODE2           38
#define KEY_CAM_FOLLOW_NEXT2    39
#define KEY_CAM_FOLLOW_PREV2    40
#define KEY_CAM_FOLLOW_PLAYER2  41
#define KEY_PAUSE2              42
#define KEY_SCREENSHOT2         43
#define KEY_CONSOLE2            44
#define KEY_CAR_RESET2          45



//! \struct SConfig
//! \brief config for a player.
//!
//! Contains the config for a player.
//!
//! \param res array containing :
//! \t - actual x,y res.
//! \t - x,y window res.
//! \t - x,y fullscreen res.
//! \t - bpp.
//! \t - sdl flags.
//! \t - fullscreen bool. ( -1=no, 1=yes );
//!
typedef struct
{
  bool cl_wireframe;
  //bool cl_fullscreen;
  //bool cl_invert_y_axis;
  bool grab_mouse;
  //int cl_resx;
  //int cl_resy;
  //int cl_resx_full;
  //int cl_resy_full;
  //int resx;
  //int resy;
  //int cl_bpp;
  //int sdl_disp_flags;
  int res[2+2+2+1+1+1];

  int particle_nb;
  int tire_nb;
  int smoke_nb;

  int cl_fov;
  int fov_current;
  float cl_mouse_x_sensib;
  float cl_mouse_y_sensib;
  float cl_mouse_pitch;
  float cl_mouse_yaw;
  char data_path[256];
  SDLKey keyconf[50];
} SConfig;


//! \fn extern void configInit( SConfig* c )
//! \brief Inits the \a SConfig structure.\n
//! Loads the default config.
//!
void configInit( SConfig* c );


//! \fn extern void configFree( SConfig* c )
//! \brief Free the \a SConfig structure.
//!
void configFree( SConfig* c );


//! \fn extern void configLoad( SConfig* c )
//! \brief Loads config from a file. TODO
//!
void configLoad( SConfig* c );


void configSave( SConfig* c );


void configCheckConflicts( SConfig* c );


#endif // CONFIG_H
