//
//


#include "render.h"


void drawVertexArray_vnt( SRender* render, GLenum mode, GLint size, float* va )
{	
  glTexCoordPointer( 2, GL_FLOAT, 8*sizeof(GLfloat), &va[0] );
  glNormalPointer( GL_FLOAT, 8*sizeof(GLfloat), &va[2] );
  glVertexPointer( 3, GL_FLOAT, 8*sizeof(GLfloat), &va[5] );
  
  glEnableClientState( GL_VERTEX_ARRAY );
  glEnableClientState( GL_NORMAL_ARRAY );
  glEnableClientState( GL_TEXTURE_COORD_ARRAY );
  
  //glInterleavedArrays( GL_T2F_N3F_V3F, 0, va );
  
  glDrawArrays( mode, 0, size );
  
  glDisableClientState( GL_TEXTURE_COORD_ARRAY );
  glDisableClientState( GL_NORMAL_ARRAY );
  glDisableClientState( GL_VERTEX_ARRAY );
}


void drawVertexArray_vnt3( SRender* render, GLenum mode, GLint size, float* va, float* vn, float* vt )
{	
  glTexCoordPointer( 2, GL_FLOAT, 0, &vt[0] );
  glNormalPointer( GL_FLOAT, 0, &vn[0] );
  glVertexPointer( 3, GL_FLOAT, 0, &va[0] );
  
  glEnableClientState( GL_VERTEX_ARRAY );
  glEnableClientState( GL_NORMAL_ARRAY );
  glEnableClientState( GL_TEXTURE_COORD_ARRAY );
  
  //glInterleavedArrays( GL_T2F_N3F_V3F, 0, va );
  
  glDrawArrays( mode, 0, size );
  
  glDisableClientState( GL_TEXTURE_COORD_ARRAY );
  glDisableClientState( GL_NORMAL_ARRAY );
  glDisableClientState( GL_VERTEX_ARRAY );
}


void drawVertexArray_vn( SRender* render, GLenum mode, GLint size, float* va , float* na )
{	
  glNormalPointer( GL_FLOAT, 0, &na[0] );
  glVertexPointer( 3, GL_FLOAT, 0, &va[0] );
  
  glEnableClientState( GL_VERTEX_ARRAY );
  glEnableClientState( GL_NORMAL_ARRAY );
    
  glDrawArrays( mode, 0, size );
  
  glDisableClientState( GL_NORMAL_ARRAY );
  glDisableClientState( GL_VERTEX_ARRAY );
}


// particle
void drawVertexArray_vc( SRender* render, GLenum mode, GLint size, float* va )
{
  glColorPointer( 3, GL_FLOAT, 9*sizeof(GLfloat),&va[6] );
  glVertexPointer( 3, GL_FLOAT, 9*sizeof(GLfloat), &va[0] );
  
  glEnableClientState( GL_VERTEX_ARRAY );
  glEnableClientState( GL_COLOR_ARRAY );
    
  glDrawArrays( mode, 0, size );
  
  glDisableClientState( GL_COLOR_ARRAY );
  glDisableClientState( GL_VERTEX_ARRAY );
}


// tire traces
void drawVertexArray_v( SRender* render, GLenum mode, GLint size, float* va )
{
  //glColorPointer( 4, GL_FLOAT, 9*sizeof(GLfloat),&va[6] );
  glVertexPointer( 3, GL_FLOAT, 0, &va[0] );
  
  glEnableClientState( GL_VERTEX_ARRAY );
  //glEnableClientState( GL_COLOR_ARRAY );
      
  glDrawArrays( mode, 0, size );

  //glDisableClientState( GL_COLOR_ARRAY );  
  glDisableClientState( GL_VERTEX_ARRAY );
}
