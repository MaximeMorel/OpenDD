//
//


//! \file sound.c
//! \brief sound test module.


#include "sound.h"


void soundInit( SSound * s )
{
  int i;

  s->status = SOUND_NOT_INIT;
  s->device = NULL;
  s->context = NULL;
  s->timeout = 0;

  for( i = 0; i < 10; i++ )
    {
      oggInit( &s->oggsound[i] );
    }

  //OV_CALLBACKS_DEFAULT;
  //OV_CALLBACKS_NOCLOSE;
  //OV_CALLBACKS_STREAMONLY;
  //OV_CALLBACKS_STREAMONLY_NOCLOSE;

  printf( "Struct sound : OK.\n" );
}


void soundFree( SSound * s )
{
  if( s->status != SOUND_NOT_INIT )
    {
      openalExit( s );
    }

  printf( "Struct sound : Free.\n" );
}


/*void soundAlutInit( SSound * s )
{
  alutInit( NULL, 0 );
  soundCheckErrorAL( "Alut init" );
  soundCheckErrorALC( s, "Alut init" );
  
  printf( "Alut sound : OK.\n" );
}


void soundAlutFree( SSound * s )
{
  alutExit();
  soundCheckErrorAL( "Alut exit" );
  soundCheckErrorALC( s, "Alut exit" );

  printf( "Alut sound : Free.\n" );
}


void soundAlutInfo( SSound * s )
{
  ALint al_maj;
  ALint al_min;

  s->context = alcGetCurrentContext();
  s->device = alcGetContextsDevice( s->context );

  al_maj = alutGetMajorVersion();
  al_min = alutGetMinorVersion();
  printf( "alut version : %d.%d\n" , al_maj , al_min ); 
  
  openalInfo( s );
  soundCheckErrorAL( "Alut info" );
  soundCheckErrorALC( s, "Alut info" );
  }*/



void openalInit( SSound * s )
{
  s->device = alcOpenDevice( NULL );
  if( s->device )
    {
      printf( "device ok.\n" );
      s->context = alcCreateContext( s->device , NULL );
      if( s->context )
	{
	  if( alcMakeContextCurrent( s->context ) )
	    {
	      printf( "context ok.\n" );
	      s->status = SOUND_INIT;
	    }
	}
      else
	{
	  printf( "Error creating context.\n" );
	}
    }
  else
    {
      printf( "Error opening device.\n" );
    }

  //alGenBuffers( 10 , s->buffers );
  //alGenSources( 10 , s->sources );

  soundCheckErrorAL( "init" );
  soundCheckErrorALC( "init" );
}


void openalExit( SSound * s )
{
  soundCheckErrorAL( "pre exit" );
  soundCheckErrorALC( "pre exit" );

  s->context = alcGetCurrentContext();
  s->device = alcGetContextsDevice( s->context );
  alcMakeContextCurrent( NULL );
  alcDestroyContext( s->context );
  alcCloseDevice( s->device );

  soundCheckErrorAL( "post exit" );
  soundCheckErrorALC( "post exit" );
}


void soundLoadFile( SSound * s )
{
  int size;
  FILE* file;
  void* data;
  
  file = fopen( "data/sound/music/9.ogg" , "rb" );
  fseek( file , 0 , SEEK_END );
  size = ftell( file );
  data = (void*)malloc( size );
  fread( data, 1, size, file );
  //printf( "file size : %d ko\n" , size/1024 );
  //alGenBuffers( 1, &s->buffers[0] );
  //alGenSources( 1, &s->sources[0] );
  //alBufferData( s->buffers[0] , AL_FORMAT_VORBIS_EXT , data , size , 44100 );
  //
  //alutLoadVorbis_LOKI( s->buffers[0], data ,size );
  soundCheckErrorAL( "load" );
  soundCheckErrorALC( "load" );
  fclose( file );
  //alSourcei( s->sources[0] , AL_BUFFER , s->buffers[0] );
  //alSourcePlay( s->sources[0] );
  soundCheckErrorAL( "play" );
  soundCheckErrorALC( "play" );
}


