// MOREL Maxime
//


//! \file texture.c
//! \brief Texture loading and binding.
//!
//!


#include "texture.h"


void textureInit( STexture* t )
{
  t->id = 0;
  
  //glGetIntegerv ( GL_MAX_TEXTURE_SIZE , &t->max_texture_size );
  t->max_texture_size = 4096;
  //printf("Max texture size : %d.\n", t->max_texture_size );
  
  t->texture = NULL;
  
  t->texture_id = (GLuint*)malloc( 1000 * sizeof(GLuint) );
  
  printf( "Struct texture : OK.\n" );
}


void textureFree( STexture* t )
{
  delAllTexture( t );
    
  if( t->texture_id != NULL )
    {
      free( t->texture_id );	// free texture id array.
    }
  t->texture_id = NULL;
  
  if( t->texture != NULL )
    {
      printf( "Error freeing temp texture memory.\n" );
      SDL_FreeSurface( t->texture );		// should be free !!
    }
  
  printf( "Struct texture : free.\n" );
}


GLuint loadTexture( STexture* t, const char* name, GLenum format, GLenum flag, bool mipmap )
{
  GLuint tex_id;
  
  if( t->texture != NULL )
    printf("Error freeing temp texture memory.\n");
  
  t->texture = IMG_Load( name );
  if( !t->texture )
    {
      printf( "Texture loading : error file %s not found.\n", name );
      return 0;
    }

  glGenTextures( 1 , &tex_id );
  
  t->texture_id[t->id] = tex_id;
  
  rescaleTexture( t , t->texture );
  
  glBindTexture( GL_TEXTURE_2D, t->texture_id[t->id] );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  if(mipmap)
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
  else
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, flag);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, flag);
  
  if(mipmap)
    gluBuild2DMipmaps( GL_TEXTURE_2D, format, t->dim[0], t->dim[1], format, GL_UNSIGNED_BYTE, t->texture->pixels );
  else
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, t->dim[0], t->dim[1], 0, format, GL_UNSIGNED_BYTE, t->texture->pixels );
  
#ifdef __DEBUG_TEXTURE__
  checkTexture( t, id );
#endif // __DEBUG_TEXTURE__
  
  SDL_FreeSurface( t->texture );
  t->texture = NULL;

  t->id++;
  
  return tex_id;
}


void loadTextures( STexture* t )
{
#ifdef __DEBUG_TEXTURE__
  printf( "texture generation...\n" );
  printf( "max texture size : %d\n", t->max_texture_size );
#endif // __DEBUG_TEXTURE__
  
  //glGenTextures ( t->num_total_textures, t->texture_id );
  
  /*load_skybox_textures( t );
    load_map_textures( t );
    load_terrain_textures( t );
    load_font_textures( t );*/
  
  // skybox textures
  /*printf( "\nskybox textures...\n" );
  loadTexture( t, "data/textures/up1.jpg", GL_RGB, GL_CLAMP_TO_EDGE, true);
  loadTexture( t, "data/textures/dn1.jpg", GL_RGB, GL_CLAMP_TO_EDGE, true);
  loadTexture( t, "data/textures/lt1.jpg", GL_RGB, GL_CLAMP_TO_EDGE, true);
  loadTexture( t, "data/textures/rt1.jpg", GL_RGB, GL_CLAMP_TO_EDGE, true);
  loadTexture( t, "data/textures/ft1.jpg", GL_RGB, GL_CLAMP_TO_EDGE, true);
  loadTexture( t, "data/textures/bk1.jpg", GL_RGB, GL_CLAMP_TO_EDGE, true);*/
  
  // terrain textures
  //printf( "\nterrain textures...\n" );
  //loadTexture( t, 6, "data/maps/terrains/gcanyon_texture.jpg", GL_RGB, GL_CLAMP_TO_EDGE, true);
  
  // font textures
  //printf( "\nfont textures...\n" );
  //loadTexture( t, 7, "data/textures/fonts/font.png", GL_RGBA, GL_REPEAT, true);
  
  // world textures
  printf( "\nworld textures...\n" );
  //loadTexture( t, "data/textures/texture.jpg", GL_RGB, GL_REPEAT, true);
  //loadTexture( t, "data/textures/brique1.jpg", GL_RGB, GL_REPEAT, true);
  //loadTexture( t, "data/textures/sand.jpg", GL_RGB, GL_REPEAT, true);
  //loadTexture( t, "data/textures/asphalt.jpg", GL_RGB, GL_REPEAT, true);
  loadTexture( t, "data/textures/land3.jpg", GL_RGB, GL_REPEAT, true);
  //loadTexture( t, "data/textures/chrome.jpg", GL_RGB, GL_REPEAT, true);

  // car texture
  //printf( "\ncar textures...\n" );
  //loadTexture( t, 12, "data/textures/car/wheel1_void.tga", GL_RGB, GL_REPEAT, true);
  //loadTexture( t, 13, "data/textures/car/wheel2_void.tga", GL_RGB, GL_REPEAT, true);
  //loadTexture( t, 14, "data/textures/car/car_void.tga", GL_RGB, GL_REPEAT, true);
  //loadTexture( t, "data/textures/car/car2.jpg", GL_RGB, GL_REPEAT, true);
  loadTexture( t, "data/textures/car/wheel2.jpg", GL_RGB, GL_REPEAT, true);

  // smoke texture
  //loadTexture( t, "data/textures/smoke.png", GL_RGBA, GL_REPEAT, true);
  
  SDL_FreeSurface( t->texture );
}


