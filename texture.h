#include "tga.h"
#include "gamehead.hpp"
//#include "glut.h"

///This the class of the texture
class Texture
{
private:
	byte *img;
	int largeur, hauteur;
	GLuint texture;
	int bpp;

public:
	///This is the default constructor
	Texture();
	///This is the default deconstructor
	~Texture();
	///This function is used to put correct texture on the object
	void charger(char* fichier);
};
