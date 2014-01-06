//
//


/*! \file model.c
  \brief Model loading.

*/


#include "model.h"


void modelInit( SModel* m )
{
  m->nb = 0;
  m->vertex_data = NULL;
  m->tex_data = NULL;
  m->norm_data = NULL;

  printf( "Struct model : OK.\n" );
}


void modelFree( SModel* m )
{
  if( m->vertex_data != NULL )
    {
      free( m->vertex_data );
    }
  if( m->tex_data != NULL )
    {
      free( m->tex_data );
    }
  if( m->norm_data != NULL )
    {
      free( m->norm_data );
    }
  
  printf( "Struct model : free.\n" );
}


void modelLoadObj2( SModel* m, char* file )
{
}


void modelLoadObj( SModel* m, char* file )
{
  FILE* f = NULL;

  char header[16];
  char line[256];

  int v_size = 0;
  int vt_size = 0;
  int vn_size = 0;
  int nb_faces = 0;

  //int v_pos = 0;
  //int vt_pos = 0;
  //int vn_pos = 0;
  //int f_pos = 0;

  int v_i = 0;
  int vt_i = 0;
  int vn_i = 0;

  int i = 0;
  int j = 0;
  //int k = 0;

  int vertex_i = 0;
  int tex_i = 0;
  int norm_i = 0;

  float* tmp_v = NULL;
  float* tmp_vt = NULL;
  float* tmp_vn = NULL;

  f = fopen( file, "rb" );

  if( !f )
    {
      printf( "Model : error loading %s!!!\n", file );
      return;
    }

  while( !feof( f ) )
    {
      fscanf( f, "%s", header );
      //printf( "%s \n", header );
      
      if( strcmp( header, "v" ) == 0 )
	{
	  v_size++;
	}
      else
	if( strcmp( header, "vt" ) == 0 )
	  {
	    vt_size++;
	  }
	else
	  if( strcmp( header, "vn" ) == 0 )
	    {
	      vn_size++;
	    }
	  else
	    if( strcmp( header, "f" ) == 0 )
	      {
		nb_faces++;
	      }
      fgets( line, 256, f );
      strcpy( header, "" );
    }

  //printf( "v : %d \t vt : %d \t vn : %d \t f : %d \n", v_size ,vt_size, vn_size, nb_faces );


  tmp_v = malloc( v_size * 3 * sizeof( float ) );
  tmp_vt = malloc( vt_size * 2 * sizeof( float ) );
  tmp_vn = malloc( vn_size * 3 * sizeof( float ) );
  
  fseek( f, 0L, SEEK_SET );

  while( !feof( f ) )
    {
      fscanf( f, "%s", header );
      //printf( "%s \n", header );
      
      if( strcmp( header, "v" ) == 0 )
	{
	  fscanf( f, "%f %f %f", &tmp_v[v_i], &tmp_v[v_i+1], &tmp_v[v_i+2] );
	  //printf( "%f %f %f \n", tmp_v[v_i], tmp_v[v_i+1], tmp_v[v_i+2] );
	  v_i += 3;
	}
      else
	if( strcmp( header, "vt" ) == 0 )
	  {
	    fscanf( f, "%f %f", &tmp_vt[vt_i], &tmp_vt[vt_i+1] );
	    //printf( "%f %f \n", tmp_vt[vt_i], tmp_vt[vt_i+1] );
	    vt_i += 2; 
	  }
	else
	  if( strcmp( header, "vn" ) == 0 )
	    {
	      fscanf( f, "%f %f %f", &tmp_vn[vn_i], &tmp_vn[vn_i+1], &tmp_vn[vn_i+2] );
	      //printf( "%f %f %f \n", tmp_vn[vn_i], tmp_vn[vn_i+1], tmp_vn[vn_i+2] );
	      vn_i += 3;
	    }
      fgets( line, 256, f );
      strcpy( header, "" );
    }

  m->vertex_data = malloc( 3 * 3 * nb_faces * sizeof( float ) );
  m->tex_data = malloc( 2 * 3 * nb_faces * sizeof( float ) );
  m->norm_data = malloc( 3 * 3 * nb_faces * sizeof( float ) );

  m->nb = nb_faces * 3;
   
  fseek( f, 0L, SEEK_SET );

  //printf( "malloc vertex : %d\n", 3 * 3 * nb_faces * sizeof( float ) );

  while( !feof( f ) )
    {
      fscanf( f, "%s", header );
      //printf( "%s : ", header );

      if( strcmp( header, "f" ) == 0 )
	{
	  //fseek( f, 1L, SEEK_CUR );
	  for( j = 0; j < 3; j++ )
	    {
	      // vertex
	      fscanf( f, "%d", &i );
	      // hit vertex identification.
	      //if( i == 14 ) printf( "hit vertex : %d\n", vertex_i );
	      i--;
	      //printf( "v%d : %d \n", j, i );
	      i *= 3;
	      m->vertex_data[vertex_i] = tmp_v[i];
	      m->vertex_data[vertex_i+1] = tmp_v[i+1];
	      m->vertex_data[vertex_i+2] = tmp_v[i+2];
	      vertex_i += 3;
	      //printf( "vertex_i : %d \t i : %d \n", vertex_i, i );

	      fseek( f, 1L, SEEK_CUR );
	      
	      // texcoord
	      fscanf( f, "%d", &i );
	      i--;
	      //printf( "t%d : %d \n", j, i );
	      i *= 2;
	      m->tex_data[tex_i] = tmp_vt[i];
	      m->tex_data[tex_i+1] = tmp_vt[i+1];
	      //m->tex_data[tex_i+2] = tmp_vt[i+2];
	      tex_i += 2;

	      fseek( f, 1L, SEEK_CUR );
	      
	      // normal
	      fscanf( f, "%d", &i );
	      i--;
	      //printf( "n%d : %d \n", j, i );
	      i *= 3;
	      m->norm_data[norm_i] = tmp_vn[i];
	      m->norm_data[norm_i+1] = tmp_vn[i+1];
	      m->norm_data[norm_i+2] = tmp_vn[i+2];
	      norm_i += 3;
	      //printf( "norm_i : %d \t i : %d \n", norm_i, i );

	      //fseek( f, 4L, SEEK_CUR );
	    }
	}
      else
	{
	  fgets( line, 256, f );
	  //printf( "next line.\n" );
	}
      strcpy( header, "" );
    }
  /*for( i = 0; i < 147 ; i += 3 )
    {
      printf( "%d \t  %f \t%f \t%f \n", i/3+1, tmp_v[i], tmp_v[i+1], tmp_v[i+2] );
    }

  for( i = 0; i < nb_faces*3*3 ; i += 9 )
    {
      printf( "%f \t%f \t%f \n", m->vertex_data[i], m->vertex_data[i+1], m->vertex_data[i+2] );
      printf( "%f \t%f \t%f \n", m->vertex_data[i+3], m->vertex_data[i+4], m->vertex_data[i+5] );
      printf( "%f \t%f \t%f \n\n", m->vertex_data[i+6], m->vertex_data[i+7], m->vertex_data[i+8] );
      }*/

  if( tmp_v != NULL )
    free( tmp_v );
  if( tmp_vt != NULL )
    free( tmp_vt );
  if( tmp_vn != NULL )
    free( tmp_vn );
}
  

