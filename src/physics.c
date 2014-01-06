//
//


//! \file physics.c
//!
//!


#include "physics.h"


//! \fn checkCollisionWorldAdv( SCar* c )
//! \brief Advanced collision check
//!
//! Realistic collision check
static p_Vector2f checkCollisionWorldAdv( SCar* c, SLevel* l );


static void wallCollide( SCar* c, p_Vector2f normal );


//! \fn checkCollisionCarAdv( SCar* c1, SCar* c2 )
//! \brief Advanced collision check between 2 cars.
//!
//! Realistic collision check
static p_Vector2f checkCollisionCarAdv( SCar* c1, SCar* c2 );


static float getCollideForce( p_Vector3f v1, p_Vector3f v2 );


//!
//!
static void carCollide( SCar* c1, SCar* c2 );


static void getConctactline( SCar* c1, p_Vector2f point, float force );





p_Vector2f checkCollisionWorld( SCar* c, SLevel* l )
{
  if( c->pos[0]-2.24f < l->x_min || c->pos[0]+2.24f > l->x_max || c->pos[2]-2.24f < l->y_min || c->pos[2]+2.24f > l->y_max )
    {      
      return checkCollisionWorldAdv( c, l );
    }
  
  return NULL;
}


p_Vector2f checkCollisionWorldAdv( SCar* c, SLevel* l )
{
  Vector2f tmp;

  carGetCorners( c );

  // corners x < x=-100
  // wall normal
  setVector2f( tmp, 1.0f, 0.0f );
  // collide force
  c->hit_power =  fabsf(c->v[0]) / CAR_MAX_SPD;
  // test
  if( c->corners[0] < l->x_min )
    { 
      c->hit_point = 1;
      c->pos[0] += ( l->x_min - c->corners[0] ) + 0.01f;
      wallCollide( c, tmp );
      return &c->corners[0];
    }
  if( c->corners[2] < l->x_min )
    { 
      c->hit_point = 2;
      c->pos[0] += ( l->x_min - c->corners[2] ) + 0.01f; 
      wallCollide( c, tmp );
      return &c->corners[2];
    }
  if( c->corners[4] < l->x_min )
    {  
      c->hit_point = 5; 
      c->pos[0] += ( l->x_min - c->corners[4] )+ 0.01f;
      wallCollide( c, tmp );
      return &c->corners[4];
    }
  if( c->corners[6] < l->x_min )
    {   
      c->hit_point = 4;
      c->pos[0] += ( l->x_min - c->corners[6 ]) + 0.01f;
      wallCollide( c, tmp );
      return &c->corners[6];
    }

  // corners x > x=100
  setVector2f( tmp, -1.0f, 0.0f );
  if( c->corners[0] > l->x_max )
    {  
      c->hit_point = 1;  
      c->pos[0] += ( l->x_max - c->corners[0] ) - 0.01f;  
      wallCollide( c, tmp );
      return &c->corners[0];
    }
  if( c->corners[2] > l->x_max )
    {   
      c->hit_point = 2;
      c->pos[0] += (l->x_max - c->corners[2] ) - 0.01f;   
      wallCollide( c, tmp );
      return &c->corners[2];
    }
  if( c->corners[4] > l->x_max )
    {   
      c->hit_point = 5;
      c->pos[0] += ( l->x_max - c->corners[4] ) - 0.01f;   
      wallCollide( c, tmp );
      return &c->corners[4];
    }
  if( c->corners[6] > l->x_max )
    {    
      c->hit_point = 4;
      c->pos[0] += ( l->x_max - c->corners[6] ) - 0.01f;  
      wallCollide( c, tmp );
      return &c->corners[6];
    }


  // corners y < y=-100
  setVector2f( tmp, 0.0f, 1.0f );
  c->hit_power =  fabsf(c->v[2]) / CAR_MAX_SPD;
  if( c->corners[1] < l->y_min )
    {    
      c->hit_point = 1;
      c->pos[2] += ( l->y_min - c->corners[1] ) + 0.01f;    
      wallCollide( c, tmp );
      return &c->corners[1];
    }
  if( c->corners[3] < l->y_min )
    {    
      c->hit_point = 2;
      c->pos[2] += ( l->y_min - c->corners[3] ) + 0.01f;    
      wallCollide( c, tmp );
      return &c->corners[3];
    }
  if( c->corners[5] < l->y_min )
    { 
      c->hit_point = 5;
      c->pos[2] += ( l->y_min - c->corners[5] ) + 0.01f;       
      wallCollide( c, tmp );
      return &c->corners[5];
    }
  if( c->corners[7] < l->y_min )
    {  
      c->hit_point = 4;
      c->pos[2] += ( l->y_min - c->corners[7] ) + 0.01f;      
      wallCollide( c, tmp );
      return &c->corners[7];
    }

  // corners y > y=100
  setVector2f( tmp, 0.0f, -1.0f );
  if( c->corners[1] > l->y_max )
    {   
      c->hit_point = 1;
      c->pos[2] += ( l->y_max - c->corners[1] ) - 0.01f;     
      wallCollide( c, tmp );
      return &c->corners[1];
    }
  if( c->corners[3] > l->y_max )
    {  
      c->hit_point = 2;
      c->pos[2] += ( l->y_max -c->corners[3] ) - 0.01f;      
      wallCollide( c, tmp );
      return &c->corners[3];
    }
  if( c->corners[5] > l->y_max )
    {  
      c->hit_point = 5;
      c->pos[2] += ( l->y_max - c->corners[5] ) - 0.01f;      
      wallCollide( c, tmp );
      return &c->corners[5];
    }
  if( c->corners[7] > l->y_max )
    {  
      c->hit_point = 4;
      c->pos[2] += ( l->y_max - c->corners[7] ) - 0.01f;      
      wallCollide( c, tmp );
      return &c->corners[7];
    }

  return NULL;
}


