//
//


//! \file light.c
//!
//!


#include "light.h"


void lightInit( SLight* l )
{
  GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  GLfloat mat_shininess[] = { 10.0f };
  GLfloat mat_ambient[] = { 0.3f, 0.3f, 0.3f, 0.8f };
  GLfloat mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 0.5f };
  GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
  GLfloat light_diffuse[] = { 0.5f, 0.5f, 0.5f, 0.5f };
  GLfloat light_ambient[] = { 0.3f, 0.3f, 0.3f, 0.8f };
  GLfloat light_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  GLfloat light_model_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
  
  glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
  glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess );
  glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
  glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );

  glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
  glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient );
  glLightfv( GL_LIGHT0, GL_POSITION, light_position );
  glLightfv( GL_LIGHT0, GL_DIFFUSE, light_color );
  glLightfv( GL_LIGHT0, GL_SPECULAR, light_color );

  glLightModelfv( GL_LIGHT_MODEL_AMBIENT, light_model_ambient );

  printf( "Struct light : OK.\n" );
}


void lightFree( SLight* l )
{

  printf( "Struct light : free.\n" );
}


void lightUpdate( SLight* l )
{
  GLfloat light_position[] = { 0.2f, 1.0f, 0.2f, 0.0f };
  
  glLightfv( GL_LIGHT0, GL_POSITION, light_position );
}