void openalInfo( SSound* s )
{
  //int i;
  const ALCchar* string = NULL;
  ALCint alc_maj;
  ALCint alc_min;
	
  string = alGetString( AL_VENDOR );
  printf( "openal vendor : %s\n" , string );
	
  string = alGetString( AL_VERSION );
  printf( "openal version : %s\n" , string );
	
  string = alGetString( AL_RENDERER );
  printf( "openal renderer : %s\n" , string );
	
  string = alGetString( AL_EXTENSIONS );
  printf( "openal extensions : %s\n" , string );
	
  string = alcGetString( NULL , ALC_EXTENSIONS );
  printf( "openalc extensions : %s\n" , string );
	
  alcGetIntegerv( s->device , ALC_MAJOR_VERSION , 1 , &alc_maj );
  alcGetIntegerv( s->device , ALC_MINOR_VERSION , 1 , &alc_min );
  printf( "openalc version : %d.%d\n" , alc_maj , alc_min );

  if( alcIsExtensionPresent( NULL, "ALC_ENUMERATION_EXT" ) )
    {
      string = alcGetString( NULL , ALC_DEVICE_SPECIFIER );
      if( string == NULL || string[0] == '\0' )
	{
	  printf( "available devices : none\n" );
	}
      else
	{
	  printf( "available devices :\n" );
	  while( string[0] != '\0' )
	    {
	      printf( "%s\t" , string );
	      string += strlen( string ) + 1;
	    }
	  printf( "\n" );
	}
      //printf( "devices : %s \t %s" , &string[1] , &string[strlen(&string[1])]);
      
      string = alcGetString( NULL , ALC_DEFAULT_DEVICE_SPECIFIER );
      printf( "default device : %s\n" , string );
      
      string = alcGetString( s->device , ALC_DEVICE_SPECIFIER );
      printf( "active device : %s\n\n" , string );
    }
  else
    {
      printf( "Enumeration not supported.\n" );
    }
}


bool soundCheckErrorAL( const char * context )
{
  char error[50];
  ALenum al_error;
  al_error = alGetError();
	
  if( al_error != AL_NO_ERROR )
    {
      switch( al_error )
	{
	case AL_INVALID_NAME :
	  strcpy( error , "AL_INVALID_NAME" );
	  break;
	case AL_INVALID_ENUM :
	  strcpy( error , "AL_INVALID_ENUM" );
	  break;
	case AL_INVALID_VALUE :
	  strcpy( error , "AL_INVALID_VALUE" );
	  break;
	case AL_INVALID_OPERATION :
	  strcpy( error , "AL_INVALID_OPERATION" );
	  break;
	case AL_OUT_OF_MEMORY  :
	  strcpy( error , "AL_OUT_OF_MEMORY" );
	  break;
	default :
	  strcpy( error , "error !!!" );
	  break;
	}
      printf( "al error( %s ) : %s\n" , context , error );
      return false;
    }
  return true;
}


bool soundCheckErrorALC( const char* context )
{
  char error[50];
  ALCenum alc_error;
  ALCdevice* device;
  ALCcontext* al_context;

  al_context = alcGetCurrentContext();
  device = alcGetContextsDevice( al_context );

  alc_error = alcGetError( device );
	
  if( alc_error != AL_NO_ERROR )
    {
      switch( alc_error )
	{
	case ALC_INVALID_DEVICE :
	  strcpy( error , "ALC_INVALID_DEVICE" );
	  break;
	case ALC_INVALID_CONTEXT :
	  strcpy( error , "ALC_INVALID_CONTEXT" );
	  break;
	case ALC_INVALID_ENUM :
	  strcpy( error , "ALC_INVALID_ENUM" );
	  break;
	case ALC_INVALID_VALUE :
	  strcpy( error , "ALC_INVALID_VALUE" );
	  break;
	case ALC_OUT_OF_MEMORY  :
	  strcpy( error , "ALC_OUT_OF_MEMORY" );
	  break;
	default :
	  strcpy( error , "error !!!" );
	  break;
	}
      if( context == NULL )
	{
	  printf( "alc error : %s\n" ,error );
	}
      else
	{
	  printf( "alc error( %s ) : %s\n" , context, error );
	}
      return false;
    }
  return true;
}


