//
//


//! \file tire.h
//!


#ifndef TIRE_H
#define TIRE_H


// system includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// user includes


//! \struct STire
//! \brief store the tire traces infos.
//!
//! \param start offset for adding traces
//! \param size max number of traces
//! \param timeout used to temporize traces creation
//! \param trace traces array
typedef struct
{
  int start;
  int size;
  int timeout;

  float* trace;
} STire;


extern void tireInit( STire* t, int nb );


extern void tireFree( STire* t );


//! \fn extern void tireTraceAdd( STire* t, float* pos );
//! \brief add a tire trace.
extern void tireTraceAdd( STire* t, float* pos );



#endif // TIRE_H
