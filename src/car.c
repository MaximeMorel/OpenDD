//
//


//! \file car.c
//! \brief Car module.
//!


#include "car.h"


void carInit( SCar* c )
{

  int i;

  c->id = 0;

  setVector3f( c->pos, 0, 0, 0);
  setVector3f( c->v, 0, 0, 0);
  setVector3f( c->a, 0, 0, 0);
  setVector3f( c->dir_vect, 0, 0, 0);
  setVector3f( c->wheel_vect, 0, 0, 0);
  setVector3f( c->wheel_vect_abs, 0, 0, 0);

  c->dir = 1;

  c->adherence_factor = 1.0f;

  c->wheel_angle = 0;
  
  c->speed = 0;
  c->acceleration = 0;
  
  c->accel = 0;
  
  c->state = 0;

  c->gear = 1;

  c->rpm = 1000.0f;

  c->sens = 0;
  c->new_sens = 0;

  c->collision = 0;

  c->rotation = 0;
  c->adherence = 0;

  c->wheel_rotation = 0;

  c->fast_steer = 1;

  c->roll = 0;
  c->pitch = 0;

  c->hit_point = 0;
  c->hit_power = 0;

  c->score_timeout = 0;

  c->score = 0;

  c->car_collide = NULL;

  for( i = 0; i < 12; i++ )
    {
      c->damage[i] = 0;
    }  

  for( i = 0; i < 18; i++ )
    {
      c->wheel_pos[i] = 0;
    }

  c->texture = 0;
  c->pTexture = NULL;

  //wheelInit( &c->wheel_fr );
  //wheelInit( &c->wheel_fl );
  //wheelInit( &c->wheel_rr );
  //wheelInit( &c->wheel_rl );

  modelInit( &c->car_model );
  modelLoadObj( &c->car_model, "data/models/car.obj" );

  printf( "Struct car : OK.\n" );
}


void carFree( SCar* c )
{
  
  modelFree( &c->car_model );

  //wheelFree( &c->wheel_fr );
  //wheelFree( &c->wheel_fl );
  //wheelFree( &c->wheel_rr );
  //wheelFree( &c->wheel_rl );

  if( c->texture > 0 && glIsTexture( c->texture ) )
    {
      glDeleteTextures( 1 , &c->texture );
      c->texture = 0;
      printf( "Car %d texture deleted.\n", c->id );
    }
  
  checkGlError( "car free" ); 
  
  printf( "Struct car %d : free.\n", c->id );
}


void carLoadTexture( SCar* c )
{
  char src[256];
  sprintf( src, "data/textures/car/car%d.jpg", c->id+1 );
  c->texture = loadTexture( c->pTexture, src, GL_RGB, GL_REPEAT, true);

  printf( "Load car %d texture.\n", c->id+1 );
}


void carSetPos( SCar* c, float x, float z, float angle )
{
  c->pos[0] = x;
  c->pos[2] = z;
  c->dir = angle;
}


void carReset( SCar* c )
{
  carSetPos( c, 0, 0, 0 );
  setVector3f( c->v , 0, 0, 0 );

  c->damage[0] = 0.0f;
  c->damage[1] = 0.0f;

  c->state &= ~CAR_DEAD;

  carSetPos( c->next, 5, 5, 0 );
  setVector3f( c->next->v , 0, 0, 0 );

  c->next->damage[0] = 0.0f;
  c->next->damage[1] = 0.0f;

  c->next->state &= ~CAR_DEAD;

}