void soundTest()
{
  /*ALuint helloBuffer, helloSource;
  alutInit(NULL, 0);
  helloBuffer = alutCreateBufferHelloWorld();
  alGenSources(1, &helloSource);
  alSourcei(helloSource, AL_BUFFER, helloBuffer);
  alSourcePlay(helloSource);
  alutSleep(1);*/
}


void oggInit( SOggSound* o )
{
  o->status = 0;
  o->mode = OGG_ONCE;
  o->file = NULL;  
  o->n_buff_processed = 0;
  o->n_buff_processed_old = 0;

  o->status |= OGG_BUFFER1_EMPTY;
  o->status |= OGG_BUFFER2_EMPTY;
}


void oggFree( SOggSound* o )
{
  // close ogg-vorbis stream
  ov_clear( &o->stream );

  // close file
  fclose( o->file );

  alSourceUnqueueBuffers( o->source, 1, &o->buffers[0] );
  alSourceUnqueueBuffers( o->source, 1, &o->buffers[1] );

  alDeleteBuffers( 2, o->buffers );

  alDeleteSources( 1, &o->source );
  
  alSourcei( o->source, AL_BUFFER, 0);

  soundCheckErrorAL( "free ogg" );
  soundCheckErrorALC( "free ogg" );
}


void oggLoad( SOggSound* o, const char* name )
{
  // file opening
  o->file = fopen( name, "rb");
  
  if( !o->file )
    {
      printf( "Sound error : %s !!!\n", name );
      return;
    }
  
  // with file, we open a ogg-vorbis stream
  if( ov_open( o->file, &o->stream, NULL, 0) )
    {
      printf( "Sound error : ogg stream error !!!\n" );
      return;
    }

  o->format = o->stream.vi->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
  
  if( !alIsSource( o->source ) )
    {
      alGenSources( 1, &o->source );
      //printf( "create source.\n" );
    }
    
  soundCheckErrorAL( "load ogg" );
  soundCheckErrorALC( "load ogg" );
}


void oggRead( SOggSound* o, ALuint* buffer )
{
  ALshort samples[SOUND_SAMPLE_SIZE];

  ALsizei read;  

  ALsizei total_read = 0;
  ALsizei total_size = SOUND_SAMPLE_SIZE * sizeof(ALshort);
  char* p_Samples = (char*)(&samples[0]);

    // Tant qu'on n'a pas atteint la taille voulue, on lit
    while( total_read < total_size)
    {
      // Lecture des échantillons à partir du flux ogg-vorbis
      read = ov_read( &o->stream, p_Samples + total_read, total_size - total_read, 0, 2, 1, NULL );
      //printf("read %d\n", read );
      
      if( read > 0 )
        {
	  // La lecture a réussi, on avance du nombre d'octets lus
	  total_read += read;
        }
      else
        {
	  // La lecture a échoué, on arrête de lire
	  return;
	  break;
        }
    }

    // Remplissage du tampon avec les données lues
    if( total_read > 0 )
      {
	if( !alIsBuffer( *buffer ) )
	  {
	    alGenBuffers( 1, buffer );
	    //printf( "create buffer.\n" );
	  }
	else
	  {
	    alDeleteBuffers( 1 , buffer );
	    alGenBuffers( 1, buffer );
	    
	  }
	
	alBufferData( *buffer, o->format, &samples[0], total_read, o->stream.vi->rate );
	
      }
    soundCheckErrorAL( "read ogg" );
    soundCheckErrorALC( "read ogg" );
}


