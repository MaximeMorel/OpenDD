//  VITANOSTRA Franck
//


#include "particle.h"


void particleInit( SParticle* p, int nb )
{
  int i;

  p->start = 0;
  p->size = nb;

  p->part = (float*)calloc( p->size * 9 ,sizeof(float) );

  for( i = 0; i < p->size * 9; i+=9 )
    {
      p->part[i] = 99999;
      p->part[i+2] = 99999;
    }

  printf( "Struct particle : OK.\n" );
}


void particleFree( SParticle* p )
{
  if( p->part != NULL )
    free( p->part );

  printf( "Struct particle : free.\n" );
}


void particleAdd( SParticle* p, p_Vector3f pos, p_Vector3f v, p_Vector3f c )
{
  float force = module3fv( v );
  int i = 0;

  //Vector3f v3;  
  //setVector3fv( v3, v1 );
  //subVector3fv( v3, v2 );
  //force = module3fv( v3 );

  
  //while ((i< force) || (i<10))
  while( i < 1 )
    {
      p->start = p->start % (p->size*9);

      // position
      p->part[p->start] = pos[0];
      p->part[p->start+1] = 0.5f;
      p->part[p->start+2] = pos[1];

      //vitesse
      /*p->part[p->start+3]=(((float)rand()/RAND_MAX)*v1[0]+((float)rand()/RAND_MAX)*v2[0])*0.1;
      p->part[p->start+4]=(((float)rand()/RAND_MAX)*force)*0.1;
      p->part[p->start+5]=(((float)r+and()/RAND_MAX)*v1[2]+((float)rand()/RAND_MAX)*v2[2])*0.1;*/

      p->part[p->start+3] = 0.01f*(v[0]*((float)rand()/RAND_MAX));
      p->part[p->start+4] = 0.01f*force*((float)rand()/RAND_MAX);
      p->part[p->start+5] = 0.01f*(v[2]*((float)rand()/RAND_MAX));

      //couleur
      p->part[p->start+6] = c[0];
      p->part[p->start+7] = c[1];
      p->part[p->start+8] = c[2];

      p->start+=9;
      i++;
      //printf( "add particle.\n" );
    }
}


void particleUpdate( SParticle* p )
{
  int i;
  float r = ((float)rand()/RAND_MAX);

  for( i = 0; i < p->size*9; i += 9 )
    {
      // check if in air
      if( p->part[i+1] <= 0.1f )
	{
	  p->part[i+1] = 0.1f;
	  p->part[i+3] = 0;
          p->part[i+4] = 0;
	  p->part[i+5] = 0;	  
	}
      else
	{
	  // update pos;
	  p->part[i]   += p->part[i+3];
	  p->part[i+1] += p->part[i+4];
	  p->part[i+2] += p->part[i+5];

	  // add gravity
	  p->part[i+4] -= 2.0f * g_fps->time;
	}

      // color change
      if( p->part[i+6] >= 0.5f )
	{
	  p->part[i+6] -= 0.2f * r * g_fps->time;
	}
      if( p->part[i+7] >= 0.5f )
	{
	  p->part[i+7] -= 0.4f * r * g_fps->time;
	}
      if( p->part[i+8] <= 0.5f )
	{

	  p->part[i+8] += 0.4f * r * g_fps->time;
	}
    }
}
