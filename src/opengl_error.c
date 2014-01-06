//
//


#include "opengl_error.h"


bool checkGlError( char* context )
{
  GLenum gl_error;
  const GLubyte* glu_error;
  if( ( gl_error = glGetError() ) != GL_NO_ERROR )
    {
      glu_error = gluErrorString( gl_error );
      printf( "Opengl error (%s) : %s\n" , context , glu_error );
      return false;
    }
  else
    return true;
}


bool checkDisplayList( int id )
{
  if( glIsList( id ) )
    {
      printf( "list %d ok.\n" , id );
      return true;
    }
  else
    {
      printf( "list %d error.\n" , id );
      return false;
    }
}
