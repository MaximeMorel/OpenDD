// MOREL Maxime
//


//! \file render.c
//! \brief
//!


#include "render.h"


void renderInit( SRender* r )
{
  r->dlist_id = 0;
  r->dlist = NULL;

  r->timeout = 0;

  r->screen = NULL;

  //particleInit( &r->particle );
  //tireInit( &r->tire );
  //smokeInit( &r->smoke );
  fontInit( &r->font );  
  menuInit( r );  
  textureInit( &r->texture );
  lightInit( &r->light );
  skyboxInit( &r->skybox );

  //modelInit( &r->car_model );
  //modelLoadObj( &r->car_model, "data/models/car.obj" );
    
  modelInit( &r->wheel_model );
  modelLoadObj( &r->wheel_model, "data/models/wheel1-2.obj" );

  modelInit( &r->wheel_model_far );
  modelLoadObj( &r->wheel_model_far, "data/models/wheel2-2.obj" );

  modelInit( &r->land );
  modelLoadObj( &r->land, "data/models/land.obj" );

  printf( "Struct render : OK.\n" );
}


void renderFree( SRender* r )
{  
  if( r->screen != NULL )
    {
      free( r->screen );
    }

  skyboxFree( &r->skybox );
  lightFree( &r->light );
  fontFree( &r->font, &r->texture );
  menuFree( r );
  smokeFree( &r->smoke );
  tireFree( &r->tire );
  particleFree( &r->particle );
  textureFree( &r->texture );

  //modelFree( &r->car_model );
  modelFree( &r->land );
  modelFree( &r->wheel_model_far );
  modelFree( &r->wheel_model );

  delAllDisplayList( r );
    
  printf ( "Struct render : free.\n" );
}


// affichage principal
void display( SRender* render, SPlayer* pl, SGame* g, SLevel* l )
{
  int i;
  // clear the screen
  clearScreen();

  glRotatef( (render->cam->rx+M_PI_2) * RAD2DEG, 0.0f, 1.0f, 0.0f );
  glRotatef( render->cam->ry * RAD2DEG, render->cam->sin_rx, 0.0f, -render->cam->cos_rx );
  
  glTranslatef( -render->cam->pos[0], -render->cam->pos[1], -render->cam->pos[2] );
      
  // start drawing scene

  displayWorld( render, l );

  // smoke first, because no depth test
  /*alphaModeOn();
  glDisable( GL_DEPTH_TEST );
  glDisable( GL_LIGHTING );
  //glEnable( GL_TEXTURE_2D );
  smokeDraw( &render->smoke, cam );
  glEnable( GL_LIGHTING );
  glEnable( GL_DEPTH_TEST );
  alphaModeOff();*/

  for( i = 0; i < *g_nb_car; i++ )
    {
      displayCar( render, &pl[i].car );
    }
    
  // particles
  glDisable( GL_LIGHTING );
  //glEnable( GL_POINT_SMOOTH ); // very slow
  //glEnable( GL_POINT_SPRITE );
  //float coeffs[] = {50.0f, 2.1f, 1.1f};
  //glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, coeffs);

  //Taille du point
  //glPointParameterf (GL_POINT_SIZE_MAX, 32.0);
  //glPointParameterf (GL_POINT_SIZE_MIN, 1.0f);
  drawVertexArray_vc( render, GL_POINTS, render->particle.size, render->particle.part );

  // tire traces
  alphaModeOn();
  glNormal3f( 0.0f, 1.0f, 0.0f );
  glColor4f( 0.0f, 0.0f, 0.0f, 0.7f );
  drawVertexArray_v( render, GL_QUADS, render->tire.size*16, render->tire.trace );
  //alphaModeOff();  

  alphaModeOn();
  glDisable( GL_DEPTH_TEST );
  glDisable( GL_LIGHTING );
  glEnable( GL_TEXTURE_2D );
  smokeDraw( &render->smoke, render->cam );
  glEnable( GL_LIGHTING );
  glEnable( GL_DEPTH_TEST );
  //alphaModeOff();

  // end drawing scene
    
  // first plane
  glDisable( GL_DEPTH_TEST );
  glDisable( GL_LIGHTING );
  //glEnable( GL_TEXTURE_2D );
  orthoMode( pl->conf->res );  

  // hud
  //glDisable( GL_TEXTURE_2D );
  //alphaModeOn();
  hudDraw( render, pl, g );
  alphaModeOff();

  glEnable( GL_DEPTH_TEST );

  //pl->conf->cl_fov = 5;
    
  perspectiveMode( pl->conf->cl_fov, pl->conf->res[0]/pl->conf->res[1] );	
  
  swapBuffers();
}


