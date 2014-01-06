//
//


#include "wheel.h"


void wheelInit( SWheel* w )
{
  w->pos_x = 0;
  w->pos_z = 0;
  w->dir = 0;
  w->cos_dir = 0;
  w->sin_dir = 0;

  printf( "Struct wheel : OK.\n" );
}


void wheelFree( SWheel* w )
{
  printf( "Struct wheel : free.\n" );
}
