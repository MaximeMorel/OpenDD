//
//


//! \file model.h
//! \brief Model loading.


#ifndef MODEL_H
#define MODEL_H


// system includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// user includes


//! \struct SModel
//! \brief save data of a 3d model
//!
//! \param nb nb of triangles
//! \param vertex_data list of triangles
//! \param tex_data textures coord data
//! \param norm_data Normals data
typedef struct
{
  int nb;
  float* vertex_data;
  float* tex_data;
  float* norm_data;
} SModel;


void modelInit( SModel* m );
void modelFree( SModel* m );


void modelLoadObj( SModel* m, char* file );


#endif // MODEL_H
