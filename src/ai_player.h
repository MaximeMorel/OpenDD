//
//


//! \file ai_player.h
//! \brief handle AI.


#ifndef AI_PLAYER_H
#define AI_PLAYER_H


// system includes
#include <stdio.h>
#include <stdlib.h>

// user includes
#include "global_vars.h"
#include "car.h"
//#include "game.h"


// AI states
#define AI_IDLE     0
#define AI_CHASE    1
#define AI_SEARCH   2
#define AI_STUCK    4
#define AI_HALFWAY  8


//! \struct SPlayerAI
//! \brief update an AI player
//!
//! \param state Actual state of the player
//! \param target targeted car by AI
//! \param car A pointer to the car owned by the AI player
//! \param timeout Counters to temporise AiUpdate
//! \param pos_target Like a waypoint
typedef struct _SPlayerAI
{
  unsigned int timeout;
  unsigned int action_timeout;
  unsigned int action_sub_timeout;
  unsigned int sub_timeout;
  unsigned int stuck_timeout;


  int state;

  Vector3f pos_target;

  SCar* target;

  SCar* car;

  void (*aiGetTarget)( struct _SPlayerAI* ai );
} SPlayerAI;


//! \fn void aiInit( SPlayerAI* ai );
//! \brief Init ai struct of a player.
void aiInit( SPlayerAI* ai, int mode );


//! \fn void aiFree( SPlayerAI* ai );
//! \brief Free ai struct of a player.
void aiFree( SPlayerAI* ai );


//! \fn void aiUpdate( SPlayerAI* ai, SLevel* l );
//! \brief Main function of AI.
void aiUpdate( SPlayerAI* ai, SLevel* l );


void aiSetTimeOut( SPlayerAI* ai, int time );


void aiChase( SPlayerAI* ai );


void aiUnstuck( SPlayerAI* ai, SLevel* l );


//! \fn void aiGetTargetRandom( SPlayerAI* ai );
//! \brief Find a random target.
void aiGetTargetRandom( SPlayerAI* ai );


//! \fn void aiGetTargetMax( SPlayerAI* ai );
//! \ brief Find the farthest target.
void aiGetTargetMax( SPlayerAI* ai );


void aiGetTargetPlayer( SPlayerAI* ai );


void aiUpdateTargetPos( SPlayerAI* ai );


void aiCarForward( SPlayerAI* ai );


void aiCarBackward( SPlayerAI* ai );


void aiCarLeft( SPlayerAI* ai );


void aiCarRight( SPlayerAI* ai );


void aiCarBrake( SPlayerAI* ai );


void aiCarNoTurn( SPlayerAI* ai );


void aiCarNoAccel( SPlayerAI* ai );


void aiIdle( SPlayerAI* ai );


#endif // AI_PLAYER
