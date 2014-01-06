//
//


//! \file skybox.h
//!


#ifndef SKYBOX_H
#define SKYBOX_H


// system includes
#include <GL/gl.h>

// user includes
//#include "render.h"
#include "texture.h"


//! \struct SSkybox
//! \brief store a skybox
//!
//! \param id id of the skybox display list
typedef struct
{
  GLuint id;

  GLuint front_tex;
  GLuint back_tex;
  GLuint down_tex;
  GLuint up_tex;
  GLuint right_tex;
  GLuint left_tex;
} SSkybox;


void skyboxInit( SSkybox* s );


void skyboxFree( SSkybox* s );


//! \fn void skyboxLoadTexture( SSkybox* s, STexture* t );
//! \brief load skybox textures
void skyboxLoadTexture( SSkybox* s, STexture* t );


//! \fn void skyboxGen( SSkybox* s );
//! \brief create skybox
void skyboxGen( SSkybox* s );


#endif // SKYBOX_H