void modelLoad( SModel* m, char* file )
{
  FILE* f;
  float* tmp;
  char dump[32];
  int nb_pts, nb_v, pos, i, j, a;
  //int color, nb_faces;
  char header[32];

  a = 0;
  nb_v = 0;

  f = fopen( file, "rb" );

  if( !f )
    {
      printf( "Model : error loading!!!\n" );
      return;
    }

  fscanf( f, "%s", header );
  //printf( "%s\n", header );
  
  fscanf( f, "%d", &nb_pts );
  //printf( "%d\n", nb_pts );

  tmp = malloc( 3 * nb_pts * sizeof( float ) );

  for( i = 0; i < nb_pts; i++ )
    {
      fscanf( f, "%f %f %f", &tmp[(i*3)], &tmp[(i*3)+1], &tmp[(i*3)+2] );
      //fscanf( f, "%f", &tmp[(i*3)] );
      //fscanf( f, "%f", &tmp[(i*3)+1] );
      //fscanf( f, "%f", &tmp[(i*3)+2] );
      //printf( "%f %f %f\n", tmp[(i*3)], tmp[(i*3)+1], tmp[(i*3)+2] );
    }

  pos = ftell( f );

  while( !feof( f ) )
    {
      fscanf( f, "%d", &j );
      printf( "%d \t", j );
      for( i = 0; i < j; i++ )
	{
	  fscanf( f, "%d", &a );
	  printf( "%d \t", a );
	  //nb_v += a;
	}
      fscanf( f, "%s", dump ); 
      printf( "%s\n", dump );
      nb_v += j;
    }
  printf( "vert : %d\n", nb_v );

  m->vertex_data = malloc( 3 * nb_v * sizeof( float ) );

  fseek( f, pos, SEEK_SET );

  i = 0;
  while( !feof( f ) )
    {
      fscanf( f, "%d", &j );
      for( i = 0; i < j; i++ )
	{
	  fscanf( f, "%d", &a );
	  m->vertex_data[(i*3)] = tmp[a];
	  m->vertex_data[(i*3)+1] = tmp[a+1];
	  m->vertex_data[(i*3)+2] = tmp[a+2];
	  i++;
	}
      fscanf( f, "%s", dump );
    }
	

  if( tmp != NULL )
    {
      free( tmp );
    }

  fclose( f );
}
