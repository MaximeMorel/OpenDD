// MOREL Maxime
//


//! \file input.c
//! \brief Look for input events.


#include "input.h"


// gestion evenement dans le menu
void inputMenu( SDL_Event* event, SPlayer* pl, int* menu )
{
  while( SDL_PollEvent( event ) )
    {
      switch( event->type )
	{
	case SDL_QUIT:
	  return;
	  break;
	case SDL_KEYDOWN:
	  switch ( event->key.keysym.sym )
	    {
	      /*case SDLK_q:
	      //quit(0);
	      pl->exit = true;
	      break;*/
	    case SDLK_F3:		// wireframe
	      toggleWireframe( &pl->conf->cl_wireframe );
	      break;
	    case SDLK_F1:				// fullscreen / window
	      //toggleFullscreen( pl->conf->res );
	      break;
	    case SDLK_F2:			   	// capture du pointeur dans la fenetre
	      toggleGrabmouse( &pl->conf->grab_mouse );
	      break;
	    case SDLK_d:
	      debugMenu( pl );
	      break;
	    case SDLK_ESCAPE:		// menu
	      toggleMenu( pl );
	      break;
	    case SDLK_SPACE:		// menu
	      //return;
	      break;
	    default:
	      break;
	    }
	  keyboardDownMenu( &event->key, menu );
	  break;
	case SDL_KEYUP:
	  keyboardUpMenu( &event->key, menu );
	  break;
	case SDL_MOUSEMOTION:
	  mouseMotionMenu(  &event->motion, menu );
	  break;
	case SDL_MOUSEBUTTONDOWN:
	  mouseButtonDownMenu( &event->button, menu );
	  break;
	case SDL_MOUSEBUTTONUP:
	  mouseButtonUpMenu( &event->button, menu );
	  break;
	default:
	  break;
	}
    }
}


// gestion evenement dans le jeu
void inputGame( SDL_Event* event, SPlayer* pl, SCamera* cam )
{
  while( SDL_PollEvent( event ) )
    {
      switch( event->type )
	{
	case SDL_QUIT:
	  return;
	  break;
	case SDL_KEYDOWN:
	  switch( event->key.keysym.sym )
	    {
	      //case SDLK_q:
	      //quit(0);
	      //pl->exit = true;
	      //pl->state |= QUIT;
	      //break;
	    case SDLK_F3:		// wireframe
	      toggleWireframe( &pl->conf->cl_wireframe );
	      break;
	    case SDLK_F1:				// fullscreen / window
	      toggleFullscreen( pl->conf->res );
	      break;
	    case SDLK_F2:			   	// capture du pointeur dans la fenetre
	      toggleGrabmouse( &pl->conf->grab_mouse );
	      break;
	    case SDLK_F4:			   	// noclip
	      //toggle_noclip( pl );
	      break;
	    case SDLK_d:
	      debugGame( pl );
	      break;
	      //case SDLK_r:
	      
	      //break;
	    case SDLK_ESCAPE:		// menu
	      toggleMenu( pl );
	      break;
	    default:
	      break;
	    }
	  keyboardDown( &event->key, pl, cam );
	  break;
	case SDL_KEYUP:
	  keyboardUp( &event->key, pl, cam );
	  break;
	case SDL_MOUSEMOTION:
	  //if( pl->cameraera == CAM_NORMAL_FREE || pl->cameraera == CAM_FREE )
	  mouseMotion( &event->motion, pl, cam );
	  break;
	case SDL_MOUSEBUTTONDOWN:
	  //if( pl->cameraera & CAM_NORMAL_FREE || pl->cameraera & CAM_FREE )
	  mouseButtonDown( &event->button, pl );
	  break;
	case SDL_MOUSEBUTTONUP:
	  mouseButtonUp( &event->button, pl );
	  break;
	default:
	  break;
	}
    }
}


// gestion evenement dans la console
void inputConsole( SDL_Event* event, SPlayer* pl )
{
}


void inputPause( SDL_Event* event, SPlayer* pl )
{
}


