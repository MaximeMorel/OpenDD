//
//


//! \file light.h
//! \brief Light module
//!
//! Functions for light and materials.


#ifndef LIGHT_H
#define LIGHT_H


// system includes
#include <stdio.h>
#include <GL/gl.h>

// user includes


typedef struct
{
} SLight;


void lightInit( SLight* l );
void lightFree( SLight* l );


//! \fn lightUpdate( SLight* l )
//! \brief Update a light source
//!
//! This has to be called if there is movement, to upate the light position.
void lightUpdate( SLight* l );


//! \fn setMaterial()
//! \brief TODO : Set a material
//!
//!
void setMaterial();


#endif // LIGHT_H