void carUpdate( SCar* c )
{
  // update vars.
  //carUpdateVars( c );

  // check key presses.
  if( c->state & CAR_ACCEL && !(c->state & CAR_DEAD) )  // acceleration
    {
      // forward
      if( c->sens == 1 )
	{
	  c->acceleration += (1.0f - ((c->damage[3]+c->damage[4])/2.5f) ) * CAR_ACCEL_SPD * g_fps->time;

	  //setVector3f( c->a , 
	  //	       c->wheel_vect_abs[0] * c->acceleration, 
	  //	       c->wheel_vect_abs[1] * c->acceleration,
	  //	       c->wheel_vect_abs[2] * c->acceleration );
	}
      else	// backward
	if( c->sens == -1 )
	  {
	    c->acceleration += (1.0f - ((c->damage[3]+c->damage[4])/2.5f) ) * CAR_ACCEL_SPD * g_fps->time;

	    //setVector3f( c->a , 
	    //		 -c->wheel_vect_abs[0] * c->acceleration, 
	    //		 -c->wheel_vect_abs[1] * c->acceleration,
	    //		 -c->wheel_vect_abs[2] * c->acceleration );
	  }
	else    // starting from 0
	  {
	    c->sens = c->new_sens;

	    c->acceleration += CAR_ACCEL_SPD * g_fps->time;

	    setVector3f( c->a , 
			 c->sens * c->acceleration, 
			 c->sens * c->acceleration,
			 c->sens * c->acceleration );

	    // set initial speed to pass threshold
	    setVector3f( c->v , 
			 c->sens * c->wheel_vect_abs[0] * CAR_THRESHOLD * 2.0f, 
			 c->sens * c->wheel_vect_abs[1] * CAR_THRESHOLD * 2.0f,
			 c->sens * c->wheel_vect_abs[2] * CAR_THRESHOLD * 2.0f );

	    c->new_sens = 0;
	    c->adherence = 1.0f;
	  }
    }
  else
    if( c->state & CAR_BRAKE )  // brake
      {
	//c->acceleration -= CAR_ACCEL_SPD * g_fps->time;
	c->acceleration -= c->acceleration * 8.0f * g_fps->time;
	//setVector3f( c->a, 0.0f, 0.0f, 0.0f );

	sumVector3f( c->v ,
		     -c->v[0] * CAR_ACCEL_SPD * 1.0f * ((1/(c->speed+0.1f))+0.1f) * g_fps->time, 
		     -c->v[1] * CAR_ACCEL_SPD * 1.0f * ((1/(c->speed+0.1f))+0.1f) * g_fps->time, 
		     -c->v[2] * CAR_ACCEL_SPD * 1.0f * ((1/(c->speed+0.1f))+0.1f) * g_fps->time );
      }
    else
      {
	// pedals released -> accel return quicly to 0.
	//                 -> speed decrease slowly.
	c->acceleration -= c->acceleration * 8.0f * g_fps->time;

	//sumVector3f( c->a, 
	//	     -c->a[0] * 10.0f * g_fps->time, 
	//	     -c->a[1] * 10.0f * g_fps->time, 
	//	     -c->a[2] * 10.0f * g_fps->time );

	sumVector3f( c->v, 
		     -c->v[0] * 0.5f * g_fps->time, 
		     -c->v[1] * 0.5f * g_fps->time, 
		     -c->v[2] * 0.5f * g_fps->time );
      }

  if( c->state & CAR_HANDBRAKE )
    {
      sumVector3f( c->v ,
		   -c->v[0] * CAR_ACCEL_SPD * 1.0f * (1.5f - c->adherence) * ((1/(c->speed+0.1f))+0.1f) * g_fps->time, 
		   -c->v[1] * CAR_ACCEL_SPD * 1.0f * (1.5f - c->adherence) * ((1/(c->speed+0.1f))+0.1f) * g_fps->time, 
		   -c->v[2] * CAR_ACCEL_SPD * 1.0f * (1.5f - c->adherence) * ((1/(c->speed+0.1f))+0.1f) * g_fps->time );

      //c->adherence += 1.0f * g_fps->time;
      c->adherence = 1.0f;
    }

  // wheel angle.
  if( c->state & CAR_TURN_LEFT )
    {
      c->wheel_angle -= c->fast_steer * g_fps->time;
    }
  else
    if( c->state & CAR_TURN_RIGHT )
      {
	c->wheel_angle += c->fast_steer * g_fps->time;
      }
    else
      {
	// steering wheel released -> returning to center.
	c->wheel_angle -= c->wheel_angle * 5.0f * g_fps->time;
      }

  carCheckAdherence( c );

  // check wheel angle.
  carCheckWheel( c );

  // check accel.
  carCheckAccel( c );

  // check speed.
  carCheckSpeed( c );

  // update pos
  carUpdatePos( c );

  // re-update some vars
  carUpdateVars( c );  
}


void carUpdateVars( SCar* c )
{
  // check if dir is between 0 and  2PI.
  if ( c->dir >= M_PIx2 )
    c->dir -= M_PIx2;
  if ( c->dir < 0.0f )
    c->dir += M_PIx2;

  // car direction vector.
  //setVector3f( c->dir_vect, cosf( c->dir ), 0.0f, sinf( c->dir ) );

  // wheel absolute direction vector.
  setVector3f( c->wheel_vect_abs, 
	       cosf( c->wheel_angle + c->dir ), 
	       0.0f, 
	       sinf( c->wheel_angle + c->dir ) );

  // reset collision counter.
  c->collision = 0;

  // sens ( backward or forward ).
  //carGetSens( c );

  // speed
  //c->speed = module3fv( c->v );

  // roll
  c->roll = -c->wheel_angle/4.0f * RAD2DEG * (c->speed/CAR_MAX_SPD);

  // pitch
  c->pitch = 0;//c->accel*500;

  // rotation
  c->rotation -= c->rotation * 2.0f * g_fps->time;
  //c->rotation = 0;

  // adherence
  c->adherence -= c->adherence * 0.15f * g_fps->time;

  // wheel rotation
  c->wheel_rotation += c->sens * c->speed * 100.0f * g_fps->time;
}


