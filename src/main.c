// MOREL Maxime
//


//! \file main.c
//! \brief Main source.
//!
//! It includes and inits almost everything.\n
//! 1 - Command line analyse.\n
//! 2 - Config init.\n
//! 3 - Fps init.\n
//! 4 - Player init.\n
//! 5 - Menu init. TODO\n
//! 6 - Texture init.\n
//! 7 - Render init.\n
//! 8 - SDL & opengl init.\n
//! 9 - Ressources loading.\n
//! 10 - Entering the main loop.\n
//! 11 - Free everything & exit.\n
//!


#include "main.h"


int main( int argc, char **argv )
{
  int i;
  cmdline( argc, argv );

  printf( "launching...\n" );

  // init...
  SGame game;
  gameInit( &game );
  gameSetNbCars( &game, 20 );
  gameSetMode( &game, GAME_NORMAL );
  game.nb_cars[0] = game.nb_cars[2];
  g_nb_car = &game.nb_cars[0];
  g_fps = &game.fps;

  SConfig conf;
  configInit( &conf );
  //configLoad( &conf );

  SCamera cam;
  cameraInit( &cam );

  SPlayer* pl = NULL;
  pl = playersInit( pl, &conf, game.mode, game.nb_cars[2] );
  cam.player = &pl[0];
  
  SRender ren;
  renderInit( &ren );
  ren.cam = &cam;
  particleInit( &ren.particle, conf.particle_nb );
  tireInit( &ren.tire, conf.tire_nb );
  smokeInit( &ren.smoke, conf.smoke_nb );

  SSound sound;
  //soundAlutInit( &sound );
  //soundAlutInfo( &sound );
  soundInit( &sound );
  openalInit( &sound );
  openalInfo( &sound );

  // run...
  if( !sdlInit() )
    {
      quit(1);
    }

  // init video...
  videoInit( &ren, &conf );
  openglInit( &ren, &conf );
  videoInfo();

  // load data...

  // textures...
  loadTextures( &ren.texture );

  // level load...
  SLevel level;
  levelInit( &level );
  levelGen( &level, &ren.texture );

  // fonts...
  fontGen( &ren.font, &ren.texture );

  // players textures
  playersLoadTexture( pl, &ren.texture );

  skyboxLoadTexture( &ren.skybox, &ren.texture );
  skyboxGen( &ren.skybox );
  smokeGen( &ren.smoke, &ren.texture );
  //createDlist( &ren );

  // game loop...
  SDL_Event event;
  pl = gameLoop( &game, &event, &level, pl, &ren, &sound );

  // free...
  levelFree( &level );
  soundFree( &sound );
  cameraFree( &cam );
  for( i = 0; i < *g_nb_car; i++ )
    {
      playerFree( &pl[i] );
    }
  free( pl );
  renderFree( &ren );
  configFree( &conf );
  gameFree( &game );

  // exit...
  quit(0);
  return 0;
}


bool sdlInit()
{
  if( SDL_Init(SDL_INIT_VIDEO) == -1 )
    {
      printf( "SDL init : error !!!\n" );
      return false;
    }
  else
    {
      printf( "SDL init : OK.\n" );
      return true;
    }
}


void cmdline ( int argc, char **argv )
{
}


int quit(int code)
{
  SDL_Quit();
  printf( "SDL exit.\n" );
  if( code )
    printf( "Error !!!\n" );
  else
    printf( "Normal exit\n" );
  
  if( code )
    exit( code );

  return 0;
}