void wallCollide( SCar* c, p_Vector2f normal )
{
  float force;
  float dot;
  if( c->sens == 1 )
    {
      dot = dotProduct2f( normal[0], normal[1], c->dir_vect[0], c->dir_vect[2] );
    }
  else
    {
      dot = dotProduct2f( normal[0], normal[1], -c->dir_vect[0], -c->dir_vect[2] );
    }  

  if( normal[0] )
    {
      force = c->v[0] / CAR_MAX_SPD;
      c->v[0] = 0.0f;
      c->v[2] += -c->v[2] * 5.0f * g_fps->time;
    }
  else
    {
      force = c->v[2] / CAR_MAX_SPD;
      c->v[2] = 0.0f;
      c->v[0] += -c->v[0] * 5.0f * g_fps->time;
    }

  c->rotation = 20.0f * c->sens * force * DEG2RAD;

  if( c->hit_point == 1 || c->hit_point == 4 )
    {
      c->rotation *= -1.0f;
      if( fabsf(dot) < 0.35f )
	{
	  c->hit_point = 3;
	  c->hit_power *= 2.0f;
	}
    }
  else
    {
      if( fabsf(dot) < 0.35f )
	{
	  c->hit_point = 6;
	  c->hit_power *= 2.0f;
	}
    }

  if( dot < -0.95f )
    {
      c->rotation *= -1.0f;
    }

  if( normal[0] > 0.0f || normal[1] > 0.0f )
    {
      c->rotation *= -1.0f;
    }


  c->adherence += force;

  c->hit_power *= 0.5f;

  //printf( "hit %d, dot=%f\n", c->hit_point, dot );
}


p_Vector2f checkCollisionCar( SCar* c1, SCar* c2 )
{
  //bool r1, r2;
  static float* pos1;
  static float* pos2;
  //float tmp[0], tmp[2];
  //we don't do sqrtf
  float dist = (c1->pos[0]-c2->pos[0])*(c1->pos[0]-c2->pos[0]) + (c1->pos[2]-c2->pos[2])*(c1->pos[2]-c2->pos[2]);
  // because we use the sqr here
  if( dist < ((2.24f * 2.0f)*(2.24f * 2.0f)) )
    { 
      pos1 = checkCollisionCarAdv( c1, c2 );
      pos2 = checkCollisionCarAdv( c2, c1 );
      //printf( "%d, %d\n", pos1, pos2 );

      if( pos2 != NULL )
	{
	  carCollide( c2, c1 );
	  return pos2;
	}
      else
	if( pos1 != NULL )
	  {
	    carCollide( c1, c2 );
	    return pos1;
	  }
      
      /*if( pos1 != NULL )
	{
	  return pos1;
	}
      if( pos2 != NULL )
	{
	  return pos2;
	  }*/
      //return ( r1 | r2 );
    }
  //c1->car_collide = NULL;
  //c2->car_collide = NULL;

  return NULL;
}


