// VITANOSTRA Franck
//


//! \file particle.h
//!


#ifndef PARTICLE_H
#define PARTICLE_H


// system includes
#include <stdio.h>
#include <stdlib.h>

// user includes
#include "vector.h"
#include "global_vars.h"


//! \struct SParticle
//! \brief store all the particle infos
//!
//! \param start offset for adding particle.
//! \param size max number of particles.
//! \part particles array.
typedef struct
{
  int start;
  int size;
  float* part;
} SParticle;


extern void particleInit( SParticle* p, int nb );


extern void particleFree( SParticle* p );


//! \fn extern void particleAdd( SParticle* p, p_Vector3f pos, p_Vector3f v, p_Vector3f c );
//! \brief add a particle.
extern void particleAdd( SParticle* p, p_Vector3f pos, p_Vector3f v, p_Vector3f c );


//! \fn extern void particleUpdate( SParticle* p );
//! \brief update the particles array.
extern void particleUpdate( SParticle* p );


#endif //PARTICLE_H
