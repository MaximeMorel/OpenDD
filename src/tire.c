//
//


#include "tire.h"


void tireInit( STire* t, int nb )
{
  int i;

  t->timeout = 0;

  t->start = 0;
  t->size = nb;

  t->trace = (float*)malloc( t->size * 3 * 4 * 4 * sizeof(float) );

  for( i = 0; i < t->size * 48; i++ )
    {
      t->trace[i] = 99999;      
    }

  for( i = 0; i < t->size * 48; i+=48 )
    {
      t->trace[i+1] = 0.012f;
      t->trace[i+4] = 0.012f;
      t->trace[i+7] = 0.012f;
      t->trace[i+10] = 0.012f;

      t->trace[i+13] = 0.014f;
      t->trace[i+16] = 0.014f;
      t->trace[i+19] = 0.014f;
      t->trace[i+22] = 0.014f;

      t->trace[i+25] = 0.016f;
      t->trace[i+28] = 0.016f;
      t->trace[i+31] = 0.016f;
      t->trace[i+34] = 0.016f;

      t->trace[i+37] = 0.018f;
      t->trace[i+40] = 0.018f;
      t->trace[i+43] = 0.018f;
      t->trace[i+46] = 0.018f;
    }

  printf( "Struct tire : OK.\n" );
}


void tireFree( STire* t )
{
  if( t->trace != NULL )
    {
      free( t->trace );
      t->trace = NULL;
    }

  printf( "Struct tire : free.\n" );
}


void tireTraceAdd( STire* t, float* pos )
{
  t->start = t->start % (t->size*48);


  float cos_fl = cosf( pos[16]+M_PI_2 );
  float sin_fl = sinf( pos[16]+M_PI_2 );

  float cos_fr = cosf( pos[16]-M_PI_2 );
  float sin_fr = sinf( pos[16]-M_PI_2 );

  float cos_rl = cosf( pos[17]+M_PI_2 );
  float sin_rl = sinf( pos[17]+M_PI_2 );

  float cos_rr = cosf( pos[17]-M_PI_2 );
  float sin_rr = sinf( pos[17]-M_PI_2 );

  
  // wheel front left
  t->trace[t->start] = pos[0] + cos_fl*0.1f;
  t->trace[t->start+2] = pos[1] + sin_fl*0.1f;

  t->trace[t->start+3] = pos[0] + cos_fr*0.1f;
  t->trace[t->start+5] = pos[1] + sin_fr*0.1f;

  t->trace[t->start+6] = pos[8] + cos_rr*0.1f;
  t->trace[t->start+8] = pos[9] + sin_rr*0.1f;

  t->trace[t->start+9] = pos[8] + cos_rl*0.1f;
  t->trace[t->start+11] = pos[9] + sin_rl*0.1f;


  // wheel front right
  t->trace[t->start+12] = pos[2] + cos_fl*0.1f;
  t->trace[t->start+14] = pos[3] + sin_fl*0.1f;

  t->trace[t->start+15] = pos[2] + cos_fr*0.1f;
  t->trace[t->start+17] = pos[3] + sin_fr*0.1f;

  t->trace[t->start+18] = pos[10] + cos_rr*0.1f;
  t->trace[t->start+20] = pos[11] + sin_rr*0.1f;

  t->trace[t->start+21] = pos[10] + cos_rl*0.1f;
  t->trace[t->start+23] = pos[11] + sin_rl*0.1f;


  // wheel rear right
  t->trace[t->start+24] = pos[4] + cos_fl*0.1f;
  t->trace[t->start+26] = pos[5] + sin_fl*0.1f;

  t->trace[t->start+27] = pos[4] + cos_fr*0.1f;
  t->trace[t->start+29] = pos[5] + sin_fr*0.1f;

  t->trace[t->start+30] = pos[12] + cos_rr*0.1f;
  t->trace[t->start+32] = pos[13] + sin_rr*0.1f;

  t->trace[t->start+33] = pos[12] + cos_rl*0.1f;
  t->trace[t->start+35] = pos[13] + sin_rl*0.1f;


  // wheel rear left
  t->trace[t->start+36] = pos[6] + cos_fl*0.1f;
  t->trace[t->start+38] = pos[7] + sin_fl*0.1f;

  t->trace[t->start+39] = pos[6] + cos_fr*0.1f;
  t->trace[t->start+41] = pos[7] + sin_fr*0.1f;

  t->trace[t->start+42] = pos[14] + cos_rr*0.1f;
  t->trace[t->start+44] = pos[15] + sin_rr*0.1f;

  t->trace[t->start+45] = pos[14] + cos_rl*0.1f;
  t->trace[t->start+47] = pos[15] + sin_rl*0.1f;


  t->start+=48;
}  
