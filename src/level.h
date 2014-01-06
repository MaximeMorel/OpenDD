//
//


//! \file level.h
//! \brief level loading and generation


#ifndef LEVEL_H
#define LEVEL_H


// system includes
#include <stdio.h>
#include <GL/gl.h>

// user includes
#include "texture.h"


//! \struct SLevel
//! \brief infos about a level
typedef struct
{
  float x_min, x_max;
  float y_min, y_max;
  float h;

  GLuint ground_tex;
  GLuint wall_tex;

  GLuint level;
} SLevel;


void levelInit( SLevel* l );


void levelFree( SLevel* l );


void levelLoad( SLevel* l, const char* name );


void levelLoadTextures( SLevel* l );


void levelGen( SLevel* l, STexture* t );


void levelDraw( SLevel* l );


#endif // LEVEL_H
