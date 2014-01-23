#ifndef TEXTURES_H
#define TEXTURES_H

#include "glut.h"

extern "C" unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);

// shared global variables, declared in Textures.cpp
extern GLuint texture;
extern GLubyte *image; // unsigned char *

extern int imageWidth;
extern int imageHeight;
extern int bitDepth;

// texture functions
void LoadTexture();

#endif