void displayWorld( SRender* render, SLevel* l )
{
  //int i,j;
  // start drawing scene
  // skybox
  glPushMatrix();
  glTranslatef( render->cam->pos[0], render->cam->pos[1], render->cam->pos[2] );
  glScalef( 1024.0f, 1024.0f, 1024.0f );
  glCallList( render->skybox.id );
  glPopMatrix();

  lightUpdate( &render->light );

  // land
  //glDisable( GL_TEXTURE_2D );
  //glColor3f( 1.0f, 0.0f, 0.0f );
  glBindTexture( GL_TEXTURE_2D, render->texture.texture_id[0] );
  drawVertexArray_vnt3( render, GL_TRIANGLES, render->land.nb,
  			render->land.vertex_data, render->land.norm_data, render->land.tex_data );
  // level
  glCallList( l->level );
  
  // end scene
}


void createDlist( SRender* render )
{	
  printf ( "\nCreating display lists...\n" );
  int i;
  int nb_dlist = 5;
  //dlist_id = 1;
  
  render->dlist_id = glGenLists( nb_dlist );
  if ( render->dlist_id == 0)
    {
      printf ( "Error finding display lists ids !!!\n" );
      return;
    }
  
  glNewList ( render->dlist_id+1, GL_COMPILE );							   // 1
  // cube
  //glBindTexture ( GL_TEXTURE_2D, 3 );
  //glColor3f(1,1,1);
  glBegin ( GL_QUADS );
  //
  glNormal3f ( 0.0, 0.0, 1.0);
  glTexCoord2f ( 0.0, 0.0 );	glVertex3f ( -0.5, 0.5, 0.5 );
  glTexCoord2f ( 0.0, 1.0 );	glVertex3f ( -0.5, -0.5, 0.5 );
  glTexCoord2f ( 1.0, 1.0 );	glVertex3f ( 0.5, -0.5, 0.5 );
  glTexCoord2f ( 1.0, 0.0 );	glVertex3f ( 0.5, 0.5, 0.5 );
  
  //
  glNormal3f ( 1.0, 0.0, 0.0);
  glTexCoord2f ( 0.0, 0.0 );	glVertex3f ( 0.5, 0.5, 0.5 );
  glTexCoord2f ( 0.0, 1.0 );	glVertex3f ( 0.5, -0.5, 0.5 );
  glTexCoord2f ( 1.0, 1.0 );	glVertex3f ( 0.5, -0.5, -0.5 );
  glTexCoord2f ( 1.0, 0.0 );	glVertex3f ( 0.5, 0.5, -0.5 );
  
  //
  glNormal3f ( 0.0, 0.0, -1.0);
  glTexCoord2f ( 0.0, 0.0 );	glVertex3f ( 0.5, 0.5, -0.5 );
  glTexCoord2f ( 0.0, 1.0 );	glVertex3f ( 0.5, -0.5, -0.5 );
  glTexCoord2f ( 1.0, 1.0 );	glVertex3f ( -0.5, -0.5, -0.5 );
  glTexCoord2f ( 1.0, 0.0 );	glVertex3f ( -0.5, 0.5, -0.5 );
  
  //
  glNormal3f ( -1.0, 0.0, 0.0);
  glTexCoord2f ( 0.0, 0.0 );	glVertex3f ( -0.5, 0.5, -0.5 );
  glTexCoord2f ( 0.0, 1.0 );	glVertex3f ( -0.5, -0.5, -0.5 );
  glTexCoord2f ( 1.0, 1.0 );	glVertex3f ( -0.5, -0.5, 0.5 );
  glTexCoord2f ( 1.0, 0.0 );	glVertex3f ( -0.5, 0.5, 0.5 );
  
  // up
  glNormal3f ( 0.0, 1.0, 0.0);
  glTexCoord2f ( 0.0, 0.0 );	glVertex3f ( -0.5, 0.5, -0.5 );
  glTexCoord2f ( 0.0, 1.0 );	glVertex3f ( -0.5, 0.5, 0.5 );
  glTexCoord2f ( 1.0, 1.0 );	glVertex3f ( 0.5, 0.5, 0.5 );
  glTexCoord2f ( 1.0, 0.0 );	glVertex3f ( 0.5, 0.5, -0.5 );
  
  // down
  glNormal3f ( 0.0, -1.0, 0.0);
  glTexCoord2f ( 0.0, 0.0 );	glVertex3f ( 0.5, -0.5, -0.5 );
  glTexCoord2f ( 0.0, 1.0 );	glVertex3f ( 0.5, -0.5, 0.5 );
  glTexCoord2f ( 1.0, 1.0 );	glVertex3f ( -0.5, -0.5, 0.5 );
  glTexCoord2f ( 1.0, 0.0 );	glVertex3f ( -0.5, -0.5, -0.5 );
  glEnd (  );
  
  glEndList (  );
#ifdef __DEBUG_DISPLAY_LIST__
  check_display_list ( render->dlist_id+1 );
#endif // __DEBUG_DISPLAY_LIST__
  
	
  // circle
  glNewList( render->dlist_id+3, GL_COMPILE );							   // 3
  glBegin( GL_LINE_LOOP );
  for( i = 0 ; i < 36 ; i++ )
    {
      //glVertex3f ( pl->px + cos((i * M_PI * 10 ) / 180 )/ 10, 0.5, pl->pz + sin((i * M_PI * 10) / 180 ) / 10 );
      glVertex2f( cosf( ( i * M_PI * 10 ) / 180 ) * 100, sinf( ( i * M_PI * 10 ) / 180 ) * 100 );
    }
  glEnd();
  glEndList();
#ifdef __DEBUG_DISPLAY_LIST__
  checkDlist( render->dlist_id+3 );
#endif // __DEBUG_DISPLAY_LIST__
  
  
  // sphere
  glNewList( render->dlist_id+4, GL_COMPILE );							   // 4
  GLUquadric* sphere;
  sphere = gluNewQuadric();
  gluQuadricDrawStyle( sphere, GLU_FILL );
  gluQuadricTexture( sphere, GL_TRUE );
  gluQuadricOrientation( sphere, GLU_OUTSIDE );
  gluSphere( sphere, 2, 36, 36 );	
  gluDeleteQuadric( sphere );
  glEndList();
#ifdef __DEBUG_DISPLAY_LIST__
  checkDlist( render->dlist_id+4 );
#endif // __DEBUG_DISPLAY_LIST__
  
  //printf ( "\n" );
}


