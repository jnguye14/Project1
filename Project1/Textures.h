#ifndef TEXTURES_H
#define TEXTURES_H

#include "glut.h"

extern "C" unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);

// shared global variables, declared in Textures.cpp
extern GLuint texture;
extern GLubyte *image; // unsigned char *

extern GLuint texture_1;
extern GLubyte *image_1;

extern GLuint playTexture;
extern GLubyte *playImage;

extern GLuint quitTexture;
extern GLubyte *quitImage;

extern GLuint turnTexture;
extern GLubyte *turnImage;

extern int imageWidth;
extern int imageHeight;
extern int bitDepth;

// texture functions
void LoadGameTextures();
void LoadTexture(char const *filename, GLubyte** image, GLuint* texture, int imageWidth, int imageHeight, int bitDepth);
//void LoadTexture();

#endif