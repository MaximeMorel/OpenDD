//
//


//! \file ai_player.c
//!
//!


#include "ai_player.h"


void aiInit( SPlayerAI* ai, int mode )
{
  ai->timeout = 0;
  ai->action_timeout = 0;
  ai->action_sub_timeout = 0;
  ai->sub_timeout = 0;

  ai->state = AI_IDLE;

  ai->car = NULL;

  setVector2f( ai->pos_target, 0, 0 );

  //if( mode == GAME_TOTAL_DESTRUCTION )
  if( mode == 2 )
    {
      ai->aiGetTarget = &aiGetTargetPlayer;
    }
  else
    {
      ai->aiGetTarget = &aiGetTargetMax;
    }

  printf( "Struct AI : OK.\n" );
}


void aiFree( SPlayerAI* ai )
{
  printf( "Struct AI : free.\n" );
}



void aiUpdate( SPlayerAI* ai, SLevel* l )
{
  if( ai->sub_timeout < g_fps->time_now )
    {
      carHandBrakeOff( ai->car );
      if( ai->car->collision )
	{
	  int rand_time = ((float)rand()/RAND_MAX)*5000;
	  ai->action_timeout = g_fps->time_now + rand_time;
	  ai->state = AI_STUCK;
	  return;
	}

      // fix ai blocked every 5 sec
      if( ai->stuck_timeout < g_fps->time_now )
	{	  
	  aiIdle( ai );
	  ai->stuck_timeout = g_fps->time_now + 5000;
	  return;
	}
      
      switch( ai->state )
	{
	case AI_IDLE :
	  ai->aiGetTarget( ai );

	  if( ai->target != NULL )
	    {
	      ai->state = AI_CHASE;
	    }
	  break;
	  
	case AI_CHASE :
	  if( ai->action_timeout > g_fps->time_now )
	      {
		aiChase( ai );
	      }
	    else
	      {
		ai->state = AI_IDLE;
	      }
	  break;
	  
	case AI_STUCK :
	  if( ai->action_timeout > g_fps->time_now )
	    {
	      aiUnstuck( ai, l );
	    }
	  else
	    {
	      ai->state = AI_IDLE;
	    }
	  break;
	  
	case AI_HALFWAY:
	  break;

	default :
	  break;
	}

      ai->sub_timeout = g_fps->time_now + 100;
    }
}


void aiSetTimeOut( SPlayerAI* ai, int time )
{
  ai->timeout = g_fps->time_now + time;
}


void aiChase( SPlayerAI* ai )
{
  bool target_left;
  Vector3f car2target, tmp;
  //float dist;
  
  setVector3fv( car2target, ai->target->pos );
  subVector3fv( car2target, ai->car->pos );
  //dist = module3fv( camera2car );
  //mulVector3fv( camera2car, 1.0f/dist );
  normalize3fv( car2target );

  target_left = false;

  // side test
  setVector3f( tmp, 1.0f, 0.0f, 0.0f );
  /*if( dotProduct3fv( ai->car->dir_vect, tmp ) > 0.0f )
    { 
      setVector3f( tmp, -ai->car->dir_vect[2], ai->car->dir_vect[1], ai->car->dir_vect[0] );
    }
  else
    {
      setVector3f( tmp, ai->car->dir_vect[2], ai->car->dir_vect[1], -ai->car->dir_vect[0] );
      }*/

  setVector3f( tmp, ai->car->dir_vect[2], ai->car->dir_vect[1], -ai->car->dir_vect[0] );

  if( dotProduct3fv( tmp, car2target ) > 0.0f )
    {
      target_left = true;
    }
  
  if( dotProduct3fv( ai->car->dir_vect, car2target ) > 0.0f )
    {      
      aiCarForward( ai );
      //aiCarNoTurn( ai );
      if( target_left )
	{
	  aiCarLeft( ai );
	}
      else
	{
	  aiCarRight( ai );
	}
    }
  else
    {
      aiCarBackward( ai );
      //aiCarRight( ai );
      //aiCarNoTurn( ai );
      /*if( target_left )
	{
	  aiCarLeft( ai );
	}
      else
	{
	  aiCarRight( ai );
	  }*/
      //aiCarNoAccel( ai );
      //ai->state = AI_IDLE;
    }

  if( dotProduct3fv( ai->car->dir_vect, car2target ) > 0.95f )
    {
      aiCarNoTurn( ai );
      //aiCarLeft( ai );
    }
}


