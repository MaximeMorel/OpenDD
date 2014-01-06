//
//


//! \file screenshot.c
//!
//!


#include "screenshot.h"


/*void screenshotInit( SScreenshot * s )
{
  s->id = 0;
  //s->prefix = NULL;
  
  printf ( "Struct screenshot : OK.\n" );
  }*/


void screenshotBmp()
{
  int i = 1;
  GLint viewport[4];
  Uint32 rmask, gmask, bmask, amask;
  SDL_Surface * picture, * finalpicture;
  char name[64];
  
  FILE* file = NULL;
  
  glGetIntegerv(GL_VIEWPORT, viewport);
  
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif
  
  picture = SDL_CreateRGBSurface(SDL_SWSURFACE,viewport[2],viewport[3], 32, rmask, gmask, bmask, amask);
  SDL_LockSurface(picture);
  glReadPixels(viewport[0],viewport[1],viewport[2],viewport[3],GL_RGBA,GL_UNSIGNED_BYTE,picture->pixels);
  SDL_UnlockSurface(picture);
  
  finalpicture = flipsurface(picture);
  
  do
  {
    if( file != NULL )
      {
	fclose( file );
	file = NULL;
      }

    sprintf( name, "screenshot%d.bmp", i );
    file = fopen( name, "rb" );
    i++;
  } while( file != NULL );

  if( file != NULL )
    {
      fclose( file );
      file = NULL;
    }

  printf( "Save screenshot as %s.\n", name );

  SDL_SaveBMP(finalpicture, name );
  SDL_FreeSurface(finalpicture);
  SDL_FreeSurface(picture);
}


void screenshotJpg()
{
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;

  GLint viewport[4];

  int i = 1;
  char name[64];
  FILE* file = NULL;
  char* screen = NULL;

  JSAMPROW row_pointer[1];        /* pointer to a single row */
  int row_stride;                 /* physical row width in buffer */

  JSAMPLE* image_buffer;

  if( screen != NULL )
    {
      free( screen );
      screen = NULL;
    }

  glGetIntegerv( GL_VIEWPORT, viewport );

  screen = (char*)malloc( 3*viewport[2]*viewport[3]*sizeof(char) );

  glReadPixels( viewport[0], viewport[1], viewport[2], viewport[3], GL_RGB, GL_BYTE, screen );

  flipImage( screen );

  image_buffer = (JSAMPLE*)screen;  
  
  do
  {
    if( file != NULL )
      {
	fclose( file );
	file = NULL;
      }

    sprintf( name, "screenshot%d.jpg", i );
    file = fopen( name, "rb" );
    i++;
  } while( file != NULL );

  if( file != NULL )
    {
      fclose( file );
      file = NULL;
    }

  printf( "Save screenshot as %s.\n", name );


  cinfo.err = jpeg_std_error( &jerr );
  jpeg_create_compress( &cinfo );

  file = fopen( name, "wb" );
  
  jpeg_stdio_dest( &cinfo, file );

  cinfo.image_width = viewport[2];      /* image width and height, in pixels */
  cinfo.image_height = viewport[3];
  cinfo.input_components = 3;     /* # of color components per pixel */
  cinfo.in_color_space = JCS_RGB; /* colorspace of input image */
  jpeg_set_defaults( &cinfo );

  jpeg_set_quality( &cinfo, 85, TRUE );

  jpeg_start_compress( &cinfo, TRUE);

  row_stride = viewport[2] * 3;   /* JSAMPLEs per row in image_buffer */
  while( cinfo.next_scanline < cinfo.image_height )
    {
      row_pointer[0] = &image_buffer[cinfo.next_scanline * row_stride];
      jpeg_write_scanlines( &cinfo, row_pointer, 1);
    }
  
  jpeg_finish_compress( &cinfo );
  jpeg_destroy_compress( &cinfo );
  
  
  if( file != NULL )
    {
      fclose( file );
      file = NULL;
    }

  if( screen != NULL )
    {
      free( screen );
      screen = NULL;
    }
}


void flipImage( char* image )
{
  int current_line, pitch;
  GLint viewport[4];

  glGetIntegerv( GL_VIEWPORT, viewport );
  
  float* tmp = malloc( 3*viewport[2]*viewport[3]* sizeof(char) );

  pitch = viewport[2] * 3;

  for( current_line = 0; current_line < viewport[3]; current_line++ )
    {
      memcpy(&((unsigned char*)tmp)[current_line*pitch],
	     &((unsigned char*)image)[(viewport[3] - 1 - current_line)*pitch], pitch);
    }

  memcpy( image, tmp, 3*viewport[2]*viewport[3] );

  free( tmp );
}


SDL_Surface* flipsurface( SDL_Surface * surface )
{
  int current_line,pitch;
  SDL_Surface* fliped_surface = SDL_CreateRGBSurface( SDL_SWSURFACE,
						      surface->w,surface->h,
						      surface->format->BitsPerPixel,
						      surface->format->Rmask,
						      surface->format->Gmask,
						      surface->format->Bmask,
						      surface->format->Amask);
  
  SDL_LockSurface( surface );
  SDL_LockSurface( fliped_surface );
  
  pitch = surface->pitch;
  for( current_line = 0; current_line < surface->h; current_line++ )
    {
      memcpy(&((unsigned char* )fliped_surface->pixels)[current_line*pitch],
	     &((unsigned char* )surface->pixels)[(surface->h - 1 - current_line)*pitch], pitch);
    }
  
  SDL_UnlockSurface( fliped_surface );
  SDL_UnlockSurface( surface );
  
  return fliped_surface;
}