void carUpdatePos( SCar* c )
{
  static Vector3f tmp;  

  // update speed vector.
  setVector3fv( tmp, c->a );
  mulVector3f( tmp, g_fps->time );
  
  sumVector3fv( c->v , tmp );

  // update sens.
  //carGetSens( c );

  // check speed.
  carCheckSpeed( c );

  // update dir.
  carUpdateDir( c );

  // direction correction & adherence
  normalize3fv( c->v );
  mulVector3f( c->v, c->adherence );
  setVector3fv( tmp, c->dir_vect );
  mulVector3f( tmp, (1.0f - c->adherence) * c->sens );
  sumVector3fv( c->v, tmp );
  mulVector3f( c->v, c->speed );
  //mulVector3f( c->v, c->speed * c->sens );

  // 0 speed check.
  if( c->speed < CAR_THRESHOLD )
    {
      if( c->state & CAR_BRAKE )
	{
	  //printf("invert\n");
	  c->state &= ~CAR_BRAKE;
	  c->state |= CAR_ACCEL;
	  c->sens *= -1;
	  c->acceleration = 0.0f;
	  mulVector3f( c->v, -1.5f );
	}
      else
	{
	  //printf("stop\n");
	  c->acceleration = 0.0f;
	  c->speed = 0.0f;
	  setVector3f( c->v, 0.0f, 0.0f, 0.0f );
	  c->sens = 0;
	}
    }

  // update position vector.
  setVector3fv( tmp, c->v );
  mulVector3f( tmp, g_fps->time );

  sumVector3fv( c->pos, tmp );
}


void carUpdateDir( SCar* c )
{
  c->dir += c->rotation;

  if( c->speed > CAR_THRESHOLD )
    {
      // the car turn less when it loses grip.
      c->dir += ( 1.0f - ( c->adherence/2.0f )) * c->sens * c->wheel_angle * 10.0f * g_fps->time;
    }

  setVector3f( c->dir_vect, cosf( c->dir ), 0.0f, sinf( c->dir ) );
}


void carCheckAdherence( SCar* c )
{
  if( c->adherence >= 1.0f )
    {
      c->adherence = 1.0f;
    }
}


void carCheckAccel( SCar* c )
{
  // get accel.
  //c->accel = module3fv( c->a );

  // check accel.
  //if( c->accel > CAR_MAX_ACCEL )
  //  {
  //    c->a[0] *= CAR_MAX_ACCEL / c->accel;
  //    c->a[2] *= CAR_MAX_ACCEL / c->accel;
  //  }

  // new max
  float max = (1.0f - ((c->damage[3]+c->damage[4])/2.5f) ) * CAR_MAX_ACCEL;


  if( fabsf( c->acceleration ) > max )
    {
      if( c->acceleration > 0.0f )
	{
	  c->acceleration = max;
	}
      else
	if( c->acceleration < 0.0f )
	  {
	    c->acceleration = -max;
	  }

      //setVector3f( c->a , 
      //		   c->sens * c->wheel_vect_abs[0] * c->acceleration, 
      //		   c->sens * c->wheel_vect_abs[1] * c->acceleration,
      //		   c->sens * c->wheel_vect_abs[2] * c->acceleration );
    }
  
  setVector3f( c->a , 
	       c->sens * c->wheel_vect_abs[0] * c->acceleration, 
	       c->sens * c->wheel_vect_abs[1] * c->acceleration,
	       c->sens * c->wheel_vect_abs[2] * c->acceleration );
}


void carCheckSpeed( SCar* c )
{
  // new max
  float max = (1.0f - ((c->damage[3]+c->damage[4])/3.5f) ) * CAR_MAX_SPD;

  // get speed.
  c->speed = module3fv( c->v );

  // check speed.
  if( c->speed > max )
    {
      c->v[0] *= max / c->speed;
      c->v[2] *= max / c->speed;
    }
}


void carCheckWheel( SCar* c )
{
  // new max
  float max_l = (1.0f - (c->damage[2]/1.5f) ) * CAR_MAX_TURN;
  float max_r = (1.0f - (c->damage[5]/1.5f) ) * CAR_MAX_TURN;

  if( c->wheel_angle > 0.0f )
    {
      if( fabsf( c->wheel_angle ) >= max_l * c->fast_steer )
	c->wheel_angle = max_l * c->fast_steer;
    }
  else
    {
      if( fabsf( c->wheel_angle ) >= max_r * c->fast_steer )
	c->wheel_angle = -max_r * c->fast_steer;
    }
}