void rescaleTexture( STexture* texture, SDL_Surface* surface )
{
  int i;
  //float ratio = (float) surface->w / surface->h;
  
  int max = texture->max_texture_size;
  max = 4096;
  
  int x = surface->w;
  int y = surface->h;
  
  int a = surface->w & ( surface->w - 1 );
  int b = surface->h & ( surface->h - 1 );
  
  if ( surface->w > max )
    {
#ifdef __DEBUG_TEXTURE_DEEP__
      printf ( "texture x too big!\n" );
#endif // __DEBUG_TEXTURE_DEEP__
      x = max;
    }
  else
    if ( a )   // if x non power of 2
      {
#ifdef __DEBUG_TEXTURE_DEEP__
	printf ( "texture x non power of 2!\n" );
#endif // __DEBUG_TEXTURE_DEEP__
	for ( i = 2 ; (max / i) > surface->w ; i *= 2 )
	  {
	    x = max / (i*2);
	  }
      }
  
  if ( surface->h > max )
    {
#ifdef __DEBUG_TEXTURE_DEEP__
      printf ( "texture y too big!\n" );
#endif // __DEBUG_TEXTURE_DEEP__
      y = max;
    }
  else
    if ( b )   // if y non power of 2
      {
#ifdef __DEBUG_TEXTURE_DEEP__
	printf ( "texture y non power of 2!\n" );
#endif // __DEBUG_TEXTURE__
	for ( i = 2 ; (max / i) > surface->h ; i *= 2 )
	  {
	    y = max / (i*2);
	  }
      }
  
#ifdef __DEBUG_TEXTURE_DEEP__
  printf ( "original :\t" );
  printf ( "%dx%d\n" , surface->w , surface->h );
  printf ( "rescaled :\t" );
  printf ( "%dx%d\n" , x , y );
#endif // __DEBUG_TEXTURE_DEEP__

  if( surface->w != x || surface->h != y )
    {
      gluScaleImage( GL_RGB, surface->w, surface->h, GL_UNSIGNED_BYTE, 
		 surface->pixels, x, y, GL_UNSIGNED_BYTE, surface->pixels );
    }
  
  texture->dim[0] = x;
  texture->dim[1] = y;
}


bool checkTexture( STexture* t, int id )
{
  /*GLenum gl_error;
    const GLubyte *glu_error;
    if ( (gl_error = glGetError() ) != GL_NO_ERROR )
    {
    glu_error = gluErrorString(gl_error);
    printf ( "Opengl error (texture) : %s\n" ,  glu_error );
    }*/
  
  checkGlError( "texture" );
  
  if( glIsTexture( t->texture_id[id] ) )
    {
      printf( "Texture %d ok.\n" , id );
      return true;
    }
  else
    {
      printf( "Error texture %d : not a texture.\n" , id );
      return false;
    }
}


void delTexture( STexture* t , int id )
{
  if ( glIsTexture( t->texture_id[id] ) )
    {
      glDeleteTextures( 1 , &t->texture_id[id] );
      printf( "Texture %d is free.\n", id );
      return;
    }
  //printf ( "Texture id nb %d unused.\n" , id );
}


void delAllTexture( STexture* t )
{
  int i;	// free all textures
  for( i = 0; i < 1000; i++ )
    {
      delTexture( t , i );		
    }
}