p_Vector2f checkCollisionCarAdv( SCar* c1, SCar* c2 )
{
  static Vector2f tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8;
  
  float force = getCollideForce( c1->v, c2->v );
  force = (1.0f * force) / CAR_MAX_SPD;

  c1->hit_power = force*0.5f;

  carGetCorners( c1 );
  carGetCorners( c2 );

  // left middle side of c1 with c2 obb
  setVector2f( tmp1, c2->corners[2] - c2->corners[0], c2->corners[3] - c2->corners[1] );
  setVector2f( tmp2, c1->side[0] - c2->corners[0], c1->side[1] - c2->corners[1] );
  setVector2f( tmp3, c2->corners[4] - c2->corners[2], c2->corners[5] - c2->corners[3] );
  setVector2f( tmp4, c1->side[0] - c2->corners[2], c1->side[1] - c2->corners[3] );
  setVector2f( tmp5, c2->corners[6] - c2->corners[4], c2->corners[7] - c2->corners[5] );
  setVector2f( tmp6, c1->side[0] - c2->corners[4], c1->side[1] - c2->corners[5] );
  setVector2f( tmp7, c2->corners[0] - c2->corners[6], c2->corners[1] - c2->corners[7] );
  setVector2f( tmp8, c1->side[0] - c2->corners[6], c1->side[1] - c2->corners[7] );

  if( dotProduct2fv( tmp1, tmp2 ) >= 0 && 
      dotProduct2fv( tmp3, tmp4 ) >= 0 && 
      dotProduct2fv( tmp5, tmp6 ) >= 0 && 
      dotProduct2fv( tmp7, tmp8 ) >= 0 )
    {
      c1->hit_point = 6;
      //c1->hit_power = force;
      getConctactline( c2, &c1->side[0], force );
      //carCollide( c1, c2 );
      return &c1->side[0];
      //return true;
    }


  // right middle side of c1 with c2 obb
  //setVector2f( tmp1, c2->corners[2] - c2->corners[0], c2->corners[3] - c2->corners[1] );
  setVector2f( tmp2, c1->side[2] - c2->corners[0], c1->side[3] - c2->corners[1] );
  //setVector2f( tmp3, c2->corners[4] - c2->corners[2], c2->corners[5] - c2->corners[3] );
  setVector2f( tmp4, c1->side[2] - c2->corners[2], c1->side[3] - c2->corners[3] );
  //setVector2f( tmp5, c2->corners[6] - c2->corners[4], c2->corners[7] - c2->corners[5] );
  setVector2f( tmp6, c1->side[2] - c2->corners[4], c1->side[3] - c2->corners[5] );
  //setVector2f( tmp7, c2->corners[0] - c2->corners[6], c2->corners[1] - c2->corners[7] );
  setVector2f( tmp8, c1->side[2] - c2->corners[6], c1->side[3] - c2->corners[7] );

  if( dotProduct2fv( tmp1, tmp2 ) >= 0 && 
      dotProduct2fv( tmp3, tmp4 ) >= 0 && 
      dotProduct2fv( tmp5, tmp6 ) >= 0 && 
      dotProduct2fv( tmp7, tmp8 ) >= 0 )
    {
      c1->hit_point = 3;
      getConctactline( c2, &c1->side[2], force );
      //carCollide( c1, c2 );
      return &c1->side[2];
      //return true;
    }


  // first corner of c1 with c2 box
  //setVector2f( tmp1, c2->corners[2] - c2->corners[0], c2->corners[3] - c2->corners[1] );
  setVector2f( tmp2, c1->corners[0] - c2->corners[0], c1->corners[1] - c2->corners[1] );
  //setVector2f( tmp3, c2->corners[4] - c2->corners[2], c2->corners[5] - c2->corners[3] );
  setVector2f( tmp4, c1->corners[0] - c2->corners[2], c1->corners[1] - c2->corners[3] );
  //setVector2f( tmp5, c2->corners[6] - c2->corners[4], c2->corners[7] - c2->corners[5] );
  setVector2f( tmp6, c1->corners[0] - c2->corners[4], c1->corners[1] - c2->corners[5] );
  //setVector2f( tmp7, c2->corners[0] - c2->corners[6], c2->corners[1] - c2->corners[7] );
  setVector2f( tmp8, c1->corners[0] - c2->corners[6], c1->corners[1] - c2->corners[7] );

  if( dotProduct2fv( tmp1, tmp2 ) >= 0 && 
      dotProduct2fv( tmp3, tmp4 ) >= 0 && 
      dotProduct2fv( tmp5, tmp6 ) >= 0 && 
      dotProduct2fv( tmp7, tmp8 ) >= 0 )
    {
      c1->hit_point = 1;
      getConctactline( c2, &c1->corners[0], force );
      //carCollide( c1, c2 );
      return &c1->corners[0];
      //return true;
    }


  // second corner of c1 with c2 box
  //setVector2f( tmp1, c2->corners[2] - c2->corners[0], c2->corners[3] - c2->corners[1] );
  setVector2f( tmp2, c1->corners[2] - c2->corners[0], c1->corners[3] - c2->corners[1] );
  //setVector2f( tmp3, c2->corners[4] - c2->corners[2], c2->corners[5] - c2->corners[3] );
  setVector2f( tmp4, c1->corners[2] - c2->corners[2], c1->corners[3] - c2->corners[3] );
  //setVector2f( tmp5, c2->corners[6] - c2->corners[4], c2->corners[7] - c2->corners[5] );
  setVector2f( tmp6, c1->corners[2] - c2->corners[4], c1->corners[3] - c2->corners[5] );
  //setVector2f( tmp7, c2->corners[0] - c2->corners[6], c2->corners[1] - c2->corners[7] );
  setVector2f( tmp8, c1->corners[2] - c2->corners[6], c1->corners[3] - c2->corners[7] );
  
  if( dotProduct2fv( tmp1, tmp2 ) >= 0 && 
      dotProduct2fv( tmp3, tmp4 ) >= 0 && 
      dotProduct2fv( tmp5, tmp6 ) >= 0 && 
      dotProduct2fv( tmp7, tmp8 ) >= 0 )
    {
      c1->hit_point = 2;
      getConctactline( c2, &c1->corners[2], force );
      //carCollide( c1, c2 );
      return &c1->corners[2];
      //return true;
    }


  // third corner of c1 with c2 box
  //setVector2f( tmp1, c2->corners[2] - c2->corners[0], c2->corners[3] - c2->corners[1] );
  setVector2f( tmp2, c1->corners[4] - c2->corners[0], c1->corners[5] - c2->corners[1] );
  //setVector2f( tmp3, c2->corners[4] - c2->corners[2], c2->corners[5] - c2->corners[3] );
  setVector2f( tmp4, c1->corners[4] - c2->corners[2], c1->corners[5] - c2->corners[3] );
  //setVector2f( tmp5, c2->corners[6] - c2->corners[4], c2->corners[7] - c2->corners[5] );
  setVector2f( tmp6, c1->corners[4] - c2->corners[4], c1->corners[5] - c2->corners[5] );
  //setVector2f( tmp7, c2->corners[0] - c2->corners[6], c2->corners[1] - c2->corners[7] );
  setVector2f( tmp8, c1->corners[4] - c2->corners[6], c1->corners[5] - c2->corners[7] );
      
  if( dotProduct2fv( tmp1, tmp2 ) >= 0 && 
      dotProduct2fv( tmp3, tmp4 ) >= 0 && 
      dotProduct2fv( tmp5, tmp6 ) >= 0 && 
      dotProduct2fv( tmp7, tmp8 ) >= 0 )
    {
      c1->hit_point = 5;
      getConctactline( c2, &c1->corners[4], force );
      //carCollide( c1, c2 );
      return &c1->corners[4];
      //return true;
    }


  // forth corner of c1 with c2 box
  //setVector2f( tmp1, c2->corners[2] - c2->corners[0], c2->corners[3] - c2->corners[1] );
  setVector2f( tmp2, c1->corners[6] - c2->corners[0], c1->corners[7] - c2->corners[1] );
  //setVector2f( tmp3, c2->corners[4] - c2->corners[2], c2->corners[5] - c2->corners[3] );
  setVector2f( tmp4, c1->corners[6] - c2->corners[2], c1->corners[7] - c2->corners[3] );
  //setVector2f( tmp5, c2->corners[6] - c2->corners[4], c2->corners[7] - c2->corners[5] );
  setVector2f( tmp6, c1->corners[6] - c2->corners[4], c1->corners[7] - c2->corners[5] );
  //setVector2f( tmp7, c2->corners[0] - c2->corners[6], c2->corners[1] - c2->corners[7] );
  setVector2f( tmp8, c1->corners[6] - c2->corners[6], c1->corners[7] - c2->corners[7] );
      
  if( dotProduct2fv( tmp1, tmp2 ) >= 0 && 
      dotProduct2fv( tmp3, tmp4 ) >= 0 && 
      dotProduct2fv( tmp5, tmp6 ) >= 0 && 
      dotProduct2fv( tmp7, tmp8 ) >= 0 )
    {
      c1->hit_point = 4;
      getConctactline( c2, &c1->corners[6], force );
      //carCollide( c1, c2 );
      return &c1->corners[6];
      //return true;
    }
  //return false;
  return NULL;     	   
}


