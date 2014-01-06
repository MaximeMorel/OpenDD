//
//


//! \file car.h
//! \brief Car module
//!
//! Structure and functions for car.
//! Functions for keypress, to set,update car attributes


#ifndef CAR_H
#define CAR_H


// system includes
#include <GL/gl.h>
#include <stdio.h>
#include <math.h>

// user includes
#include "fps.h"
//#include "wheel.h"
#include "bool.h"
#include "model.h"
#include "vector.h"
#include "math_ext.h"
#include "global_vars.h"
//#include "physics.h"
#include "texture.h"
#include "opengl_error.h"


//#define CAR_SPD 10.0f
//#define SPD 1.0f
#define CAR_ACCEL_SPD 25.0f
#define CAR_MAX_SPD 100.0f
#define CAR_MAX_ACCEL 20.0f
#define CAR_MAX_TURN 0.25f
#define CAR_THRESHOLD 1.0f


// car state
#define CAR_IDLE        0
#define CAR_ACCEL       1
#define CAR_BRAKE       2
#define CAR_TURN_LEFT   4
#define CAR_TURN_RIGHT  8
#define CAR_HANDBRAKE   16
#define CAR_FASTSTEER   32
#define CAR_REVERSE     64
#define CAR_HORN        128
#define CAR_DAMAGED     256
#define CAR_DEAD        512


//! \struct SCar
//! \brief Car structure
//!
//! \param dir_vect Is a unit vector, containing cos(dir), 0, sin(dir)
//! \param wheel_vect Is a unit vector containing cos(wheel_angle), 0, sin(wheel_angle)
//! \param wheel_vect_abs Is a unit vector containing cos(wheel_angle_abs), 0, sin(wheel_angle_abs)
//! \param dim[2] Contain car half lenght and half width.
//! \param pos Car position
//! \param v Speed vector of the car
//! \param a Accel vector
typedef struct _SCar
{
  int id;
  Vector3f pos;
  Vector4f pos_old;
  //float pos_x, pos_z; // deprec
  //float pos_x_old, pos_z_old; // deprec
  float speed; //speed_x, speed_z; // deprec
  float acceleration;
  Vector3f v;
  //float vx, vz, vx_old, vz_old, 
  //  acc, accel, accel_x, accel_z, wheel_angle, cos_wheel, sin_wheel, 
  //  dir, cos_dir, sin_dir, rpm, time, adherence_factor, cos_wheel_angle, sin_wheel_angle;
  float accel, rpm, wheel_angle, dir, adherence_factor;
  float wheel_angle_abs;
  Vector3f a;
  Vector3f dir_vect;
  Vector3f wheel_vect;
  Vector3f wheel_vect_abs;
  Vector2f tmp1,tmp2;
  float corners[8];
  float side[4];
  float wheel_pos[18];
  //float wheel_pos_old[8];
  //bool reverse;
  float dim[2];
  int state, gear;
  int sens;
  int new_sens;
  int collision;
  int hit_point;
  float hit_power;
  float rotation;
  float adherence;
  float fast_steer;
  float wheel_rotation;
  float roll;
  float pitch;
  float damage[12];
  float mass;
  unsigned int score_timeout;
  GLuint texture;
  //SWheel wheel_fl, wheel_fr, wheel_rl, wheel_rr;
  STexture* pTexture;
  SModel car_model;

  struct _SCar* car_collide;
  float car_collide_rotation;
  float car_collide_rotation_old;
  int score;

  struct _SCar* next; // pointer to next car for circle linked list
} SCar;


#include "physics.h"


void carInit( SCar* c );
void carFree( SCar* c );


void carLoadTexture( SCar* c );


//! \fn void carSetPos( SCar* c, float x, float z, float angle )
//! \brief Set pos and angle of the car.
void carSetPos( SCar* c, float x, float z, float angle );


void carReset( SCar* c );


//! \fn void carUpdate( SCar* c )
//! \brief Check \a SCar attributes and update them.
void carUpdate( SCar* c );


//! \fn void carUpdatePos( SCar* c )
//! \brief Update car position.
void carUpdatePos( SCar* c );


//! \fn void carUpdateDir( SCar* c )
//! \brief Update car direction.
void carUpdateDir( SCar* c );


void carCheckAdherence( SCar* c );


//! \fn void carCheckAccel( SCar*c );
//! \brief Check if accel is to high.
void carCheckAccel( SCar* c );


//! \fn void carCheckSpeed( SCar*c );
//! \brief Check if speed is to high.
void carCheckSpeed( SCar* c );


//! \fn void carCheckWheel( SCar*c );
//! \brief Check if wheel angle is to high.
void carCheckWheel( SCar* c );


void carCheckScore( SCar* c );


//! \fn void carSavePos( SCar* c )
//! \brief Save Last good pos.
void carSavePos( SCar* c );


void carRestorePos( SCar* c );


//! \fn void carUpdateVars( SCar* c )
//! \brief Calculate car vars.
//! This is just to make carUpdate cleaner.
void carUpdateVars( SCar* c );


//! \fn void carGetCorners( SCar* c )
//! \brief Get the absolute coordinates of the car corners.
void carGetCorners( SCar* c );


void carGetWheelPos( SCar* c );


//! \fn void carGetSens( SCar* c )
//! \brief Used to know if the car is in forward or backward direction.
//!
//! This will put a -1 c->sens if backward, or 1 if forward, 0 else( no speed ).
void carGetSens( SCar* c );


//! \fn void carSetDamage( SCar* c );
//! \brief set car damage according to hit_point and hit_power.
void carSetDamage( SCar* c );


//! \fn void carSetDeformation( SCar* c );
//! \brief move car vertex after a crash
void carSetDeformation( SCar* c );


//! \fn void carCheckDamage( SCar* c );
//! \brief check if damage is not out of bound
void carCheckDamage( SCar* c );


void CarReComputeNormals( SCar* c );


// functions to call when there is a key press
inline void carForwardOn( SCar* c );
inline void carBackwardOn( SCar* c );
inline void carLeftOn( SCar* c );
inline void carRightOn( SCar* c );
inline void carHandBrakeOn( SCar *c );
inline void carFastSteerOn( SCar *c );


// functions to call when a key is released
inline void carForwardOff( SCar* c );
inline void carBackwardOff( SCar* c );
inline void carLeftOff( SCar* c );
inline void carRightOff( SCar* c );
inline void carHandBrakeOff( SCar *c );
inline void carFastSteerOff( SCar *c );

void carHorn( SCar *c );


#endif // CAR_H
