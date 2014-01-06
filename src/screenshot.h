//
//


//! \file screenshot.h
//!
//!


#ifndef SCREENSHOT_H
#define SCREENSHOT_H


// system includes
#include <GL/gl.h>
#include <stdio.h>
#include <jpeglib.h>
#include <SDL/SDL.h>

// user includes


/*typedef struct
{
  int id;
  //char * prefix;
  } SScreenshot;*/


//void screenshotInit( SScreenshot * s );

void screenshotBmp();


void screenshotJpg();


void flipImage( char* image );


SDL_Surface* flipsurface( SDL_Surface * surface );


#endif // SCREENSHOT_H
