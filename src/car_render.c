//
//


#include "render.h"


void displayCar( SRender* render, SCar* c )
{
  Vector3f camera2car;
  float dist;

  setVector3fv( camera2car, c->pos );
  subVector3fv( camera2car, render->cam->pos );
  dist = sqrModule3fv( camera2car );
  //mulVector3fv( camera2car, 1.0f/dist );
  normalize3fv( camera2car );

  if( dotProduct3fv( render->cam->look, camera2car ) > 0.70f || dist < 100.0f )
    {
      // lod :-)
      //static int i;
      static SModel* wheel;
      if( sqrModule3f( c->pos[0]-render->cam->pos[0], c->pos[1]-render->cam->pos[1], c->pos[2]-render->cam->pos[2] ) < 400.0f )
	{
	  wheel = &render->wheel_model;
	}
      else
	{
	  wheel = &render->wheel_model_far;
	}
      
      glEnable( GL_LIGHTING );
      glEnable( GL_TEXTURE_2D );
      
      glPushMatrix();
      
      // car position.
      glTranslatef( c->pos[0], 0.01f, c->pos[2] );
      
      // roll TODO
      glRotatef( c->roll, c->dir_vect[0], 0.0f, c->dir_vect[2] );

      // pitch TODO
      glRotatef( c->pitch, -c->dir_vect[2], 0.0f, c->dir_vect[0]);

      // car angle.
      glRotatef( -c->dir * RAD2DEG, 0.0f, 1.0f, 0.0f );

      // draw car
      glDisable( GL_CULL_FACE );
      glBindTexture( GL_TEXTURE_2D, c->texture );
      drawVertexArray_vnt3( render, GL_TRIANGLES, c->car_model.nb,
			    c->car_model.vertex_data, c->car_model.norm_data, c->car_model.tex_data );
      //glEnable( GL_CULL_FACE );
      glPopMatrix();
      //glPopMatrix();

  
      // wheels
      glBindTexture( GL_TEXTURE_2D, render->texture.texture_id[1] );

      // wheel fr
      glPushMatrix();  
      glTranslatef( c->pos[0], 0.27f, c->pos[2] );
      glRotatef(  -c->dir * RAD2DEG, 0.0f, 1.0f, 0.0f );
      glTranslatef( 1.36f, 0.0f, 0.92f );
      glRotatef( -c->wheel_angle * RAD2DEG, 0.0f, 1.0f, 0.0f );
      glRotatef( -c->wheel_rotation, 0.0f, 0.0f, 1.0f );
      drawVertexArray_vnt3( render, GL_TRIANGLES, wheel->nb,
			    wheel->vertex_data, wheel->norm_data, wheel->tex_data );
      glPopMatrix();


      // wheel fl
      glPushMatrix();
      glTranslatef( c->pos[0], 0.27f, c->pos[2] );
      glRotatef( 180.0f, 0.0f, 1.0f, 0.0f );
      glRotatef(  -c->dir * RAD2DEG, 0.0f, 1.0f, 0.0f );
      glTranslatef( -1.36f, 0.0f, 0.92f );
      glRotatef( -c->wheel_angle * RAD2DEG, 0.0f, 1.0f, 0.0f );
      glRotatef( c->wheel_rotation, 0.0f, 0.0f, 1.0f );
      drawVertexArray_vnt3( render, GL_TRIANGLES, wheel->nb,
			    wheel->vertex_data, wheel->norm_data, wheel->tex_data );
      glPopMatrix();
  
  
      // wheel rr
      glPushMatrix();
      glTranslatef( c->pos[0], 0.27f, c->pos[2] );
      glRotatef( -c->dir * RAD2DEG, 0.0f, 1.0f, 0.0f );
      glTranslatef( -0.92f, 0.0f, 0.9f );
      glRotatef( -c->wheel_rotation, 0.0f, 0.0f, 1.0f );  
      drawVertexArray_vnt3( render, GL_TRIANGLES, wheel->nb,
			    wheel->vertex_data, wheel->norm_data, wheel->tex_data );
      glPopMatrix();


      // wheel rl
      glPushMatrix();
      glTranslatef( c->pos[0], 0.27f, c->pos[2] );
      glRotatef( 180.0f, 0.0f, 1.0f, 0.0f );
      glRotatef( -c->dir * RAD2DEG, 0.0f, 1.0f, 0.0f );
      glTranslatef( 0.92f, 0.0f, 0.9f );
      glRotatef( c->wheel_rotation, 0.0f, 0.0f, 1.0f );     
      drawVertexArray_vnt3( render, GL_TRIANGLES, wheel->nb,
			    wheel->vertex_data, wheel->norm_data, wheel->tex_data );
      glPopMatrix();

      glDisable( GL_TEXTURE_2D );
      glDisable( GL_LIGHTING );

  
      //glTranslatef( -0.92f, 0.0f, -1.0f );
      // shadow
      alphaModeOn();
      glPushMatrix();
      glTranslatef( c->pos[0], 0.01f, c->pos[2] );
      glRotatef( -c->dir * RAD2DEG, 0.0f, 1.0f, 0.0f );
      glBegin( GL_QUADS );

      glColor4f( 0.0f, 0.0f, 0.0f, 0.5f );

      glVertex3i( 2, 0, 1 );
      glVertex3i( 2, 0, -1 );
      glVertex3i( -2, 0, -1 );
      glVertex3i( -2, 0, 1 );

      glEnd();
      glPopMatrix();
      alphaModeOff();

      // bounding circle
      /*glColor3f( 0.0f, 0.0f, 1.0f );
	glBegin( GL_LINE_LOOP );
	for( i = 0 ; i < 36 ; i++ )
	{
	glVertex3f( c->pos[0]+cosf(( i * M_PI * 10.0f )/180.0f )*2.24f, 0.01f, \
	c->pos[2]+sinf(( i * M_PI * 10.0f )/180.0f )*2.24f );
	}
	glEnd();*/

      //axes
      //drawAxes();

  
      // camera pos
      //glBegin( GL_LINES );
      //glVertex3f( c->pos_x, 0.0f, c->pos_z );
      //glVertex3f( pl->px_norm, 0.0f, pl->pz_norm );
      //glEnd();

      // speed vector
      /*glColor3f( 1.0f, 0.0f, 0.0f );
	glBegin( GL_LINES );
	glVertex3f( c->pos[0], 1.2, c->pos[2] );
	glVertex3f( c->pos[0] + 3.0f*c->v[0], 1.2, c->pos[2] + 3.0f*c->v[2] );
	glEnd();*/

      // accel vector
      /*glColor3f( 0.0f, 1.0f, 0.0f );
	glBegin( GL_LINES );
	glVertex3f( c->pos[0], 1.2, c->pos[2] );
	glVertex3f( c->pos[0] + 3.0f*c->a[0], 1.2, c->pos[2] + 3.0f*c->a[2] );
	glEnd();*/

      // corners test
      /*glColor3f( 0.0f, 1.0f, 1.0f );
	glBegin( GL_LINE_LOOP );
	glVertex3f( c->corners[0], 0.1f, c->corners[1] );
	glVertex3f( c->corners[2], 0.1f, c->corners[3] );
	glVertex3f( c->corners[4], 0.1f, c->corners[5] );
	glVertex3f( c->corners[6], 0.1f, c->corners[7] );
	glEnd();

	glBegin( GL_POINTS );

	glColor3f( 1.0f, 0.0f, 0.0f );
	glVertex3f( c->corners[0], 0.1f, c->corners[1] );
	glColor3f( 0.0f, 1.0f, 0.0f );
	glVertex3f( c->corners[2], 0.1f, c->corners[3] );
	glColor3f( 0.0f, 0.0f, 1.0f );
	glVertex3f( c->corners[4], 0.1f, c->corners[5] );
	glColor3f( 1.0f, 0.0f, 1.0f );
	glVertex3f( c->corners[6], 0.1f, c->corners[7] );

	glColor3f( 1.0f, 0.0f, 0.0f );
	glVertex3f( c->side[0], 0.1f, c->side[1] );
	glColor3f( 0.0f, 1.0f, 0.0f );
	glVertex3f( c->side[2], 0.1f, c->side[3] );

	glEnd();*/
    }
}
