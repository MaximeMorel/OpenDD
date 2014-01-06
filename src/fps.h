//
//


//! \file fps.h
//! \brief fps.h
//!
//! Fonctions related to time.
//!


#ifndef FPS_H
#define FPS_H


// system includes
#include <stdio.h>
#include <SDL/SDL.h>

// user includes

//! \def MAX_FRAME_TIME Maximum time in ms for a frame.*/
#define MAX_FRAME_TIME 25


//! \struct SFps
//! \brief fps and timer counter
//! \param time_delta Delta time of a frame in ms.
//! \param time Delta time of a frame in seconds.
//! \param frame Number of frames per seconds(integer).
//! \param frame_old Number of frames per seconds for last frame(integer).
//! \param fps Instant number of frame per seconds(float).
//! \param time_now Absolute time in ms of the begining of the frame.
//! \param time_old Absolute time in ms of the begining of the last frame.
typedef struct
{
  int time_start;

  int time_now;
  int time_old;
  int time_delta;
  int fps_timer;
  int frame, frame_old;
  int fps_per_sec;
  float fps;
  float fps_per_frame;
  float fps_per_frame_old;

  int time_now_save;
  int time_old_save;

  float time;

  int time_start_pause;
  int time_stop_pause;
} SFps;
	

//! \fn void fpsInit( SFps* f )
//! \brief Init the structure
//! 
//! Just put 0 into the vars.
//!
void fpsInit( SFps* f );


//! \fn void fpsFree( SFps* f )
//! \brief Do nothing.
//!
void fpsFree( SFps* f );


//! \fn inline void fpsCount( SFps* f )
//! \brief
//!
inline void fpsCount( SFps* f );


//! \fn inline void fpsWait( SFps* f )
//! \brief
//!
inline void fpsWait( SFps* f );


//! \fn inline void fpsEndframe( SFps* f )
//! \brief
//!
inline void fpsEndframe( SFps* f );


void fpsSaveTime( SFps* f );


void fpsRestoreTime( SFps* f );


void fpsResetTime( SFps* f );


void fpsSleep( int delay );


#endif // FPS_H