// ingame
// gestion touche clavier enfonce
void keyboardDown( const SDL_KeyboardEvent* kb_event, SPlayer* pl, SCamera* cam )
{
  if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_FORWARD] ) ||	\
      ( kb_event->keysym.sym == pl->conf->keyconf[KEY_FORWARD2] ) )
    {
      carForwardOn( &pl->car );
    }
  
  else
    if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_BACKWARD] ) ||	\
	( kb_event->keysym.sym == pl->conf->keyconf[KEY_BACKWARD2] ) )
      {
	carBackwardOn( &pl->car );
      }
  
    else
      if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_LEFT] ) ||	\
	  ( kb_event->keysym.sym == pl->conf->keyconf[KEY_LEFT2] ) )
	{
	  carLeftOn( &pl->car );
	}
  
      else
	if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_RIGHT] ) || \
	    ( kb_event->keysym.sym == pl->conf->keyconf[KEY_RIGHT2] ) )
	  {
	    carRightOn( &pl->car );
	  }
  
	else
	  if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_FASTSTEER] ) || \
	      ( kb_event->keysym.sym == pl->conf->keyconf[KEY_FASTSTEER2] ) )
	    {
	      carFastSteerOn( &pl->car );
	    }
  
	  else
	    if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_HANDBRAKE] ) || \
		( kb_event->keysym.sym == pl->conf->keyconf[KEY_HANDBRAKE2] ) )
	      {
		carHandBrakeOn( &pl->car );
	      }
  
	    else
	      if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_REAR_VIEW] ) || \
		  ( kb_event->keysym.sym == pl->conf->keyconf[KEY_REAR_VIEW2] ) )
		{
		  camRearOn( cam );
		}
  
	      else
		if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_MODE] ) || \
		    ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_MODE2] ) )
		  {
		    camChangeView( cam );
		  }
  
		else
		  if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_PAUSE] ) || \
		      ( kb_event->keysym.sym == pl->conf->keyconf[KEY_PAUSE2] ) )
		    {
		      togglePause( pl );
		    }
  
		  else
		    if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_SCREENSHOT] ) || \
			( kb_event->keysym.sym == pl->conf->keyconf[KEY_SCREENSHOT2] ) )
		      {
			//screenshotBmp();
			screenshotJpg();
		      }
  
		    else
		      if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CONSOLE] ) || \
			  ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CONSOLE2] ) )
			{
			  toggleConsole( pl );
			}
  
		      else
			if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_RESET] ) || \
			    ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_RESET2] ) )
			  {
			    camReset( cam );
			  }
  
		      else
			if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_FORWARD] ) || \
			    ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_FORWARD2] ) )
			  {
			    camForwardOn( cam );
			  }
  
			else
			  if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_BACKWARD] ) || \
			      ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_BACKWARD2] ) )
			    {
			      camBackwardOn( cam );
			    }
  
			  else
			    if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_LEFT] ) || \
				( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_LEFT2] ) )
			      {
				camLeftOn( cam );
			      }
  
			    else
			      if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_RIGHT] ) || \
				  ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_RIGHT2] ) )
				{
				  camRightOn( cam );
				}
  
			      else
				if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_UP] ) || \
				    ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_UP2] ) )
				  {
				    camUpOn( cam );
				  }
  
				else
				  if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_DOWN] ) || \
				      ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_DOWN2] ) )
				    {
				      camDownOn( cam );
				    }
				  else
				    if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_HORN] ) || \
					( kb_event->keysym.sym == pl->conf->keyconf[KEY_HORN2] ) )
				      {
					carHorn( &pl->car );
				      }
				    else
				      if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_FOLLOW_NEXT] ) || \
					  ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_FOLLOW_NEXT2] ) )
					{
					  camFollowNext( cam );
					}
				      else
					if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_FOLLOW_PREV] ) || \
					    ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_FOLLOW_PREV2] ) )
					  {
					    camFollowPrev( cam );			    			    
					  }
					else
					  if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_FOLLOW_PLAYER] ) || \
					      ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_FOLLOW_PLAYER2] ) )
					    {
					      camFollowPlayer( cam, pl );
					    }
					  else
					    if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAR_RESET] ) || \
						( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAR_RESET2] ) )
					      {
						carReset( &pl->car );
					      }
}


// gestion touche clavier relache
void keyboardUp(const SDL_KeyboardEvent* kb_event, SPlayer* pl, SCamera* cam )
{
  if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_FORWARD] ) || \
      ( kb_event->keysym.sym == pl->conf->keyconf[KEY_FORWARD2] ) )
    {
      carForwardOff( &pl->car );
    }
  
  else
    if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_BACKWARD] ) || \
	( kb_event->keysym.sym == pl->conf->keyconf[KEY_BACKWARD2] ) )
      {
	carBackwardOff( &pl->car );
      }
  
    else
      if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_LEFT] ) || \
	  ( kb_event->keysym.sym == pl->conf->keyconf[KEY_LEFT2] ) )
	{
	  carLeftOff( &pl->car );
	}
  
      else
	if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_RIGHT] ) || \
	    ( kb_event->keysym.sym == pl->conf->keyconf[KEY_RIGHT2] ) )
	  {
	    carRightOff( &pl->car );
	  }
  
	else
	  if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_HANDBRAKE] ) || \
	      ( kb_event->keysym.sym == pl->conf->keyconf[KEY_HANDBRAKE2] ) )
	    {
	      carHandBrakeOff( &pl->car );
	    }

	  else
	    if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_FASTSTEER] ) || \
		( kb_event->keysym.sym == pl->conf->keyconf[KEY_FASTSTEER2] ) )
	      {
		carFastSteerOff( &pl->car );
	      }
  
	    else
	      if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_REAR_VIEW] ) || \
		  ( kb_event->keysym.sym == pl->conf->keyconf[KEY_REAR_VIEW2] ) )
		{
		  camRearOff( cam );
		}


	    else
	      if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_FORWARD] ) || \
		  ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_FORWARD2] ) )
		{
		  camForwardOff( cam );
		}
  
	      else
		if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_BACKWARD] ) || \
		    ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_BACKWARD2] ) )
		  {
		    camBackwardOff( cam );
		  }
  
		else
		  if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_LEFT] ) || \
		      ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_LEFT2] ) )
		    {
		      camLeftOff( cam );
		    }
  
		  else
		    if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_RIGHT] ) || \
			( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_RIGHT2] ) )
		      {
			camRightOff( cam );
		      }
  
		    else
		      if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_UP] ) || \
			  ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_UP2] ) )
			{
			  camUpOff( cam );
			}
  
		      else
			if( ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_DOWN] ) || \
			    ( kb_event->keysym.sym == pl->conf->keyconf[KEY_CAM_DOWN2] ) )
			  {
			    camDownOff( cam );
			  }
}
		 

