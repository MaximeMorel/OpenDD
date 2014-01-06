//
//


//! \file sound.h
//! \brief sound test module.


#ifndef SOUND_H
#define SOUND_H


// system includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <AL/al.h>
#include <AL/alc.h>
//#include <AL/alut.h>
#include <AL/alext.h>
#include <vorbis/vorbisfile.h>

// user includes
#include "bool.h"
#include "fps.h"

// openal status
#define SOUND_NOT_INIT		0
#define SOUND_INIT		1
#define SOUND_ERROR		2

// ogg sound status
#define OGG_INACTIVE            0
#define OGG_BUFFER1_EMPTY       1
#define OGG_BUFFER2_EMPTY       2
#define OGG_BUFFER1_FINISHED    4
#define OGG_BUFFER2_FINISHED    8
#define OGG_BUFFER1_PLAYING     16
#define OGG_BUFFER2_PLAYING     32
#define OGG_PLAY                64
#define OGG_STOP                128

// ogg mode
#define OGG_ONCE                1
#define OGG_LOOP                2


#define SOUND_SAMPLE_SIZE 44100


typedef struct
{
  int status;
  int mode;
  FILE* file;
  ALenum format;
  OggVorbis_File stream;

  ALint n_buff_processed;
  ALint n_buff_processed_old;

  ALuint source;
  ALuint buffers[2];
} SOggSound;


typedef struct
{
  int status;
  ALCdevice* device;
  ALCcontext* context;

  unsigned int timeout;

  //FILE* file;
  //OggVorbis_File stream;

  //ALuint sources[10];
  //ALuint buffers[10];

  SOggSound oggsound[32];
} SSound;	
	
	
void soundInit( SSound* s );
void soundFree( SSound* s );

//void soundAlutInit( SSound* s );
//void soundAlutFree( SSound* s );
//void soundAlutInfo( SSound* s );

void openalInit( SSound* s );
void openalExit( SSound* s );
void soundLoadFile( SSound* s );
void openalInfo( SSound* s );

inline bool soundCheckErrorAL( const char* context );
inline bool soundCheckErrorALC( const char* context );


void soundUpdate( SSound* s );


void soundAdd( SSound* s );


void soundDel( SSound* s );


void soundSet( SSound* s );


void soundTest();


void oggInit( SOggSound* o );


void oggFree( SOggSound* o );


void oggLoad( SOggSound* o, const char* name );


void oggRead( SOggSound* o, ALuint* buffer );


void oggPlay( SOggSound* o, const char* name  );


#endif // SOUND_H
