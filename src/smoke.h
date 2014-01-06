//
//


//! \file smoke.h
//! \brief handle the smoke


#ifndef SMOKE_H
#define SMOKE_H


// system includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>

// user includes
#include "vector.h"
#include "camera.h"
#include "texture.h"
#include "global_vars.h"



//! \struct SSmoke
//! \brief Store all the smoke infos.
//!
//! \param start offset for adding smoke.
//! \param size max number of smoke particles
//! \param timeout used to temporize smoke creation
//! \param id smoke display list id
//! \param texture smoke texture id
//! \param smoke smoke array
typedef struct
{
  int start;
  int size;

  int timeout;

  int id;

  GLuint texture;

  float* smoke;
} SSmoke;


void smokeInit( SSmoke* s, int nb );


void smokeFree( SSmoke* s );


//! \fn void smokeGen( SSmoke* s, STexture* t );
//! \brief load texture and create display list
void smokeGen( SSmoke* s, STexture* t );


//! \fn void smokeAdd( SSmoke* s, p_Vector3f pos, float color );
//! \brief add a smoke particle.
void smokeAdd( SSmoke* s, p_Vector3f pos, float color );


//! \fn void smokeUpdate( SSmoke* s );
//! \brief update the smoke array.
void smokeUpdate( SSmoke* s );


//! \fn void smokeDraw( SSmoke* s, SCamera* c );
//! \brief draw a smoke quad facing the camera.
void smokeDraw( SSmoke* s, SCamera* c );


#endif // SMOKE_H