void carCheckScore( SCar* c )
{
  //printf( "car %d\n", c->id );
  //printf( "car %d -> %d\n", c->id, c->car_collide->id );
  //printf( "now %f old %f\n", c->car_collide->dir ,c->car_collide_rotation_old );
  //printf( "rot %f\n", c->car_collide_rotation );

  if( c->car_collide != NULL )
    {
      if( (c->car_collide->dir - c->car_collide_rotation_old) > M_PIx2 )
	{
	  c->car_collide_rotation -= M_PIx2;
	}
      else
	if( c->car_collide->dir - c->car_collide_rotation_old < -M_PIx2 )
	  {
	    c->car_collide_rotation += M_PIx2;
	  }

      c->car_collide_rotation += (c->car_collide->dir - c->car_collide_rotation_old );
      c->car_collide_rotation_old = c->car_collide->dir;
    }
  if( c->score_timeout - g_fps->time_now < 50 )
    {
      if( fabsf(c->car_collide_rotation) > M_PIx2 )
	c->score += 10;
      else
	if( fabsf(c->car_collide_rotation) > M_PI )
	  c->score += 4;
	else
	  if( fabsf(c->car_collide_rotation) > M_PI_2 )
	    c->score += 2;

      c->score_timeout = 0;
    }
}


void carSavePos( SCar* c )
{
  setVector3fv( c->pos_old, c->pos );
  c->pos_old[3] = c->dir;
}


void carRestorePos( SCar* c )
{
  setVector3fv( c->pos, c->pos_old );
  //c->dir = c->pos_old[3];
}


void carGetSens( SCar* c )
{
  if( c->sens != 0 )
    {
      if( dotProduct3fv( c->v, c->dir_vect ) > 0.0f )
	{
	  c->sens = 1;
	}
      else
	{
	  c->sens = -1;
	}
    }
}


void carGetCorners( SCar* c )
{
  static float angle = 0.463647609000806f;   // = atanf( 1.0f / 2.0f )

  //setVector2f( c->corner_left, cosf( c->dir + angle ), sinf( c->dir + angle ) );
  //setVector2f( c->corner_right, cosf( c->dir - angle ), sinf( c->dir - angle ) );

  // front
  // left
  c->corners[0] = 2.24f * cosf( c->dir + angle );
  c->corners[1] = 2.24f * sinf( c->dir + angle );

  // right
  c->corners[2] = 2.24f * cosf( c->dir - angle );
  c->corners[3] = 2.24f * sinf( c->dir - angle );

  // rear
  // left
  c->corners[6] = c->pos[0] - c->corners[2];
  c->corners[7] = c->pos[2] - c->corners[3];

  // right
  c->corners[4] = c->pos[0] - c->corners[0];
  c->corners[5] = c->pos[2] - c->corners[1];

  // correction
  c->corners[0] += c->pos[0];
  c->corners[1] += c->pos[2];

  c->corners[2] += c->pos[0];
  c->corners[3] += c->pos[2];

  // side left
  c->side[0] = c->pos[0] + 1.0f * cosf( c->dir - M_PI_2 );
  c->side[1] = c->pos[2] + 1.0f * sinf( c->dir - M_PI_2 );

  // side right
  c->side[2] = c->pos[0] + 1.0f * cosf( c->dir + M_PI_2 );
  c->side[3] = c->pos[2] + 1.0f * sinf( c->dir + M_PI_2 );

}


void carGetWheelPos( SCar* c )
{
  static float a1 = 0.594759f;      //atanf( 0.92f / 1.36f );
  static float a2 = 0.796386f;      //atanf( 0.92f / 0.9f );

  float tmp[8];

  // wheel front left
  tmp[0] = c->pos[0] + 1.64f * cosf( c->dir + a1 );
  tmp[1] = c->pos[2] + 1.64f * sinf( c->dir + a1 );

  // wheel front right
  tmp[2] = c->pos[0] + 1.64f * cosf( c->dir - a1 );
  tmp[3] = c->pos[2] + 1.64f * sinf( c->dir - a1 );

  // wheel rear right
  tmp[4] = c->pos[0] - 1.29f * cosf( c->dir + a2 );
  tmp[5] = c->pos[2] - 1.29f * sinf( c->dir + a2 );

  // wheel rear left
  tmp[6] = c->pos[0] - 1.29f * cosf( c->dir - a2 );
  tmp[7] = c->pos[2] - 1.29f * sinf( c->dir - a2 );

  // save last wheel pos
  if( fabsf(tmp[0] - c->wheel_pos[0]) < 4.5f && fabsf(tmp[1] - c->wheel_pos[1]) < 4.5f )
    {
      c->wheel_pos[8] = c->wheel_pos[0];
      c->wheel_pos[9] = c->wheel_pos[1];
      c->wheel_pos[10] = c->wheel_pos[2];
      c->wheel_pos[11] = c->wheel_pos[3];
      c->wheel_pos[12] = c->wheel_pos[4];
      c->wheel_pos[13] = c->wheel_pos[5];
      c->wheel_pos[14] = c->wheel_pos[6];
      c->wheel_pos[15] = c->wheel_pos[7];

      c->wheel_pos[17] = c->wheel_pos[16];      
    }
  else
    {
      c->wheel_pos[8] = tmp[0];
      c->wheel_pos[9] = tmp[1];
      c->wheel_pos[10] = tmp[2];
      c->wheel_pos[11] = tmp[3];
      c->wheel_pos[12] = tmp[4];
      c->wheel_pos[13] = tmp[5];
      c->wheel_pos[14] = tmp[6];
      c->wheel_pos[15] = tmp[7];
      
      c->wheel_pos[17] = c->pos_old[3];
    }

  // wheel front left
  c->wheel_pos[0] = tmp[0];
  c->wheel_pos[1] = tmp[1];

  // wheel front right
  c->wheel_pos[2] = tmp[2];
  c->wheel_pos[3] = tmp[3];

  // wheel rear right
  c->wheel_pos[4] = tmp[4];
  c->wheel_pos[5] = tmp[5];

  // wheel rear left
  c->wheel_pos[6] = tmp[6];
  c->wheel_pos[7] = tmp[7];

  c->wheel_pos[16] = c->dir;
}


