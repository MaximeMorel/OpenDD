//
//


#include "font.h"


void fontInit( SFont* f )
{
  f->offset = 0;
  f->texture = 0;

  printf( "Struct bitmap font : OK.\n" );
}


void fontFree( SFont* f, STexture* t )
{
  if( glIsTexture(f->texture) )
    {
      glDeleteTextures( 1 , &f->texture );
      printf( "Font texture deleted.\n" );
    }
  
  glDeleteLists( f->offset, 96 );

  printf( "Struct bitmap font : free.\n" );
}


void fontGen( SFont* f, STexture* t )
{
  int x = 0;
  int y = -1;
  int i = 0;
  int j;

  printf ( "font generation...\n" );

  f->offset = glGenLists( 96 );

  f->texture = loadTexture( t, "data/textures/fonts/font.png", GL_RGBA, GL_REPEAT, true);
    
  for( j = 0; j <= 96; j++ )
    {
      if( !(i % 16) )
	{
	  x = 0;
	  y++;
	}
      glNewList( f->offset + j , GL_COMPILE );
      
      glBegin( GL_QUADS );
      glTexCoord2f( (float)(x*32)/512 , (float)((y+1)*32)/512 );
      glVertex2i ( 0 , 0 );

      glTexCoord2f( (float)((x+1)*32)/512 , (float)((y+1)*32)/512 );
      glVertex2i ( 1 , 0 );

      glTexCoord2f( (float)((x+1)*32)/512 , (float)(y*32)/512 );
      glVertex2i ( 1 , 2 );

      glTexCoord2f( (float)(x*32)/512 , (float)(y*32)/512 );
      glVertex2i ( 0, 2 );
      glEnd();
      
      glEndList();
      
      x++;
      i++;
    }
}


void glPrintf( SFont* f, const char *text, float x, float y, float size)
{
  int i;
  int len = strlen( text );

  glBindTexture( GL_TEXTURE_2D, f->texture );
  
  //glColor4f( 0.8f, 0.8f, 0.8f, 0.95f );
  glPushMatrix();
  glTranslatef( x , y , 0.0f );
  glScalef( size , size , 0.0f );
  for( i =0 ; i <= len ; i++ )
    {
      
      glCallList( f->offset - 32 + text[i] );
      glTranslatef( 1.0f , 0.0f , 0.0f );
    }
  glPopMatrix();
}
