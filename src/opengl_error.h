//
//


#ifndef OPENGL_ERROR_H
#define OPENGL_ERROR_H

// system includes
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>

// user includes
#include "bool.h"


inline bool checkGlError( char* context );
bool checkDisplayList( int id );


#endif // OPENGL_ERROR_H
