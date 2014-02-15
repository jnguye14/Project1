#include "Textures.h"

GLuint texture;
GLubyte *image;

GLuint texture_1;
GLubyte *image_1;

GLuint titleTexture;
GLubyte *titleImage;

GLuint playTexture;
GLubyte *playImage;

GLuint quitTexture;
GLubyte *quitImage;

GLuint turnTexture;
GLubyte *turnImage;

int imageWidth = 64*6;
int imageHeight = 64;
int bitDepth = 32;

void LoadGameTextures()
{
	LoadTexture("Images/Units.png", &image, &texture, imageWidth, imageHeight, bitDepth);
	LoadTexture("Images/Units_Blue.png", &image_1, &texture_1, imageWidth, imageHeight, bitDepth);
	LoadTexture("Images/Game_Screen.psd", &titleImage, &titleTexture, 256, 128, 64);
	LoadTexture("Images/Play.png", &playImage, &playTexture, 128, 64, 32);
	LoadTexture("Images/Quit.png", &quitImage, &quitTexture, 128, 64, 64);
	LoadTexture("Images/Player_Turn.png", &turnImage, &turnTexture, 128, 64, 64);
}

void LoadTexture(char const *filename, GLubyte** image, GLuint* texture, int imageWidth, int imageHeight, int bitDepth)
{
	//Use the stbi_image file to load an image
	*image = stbi_load(filename, &imageWidth, &imageHeight, &bitDepth, 0);

	//gluScaleImage(GL_RGB,imageWidth,imageHeight,GL_RGB,imageWidth,imageHeight,GL_RGB,image);

	glGenTextures(1, texture); //generate the texture with the loaded data


	//The first thing that must take place in the process of uploading the texture is a call to glBindTexture. 
	//What glBindTexture does is it tells OpenGL which texture "id" we will be working with. 
	//A texture "id" is just a number that you will use to access your textures. Here is a sample call.
	glBindTexture(GL_TEXTURE_2D, *texture); //bind texture to its array



	//The glPixelStorei call tells OpenGL how the data that is going to be uploaded is aligned. 
	//This call tells OpenGL that the pixel data which is going to be passed to it is aligned in byte order, 
	//this means that the data has one byte for each component, one for red, green and blue
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);// GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//The glTexEnvf call sets environment variables for the current texture. 
	//What this does is tell OpenGL how the texture will act when it is rendered into a scene.
	//What this does is sets the active texture to GL_MODULATE. 
	//The GL_MODULATE attribute allows you to apply effects such as lighting and coloring to your texture. 
	//If you do not want lighting and coloring to effect your texture and you would like to display the texture unchanged when 
	//coloring is applied replace GL_MODULATE with GL_DECAL.
	//This is not needed if you use shaders!!
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//The glTexImage2D call is our goal. 
	//This call will upload the texture to the video memory where it will be ready for us to use in our programs. 
	//I am going to explain this call parameter by parameter since it is so important to what we are doing.
	//target - The target of this call, it will always be GL_TEXTURE_2D.
	//level - The level of detail number, this should be left at 0 for our purposes. 
	//Once you become more adept at OpenGL texture mapping this parameter will be something that you might change.
	//internalformat - Internal components parameter. 
	//This tells OpenGL how many color components to represent internally from the texture that is uploaded. 
	//There are many symbolic constants for this parameter but the one which is most widely used is GL_RGB; this constant is equal to 3.
	//width & height - The width and height of the image data. These must be integers that are equal to 2n+2(border) for some integer n.
	//What this basically means is that the texture width and height must be a power of two (2,4,8,16,32,63,128,256,512, etc).
	//border - Image border, must be 0 or 1. I always use 0 in my code since I do not use image borders.
	//format - Format of the pixel data that will be uploaded. There are many constants which are accepted but GL_RGB is the value that is widely used.
	//type - Type of data that will be uploaded. Again there are several symbolic constants but the one which I use is GL_UNSIGNED_BYTE.
	//pixels - Pointer to the image data. 
	//This is the image data that will be uploaded to the video memory. 
	//Note that after your call to glTexImage2D you can free this memory since the texture is already uploaded into video memory.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, *image);
}