float getCollideForce( p_Vector3f v1, p_Vector3f v2 )
{
  Vector3f tmp;

  setVector3fv( tmp, v1 );
  subVector3fv( tmp, v2 );

  return module3fv( tmp );
}


void carCollide( SCar* c1, SCar* c2 )
{
  static float v1x, v1z;
  v1x = c1->v[0];
  v1z = c1->v[2];

  //carRestorePos( c1 );
  //carRestorePos( c2 );

  // rotation score
  if( !(c1->state & CAR_DEAD ) && !(c2->state & CAR_DEAD ) )
    {
      c1->car_collide = c2;
      c2->car_collide = c1;
      c1->score_timeout = g_fps->time_now + 1500;
      c2->score_timeout = g_fps->time_now + 1500;
      c1->car_collide_rotation = 0;
      c2->car_collide_rotation = 0;
      c1->car_collide_rotation_old = 0;
      c2->car_collide_rotation_old = 0;
    }
  

  // avoid cars being stuck
  Vector3f tmp;
  setVector3fv( tmp, c2->pos );
  subVector3fv( tmp, c1->pos );

  mulVector3f( tmp, 2.0f * g_fps->time );
  //normalize3fv( tmp );
  //mulVector3f( tmp, 0.05f );

  subVector3fv( c1->pos, tmp );
  sumVector3fv( c2->pos, tmp );


  /*if( c1->car_collide == NULL )
    {
      c1->car_collide = c2;
    }
  else
    {
      Vector3f tmp;
      setVector3fv( tmp, c1->car_collide->pos );
      subVector3fv( tmp, c1->pos );

      //mulVector3f( tmp, 0.7f );

      subVector3fv( c1->pos, tmp );
      sumVector3fv( c1->car_collide->pos, tmp );
    }

  if( c2->car_collide == NULL )
    {
      c2->car_collide = c1;
    }
  else
    {
      Vector3f tmp;
      setVector3fv( tmp, c2->car_collide->pos );
      subVector3fv( tmp, c2->pos );

      //mulVector3f( tmp, 0.7f );

      subVector3fv( c2->pos, tmp );
      sumVector3fv( c2->car_collide->pos, tmp );
      }*/
    

  // restore last position without collision
  //carRestorePos( c1 );
  //c1->pos[0] = c1->pos_old[0];
  //c1->pos[2] = c1->pos_old[2];

  // if the car is stopped, give a sens
  if( c1->speed < CAR_THRESHOLD )
    {
      setVector3fv( c1->v, c2->v );
      c1->sens = 1;
      c1->speed = module3fv( c1->v );
      carGetSens( c1 );
      c1->adherence = 1.0f;

      mulVector3f( c2->v, 0.5f );
      return;
    }
  else
    {
      //c1->v[0] = ( c1->v[0] + c2->v[0] ) / 2.0f;
      //c1->v[2] = ( c1->v[2] + c2->v[2] ) / 2.0f;
      mulVector3f( c1->v, 0.5f );
    }

  //c1->v[0] = 0;
  //c1->v[2] = 0;

  // restore last position without collision
  //carRestorePos( c2 );
  //c2->pos[0] = c2->pos_old[0];
  //c2->pos[2] = c2->pos_old[2];
  
  // if the car is stopped, give a sens
  if( c2->speed < CAR_THRESHOLD )
    {
      setVector3fv( c2->v, c1->v );
      c2->sens = 1;
      c2->speed = module3fv( c2->v );
      carGetSens( c2 );  
      c2->adherence = 1.0f;

      mulVector3f( c1->v, 0.5f );
      return;
    }
  else
    {
      //c2->v[0] = ( c2->v[0] + v1x ) / 2.0f;
      //c2->v[2] = ( c2->v[2] + v1z ) / 2.0f;
      mulVector3f( c2->v, 0.5f );
    }

  //c2->v[0] = 0;
  //c2->v[2] = 0;

   // set adherence after a crash
  c1->adherence += 0.5f;
  c2->adherence += 0.5f;
}