void oggPlay( SOggSound* o, const char* name  )
{
  ALint status;

  if( o->status & OGG_STOP )
    return;

  //printf( "sound status : %d\n", o->status );
  
  if( o->file == NULL )
    {
      //printf( "loading file.\n" );
      oggLoad( o, name );
    }
  
  if( o->status & OGG_BUFFER1_FINISHED || o->status & OGG_BUFFER1_EMPTY )
    {
      oggRead( o, &o->buffers[0] );
      alSourceQueueBuffers( o->source, 1, &o->buffers[0] );
      soundCheckErrorAL( "queue buffer 1" );
      soundCheckErrorALC( "queue buffer 1" );
      o->status &= ~OGG_BUFFER1_EMPTY;
      o->status &= ~OGG_BUFFER1_FINISHED;
      if( !( o->status & OGG_BUFFER2_PLAYING ) )
	{
	  o->status |= OGG_BUFFER1_PLAYING;
	}
      //printf( "fill buffer1.\n" );
    }
      
    if( o->status & OGG_BUFFER2_FINISHED || o->status & OGG_BUFFER2_EMPTY )
    {
      oggRead( o, &o->buffers[1] );
      alSourceQueueBuffers( o->source, 1, &o->buffers[1] );
      soundCheckErrorAL( "queue buffer 2" );
      soundCheckErrorALC( "queue buffer 2" );
      o->status &= ~OGG_BUFFER2_EMPTY;
      o->status &= ~OGG_BUFFER2_FINISHED;
      if( !( o->status & OGG_BUFFER1_PLAYING ) )
	{
	  o->status |= OGG_BUFFER2_PLAYING;
	}
      //printf( "fill buffer2.\n" );
    }

    alGetSourcei( o->source, AL_SOURCE_STATE, &status );
    switch( o->mode )
      {
      case OGG_ONCE :
	if( !(o->status & OGG_PLAY) )
	  {
	    alSourcePlay( o->source );
	    o->status |= OGG_PLAY;
	    break;
	  }	
	if( status != AL_PLAYING )
	  {
	    o->status |= OGG_STOP;
	    oggFree( o );
	  }
	break;
      case OGG_LOOP :
	if( !(o->status & OGG_PLAY) )
	  {
	    alSourcePlay( o->source );
	    o->status |= OGG_PLAY;
	  }
	if( status != AL_PLAYING )
	  {
	    
	  }
	break;
      default :
	break;
      }

    /*alGetSourcei( o->source, AL_SOURCE_STATE, &status );
    if( status != AL_PLAYING )
      {
	//printf( "playing...\n" );
	alSourcePlay( o->source );
	}*/

    o->n_buff_processed_old = o->n_buff_processed;
    alGetSourcei( o->source, AL_BUFFERS_PROCESSED, &o->n_buff_processed );
    
    //printf( "nb buff before : %d \t now : %d\n", o->n_buff_processed_old, o->n_buff_processed );

    if( o->n_buff_processed - o->n_buff_processed_old == 1 )
      {
	//printf( "a buffer is finished.\n" );
	if( o->status & OGG_BUFFER1_PLAYING )
	  {
	    //printf( "buffer1 finished.\n" );
	    o->status &= ~OGG_BUFFER1_PLAYING;
	    o->status |= OGG_BUFFER2_PLAYING;
	    o->status |= OGG_BUFFER1_FINISHED;
	    //o->status |= OGG_BUFFER1_EMPTY;
	    alSourceUnqueueBuffers( o->source, 1, &o->buffers[0] );
	  }
	else
	  if( o->status & OGG_BUFFER2_PLAYING )
	    {
	      //printf( "buffer2 finished.\n" );
	      o->status &= ~OGG_BUFFER2_PLAYING;
	      o->status |= OGG_BUFFER1_PLAYING;
	      o->status |= OGG_BUFFER2_FINISHED;
	      //o->status |= OGG_BUFFER2_EMPTY;
	      alSourceUnqueueBuffers( o->source, 1, &o->buffers[1] );
	    } 
      }

  soundCheckErrorAL( "play ogg" );
  soundCheckErrorALC( "play ogg" );
}