void aiUnstuck( SPlayerAI* ai, SLevel* l )
{
  if( ai->pos_target[0] != 0.0f && ai->pos_target[2] != 0.0f )
    {
      bool target_left = false;
      Vector3f car2target, tmp;
      
      setVector3fv( car2target, ai->pos_target );
      subVector3fv( car2target, ai->car->pos );
      
      normalize3fv( car2target );

      // side test
      setVector3f( tmp, 1.0f, 0.0f, 0.0f );
      /*if( dotProduct3fv( ai->car->dir_vect, tmp ) > 0.0f )
	{ 
	setVector3f( tmp, -ai->car->dir_vect[2], ai->car->dir_vect[1], ai->car->dir_vect[0] );
	}
	else
	{
	setVector3f( tmp, ai->car->dir_vect[2], ai->car->dir_vect[1], -ai->car->dir_vect[0] );
	}*/
      
      setVector3f( tmp, ai->car->dir_vect[2], ai->car->dir_vect[1], -ai->car->dir_vect[0] );

  if( dotProduct3fv( tmp, car2target ) > 0.0f )
    {
      target_left = true;
    }
  
  if( dotProduct3fv( ai->car->dir_vect, car2target ) > 0.0f )
    {      
      aiCarForward( ai );
      //aiCarNoTurn( ai );
      if( target_left )
	{
	  aiCarLeft( ai );
	}
      else
	{
	  aiCarRight( ai );
	}
    }
  else
    {
      carHandBrakeOn( ai->car );
      aiCarBackward( ai );
      //aiCarRight( ai );
      //aiCarNoTurn( ai );
      /*if( target_left )
	{
	  aiCarLeft( ai );
	}
      else
	{
	  aiCarRight( ai );
	  }*/
      //aiCarNoAccel( ai );
      //ai->state = AI_IDLE;
    }

  if( dotProduct3fv( ai->car->dir_vect, car2target ) > 0.9f )
    {
      aiCarNoTurn( ai );
      //aiCarLeft( ai );
    }
    }
  else
    {
      // generate a random point in the level
      float rx, ry;
      rx = (((float)rand()/RAND_MAX)*(l->x_max - l->x_min))+l->x_min;
      ry = (((float)rand()/RAND_MAX)*(l->y_max - l->y_min))+l->y_min;
      
      setVector3f( ai->pos_target, rx, 0.0f, ry );

      //printf( "pos %f,%f\n", ai->pos_target[0], ai->pos_target[2] );
    }
}


void aiGetTargetRandom( SPlayerAI* ai )
{
  SCar* c = ai->car;
  int i, r;  

  r = ((float)rand()/RAND_MAX)*(*g_nb_car);

  // go through the circle linked list to find a random target
  for( i = 0; i <= r; i++ )
    {
      c = c->next;
    }

  if( c != ai->car && !(c->state & CAR_DEAD))
    {
      int rand_time = ((float)rand()/RAND_MAX)*20000;
      ai->target = c;
      ai->action_timeout = g_fps->time_now + rand_time;
      //printf( "car %d -> %d for %d\n", ai->car->id, ai->target->id, rand_time );
    }
  else
    {
      ai->target = NULL;
    }  
}


void aiGetTargetMax( SPlayerAI* ai )
{
  SCar* c = ai->car;
  int i, rand_time;
  float max = 0.0f;
  Vector3f tmp;

  // go through the circle linked list to find the max distant target
  for( i = 0; i <= *g_nb_car; i++ )
    {
      float tmp_max;

      c = c->next;

      if( c->state & CAR_DEAD )
	{
	  continue;
	}

      setVector3fv( tmp, ai->car->pos );
      subVector3fv( tmp, c->pos );

      tmp_max = module3fv( tmp );

      if( tmp_max > max )
	{
	  max = tmp_max;
	  ai->target = c;
	}
    }

  rand_time = ((float)rand()/RAND_MAX)*20000;
  ai->action_timeout = g_fps->time_now + rand_time;
}


void aiGetTargetPlayer( SPlayerAI* ai )
{
  SCar* c = ai->car;
  int i;
  float rand_time;

  for( i = 0; i <= *g_nb_car; i++ )
    {
      //printf( "c %d -> %d\n", ai->car->id , c->id );
      if( c->id == 0 )
	{
	  ai->target = c;
	  break;
	}
      c = c->next;
    }

  rand_time = ((float)rand()/RAND_MAX)*20000;
  ai->action_timeout = g_fps->time_now + rand_time;
}


void aiUpdateTargetPos( SPlayerAI* ai )
{

}


void aiCarForward( SPlayerAI* ai )
{
  carBackwardOff( ai->car );
  carForwardOn( ai->car );
}

void aiCarBackward( SPlayerAI* ai )
{
  carForwardOff( ai->car );
  carBackwardOn( ai->car );
}


void aiCarLeft( SPlayerAI* ai )
{
  carRightOff( ai->car );
  carLeftOn( ai->car );
}


void aiCarRight( SPlayerAI* ai )
{
  carLeftOff( ai->car );
  carRightOn( ai->car );
}


void aiCarBrake( SPlayerAI* ai )
{
  
}


void aiCarNoTurn( SPlayerAI* ai )
{
  carRightOff( ai->car );
  carLeftOff( ai->car );
}


void aiCarNoAccel( SPlayerAI* ai )
{
  carForwardOff( ai->car );
  carBackwardOff( ai->car );
}


void aiIdle( SPlayerAI* ai )
{
  carForwardOff( ai->car );
  carBackwardOff( ai->car );
  carRightOff( ai->car );
  carLeftOff( ai->car );
  carHandBrakeOff( ai->car );
  carFastSteerOff( ai->car );
}
