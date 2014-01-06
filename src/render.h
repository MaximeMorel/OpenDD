// MOREL Maxime
//


//! \file render.h
//! \brief Handle the opengl rendering.
//!


#ifndef RENDER_H
#define RENDER_H


// system includes
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <math.h>

// user includes
#include "smoke.h"
//#include "player.h"
//#include "camera.h"
#include "config.h"
#include "model.h"
#include "light.h"
#include "texture.h"
//#include "menu.h"
#include "opengl_error.h"
#include "version.h"
#include "math_ext.h"
#include "global_vars.h"
#include "vector.h"
#include "particle.h"
#include "tire.h"
//#include "smoke.h"
#include "font.h"
//#include "hud.h"
#include "skybox.h"


//! \struct SRender
//! \brief 
//!
//! \param menu page, selection, nb items in page, activate item.
typedef struct
{
  GLuint dlist_id;
  GLuint* dlist;

  Vector3f camera_pos;

  unsigned int timeout;

  char title[32];
  char title_fps[32]; 
  
  // menu
  int menu[4];
  
  
  //SDL_Surface* screen;
  float* screen;
  
  SCamera* cam;

  SLight light;
  STexture texture;
  //SMenu menu;
  SParticle particle;
  STire tire;
  SSmoke smoke;
  SFont font;
  SSkybox skybox;
  //SModel car_model;
  SModel wheel_model;
  SModel wheel_model_far;

  SModel land;
} SRender;


#include "player.h"
#include "hud.h"
#include "menu.h"
#include "game.h"


void renderInit( SRender* r );
void renderFree( SRender* r );


// init
//! \fn void videoInfo()
//! \brief Give some info about video...
void videoInfo();


//! \fn void videoInit( SPlayer* pl, SRender* r )
//! \brief Init the video and create a window.
void videoInit( SRender* r, SConfig* conf );


//! \fn void setTitle( SRender* r, int nb_frame )
//! \brief Set the title which appear in the window border.
void setTitle( SRender* r, int nb_frame );


//! \fn void openglInit( SRender* render, SPlayer* pl )
//! \brief Init opengl.
void openglInit( SRender* render, SConfig* conf );


//! \fn void createDlist( SRender* render )
//! \brief Store some shapes in opengl display lists.
void createDlist( SRender* render );


//! \fn void reshape( int* res )
//! \brief Toggle fullscreen, set resolution, aspect ratio...
void reshape( int* res );


//! \fn void toggleFullscreen( int* res )
//! \brief 
void toggleFullscreen( int* res );
//void changeResolution( SPlayer* pl );


//! \fn void toggleGrabmouse( bool* grab_mouse )
//! \brief Capture the mouse in the window.
void toggleGrabmouse( bool* grab_mouse );


//! \fn void toggleWireframe( bool* cl_wireframe )
//! \brief Toggle wireframe mode.
void toggleWireframe( bool* cl_wireframe );


//! \fn inline void setFov( int fov )
//! \brief Change fov.
inline void setFov( int fov );


//! \fn inline void orthoMode( const int* res )
//! \brief Set orthographic mode for 2D drawing.
inline void orthoMode( const int* res );


//! \fn inline void perspectiveMode( const int fov, const float ratio )
//! \brief Set perspective mode for 3D ingame drawing.
inline void perspectiveMode( const int fov, const float ratio );


//! \fn inline void clearScreen()
//! \brief Clear the screen. Call it at the end of display.
inline void clearScreen();


//! \fn inline void swapBuffers()
//! \brief Swap the buffers. Usefull when double buffering is on.
inline void swapBuffers();


//! \fn inline void alphaModeOn()
//! \brief Put alpha mode on.
inline void alphaModeOn();


//! \fn inline void alphaModeOff()
//! \brief Put alpha mode off.
inline void alphaModeOff();


//! \fn void drawAxes()
//! \brief A test to draw the axes.
void drawAxes();


//! \fn void display( SRender* render, SPlayer* pl )
//! \brief Display everything.
void display( SRender* render, SPlayer* pl, SGame* g, SLevel* l );


//! \fn void displayWorld( SRender* render, SPlayer* pl )
//! \brief Display mostly static objects.
void displayWorld( SRender* render, SLevel* l );


//! \fn void displayCar( SRender* render, SPlayer* pl )
//! \brief Draw a car.
void displayCar( SRender* render, SCar* c );


//! \fn inline void drawVertexArray( SRender* render, GLenum mode, GLint size, float* va )
//! \brief Draw a vertex array.
inline void drawVertexArray_vnt( SRender* render, GLenum mode, GLint size, float* va );


//! \fn inline void drawVertexArray2( SRender* render, GLenum mode, GLint size, float* va,float* na );
//! \brief Draw a vertex array.
inline void drawVertexArray_vn( SRender* render, GLenum mode, GLint size, float* va,float* na );


inline void drawVertexArray_vc( SRender* render, GLenum mode, GLint size, float* va );


void drawVertexArray_vnt3( SRender* render, GLenum mode, GLint size, float* va, float* vn, float* vt );


void drawVertexArray_v( SRender* render, GLenum mode, GLint size, float* va );


//! \fn void screenFilter( SRender* r, SPlayer* pl );
//! \brief used to filter menu background
void screenFilter( SRender* r, SPlayer* pl );


//! \fn void copyScreen( SRender* r, SPlayer* pl );
//! \brief fill the buffer for the menu background
void copyScreen( SRender* r, SPlayer* pl );


//! \fn void restoreScreen( SRender* r, SPlayer* pl );
//! \brief draw the menu background
void restoreScreen( SRender* r, SPlayer* pl );


//! \fn void delDisplayList( SRender* r, int id )
//! \brief Delete a display list.
void delDisplayList( SRender* r, int id );


void delAllDisplayList( SRender* r );


#endif // RENDER_H
