//
//


#ifndef VECTOR_H
#define VECTOR_H


//! \file vector.h
//! \brief
//!
//!


// system includes
#include <stdio.h>
#include <math.h>

// user includes


typedef float Vector2f[2];
typedef float Vector3f[3];
typedef float Vector4f[4];

typedef float* p_Vector2f;
typedef float* p_Vector3f;
typedef float* p_Vector4f;


void setVector2f( p_Vector2f v, float x, float y );
void setVector2fv( p_Vector2f v, p_Vector2f src );
void setVector3f( p_Vector3f v, float x, float y, float z );
void setVector3fv( p_Vector3f v, p_Vector3f src );

void sumVector2f( p_Vector2f v, float x, float y );
void sumVector2fv( p_Vector2f v, p_Vector2f s );
void sumVector3f( p_Vector3f v, float x, float y, float z );
void sumVector3fv( p_Vector3f v, p_Vector3f s );

void subVector2f( p_Vector2f v, float x, float y );
void subVector2fv( p_Vector2f v, p_Vector2f s );
void subVector3f( p_Vector3f v, float x, float y, float z );
void subVector3fv( p_Vector3f v, p_Vector3f s );

void mulVector2f( p_Vector2f v, float k );
void mulVector3f( p_Vector3f v, float k );

float module2f( float vx, float vy );
float module2fv( p_Vector2f v );
float module3fv( p_Vector3f v );

float sqrModule2f( float vx, float vy );
float sqrModule2fv( p_Vector2f v );
float sqrModule3fv( p_Vector3f v );
float sqrModule3f( float vx, float vy, float vz );

void normalize2fv( p_Vector2f v );
void normalize3fv( p_Vector3f v );

float dotProduct2fv( p_Vector2f v1, p_Vector2f v2 );
float dotProduct3fv( p_Vector3f v1, p_Vector3f v2 );
float dotProduct2f( float x1, float y1, float x2, float y2 );
float dotProduct3f( float x1, float y1, float z1, float x2, float y2, float z2 );

void crossProduct( p_Vector3f crossprod, p_Vector3f vect1 , p_Vector3f vect2 );

void rotateVector3f( p_Vector3f v, float a );


void printVector3fv( p_Vector3f v );


void printfVector2fv( p_Vector2f v );


#endif // VECTOR_H