void getConctactline( SCar* c1, p_Vector2f point, float force )
{
  static Vector2f tmp1, tmp2;
  float m, d, d_tmp, rotate_coeff, r_tmp;
  int side;

  // distance of point to c1 front side
  setVector2f( tmp1, c1->corners[2] - c1->corners[0], c1->corners[3] - c1->corners[1] );
  setVector2f( tmp2, point[0] - c1->corners[0], point[1] - c1->corners[1] );

  m = module2fv(tmp2);
  rotate_coeff = dotProduct2fv( tmp1, tmp2 ) / module2fv(tmp1);
  d = m*m - rotate_coeff*rotate_coeff;
  //d = sqrtf( d );
  side = 1;//printf("1 - %d side:%d  d:%f  r:%f\n",c1->id, side, d, rotate_coeff );

  // distance of point to c1 right side
  setVector2f( tmp1, c1->corners[2] - c1->corners[4], c1->corners[3] - c1->corners[5] );
  setVector2f( tmp2, point[0] - c1->corners[4], point[1] - c1->corners[5] );

  m = module2fv(tmp2);
  r_tmp = dotProduct2fv( tmp1, tmp2 ) / module2fv(tmp1);
  d_tmp = m*m - r_tmp*r_tmp;
  if( d_tmp < d )
    {
      d = d_tmp;
      rotate_coeff = r_tmp;
      side = 4;
    }//printf("2 - %d side:%d  d:%f  r:%f\n",c1->id, side, d, rotate_coeff );

  // distance of point to c1 back side
  setVector2f( tmp1, c1->corners[6] - c1->corners[4], c1->corners[7] - c1->corners[5] );
  setVector2f( tmp2, point[0] - c1->corners[4], point[1] - c1->corners[5] );

  m = module2fv(tmp2);
  r_tmp = dotProduct2fv( tmp1, tmp2 ) / module2fv(tmp1);
  d_tmp = m*m - r_tmp*r_tmp;
  if( d_tmp < d )
    {
      d = d_tmp;
      rotate_coeff = r_tmp;
      side = 3;
    }//printf("3 - %d side:%d  d:%f  r:%f\n",c1->id, side, d, rotate_coeff  );

  // distance of point to c1 left side
  setVector2f( tmp1, c1->corners[0] - c1->corners[6], c1->corners[1] - c1->corners[7] );
  setVector2f( tmp2, point[0] - c1->corners[6], point[1] - c1->corners[7] );

  m = module2fv(tmp2);
  r_tmp = dotProduct2fv( tmp1, tmp2 ) / module2fv(tmp1);
  d_tmp = m*m - r_tmp*r_tmp;
  if( d_tmp < d )
    {
      d = d_tmp;
      rotate_coeff = r_tmp;
      side = 2;
    }//printf("end - %d side:%d  d:%f  r:%f\n",c1->id, side, d, rotate_coeff );

  d = sqrtf( d );

  switch( side )
    {
    case 1 :
      rotate_coeff -= 1.0f;
      rotate_coeff *= -0.25f;
      break;
      
    case 2 :
      rotate_coeff -= 2.0f;
      rotate_coeff *= -1.0f;
      break;

    case 3 :
      rotate_coeff -= 1.0f;
      rotate_coeff *= 0.25f;
      break;
      
    case 4 :
      rotate_coeff -= 2.0f;
      break;

    default :
      break;
    }

  //printf("end2 - %d side:%d  d:%f  r:%f  f:%f\n",c1->id, side, d, rotate_coeff, force );
  c1->rotation += 10.0f * force * rotate_coeff * DEG2RAD;
  c1->adherence += force;
}
