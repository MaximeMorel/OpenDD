//
//


//!
//!


#include "skybox.h"


void skyboxInit( SSkybox* s )
{
  s->id = 0;

  s->front_tex = 0;
  s->back_tex = 0;
  s->down_tex = 0;
  s->up_tex = 0;
  s->right_tex = 0;
  s->left_tex = 0;

  printf( "Struct skybox : OK.\n" );
}

void skyboxFree( SSkybox* s )
{
  if( glIsTexture(s->front_tex) )
    glDeleteTextures( 1, &s->front_tex );
  
  if( glIsTexture(s->back_tex) )
    glDeleteTextures( 1, &s->back_tex );
  
  if( glIsTexture(s->down_tex) )
    glDeleteTextures( 1, &s->down_tex );
  
  if( glIsTexture(s->up_tex) )
    glDeleteTextures( 1, &s->up_tex );
  
  if( glIsTexture(s->right_tex) )
    glDeleteTextures( 1, &s->right_tex );
  
  if( glIsTexture(s->left_tex) )
    glDeleteTextures( 1, &s->left_tex );

  glDeleteLists( s->id, 1 );

  printf( "Struct skybox : free.\n" );
}


void skyboxLoadTexture( SSkybox* s, STexture* t )
{
  s->front_tex = loadTexture( t, "data/textures/skybox/ft1.jpg", GL_RGB, GL_CLAMP_TO_EDGE, true);
  s->back_tex = loadTexture( t, "data/textures/skybox/bk1.jpg", GL_RGB, GL_CLAMP_TO_EDGE, true);
  s->down_tex = loadTexture( t, "data/textures/skybox/dn1.jpg", GL_RGB, GL_CLAMP_TO_EDGE, true);
  s->up_tex = loadTexture( t, "data/textures/skybox/up1.jpg", GL_RGB, GL_CLAMP_TO_EDGE, true);
  s->right_tex = loadTexture( t, "data/textures/skybox/rt1.jpg", GL_RGB, GL_CLAMP_TO_EDGE, true);
  s->left_tex = loadTexture( t, "data/textures/skybox/lt1.jpg", GL_RGB, GL_CLAMP_TO_EDGE, true);

  printf( "Load skybox texture.\n" );
}


void skyboxGen( SSkybox* s )
{
  s->id = glGenLists( 1 );
  glNewList( s->id, GL_COMPILE );
  // skybox
  glFrontFace( GL_CW );
  glColor3f( 1.0f ,1.0f ,1.0f );
  glEnable( GL_TEXTURE_2D );
  glDisable( GL_LIGHTING );
  glDisable( GL_DEPTH_TEST );
  glDepthMask( GL_FALSE );
  
  // bk
  glBindTexture( GL_TEXTURE_2D, s->front_tex );
  glBegin( GL_QUADS );
  glTexCoord2f( 0, 0 );	glVertex3f( -0.5, 0.5, 0.5 );
  glTexCoord2f( 0, 1 );	glVertex3f( -0.5, -0.5, 0.5 );
  glTexCoord2f( 1, 1 );	glVertex3f( 0.5, -0.5, 0.5 );
  glTexCoord2f( 1, 0 );	glVertex3f( 0.5, 0.5, 0.5 );
  glEnd();
  
  // lt
  glBindTexture( GL_TEXTURE_2D, s->right_tex );
  glBegin( GL_QUADS );
  glTexCoord2f( 0, 0 );	glVertex3f( 0.5, 0.5, 0.5 );
  glTexCoord2f( 0, 1 );	glVertex3f( 0.5, -0.5, 0.5 );
  glTexCoord2f( 1, 1 );	glVertex3f( 0.5, -0.5, -0.5 );
  glTexCoord2f( 1, 0 );	glVertex3f( 0.5, 0.5, -0.5 );
  glEnd();
  
  // ft
  glBindTexture( GL_TEXTURE_2D, s->back_tex );
  glBegin( GL_QUADS );
  glTexCoord2f( 0, 0 );	glVertex3f( 0.5, 0.5, -0.5 );
  glTexCoord2f( 0, 1 );	glVertex3f( 0.5, -0.5, -0.5 );
  glTexCoord2f( 1, 1 );	glVertex3f( -0.5, -0.5, -0.5 );
  glTexCoord2f( 1, 0 );	glVertex3f( -0.5, 0.5, -0.5 );
  glEnd();
  
  // rt
  glBindTexture( GL_TEXTURE_2D, s->left_tex );
  glBegin( GL_QUADS );
  glTexCoord2f( 0, 0 );	glVertex3f( -0.5, 0.5, -0.5 );
  glTexCoord2f( 0, 1 );	glVertex3f( -0.5, -0.5, -0.5 );
  glTexCoord2f( 1, 1 );	glVertex3f( -0.5, -0.5, 0.5 );
  glTexCoord2f( 1, 0 );	glVertex3f( -0.5, 0.5, 0.5 );
  glEnd();
  
  // up
  glBindTexture( GL_TEXTURE_2D, s->up_tex );
  glBegin( GL_QUADS );
  glTexCoord2f( 0, 0 );	glVertex3f( -0.5, 0.5, -0.5 );
  glTexCoord2f( 0, 1 );	glVertex3f( -0.5, 0.5, 0.5 );
  glTexCoord2f( 1, 1 );	glVertex3f( 0.5, 0.5, 0.5 );
  glTexCoord2f( 1, 0 );	glVertex3f( 0.5, 0.5, -0.5 );
  glEnd();
  
  // down
  glBindTexture( GL_TEXTURE_2D, s->down_tex );
  glBegin( GL_QUADS );
  //glTexCoord2f ( 0.0, 0.0 );
  glTexCoord2f( 1.0, 1.0 );	glVertex3f( 0.5, -0.5, -0.5 );
  //glTexCoord2f ( 0.0, 1.0 );
  glTexCoord2f( 1.0, 0.0 );	glVertex3f( 0.5, -0.5, 0.5 );
  //glTexCoord2f ( 1.0, 1.0 );
  glTexCoord2f( 0.0, 0.0 );	glVertex3f( -0.5, -0.5, 0.5 );
  //glTexCoord2f ( 1.0, 0.0 );
  glTexCoord2f( 0.0, 1.0 );	glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();
  
  glFrontFace( GL_CCW );
  glDepthMask( GL_TRUE );
  glEnable( GL_DEPTH_TEST );
  glEnable( GL_LIGHTING );
  
  glEndList();
}