void carCheckDamage( SCar* c )
{
  int i;
  for( i = 0; i < 6; i++ )
    {
      if( c->damage[i] >= 1.0f )
	{
	  c->damage[i] = 1.0f;
	}
    }
  if( c->damage[0] > 0.9f || c->damage[1] > 0.9f )
    {
      c->state |= CAR_DAMAGED;
    }
  
}


void carSetDamage( SCar* c )
{
  if( c->hit_point==1 && c->damage[0] < 1.0f )
    {// front left
      c->damage[6] = 0.5f * c->hit_power;
      if( c->damage[0] + c->damage[6] > 1.0f )
	{
	  c->damage[6] = c->damage[0] + c->damage[6] - 1.0f;
	}
    }
  else
  if( c->hit_point==2 && c->damage[1] + c->damage[7] < 1.0f )
    {// front right
      c->damage[7] = 0.5f * c->hit_power;
      if( c->damage[1] + c->damage[7] > 1.0f )
	{
	  c->damage[7] = c->damage[1] + c->damage[7] - 1.0f;
	}
    }
  else
  if( c->hit_point==3 && c->damage[2] + c->damage[8] < 1.0f )
    {// side right
      c->damage[8] = 0.5f * c->hit_power;
      if( c->damage[2] + c->damage[8] > 1.0f )
	{
	  c->damage[8] = c->damage[2] + c->damage[8] - 1.0f;
	}
    }
  else
  if( c->hit_point==4 && c->damage[3] + c->damage[9] < 1.0f )
    {// rear right
      c->damage[9] = 0.5f * c->hit_power;
      if( c->damage[3] + c->damage[9] > 1.0f )
	{
	  c->damage[9] = c->damage[3] + c->damage[9] - 1.0f;
	}
    }
  else
  if( c->hit_point==5 && c->damage[4] + c->damage[10] < 1.0f )
    {// rear left
      c->damage[10] = 0.5f * c->hit_power;
      if( c->damage[4] + c->damage[10] > 1.0f )
	{
	  c->damage[10] = c->damage[4] + c->damage[10] - 1.0f;
	}
    }
  else
  if( c->hit_point==6 && c->damage[5] + c->damage[11] < 1.0f )
    {// side left
      c->damage[11] = 0.5f * c->hit_power;
      if( c->damage[5] + c->damage[11] > 1.0f )
	{
	  c->damage[11] = c->damage[5] + c->damage[11] - 1.0f;
	}
    }

  c->damage[0] += c->damage[6];
  c->damage[1] += c->damage[7];
  c->damage[2] += c->damage[8];
  c->damage[3] += c->damage[9];
  c->damage[4] += c->damage[10];
  c->damage[5] += c->damage[11];
  
  carCheckDamage( c );  

  carSetDeformation( c );

  c->damage[6] = 0;
  c->damage[7] = 0;
  c->damage[8] = 0;
  c->damage[9] = 0;
  c->damage[10] = 0;
  c->damage[11] = 0;

  c->hit_point = 0;
  c->hit_power = 0;

  if( c->damage[0] >= 1.0f || c->damage[1] >= 1.0f )
    {
      c->state |= CAR_DEAD;
    }
}