// gestion mouvement souris
void mouseMotion( const SDL_MouseMotionEvent* event, SPlayer* pl, SCamera* cam )
{
  if( cam->mode == 2 || pl->mouse_press )
    {
      cam->rx += (float)event->xrel / pl->conf->cl_mouse_yaw;
      cam->ry += (float)event->yrel / pl->conf->cl_mouse_pitch;
    }
}


// gestion boutton souris enfonce
void mouseButtonDown( const SDL_MouseButtonEvent* mb_event, SPlayer* pl )
{
  /*if( ( mb_event->button == pl->conf->mouseconf[MOUSE_FIRE] ) || \
      ( mb_event->button == pl->conf->mouseconf[MOUSE_FIRE2] ) )
    {
      pl->mouse_press |= MOUSEPRESS_LEFT;
      fire_on ( pl );
    }
  
  else
    if( ( mb_event->button == pl->conf->mouseconf[MOUSE_ZOOM] ) || \
	( mb_event->button == pl->conf->mouseconf[MOUSE_ZOOM2] ) )
      {
	zoom_on ( pl );
	change_fov ( pl->conf->cl_fov );
      }
  
    else
      if( ( mb_event->button == pl->conf->mouseconf[MOUSE_ALTFIRE] ) || \
	  ( mb_event->button == pl->conf->mouseconf[MOUSE_ALTFIRE2] ) )
	{
	  pl->mouse_press |= MOUSEPRESS_RIGHT;
	  alt_fire_off ( pl );
	  }*/
}

// gestion boutton souris relache
void mouseButtonUp( const SDL_MouseButtonEvent* mb_event , SPlayer* pl )
{
  /*if( ( mb_event->button == pl->conf->mouseconf[MOUSE_FIRE] ) || \
      ( mb_event->button == pl->conf->mouseconf[MOUSE_FIRE2] ) )
    {
      pl->mouse_press ^= MOUSEPRESS_LEFT;
      fire_off ( pl );
    }
  
  else
    if ( ( mb_event->button == pl->conf->mouseconf[MOUSE_ZOOM] ) || \
	 ( mb_event->button == pl->conf->mouseconf[MOUSE_ZOOM2] ) )
      {
	zoom_off( pl );
	change_fov ( pl->conf->cl_fov );
      }
  
    else
      if ( ( mb_event->button == pl->conf->mouseconf[MOUSE_ALTFIRE] ) || \
	   ( mb_event->button == pl->conf->mouseconf[MOUSE_ALTFIRE2] ) )
	{
	  pl->mouse_press ^= MOUSEPRESS_RIGHT;
	  }*/
}


// menu
void keyboardDownMenu( const SDL_KeyboardEvent* kb_event, int* menu )
{
  switch ( kb_event->keysym.sym )
    {
    case SDLK_UP:
      menu[MENU_SELECTION]--;
      break;
      
    case SDLK_DOWN:
      menu[MENU_SELECTION]++;
      break;

    case SDLK_RETURN:
      menu[MENU_ACTIVE] = 1;
      break;

    case SDLK_F12:
      screenshotJpg();
      break;
      
    default:
      break;
    }

  if( menu[MENU_SELECTION] < 0 )
    menu[MENU_SELECTION] += menu[MENU_NB_ITEMS];
  else
    if( menu[MENU_SELECTION] >= menu[MENU_NB_ITEMS] )
      menu[MENU_SELECTION] -= menu[MENU_NB_ITEMS];
}


void keyboardUpMenu( const SDL_KeyboardEvent* event, int* menu )
{
	
}


void mouseMotionMenu( const SDL_MouseMotionEvent* event, int* menu )
{
	
}


void mouseButtonDownMenu( const SDL_MouseButtonEvent* event, int* menu )
{
	
}


void mouseButtonUpMenu( const SDL_MouseButtonEvent* event, int* menu )
{
	
}
