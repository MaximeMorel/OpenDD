//
//


#include "hud.h"


void hudDraw( SRender* r, SPlayer* p, SGame* g )
{
  glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
  hudScore( r, p );
  hudFps( r, p );
  hudTimer( r, p );
  hudSpeed( r, p );
  hudGameStatus( r, g, p );
  //hudDebug( r, p );

  if( p->car.state & CAR_DEAD )
    {
      hudCarDead( r, g, p );
    }
  else
    {
      if( g->nb_cars[1] == 1 )
	{
	  glColor4f( 0.8f, 0.0f, 0.0f, 1.0f );
	  glPrintf( &r->font, "Your are the only survivor !!!", 3*p->conf->res[0]/20, 4*p->conf->res[1]/20, p->conf->res[0]/40 );
	}
    }



  if( p->state & PAUSE )
    {
      glPrintf( &r->font, "PAUSE", p->conf->res[0]/2 - 50, 2*p->conf->res[1]/3, 20 );
    }

  hudCarState( r, p );
}


void hudCarState( SRender* r, SPlayer* p )
{
  float a = p->conf->res[0]/64.0f;
  float b = p->conf->res[1]/64.0f;
  
  glDisable( GL_TEXTURE_2D );

  glBegin( GL_TRIANGLES );

  // front right
  if( (int)p->car.damage[0] == 1 )
    {
      glColor4f( 0.0f, 0.0f, 0.0f, 0.55f );
    }
  else
    {
      glColor4f( p->car.damage[0], 1.0f - p->car.damage[0], 0.0f, 0.55f );
    }
  glVertex2f( a*60.0f, b*10.0f );
  glVertex2f( a*59.0f, b*10.0f );
  glVertex2f( a*59.5f, b*9.0f );
  
  // front left
  if( (int)p->car.damage[1] == 1 )
    {
      glColor4f( 0.0f, 0.0f, 0.0f, 0.55f );
    }
  else
    {
      glColor4f( p->car.damage[1], 1.0f - p->car.damage[1], 0.0f, 0.55f );
    }
  glVertex2f( a*58.0f, b*10.0f );
  glVertex2f( a*57.0f, b*10.0f );
  glVertex2f( a*57.5f, b*9.0f );

  // rear right
  if( (int)p->car.damage[3] == 1 )
    {
      glColor4f( 0.0f, 0.0f, 0.0f, 0.55f );
    }
  else
    {
      glColor4f( p->car.damage[3], 1.0f - p->car.damage[3], 0.0f, 0.55f );
    }
  glVertex2f( a*59.0f, b*2.0f );
  glVertex2f( a*60.0f, b*2.0f );
  glVertex2f( a*59.5f, b*3.0f );

  // rear left
  if( (int)p->car.damage[4] == 1 )
    {
      glColor4f( 0.0f, 0.0f, 0.0f, 0.55f );
    }
  else
    {
      glColor4f( p->car.damage[4], 1.0f - p->car.damage[4], 0.0f, 0.55f );
    }
  glVertex2f( a*57.0f, b*2.0f );
  glVertex2f( a*58.0f, b*2.0f );
  glVertex2f( a*57.5f, b*3.0f );

  // side right
  if( (int)p->car.damage[2] == 1 )
    {
      glColor4f( 0.0f, 0.0f, 0.0f, 0.55f );
    }
  else
    {
      glColor4f( p->car.damage[2], 1.0f - p->car.damage[2], 0.0f, 0.55f );
    }
  glVertex2f( a*60.5f, b*5.5f );
  glVertex2f( a*60.5f, b*6.5f );
  glVertex2f( a*59.5f, b*6.0f );

  // side left
  if( (int)p->car.damage[5] == 1 )
    {
      glColor4f( 0.0f, 0.0f, 0.0f, 0.55f );
    }
  else
    {
      glColor4f( p->car.damage[5], 1.0f - p->car.damage[5], 0.0f, 0.55f );
    }
  glVertex2f( a*56.5f, b*6.5f );
  glVertex2f( a*56.5f, b*5.5f );
  glVertex2f( a*57.5f, b*6.0f );

  glEnd();
}


void hudScore( SRender* r, SPlayer* p )
{
  char score[50];
  sprintf( score, "Score brutal : %3d", p->score[0] );
  glPrintf( &r->font, score, p->conf->res[0]/50, 19*p->conf->res[1]/20, p->conf->res[0]/55 );
  sprintf( score, "      normal : %3d", p->car.score );
  glPrintf( &r->font, score, p->conf->res[0]/50, 18*p->conf->res[1]/20, p->conf->res[0]/55 );
}


void hudSpeed( SRender* r, SPlayer* p )
{
  char spd[10];
  sprintf( spd, "%3d KM/H", (int)(1.5f*p->car.speed) );
  glPrintf( &r->font, spd, 13*p->conf->res[0]/20, 1*p->conf->res[1]/20, p->conf->res[0]/40 );
}