void carSetDeformation( SCar* c )
{
  float coeff = 0.25f;

  //if( c->damage[0] >= 1.0f )
  //return;

  // left side : +z
  // 282 294 300 312 321 330 339 348 357 366 375 384
  // 285 291

  // right side : -z
  // 417 429 438 456 465 474 483 489 501 510 519 528
  // 480 492

  // hood left : +y
  // 144 159 168 588

  // hood righy : +y
  // 147 165 582

  // front left : -x
  // 198 258
  // 201 255 267 270 297 378 558 585

  // front right : -x
  // 207 420 525 537 546 549 570 576
  // 210 555

  // front middle : -x/2
  // 150 561 567 579 591
  // 204 213 564 573

  // trunk left : +y
  // 105 171 183

  // trunk right : +y
  // 93 177 186 192

  // rear left : +x
  // 99 108 123 222 231 240 249 315 327
  // 117 219

  // rear right : +x
  // 90 126 135 387 396 405 435 441 450
  // 132 390

  // rear middle : +x/2
  // 96 102 114 138 174
  // 111 120 129 141


  // left side damage
  if( c->damage[11] > 0.0f )
    {
      c->car_model.vertex_data[284] += c->damage[11] * coeff * 1.33f;
      c->car_model.vertex_data[296] += c->damage[11] * coeff * 1.33f;
      c->car_model.vertex_data[302] += c->damage[11] * coeff * 1.33f;
      c->car_model.vertex_data[314] += c->damage[11] * coeff * 1.33f;
      c->car_model.vertex_data[323] += c->damage[11] * coeff * 1.33f;
      c->car_model.vertex_data[332] += c->damage[11] * coeff * 1.33f;
      c->car_model.vertex_data[341] += c->damage[11] * coeff * 1.33f;
      c->car_model.vertex_data[350] += c->damage[11] * coeff * 1.33f;
      c->car_model.vertex_data[359] += c->damage[11] * coeff * 1.33f;
      c->car_model.vertex_data[368] += c->damage[11] * coeff * 1.33f;
      c->car_model.vertex_data[377] += c->damage[11] * coeff * 1.33f;
      c->car_model.vertex_data[386] += c->damage[11] * coeff * 1.33f;
      c->car_model.vertex_data[287] += c->damage[11] * coeff * 1.33f;
      c->car_model.vertex_data[293] += c->damage[11] * coeff * 1.33f;
    }


  // right side damage
  if( c->damage[8] > 0.0f )
    {
      c->car_model.vertex_data[419] -= c->damage[8] * coeff * 1.33f;
      c->car_model.vertex_data[431] -= c->damage[8] * coeff * 1.33f;
      c->car_model.vertex_data[440] -= c->damage[8] * coeff * 1.33f;
      c->car_model.vertex_data[458] -= c->damage[8] * coeff * 1.33f;
      c->car_model.vertex_data[467] -= c->damage[8] * coeff * 1.33f;
      c->car_model.vertex_data[476] -= c->damage[8] * coeff * 1.33f;
      c->car_model.vertex_data[485] -= c->damage[8] * coeff * 1.33f;
      c->car_model.vertex_data[491] -= c->damage[8] * coeff * 1.33f;
      c->car_model.vertex_data[503] -= c->damage[8] * coeff * 1.33f;
      c->car_model.vertex_data[512] -= c->damage[8] * coeff * 1.33f;
      c->car_model.vertex_data[521] -= c->damage[8] * coeff * 1.33f;
      c->car_model.vertex_data[530] -= c->damage[8] * coeff * 1.33f;
      c->car_model.vertex_data[482] -= c->damage[8] * coeff * 1.33f;
      c->car_model.vertex_data[494] -= c->damage[8] * coeff * 1.33f;
    }


  // hood left damage
  // up
  if( c->damage[6] > 0.0f )
    {
      c->car_model.vertex_data[148] += c->damage[6] * coeff;
      c->car_model.vertex_data[166] += c->damage[6] * coeff;
      c->car_model.vertex_data[583] += c->damage[6] * coeff;
      // recoil
      c->car_model.vertex_data[147] -= c->damage[6] * coeff * 0.5f;
      c->car_model.vertex_data[165] -= c->damage[6] * coeff * 0.5f;
      c->car_model.vertex_data[582] -= c->damage[6] * coeff * 0.5f;
      
      // front left damage
      c->car_model.vertex_data[198] -= c->damage[6] * coeff;
      c->car_model.vertex_data[258] -= c->damage[6] * coeff;
      c->car_model.vertex_data[201] -= c->damage[6] * coeff;
      c->car_model.vertex_data[255] -= c->damage[6] * coeff;
      c->car_model.vertex_data[267] -= c->damage[6] * coeff;
      c->car_model.vertex_data[270] -= c->damage[6] * coeff;
      c->car_model.vertex_data[297] -= c->damage[6] * coeff;
      c->car_model.vertex_data[378] -= c->damage[6] * coeff;
      c->car_model.vertex_data[558] -= c->damage[6] * coeff;
      c->car_model.vertex_data[585] -= c->damage[6] * coeff;
    }


  // front middle damage
  if( c->damage[6] > 0.0f || c->damage[7] > 0.0f )
    {
      c->car_model.vertex_data[150] -= (c->damage[6]+c->damage[7]) * coeff * 0.45f;
      c->car_model.vertex_data[561] -= (c->damage[6]+c->damage[7]) * coeff * 0.45f;
      c->car_model.vertex_data[567] -= (c->damage[6]+c->damage[7]) * coeff * 0.45f;
      c->car_model.vertex_data[579] -= (c->damage[6]+c->damage[7]) * coeff * 0.45f;
      c->car_model.vertex_data[591] -= (c->damage[6]+c->damage[7]) * coeff * 0.45f;
      c->car_model.vertex_data[204] -= (c->damage[6]+c->damage[7]) * coeff * 0.45f;
      c->car_model.vertex_data[213] -= (c->damage[6]+c->damage[7]) * coeff * 0.45f;
      c->car_model.vertex_data[564] -= (c->damage[6]+c->damage[7]) * coeff * 0.45f;
      c->car_model.vertex_data[573] -= (c->damage[6]+c->damage[7]) * coeff * 0.45f;
    }


  // hood right damage
  // up
  if( c->damage[7] > 0.0f )
    {
      c->car_model.vertex_data[145] += c->damage[7] * coeff;
      c->car_model.vertex_data[160] += c->damage[7] * coeff;
      c->car_model.vertex_data[169] += c->damage[7] * coeff;
      c->car_model.vertex_data[589] += c->damage[7] * coeff;
      // recoil
      c->car_model.vertex_data[144] -= c->damage[7] * coeff * 0.5f;
      c->car_model.vertex_data[159] -= c->damage[7] * coeff * 0.5f;
      c->car_model.vertex_data[168] -= c->damage[7] * coeff * 0.5f;
      c->car_model.vertex_data[588] -= c->damage[7] * coeff * 0.5f;
    
      // front right damage
      c->car_model.vertex_data[207] -= c->damage[7] * coeff;
      c->car_model.vertex_data[420] -= c->damage[7] * coeff;
      c->car_model.vertex_data[525] -= c->damage[7] * coeff;
      c->car_model.vertex_data[537] -= c->damage[7] * coeff;
      c->car_model.vertex_data[546] -= c->damage[7] * coeff;
      c->car_model.vertex_data[549] -= c->damage[7] * coeff;
      c->car_model.vertex_data[570] -= c->damage[7] * coeff;
      c->car_model.vertex_data[576] -= c->damage[7] * coeff;
      c->car_model.vertex_data[210] -= c->damage[7] * coeff;
      c->car_model.vertex_data[555] -= c->damage[7] * coeff;
    }
  

  // trunk left damage
  // up
  if( c->damage[10] > 0.0f )
    {
      c->car_model.vertex_data[106] += c->damage[10] * coeff;
      c->car_model.vertex_data[172] += c->damage[10] * coeff;
      c->car_model.vertex_data[184] += c->damage[10] * coeff;
      // recoil
      c->car_model.vertex_data[105] += c->damage[10] * coeff * 0.5f;
      c->car_model.vertex_data[171] += c->damage[10] * coeff * 0.5f;
      c->car_model.vertex_data[183] += c->damage[10] * coeff * 0.5f;
      
      // rear left damage
      c->car_model.vertex_data[99] += c->damage[10] * coeff;
      c->car_model.vertex_data[108] += c->damage[10] * coeff;
      c->car_model.vertex_data[123] += c->damage[10] * coeff;
      c->car_model.vertex_data[222] += c->damage[10] * coeff;
      c->car_model.vertex_data[231] += c->damage[10] * coeff;
      c->car_model.vertex_data[240] += c->damage[10] * coeff;
      c->car_model.vertex_data[249] += c->damage[10] * coeff;
      c->car_model.vertex_data[315] += c->damage[10] * coeff;
      c->car_model.vertex_data[327] += c->damage[10] * coeff;
      c->car_model.vertex_data[117] += c->damage[10] * coeff;
      c->car_model.vertex_data[219] += c->damage[10] * coeff;
    }


  // rear middle damage
  if( c->damage[10] > 0.0f ||c->damage[9] > 0.0f )
    {
      c->car_model.vertex_data[96] += (c->damage[10]+c->damage[9]) * coeff * 0.45f;
      c->car_model.vertex_data[102] += (c->damage[10]+c->damage[9]) * coeff * 0.45f;
      c->car_model.vertex_data[114] += (c->damage[10]+c->damage[9]) * coeff * 0.45f;
      c->car_model.vertex_data[138] += (c->damage[10]+c->damage[9]) * coeff * 0.45f;
      c->car_model.vertex_data[174] += (c->damage[10]+c->damage[9]) * coeff * 0.45f;
      c->car_model.vertex_data[111] += (c->damage[10]+c->damage[9]) * coeff * 0.45f;
      c->car_model.vertex_data[120] += (c->damage[10]+c->damage[9]) * coeff * 0.45f;
      c->car_model.vertex_data[129] += (c->damage[10]+c->damage[9]) * coeff * 0.45f;
      c->car_model.vertex_data[141] += (c->damage[10]+c->damage[9]) * coeff * 0.45f;
    }


  // trunk right damage
  // up
  if( c->damage[9] > 0.0f )
    {
      c->car_model.vertex_data[94] += c->damage[9] * coeff;
      c->car_model.vertex_data[178] += c->damage[9] * coeff;
      c->car_model.vertex_data[187] += c->damage[9] * coeff;
      c->car_model.vertex_data[193] += c->damage[9] * coeff;
      // recoil
      c->car_model.vertex_data[93] += c->damage[9] * coeff * 0.5f;
      c->car_model.vertex_data[177] += c->damage[9] * coeff * 0.5f;
      c->car_model.vertex_data[186] += c->damage[9] * coeff * 0.5f;
      c->car_model.vertex_data[192] += c->damage[9] * coeff * 0.5f;
      
      
      // rear right damage
      c->car_model.vertex_data[90] += c->damage[9] * coeff;
      c->car_model.vertex_data[126] += c->damage[9] * coeff;
      c->car_model.vertex_data[135] += c->damage[9] * coeff;
      c->car_model.vertex_data[387] += c->damage[9] * coeff;
      c->car_model.vertex_data[396] += c->damage[9] * coeff;
      c->car_model.vertex_data[405] += c->damage[9] * coeff;
      c->car_model.vertex_data[435] += c->damage[9] * coeff;
      c->car_model.vertex_data[441] += c->damage[9] * coeff;
      c->car_model.vertex_data[450] += c->damage[9] * coeff;
      c->car_model.vertex_data[132] += c->damage[9] * coeff;
      c->car_model.vertex_data[390] += c->damage[9] * coeff;
    }
  
  
  CarReComputeNormals( c );  
}


