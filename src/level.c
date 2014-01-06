//
//


#include "level.h"


void levelInit( SLevel* l )
{
  l->x_min = -100;
  l->x_max = 100;
  l->y_min = -100;
  l->y_max = 100;
  l->h = 1;
  l->ground_tex = 0;
  l->wall_tex = 0;
  l->level = 0;

  //c->pTexture = NULL;

  printf( "Struct level : OK.\n" );
}


void levelFree( SLevel* l )
{
  if( glIsTexture(l->ground_tex) )
    {
      glDeleteTextures( 1 , &l->ground_tex );
      printf( "Level ground texture deleted.\n" );
    }

  if( glIsTexture(l->wall_tex) )
    {
      glDeleteTextures( 1 , &l->wall_tex );
      printf( "Level wall texture deleted.\n" );
    }

  if( glIsList( l->level ) )
    {
      glDeleteLists( l->level, 1 );
    }

  printf( "Struct level : free.\n" );
}


void levelLoad( SLevel* l, const char* name )
{

}


/*void levelLoadTextures( SLevel* l )
{
  l->ground_tex = loadTexture( c->pTexture, "data/textures/asphalt.jpg", GL_RGB, GL_REPEAT, true);
  l->wall_tex = loadTexture( c->pTexture, "data/textures/brique1.jpg", GL_RGB, GL_REPEAT, true);

  printf( "Load level textures.\n" );
}*/


void levelGen( SLevel* l, STexture* t )
{
  int i, j;

  l->ground_tex = loadTexture( t, "data/textures/asphalt.jpg", GL_RGB, GL_REPEAT, true );
  l->wall_tex = loadTexture( t, "data/textures/brique1.jpg", GL_RGB, GL_REPEAT, true );
  printf( "Load level textures.\n" );

  l->level = glGenLists( 1 );
  glNewList( l->level, GL_COMPILE );	

  // world : ground
  //glColor3f ( 1, 1, 1 );
  glBindTexture( GL_TEXTURE_2D, l->ground_tex );
  glBegin( GL_QUADS );
  glNormal3f( 0.0f, 1.0f ,0.0f );
  for ( i = -100; i <= 100; i+=10 )
    {
      for ( j = -100; j <= 100; j+=10 )
	{
	  //glColor3f((j + i) % 2, (j + i) % 2, (j + i) % 2);
	  //glBindTexture( GL_TEXTURE_2D, render->texture->texture_id[10] );
	  //glBegin( GL_QUADS );
	  //glNormal3f( 0.0f, 1.0f ,0.0f );
	  glTexCoord2f( 5.0f, 0.0f );	glVertex3i( i + 10.0f, 0.0f, j );
	  glTexCoord2f( 5.0f, 5.0f );	glVertex3i( i + 10.0f, 0.0f, j - 10.0f );
	  glTexCoord2f( 0.0f, 5.0f );	glVertex3i( i, 0.0f, j - 10.0f );
	  glTexCoord2f( 0.0f, 0.0f );	glVertex3i( i, 0.0f, j );
	  //glEnd();
	}
    }
  glEnd();
  
  
  // walls
  glBindTexture( GL_TEXTURE_2D, l->wall_tex );
  glBegin ( GL_QUADS );
  glNormal3f( 0.0f, 0.0f, 1.0f );
  glTexCoord2f( 0.0f, 0.5f );	glVertex3i( -100, 0, -100 );
  glTexCoord2f( 50.0f, 0.5f );	glVertex3i( 100, 0, -100 );
  glTexCoord2f( 50.0f, 0.0f );	glVertex3i( 100, 1, -100 );
  glTexCoord2f( 0.0f, 0.0f );	glVertex3i( -100, 1, -100 );
  
  glNormal3f( -1.0f, 0.0f, 0.0f );
  glTexCoord2f( 0.0f, 0.5f );	glVertex3i( 100, 0, -100 );
  glTexCoord2f( 50.0f, 0.5f );	glVertex3i( 100, 0, 100 );
  glTexCoord2f( 50.0f, 0.0f );	glVertex3i( 100, 1, 100 );
  glTexCoord2f( 0.0f, 0.0f );	glVertex3i( 100, 1, -100 );
  
  glNormal3f( 0.0f, 0.0f, -1.0f );
  glTexCoord2f( 0.0f, 0.5f );	glVertex3i( 100, 0, 100 );
  glTexCoord2f( 50.0f, 0.5f );	glVertex3i( -100, 0, 100 );
  glTexCoord2f( 50.0f, 0.0f );	glVertex3i( -100, 1, 100 );
  glTexCoord2f( 0.0f, 0.0f );	glVertex3i( 100, 1, 100 );
  
  glNormal3f( 1.0f, 0.0f, 0.0f );
  glTexCoord2f( 0.0f, 0.5f );	glVertex3i( -100, 0, 100 );
  glTexCoord2f( 50.0f, 0.5f );	glVertex3i( -100, 0, -100 );
  glTexCoord2f( 50.0f, 0.0f );	glVertex3i( -100, 1, -100 );
  glTexCoord2f( 0.0f, 0.0f );	glVertex3i( -100, 1, 100 );
  glEnd();

  glEndList();
}


void levelDraw( SLevel* l )
{

}
