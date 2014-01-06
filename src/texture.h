// MOREL Maxime
//


//! \file texture.h
//! \brief Texture loading and binding.
//!
//!


#ifndef TEXTURE_H
#define TEXTURE_H


// system includes
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

// user includes
#include "bool.h"
#include "opengl_error.h"


#define TEXTURE_SKYBOX_UP 0
#define TEXTURE_SKYBOX_DN 1
#define TEXTURE_SKYBOX_LT 2
#define TEXTURE_SKYBOX_RT 3
#define TEXTURE_SKYBOX_FT 4
#define TEXTURE_SKYBOX_BK 5


//! \struct STexture
//! \brief Mainly store the ids of loaded textures
//!
//! \param texture_id texture ids array
//! \param texture tem SDL_Surface for loading textures
typedef struct
{
  int id;
  int status;
  int num_total_textures, num_textures, num_skybox_textures, dim[2];
  GLint max_texture_size;
  GLuint* texture_id;
  SDL_Surface* texture;
} STexture;


void textureInit( STexture* t );
void textureFree( STexture* t );


//! \fn void loadTextures( STexture* t )
//! \brief Load all textures.
//!
//!
void loadTextures( STexture* t );


//! \fn void rescaleTexture( STexture* texture, SDL_Surface* surface )
//! \brief Rescale a texture.
//!
//!
void rescaleTexture( STexture* texture, SDL_Surface* surface );

//void load_cubemap_textures( STexture* t, char* name, GLenum target, GLenum format, GLenum flag, bool mipmap );


//! \fn int loadTexture( STexture* t, int id, char* name, GLenum format, GLenum flag, bool mipmap )
//! \brief Generic texture loader.
//!
//!
GLuint loadTexture( STexture* t, const char* name, GLenum format, GLenum flag, bool mipmap );


//! \fn void delTexture( STexture* t, int id )
//! \brief Delete a texture.
//!
//!
void delTexture( STexture* t, int id );


//! \fn void delAllTexture( STexture* t );
//! \brief delete all textures.
void delAllTexture( STexture* t );


//! \fn bool checkTexture( STexture* t, int id )
//! \brief Check if id is a valid texture.
//!
//!
bool checkTexture( STexture* t, int id );


#endif // TEXTURE_H
