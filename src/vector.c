//
//


#include "vector.h"


void setVector2f( p_Vector2f v, float x, float y )
{
  v[0] = x;
  v[1] = y;
}


void setVector2fv( p_Vector2f v, p_Vector2f src )
{
  v[0] = src[0];
  v[1] = src[1];
}


void setVector3f( p_Vector3f v, float x, float y, float z )
{
  v[0] = x;
  v[1] = y;
  v[2] = z;
}


void setVector3fv( p_Vector3f v, p_Vector3f src )
{
  v[0] = src[0];
  v[1] = src[1];
  v[2] = src[2];
}


void sumVector2f( p_Vector2f v, float x, float y )
{
  v[0] += x;
  v[1] += y;
}


void sumVector2fv( p_Vector2f v, p_Vector2f s )
{
  v[0] += s[0];
  v[1] += s[1];
}


void sumVector3f( p_Vector3f v, float x, float y, float z )
{
  v[0] += x;
  v[1] += y;
  v[2] += z;
}


void sumVector3fv( p_Vector3f v, p_Vector3f s )
{
  v[0] += s[0];
  v[1] += s[1];
  v[2] += s[2];
}


void subVector2f( p_Vector2f v, float x, float y )
{
  v[0] -= x;
  v[1] -= y;
}


void subVector2fv( p_Vector2f v, p_Vector2f s )
{
  v[0] -= s[0];
  v[1] -= s[1];
}


void subVector3f( p_Vector3f v, float x, float y, float z )
{
  v[0] -= x;
  v[1] -= y;
  v[2] -= z;
}


void subVector3fv( p_Vector3f v, p_Vector3f s )
{
  v[0] -= s[0];
  v[1] -= s[1];
  v[2] -= s[2];
}


void mulVector2f( p_Vector2f v, float k )
{
  v[0] *= k;
  v[1] *= k;
}


void mulVector3f( p_Vector3f v, float k )
{
  v[0] *= k;
  v[1] *= k;
  v[2] *= k;
}


float module2f( float vx, float vy )
{
  return sqrtf( ( vx * vx ) + ( vy * vy ) );
}


float module2fv( p_Vector2f v )
{
  return sqrtf( ( v[0] * v[0] ) + ( v[1] * v[1] ) );
}


float sqrModule2f( float vx, float vy )
{
  return ( vx * vx ) + ( vy * vy );
}


float sqrModule2fv( p_Vector2f v )
{
  return ( v[0] * v[0] ) + ( v[1] * v[1] );
}


float module3fv( p_Vector3f v )
{
  return sqrtf( ( v[0] * v[0] ) + ( v[1] * v[1] ) + ( v[2] * v[2] ) );
}


float sqrModule3fv( p_Vector3f v )
{
  return ( v[0] * v[0] ) + ( v[1] * v[1] ) + ( v[2] * v[2] );
}


float sqrModule3f( float vx, float vy, float vz )
{
  return ( vx * vx ) + ( vy * vy ) + ( vz * vz );
}


void normalize2fv( p_Vector2f v )
{
  float m = module2fv( v );
  v[0] /= m;
  v[1] /= m;
}


void normalize3fv( p_Vector3f v )
{
  float m = module3fv( v );
  if( m != 0.0f )
    {
      v[0] /= m;
      v[1] /= m;
      v[2] /= m;
    }
}


float dotProduct2fv( p_Vector2f v1, p_Vector2f v2 )
{
  return v1[0] * v2[0] + v1[1] * v2[1];
}


float dotProduct3fv( p_Vector3f v1, p_Vector3f v2 )
{
  return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}


float dotProduct2f( float x1, float y1, float x2, float y2 )
{
  return x1 * x2 + y1 * y2;
}


float dotProduct3f( float x1, float y1, float z1, float x2, float y2, float z2 )
{
  return x1 * x2 + y1 * y2 + z1 * z2;
}


void rotateVector3f( p_Vector3f v, float a )
{
  v[0] = v[0] * cosf(a) - v[2] * sinf(a);
  v[2] = v[0] * sinf(a) + v[2] * cosf(a);
}


void crossProduct( p_Vector3f crossprod, p_Vector3f vect1 , p_Vector3f vect2 )
{
  crossprod[0] = ( vect1[1] * vect2[2] ) - ( vect2[1] * vect1[2] );
  crossprod[1] = ( vect1[2] * vect2[0] ) - ( vect2[2] * vect1[0] );
  crossprod[2] = ( vect1[0] * vect2[1] ) - ( vect2[0] * vect1[1] );
}


void printVector3fv( p_Vector3f v )
{
  printf( "V(%f,%f,%f)\n",v[0], v[1], v[2] );
}


void printfVector2fv( p_Vector2f v )
{
  printf( "V(%f,%f)\n",v[0], v[1] );
}