void openglInit( SRender* render, SConfig* conf )
{
  glShadeModel( GL_SMOOTH );
  
  glCullFace( GL_BACK );
  glFrontFace( GL_CCW );
  glEnable( GL_CULL_FACE );
  glEnable( GL_DEPTH_TEST );
  glEnable( GL_LIGHTING );
  glEnable( GL_LIGHT0 );

  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( conf->cl_fov, conf->res[0]/conf->res[1], 0.1f, 1024.0f );

  glMatrixMode( GL_MODELVIEW );
  
  glPointSize( 5 );
  
  //GLfloat fog_color[] = {0.8, 0.8, 0.8, 1.0};
  /*GLfloat fog_color[] = {0, 0, 0, 1.0};
    glEnable ( GL_FOG );
    glFogi ( GL_FOG_MODE, GL_EXP );
    glFogfv ( GL_FOG_COLOR, fog_color );
    glFogf ( GL_FOG_START, 0 );
    glFogf ( GL_FOG_END, 100 );
    glFogf ( GL_FOG_DENSITY, 0.1 );*/
  
  if( conf->cl_wireframe )
    {
      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }
}


void videoInit( SRender* r, SConfig* conf )
{
  reshape( conf->res );	// create opengl window
  strcpy( r->title, TITLE );
  strcat( r->title, " v" );
  strcat( r->title, VERSION );
  SDL_WM_SetCaption( r->title, r->title );
  SDL_WM_SetIcon( SDL_LoadBMP("data/icon.bmp"), NULL );
  
  toggleGrabmouse( &conf->grab_mouse );

  //  if ( pl->conf->grab_mouse )
  //  {
  //    SDL_Delay( 100 );
  //    SDL_WM_GrabInput( SDL_GRAB_ON );
  //    SDL_ShowCursor( 0 );
  //  }
}


