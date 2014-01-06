//
//


//! \file font.h
//! \brief bitmap font engine.


#ifndef FONT_H
#define FONT_H


// system includes
#include <GL/gl.h>
#include <stdio.h>

// user includes
#include "texture.h"


//! \struct SFont
//! \brief few info on font
//!
//! \param offset internal use
//! \param texture id of the font texture internal use
typedef struct
{
  int offset;
  GLuint texture;
} SFont;


void fontInit( SFont* f );


void fontFree( SFont* f, STexture* t );


void fontGen( SFont* f, STexture* t );


void glPrintf( SFont* f, const char *text, float x, float y, float size);


#endif // FONT_H
