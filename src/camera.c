//
//


//! \file camera.c
//! \brief Handle the camera for the local human player.


#include "camera.h"


void cameraInit( SCamera* c )
{
  setVector3f( c->pos, 0, 1, 0 );
  setVector3f( c->pos_norm, 0, 0, 0 );
  setVector3f( c->pos_offset, 0, 0, 0 );
  setVector3f( c->v, 0, 0, 0 );
  setVector3f( c->look, 0, 0, 0 );

  c->rx = 0;
  c->ry = 0;

  c->cos_rx = 0;
  c->sin_rx = 0;
  c->cos_ry = 0;
  c->sin_ry = 0;

  c->distance = 6;
  c->height = 3;
  c->angle = 0;
  c->offset = 0;
  c->lazy_cam = 0;

  c->key_press = 0;

  c->mode = 0;

  c->cameraUpdateMode = &cameraUpdateMode1;

  c->player = NULL;

  printf( "Struct Camera : OK.\n" );
}


void cameraFree( SCamera* c )
{
  printf( "Struct Camera : Free.\n" );
}


void cameraUpdate( SCamera* c )
{
  // update vars.
  //cameraUpdateVars( c );
  
  c->cameraUpdateMode( c );
  
  // re-update some vars
  //c->cos_rx = cosf( c->rx );
  //c->sin_rx = sinf( c->rx );
  cameraUpdateVars( c );
}


void cameraUpdatePos( SCamera* c )
{
  static Vector3f tmp;

  setVector3fv( tmp, c->v );
  mulVector3f( tmp, g_fps->time );

  sumVector3fv( c->pos, tmp );
}


void cameraCheckSpeed( SCamera* c )
{
  // get speed
  c->speed = module3fv( c->v );
  
  if( c->speed > CAM_MAX_SPD )
    {
      mulVector3f( c->v, CAM_MAX_SPD/c->speed );
    }
}


// chase lock mode.
void cameraUpdateMode1( SCamera* c )
{
  int rear = (c->key_press & CAM_REAR)? -1 : 1;
  float inv_cam = (rear == -1)? M_PI : 0;

  if( c->key_press & CAM_FORWARD )
    {
      c->distance -= 5.0f * g_fps->time;
    } 
  if( c->key_press & CAM_BACKWARD )
    {
      c->distance += 5.0f * g_fps->time;
    }
  if( c->key_press & CAM_LEFT )
    {
      c->offset -= 5.0f * g_fps->time;
    }
  if( c->key_press & CAM_RIGHT )
    {
      c->offset += 5.0f * g_fps->time;
    }
  if( c->key_press & CAM_UP )
    {
      c->height += 5.0f * g_fps->time;
    }
  if( c->key_press & CAM_DOWN )
    {
      c->height -= 5.0f * g_fps->time;
    }


  if( c->player->car.sens )
    { // if car moving
      c->lazy_cam = c->player->car.wheel_angle * c->speed * 0.1f;
      setVector3f( c->pos, 
		   c->player->car.pos[0] -rear*( c->player->car.sens * c->player->car.dir_vect[0]* c->distance ) -( c->player->car.dir_vect[2]* (c->offset + c->lazy_cam) ), 
		   c->height, 
		   c->player->car.pos[2] -rear*( c->player->car.sens * c->player->car.dir_vect[2]* c->distance ) +( c->player->car.dir_vect[0]* (c->offset + c->lazy_cam)) );
      
      if( c->player->car.sens == 1 )
	{
	  c->rx = c->player->car.dir - atanf( c->offset / c->distance ) + inv_cam;
	}
      else
	{
	  c->rx = c->player->car.dir + M_PI + atanf( c->offset / c->distance ) + inv_cam;
	}
    }
  else
    { // if car stooped
      c->lazy_cam -= c->lazy_cam * 0.5f * g_fps->time;
      setVector3f( c->pos, 
		   c->player->car.pos[0] -rear*( c->player->car.dir_vect[0]* c->distance ) -( c->player->car.dir_vect[2]* (c->offset + c->lazy_cam) ), 
		   c->height, 
		   c->player->car.pos[2] -rear*( c->player->car.dir_vect[2]* c->distance ) +( c->player->car.dir_vect[0]* (c->offset + c->lazy_cam) ) );
      c->rx = c->player->car.dir - atanf( c->offset / c->distance ) + inv_cam;
    }
      
  c->ry = -atanf( c->height / sqrtf(c->distance*c->distance + c->offset*c->offset) );
 }


// interior mode
void cameraUpdateMode2( SCamera* c )
{
  int rear = (c->key_press & CAM_REAR)? -1 : 1;

  setVector3f( c->pos, 
	       c->player->car.pos[0] + rear*( c->player->car.dir_vect[0] * 2.0f ), 
	       1.0f, 
	       c->player->car.pos[2] + rear*( c->player->car.dir_vect[2] * 2.0f ) );

  if( rear == -1 )
    {
      c->rx = c->player->car.dir+M_PI;
    }
  else
    {
      c->rx = c->player->car.dir;
    }
  
  c->ry = 0;
}