void setTitle( SRender* r, int nb_frame )
{
  //sprintf( r->title_fps, "%s fps:%3d", r->title, (int)pl->pl_fps->fps );
  sprintf( r->title_fps, "%s fps:%3d", r->title, nb_frame );
  SDL_WM_SetCaption( r->title_fps, NULL );
}


void reshape( int* res )
{
  res[7] = 0;
  if( res[8] == 1 )
    {
      res[7] = SDL_OPENGL | SDL_FULLSCREEN;
      res[0] = res[4];
      res[1] = res[5];
    }
  else
    {
      res[7] = SDL_OPENGL;
      res[0] = res[2];
      res[1] = res[3];
    }

  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, res[6] );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

  if( SDL_SetVideoMode( res[0], res[1], res[6], res[7] ) == NULL )
    {
      printf( "\nVideo mode set failed: %s\n", SDL_GetError() );
      //quit( 1 );
    }
    glViewport( 0, 0, res[0], res[1] );
  printf( "\nVideo mode set : %dx%dx%d\n", res[0], res[1], res[6] ); 
}


void toggleFullscreen( int* res )
{
  res[8] = 1 - res[8];
  reshape( res );
}


void set_resolution()
{
	
}


void toggleGrabmouse( bool* grab_mouse )
{
  if( *grab_mouse )
    {
      SDL_WM_GrabInput( SDL_GRAB_OFF );
      SDL_ShowCursor( SDL_ENABLE );
      *grab_mouse = false;
    }
  else
    {
      SDL_WM_GrabInput( SDL_GRAB_ON );
      SDL_ShowCursor( SDL_DISABLE );
      *grab_mouse = true;
    }
}


void toggleWireframe( bool* cl_wireframe )
{
  if( *cl_wireframe )
    {
      glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
      *cl_wireframe = false;
    }
  else
    {
      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
      *cl_wireframe = true;
    }
}


void setFov( int fov )
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( fov, 1.0f, 0.1f, 1024.0f );
  glMatrixMode( GL_MODELVIEW );
}


// orthogonal draw
void orthoMode( const int *res )
{
  glMatrixMode( GL_PROJECTION );
  //glPushMatrix();
  glLoadIdentity();
  gluOrtho2D( 0, res[0], 0, res[1] );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}


// perspective draw
void perspectiveMode( const int fov, const float ratio )
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( fov, ratio, 0.1f, 1024.0f );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}


// wipe screen
void clearScreen()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}


// swap front & back buffers ( end of frame )
void swapBuffers()
{
  glFlush();
  
  checkGlError( "swap" );
  
  SDL_GL_SwapBuffers();
}