void hudFps( SRender* r, SPlayer* p )
{
  char fps[15];
  sprintf( fps, "FPS : %3d", g_fps->fps_per_sec );
  glPrintf( &r->font, fps, 17*p->conf->res[0]/20, 19*p->conf->res[1]/20, p->conf->res[0]/80 );
}


void hudTimer( SRender* r, SPlayer* p )
{
  char timer[30];
  int time, minutes, seconds, mseconds;

  if( p->state & PAUSE )
    {
      time = g_fps->time_start_pause - g_fps->time_start;
    }
  else
    {
      time = g_fps->time_now - g_fps->time_start;
    }

  minutes = 0;

  mseconds = (time%1000)/10;

  seconds = time/1000;
  while( seconds >= 60 )
    {
      minutes++;
      seconds-=60;
    }

  sprintf( timer, "%3d'%2d\"%2d", minutes, seconds, mseconds );
  //sprintf( timer, "%d", time );
  glPrintf( &r->font, timer, 1*p->conf->res[0]/50, 1*p->conf->res[1]/20, p->conf->res[0]/70 );
}


void hudCarDead( SRender* r, SGame* g, SPlayer* p )
{
  char word[25];
  sprintf( word, "Your car is dead !!!" );
  glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
  glPrintf( &r->font, word, 5*p->conf->res[0]/20, 10*p->conf->res[1]/20, p->conf->res[0]/30 );

  if( g->nb_cars[1] == 0 )
    {
      sprintf( word, "No survivors !!!" );
      glColor4f( 0.8f, 0.0f, 0.0f, 1.0f );
      glPrintf( &r->font, word, 6*p->conf->res[0]/20, 8*p->conf->res[1]/20, p->conf->res[0]/30 );
    }
}


void hudGameStatus( SRender* r, SGame* g, SPlayer* p )
{
  char stat[20];
  sprintf( stat, "Cars : %2d/%2d", g->nb_cars[1], g->nb_cars[0] );
  glPrintf( &r->font, stat, 16*p->conf->res[0]/20, 18*p->conf->res[1]/20, p->conf->res[0]/70 );
}


void hudDebug( SRender* r, SPlayer* p )
{
  char debug[64];
  sprintf( debug, "car speed: %.2f", p->car.speed );
  glPrintf( &r->font, debug, 35*p->conf->res[0]/50, 18*p->conf->res[1]/20, p->conf->res[0]/70 );
  sprintf( debug, "car accel: %.2f", p->car.acceleration );
  glPrintf( &r->font, debug, 35*p->conf->res[0]/50, 17*p->conf->res[1]/20, p->conf->res[0]/70 );
  sprintf( debug, "car state: %d", p->car.state );
  glPrintf( &r->font, debug, 35*p->conf->res[0]/50, 16*p->conf->res[1]/20, p->conf->res[0]/70 );
  sprintf( debug, "car sens: %d", p->car.sens );
  glPrintf( &r->font, debug, 35*p->conf->res[0]/50, 15*p->conf->res[1]/20, p->conf->res[0]/70 );
  sprintf( debug, "time: %.4f", g_fps->time );
  glPrintf( &r->font, debug, 35*p->conf->res[0]/50, 14*p->conf->res[1]/20, p->conf->res[0]/70 );

  //sprintf( debug, "damage: %.2f,%.2f,%.2f,%.2f,%.2f,%.2f", p->car.damage[0],p->car.damage[1],p->car.damage[2],p->car.damage[3],p->car.damage[4],p->car.damage[5] );
  //glPrintf( &r->font, debug, 25*p->conf->res[0]/50, 13*p->conf->res[1]/20, p->conf->res[0]/70 );
  sprintf( debug, "car pos: %.2f,%.2f,%.2f", p->car.pos[0],p->car.pos[1],p->car.pos[2] );
  glPrintf( &r->font, debug, 30*p->conf->res[0]/50, 13*p->conf->res[1]/20, p->conf->res[0]/70 );
  sprintf( debug, "car a: %.2f,%.2f,%.2f", p->car.a[0],p->car.a[1],p->car.a[2] );
  glPrintf( &r->font, debug, 30*p->conf->res[0]/50, 12*p->conf->res[1]/20, p->conf->res[0]/70 );
  sprintf( debug, "car v: %.2f,%.2f,%.2f", p->car.v[0],p->car.v[1],p->car.v[2] );
  glPrintf( &r->font, debug, 30*p->conf->res[0]/50, 11*p->conf->res[1]/20, p->conf->res[0]/70 );

  sprintf( debug, "car adherence: %.2f", p->car.adherence );
  glPrintf( &r->font, debug, 30*p->conf->res[0]/50, 10*p->conf->res[1]/20, p->conf->res[0]/70 );

  sprintf( debug, "car next adherence: %.2f", p->next->car.adherence );
  glPrintf( &r->font, debug, 30*p->conf->res[0]/50, 9*p->conf->res[1]/20, p->conf->res[0]/70 );

  sprintf( debug, "car collide: %p", p->car.car_collide );
  glPrintf( &r->font, debug, 30*p->conf->res[0]/50, 8*p->conf->res[1]/20, p->conf->res[0]/70 );
}