// free mode.
void cameraUpdateMode3( SCamera* c )
{
  // check key presses.
  if( c->key_press & CAM_FORWARD )
    {
      sumVector3f( c->v, 
		   c->look[0] * CAM_SPD * g_fps->time, 
		   c->look[1] * CAM_SPD * g_fps->time, 
		   c->look[2] * CAM_SPD * g_fps->time );
    }
  if( c->key_press & CAM_BACKWARD )
    {
      sumVector3f( c->v, 
		   -c->look[0] * CAM_SPD * g_fps->time, 
		   -c->look[1] * CAM_SPD * g_fps->time, 
		   -c->look[2] * CAM_SPD * g_fps->time );
    }
  if( c->key_press & CAM_LEFT )
    {
      sumVector3f( c->v, 
		   c->sin_rx * CAM_SPD * g_fps->time, 
		   0.0f, 
		   -c->cos_rx * CAM_SPD * g_fps->time );
    }
  if( c->key_press & CAM_RIGHT )
    {
      sumVector3f( c->v, 
		   -c->sin_rx * CAM_SPD * g_fps->time, 
		   0.0f,  
		   c->cos_rx * CAM_SPD * g_fps->time );
    }
  if( c->key_press & CAM_UP )
    {
      //sumVector3f( c->v, 0.0f, 1.0f, 0.0f );
      c->v[1] += CAM_SPD * g_fps->time;
    }
  if( c->key_press & CAM_DOWN )
    {
      //sumVector3f( c->v, 0.0f, -1.0f, 0.0f );
      c->v[1] -= CAM_SPD * g_fps->time;
    }

  
  if( !c->key_press )
    {
      // reduce speed if no keys are pressed.
      c->v[0] -= (c->v[0]*0.15f);// * g_fps->time;
      c->v[1] -= (c->v[1]*0.15f);// * g_fps->time;
      c->v[2] -= (c->v[2]*0.15f);// * g_fps->time;
    }
  
  // check speed.
  cameraCheckSpeed( c );

  // update pos.
  cameraUpdatePos( c );
}


void cameraUpdateMode4( SCamera* c )
{
  
}


void cameraUpdateVars( SCamera* c )
{
  // check if rx is between 0 and 360.
  if( c->rx >= M_PIx2 )
    c->rx -= M_PIx2;
  else if( c->rx < 0.0f )
    c->rx += M_PIx2;

  // check if ry is between -90 and 90.
  if( c->ry > M_PI_2 )
    c->ry = M_PI_2;
  else if( c->ry < -M_PI_2 )
    c->ry = -M_PI_2;

  // save cos and sin.
  c->cos_rx = cosf( c->rx );
  c->sin_rx = sinf( c->rx );
  c->cos_ry = cosf( c->ry );
  c->sin_ry = sinf( c->ry );

  // view angle vector.
  setVector3f( c->look, c->cos_rx * c->cos_ry, c->sin_ry, c->sin_rx * c->cos_ry );

  // speed
  //c->speed = module3fv( c->v );

  // lazy cam
  //c->lazy_cam = 
}


// press on
void camForwardOn( SCamera* c )
{
  c->key_press |= CAM_FORWARD;
}


void camBackwardOn( SCamera* c )
{
  c->key_press |= CAM_BACKWARD;
}


void camLeftOn( SCamera* c )
{
  c->key_press |= CAM_LEFT;
}


void camRightOn( SCamera* c )
{
  c->key_press |= CAM_RIGHT;
}


void camUpOn( SCamera* c )
{
  c->key_press |= CAM_UP;
}


void camDownOn( SCamera* c )
{
  c->key_press |= CAM_DOWN;
}


void camRearOn( SCamera* c )
{
  c->key_press |= CAM_REAR;
}


// press off
void camForwardOff( SCamera* c )
{
  c->key_press &= ~CAM_FORWARD;
}


void camBackwardOff( SCamera* c )
{
  c->key_press &= ~CAM_BACKWARD;
}


void camLeftOff( SCamera* c )
{
  c->key_press &= ~CAM_LEFT;
}


void camRightOff( SCamera* c )
{
  c->key_press &= ~CAM_RIGHT;
}


void camUpOff( SCamera* c )
{
  c->key_press &= ~CAM_UP;
}


void camDownOff( SCamera* c )
{
  c->key_press &= ~CAM_DOWN;
}


void camRearOff( SCamera* c )
{
  c->key_press &= ~CAM_REAR;
}


void camZoomIn( SCamera* c )
{
  //c->conf->cl_fov = 75;
  //c->mouse_press ^= MOUSEPRESS_MIDDLE;
}


void camZoomOut( SCamera* c )
{
  //c->conf->cl_fov = 75;
  //c->mouse_press ^= MOUSEPRESS_MIDDLE;
}



void camReset( SCamera* c )
{
  c->distance = 6;
  c->height = 3;
  c->offset = 0;
}


void camChangeView( SCamera* c )
{
  if( c->mode != CAM_MODE3 )
    c->mode++;
  else
    c->mode = CAM_MODE1;

  switch( c->mode )
    {
    case CAM_MODE1 :
      //cameraUpdateMode1( c, car );
      c->cameraUpdateMode = &cameraUpdateMode1;
      break;
    case CAM_MODE2 :
      //cameraUpdateMode2( c, car );
      c->cameraUpdateMode = &cameraUpdateMode2;
      break;
    case CAM_MODE3 :
      //cameraUpdateMode3( c );
      c->cameraUpdateMode = &cameraUpdateMode3;
      break;
      //case CAM_MODE4 :
      //cameraUpdateMode4( c );
      //break;
    default:
      break;
    }
}


void camFollowPrev( SCamera* c )
{
  int i = *g_nb_car;
  while( i > 1 )
    {
      c->player = c->player->next;
      i--;
    };
}


void camFollowNext( SCamera* c )
{
  c->player = c->player->next;
}


void camFollowPlayer( SCamera* c, SPlayer* pl )
{
  c->player = pl;
}