// transparence
void alphaModeOn()
{
  glEnable( GL_BLEND );
  //glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}


void alphaModeOff()
{
  glDisable( GL_BLEND );
}


void videoInfo()
{
  char drv[100 + 1];
  const SDL_VideoInfo* vid_info = SDL_GetVideoInfo();
  printf( "\nVid info : %s  ", SDL_VideoDriverName( drv, 100 ) );
  printf( "%d ", vid_info->hw_available );
  printf( "%d ", vid_info->wm_available );
  printf( "%d ", vid_info->blit_hw );
  printf( "%d ", vid_info->blit_hw_CC );
  printf( "%d ", vid_info->blit_hw_A );
  printf( "%d ", vid_info->blit_sw );
  printf( "%d ", vid_info->blit_sw_CC );
  printf( "%d ", vid_info->blit_sw_A );
  printf( "%d ", vid_info->blit_fill );
  printf( "%d ", vid_info->video_mem );
  printf( "%d \n", vid_info->vfmt->BitsPerPixel );
  printf( "Vendor : %s\n", glGetString ( GL_VENDOR ) );
  printf( "Renderer : %s\n", glGetString( GL_RENDERER ) );
  printf( "Opengl version : %s\n", glGetString( GL_VERSION ) );
  printf( "GLU version : %s\n", gluGetString( GLU_VERSION ) );
  printf( "GL extensions : %s \n", glGetString( GL_EXTENSIONS ) );
  printf( "GLU extensions : %s \n", gluGetString( GLU_EXTENSIONS ) );
  printf( "\n" );
}


void screenFilter( SRender* r, SPlayer* pl )
{
  int i;

  if( r->screen != NULL )
    {
      if( r->screen[0] < 10.0f )
	{
	  for( i = 3*pl->conf->res[0]; i < 3*pl->conf->res[0]*pl->conf->res[1]-3*pl->conf->res[0]; i+=3 )
	    {
	      r->screen[i] = r->screen[i-3-3*pl->conf->res[0]]/9.0f +r->screen[i-3*pl->conf->res[0]]/9.0f + r->screen[i+3-3*pl->conf->res[0]]/9.0f + 
		r->screen[i-3]/9.0f +r->screen[i]/9.0f + r->screen[i+3]/9.0f + 
		r->screen[i-3+3*pl->conf->res[0]]/9.0f +r->screen[i+3*pl->conf->res[0]]/9.0f + r->screen[i+3+3*pl->conf->res[0]]/9.0f;
	      
	      r->screen[i+1] = r->screen[i-2-3*pl->conf->res[0]]/9.0f +r->screen[i+1-3*pl->conf->res[0]]/9.0f + r->screen[i+4-3*pl->conf->res[0]]/9.0f + 
		r->screen[i-2]/9.0f +r->screen[i+1]/9.0f + r->screen[i+4]/9.0f + 
		r->screen[i-2+3*pl->conf->res[0]]/9.0f +r->screen[i+1+3*pl->conf->res[0]]/9.0f + r->screen[i+4+3*pl->conf->res[0]]/9.0f;
	      
	      r->screen[i+2] = r->screen[i-1-3*pl->conf->res[0]]/9.0f +r->screen[i+2-3*pl->conf->res[0]]/9.0f + r->screen[i+5-3*pl->conf->res[0]]/9.0f + 
		r->screen[i-1]/9.0f +r->screen[i+2]/9.0f + r->screen[i+5]/9.0f + 
		r->screen[i-1+3*pl->conf->res[0]]/9.0f +r->screen[i+2+3*pl->conf->res[0]]/9.0f + r->screen[i+5+3*pl->conf->res[0]]/9.0f;
	    }

	  r->screen[0]++;
	}
    }
}


void copyScreen( SRender* r, SPlayer* pl )
{
  if( r->screen != NULL )
    {
      free( r->screen );
      r->screen = NULL;
    }

  r->screen = malloc( 3*pl->conf->res[0]*pl->conf->res[1]*sizeof(float) );

  glReadPixels( 0, 0, pl->conf->res[0], pl->conf->res[1], GL_RGB, GL_FLOAT, r->screen );

  // counter
  r->screen[0] = 0.0f;
}


void restoreScreen( SRender* r, SPlayer* pl )
{
  if( r->screen != NULL )
    {  
      glDrawPixels( pl->conf->res[0], pl->conf->res[1], GL_RGB, GL_FLOAT, r->screen );
    }
}


void delDisplayList( SRender* r, int id )
{
  if( glIsList( r->dlist_id ) )
    {
      glDeleteLists( r->dlist_id+id, 1 );
    }
}


void delAllDisplayList( SRender* r )
{
  int i;
  for( i = 1000; i > 0; i-- )
    {
      delDisplayList( r, i );
    }
}
