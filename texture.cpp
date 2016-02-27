#include <iostream>
#include "texture.h"

///This function is used to put correct texture on the object
void Texture::charger(char* fichier)
{
	glGenTextures(1, &texture);
	img = load_tga(fichier, &largeur, &hauteur, &bpp);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, largeur, hauteur, 0, GL_RGB, GL_UNSIGNED_BYTE,img);
	delete[] img;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}

///This is the default constructor
Texture::Texture()
{
}

///This is the default deconstructor
Texture::~Texture()
{
}