void CarReComputeNormals( SCar* c )
{

}


// press on
void carForwardOn( SCar* c )
{
  if( c->sens == 0 )
    {
      c->new_sens = 1;
      c->state |= CAR_ACCEL;

      //c->vx = c->cos_dir * 0.1f;
      //c->vz = c->sin_dir * 0.1f;
    }
  else
    if( c->sens == -1 )
      {
	c->state |= CAR_BRAKE;
      }
    else
      {
	c->state |= CAR_ACCEL;
      }
}


void carBackwardOn( SCar* c )
{
  if( c->sens == 0 )
    {
      c->new_sens = -1;
      c->state |= CAR_ACCEL;

      //c->vx = -c->cos_dir * 0.1f;
      //c->vz = -c->sin_dir * 0.1f;
    }
  else
    if( c->sens == 1 )
      {
	c->state |= CAR_BRAKE;
      }
    else
      {
	c->state |= CAR_ACCEL;
      }
}


void carLeftOn( SCar* c )
{
  c->state |= CAR_TURN_LEFT;
}


void carRightOn( SCar* c )
{
  c->state |= CAR_TURN_RIGHT;
}


void carHandBrakeOn( SCar *c )
{
  c->state |= CAR_HANDBRAKE;
}


// press off
void carFastSteerOn( SCar *c )
{
  c->state |= CAR_FASTSTEER;
  c->fast_steer = 1.5f;
}


void carForwardOff( SCar* c )
{
  /*if( c->sens == -1 )
    {
      c->state ^= CAR_BRAKE;
    }
  else
    {
      c->state ^= CAR_ACCEL;
      }*/

  c->state &= ~CAR_ACCEL;
  c->state &= ~CAR_BRAKE;
}


void carBackwardOff( SCar* c )
{
  /*if( c->sens == -1 )
    {
      c->state ^= CAR_ACCEL;
    }
  else
    {
      c->state ^= CAR_BRAKE;
      }*/

  c->state &= ~CAR_ACCEL;
  c->state &= ~CAR_BRAKE;
}


void carLeftOff( SCar* c )
{
  c->state &= ~CAR_TURN_LEFT;
}


void carRightOff( SCar* c )
{
  c->state &= ~CAR_TURN_RIGHT;
}


void carHandBrakeOff( SCar *c )
{
  c->state &= ~CAR_HANDBRAKE;
}


void carFastSteerOff( SCar *c )
{
  c->state &= ~CAR_FASTSTEER;
  c->fast_steer = 1.0f;

  c->state &= ~CAR_HORN;
}


void carHorn( SCar *c )
{
  c->state |= CAR_HORN;
}
