//
//


#ifndef WHEEL_H
#define WHEEL_H


// system includes
#include <stdio.h>

// user includes


typedef struct
{
  float pos_x, pos_z, dir, cos_dir, sin_dir;
} SWheel;


extern void wheelInit( SWheel* w );
extern void wheelFree( SWheel* w );


#endif // WHEEL_H
