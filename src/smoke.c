//
//


#include "smoke.h"


void smokeInit( SSmoke* s, int nb )
{
  int i;

  s->id = 0;
  s->start = 0;
  s->size = nb;

  s->timeout = 0;

  s->texture = 0;

  s->smoke = (float*)malloc( s->size * 6 * sizeof(float) );

  for( i = 0; i < s->size * 6; i++ )
    {
      s->smoke[i] = 0.0f;      
    }

  printf( "Struct smoke : OK.\n" );
}


void smokeGen( SSmoke* s, STexture* t )
{
  s->texture = loadTexture( t, "data/textures/smoke.png", GL_RGBA, GL_REPEAT, true);
  printf( "Load smoke testure.\n" );

  s->id = glGenLists( 1 );
  glNewList( s->id, GL_COMPILE );	
  glBegin( GL_QUADS );
  
  glTexCoord2f( 0.0f, 0.0f );  glVertex3f( -0.5f, -0.5f, 0.0f );
  glTexCoord2f( 1.0f, 0.0f );  glVertex3f( 0.5f, -0.5f, 0.0f );
  glTexCoord2f( 1.0f, 1.0f );  glVertex3f( 0.5f, 0.5f, 0.0f );
  glTexCoord2f( 0.0f, 1.0f );  glVertex3f( -0.5f, 0.5f, 0.0f );
  
  glEnd();
  glEndList();
}


void smokeFree( SSmoke* s )
{
  if( s->smoke != NULL )
    {
      free( s->smoke );
      s->smoke = NULL;
    }

  if( glIsTexture(s->texture) )
    {
      glDeleteTextures( 1 , &s->texture );
      printf( "Smoke texture deleted.\n" );
    }

  if( glIsList( s->id ) )
    {
      glDeleteLists( s->id, 1 );
    }

  printf( "Struct smoke : free.\n" );
}


void smokeAdd( SSmoke* s, p_Vector3f pos, float color )
{
  s->start = s->start % (s->size*6);

  // position
  s->smoke[s->start] = pos[0];
  s->smoke[s->start+1] = 0.5f;
  s->smoke[s->start+2] = pos[2];

  // color
  s->smoke[s->start+3] = color;

  // alpha
  s->smoke[s->start+4] = 1.0f;

  // size
  s->smoke[s->start+5] = 1.5f;

  s->start+=6;
}


void smokeUpdate( SSmoke* s )
{
  int i;
  float r;

  for( i = 0; i < s->size*6; i += 6 )
    {
      r = (float)rand()/RAND_MAX;
      // if not totally translucent, we update
      if( s->smoke[i+4] > 0.0f )
	{
	  // smoke goes up
	  s->smoke[i+1] += 3.0f * r * g_fps->time;

	  // alpha descrease
	  s->smoke[i+4] -= 0.25f * r * g_fps->time;

	  // size increase
	  s->smoke[i+5] += 2.0f * r * g_fps->time;
	}
    }
}


void smokeDraw( SSmoke* s, SCamera* c )
{
  int i;

  glBindTexture( GL_TEXTURE_2D, s->texture );
  //glPushMatrix();
  //glRotatef( (c->rx+M_PI_2) * RAD2DEG, 0.0f, 1.0f, 0.0f );
  glNormal3f( -c->look[0], -c->look[1], -c->look[2] );

  for( i = 0; i < s->size*6; i += 6 )
    {
      // if not totally translucent, we draw
      if( s->smoke[i+4] > 0.0f )
	{
	  glPushMatrix();
	  glColor4f( s->smoke[i+3], s->smoke[i+3], s->smoke[i+3], s->smoke[i+4] );
	  //glColor4f( 1, 0, 0, s->smoke[i+4] );
	  glTranslatef( s->smoke[i], s->smoke[i+1], s->smoke[i+2] );
	  glRotatef( -(c->rx + M_PI_2) * RAD2DEG, 0.0f, 1.0f, 0.0f );
	  glScalef( s->smoke[i+5], s->smoke[i+5], 0.0f );


	  glCallList( s->id );
	  /*glBegin( GL_QUADS );

	  glTexCoord2f( 0.0f, 0.0f );  glVertex3f( -0.5f, -0.5f, 0.0f );
	  glTexCoord2f( 1.0f, 0.0f );  glVertex3f( 0.5f, -0.5f, 0.0f );
	  glTexCoord2f( 1.0f, 1.0f );  glVertex3f( 0.5f, 0.5f, 0.0f );
	  glTexCoord2f( 0.0f, 1.0f );  glVertex3f( -0.5f, 0.5f, 0.0f );
	  
	  glEnd();*/

	  glPopMatrix();	  
	}
    }

  //glPopMatrix();
}
