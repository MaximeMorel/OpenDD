//
//


//! \file camera.h
//! \brief Handle the camera for the local human player.


#ifndef CAMERA_H
#define CAMERA_H


// system includes
#include <stdio.h>

// user includes
#include "vector.h"
#include "global_vars.h"
#include "math_ext.h"
#include "player.h"


// camera modes
#define CAM_MODE1     0  // chase lock mode
#define CAM_MODE2     1  // interior mode
#define CAM_MODE3     2  // free mode
#define CAM_MODE4     3  // chase free mode

// camera key states
#define CAM_FORWARD   1
#define CAM_BACKWARD  2
#define CAM_LEFT      4
#define CAM_RIGHT     8
#define CAM_UP        16
#define CAM_DOWN      32
#define CAM_REAR      64


// other stuff
#define CAM_SPD       15.0f
#define CAM_MAX_SPD   30.0f


//! \struct SCamera
//! \brief SCamera contains postion, speed, view angle, camera type...
//!
//! \param pos This is a vector which contains the absolute position of the camera.
//! \param v This is a vector which contains the movement of the camera.
//! \param look This is a normalized vector which contains the view angle.
//! \param mode This is an integer which contains the camera mode.
//! \param rx The view angle in radians in plane x,z.
//! \param ry The view angle in radians in plane (cos(rx),sin(rx)),y.
//! \param cos_rx The cosine of rx.
//! \param sin_rx The sine of rx.
//! \param cos_ry The cosine of ry.
//! \param sin_ry The sine of ry.
//! \param distance The distance of the camera from the car in chase mode.
//! \param height The height of the camera from the floor in chase mode.
//! \param key_press Keyboard events for the camera.
//! \param speed The speed. Can be < 0.
typedef struct _SCamera
{
  Vector3f pos;
  Vector3f pos_norm;
  Vector3f pos_offset;
  Vector3f v;
  Vector3f look;
  Vector3f tmp;

  float rx, ry;

  float speed;

  float cos_rx, sin_rx;
  float cos_ry,sin_ry;

  float distance;
  float height;
  float angle;
  float offset;
  float lazy_cam;

  int key_press;

  int mode;

  void (*cameraUpdateMode)( struct _SCamera* c );

  SPlayer* player;
} SCamera;


//! \fn void cameraInit( SCamera* c )
//! \brief Init the \a SCamera structure.
void cameraInit( SCamera* c );


//! \fn void cameraFree( SCamera* c )
//! \brief Free the \a SCamera structure.
void cameraFree( SCamera* c );


//! \fn void cameraUpdate( SCamera* c )
//! \brief Update all \a SCamera attributes each frame.
void cameraUpdate( SCamera* c );


//! \fn void cameraUpdatePos( SCamera* c )
//! \brief Update position of the camera.
void cameraUpdatePos( SCamera* c );


//! \fn void cameraCheckSpeed( SCamera* c )
//! \brief Check the speed of the camera.
void cameraCheckSpeed( SCamera* c );


//! \fn void cameraUpdate( SCamera* c )
//! \brief Update all \a SCamera attributes each frame for camera mode 1.
//!
//! Chase locked mode.
void cameraUpdateMode1( SCamera* c );


//! \fn void cameraUpdate( SCamera* c )
//! \brief Update all \a SCamera attributes each frame for camera mode 2.
//!
//! Interior mode.
void cameraUpdateMode2( SCamera* c );


//! \fn void cameraUpdate( SCamera* c )
//! \brief Update all \a SCamera attributes each frame for camera mode 3.
//!
//! Free mode.
void cameraUpdateMode3( SCamera* c );


//! \fn void cameraUpdate( SCamera* c )
//! \brief Update all \a SCamera attributes each frame for camera mode 4.
//!
//! Chase free mode.
void cameraUpdateMode4( SCamera* c );


//! \fn void cameraUpdateVars( SCamera* c )
//! \brief Calculate camera mode independant vars.
//! This is just to make cameraUpdate cleaner.
void cameraUpdateVars( SCamera* c );


// press on
inline void camForwardOn( SCamera* c );
inline void camBackwardOn( SCamera* c );
inline void camLeftOn( SCamera* c );
inline void camRightOn( SCamera* c );
inline void camUpOn( SCamera* c );
inline void camDownOn( SCamera* c );
inline void camRearOn( SCamera* c );


// press off
inline void camForwardOff( SCamera* c );
inline void camBackwardOff( SCamera* c );
inline void camLeftOff( SCamera* c );
inline void camRightOff( SCamera* c );
inline void camUpOff( SCamera* c );
inline void camDownOff( SCamera* c );
inline void camRearOff( SCamera* c );


void camReset( SCamera* c );

void camChangeView( SCamera* c );

void camFollowPrev( SCamera* c );

void camFollowNext( SCamera* c );

void camFollowPlayer( SCamera* c, SPlayer* pl );


#endif // CAMERA_H
