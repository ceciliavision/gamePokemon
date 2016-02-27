#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "texture.h"
#include <iostream>

using namespace std;

/// This is a house class that creates a house object onto the scene
class house{
private:
  float _x; /// the x-position of the house object
  float _y; /// the y-position of the house object
  float _z; /// the z-position of the house object
  float _r; /// the rotation angle of the house object
  int _width; /// the width of the house
  int _length; /// the length of the house
  int _floor; /// the number of stories of the house
  string _name; /// name of the house object for later reference

public:
  /// default constructor
  house(){
    cout << "In: default vector constructor" 
	 << endl;
    _x = 0;
    _y = 0;
    _z = 0;
    _r = 0;
    _width = 5;
  	_length = 4;
    _name = "";
    _floor = 1;
  };

  ///constructor with input house position, house size, story number and the object name
  house(float xp, float yp, float zp, float yr, int l, int w, int s, string name){
    _x = xp;
  	_y = yp;
  	_z = zp;
  	_r = yr;
  	_width = w;
  	_length = l;
	_floor = s;
  	_name = name;
  };

  /// the method that starts the draw of the house object
  void startDraw(house h){
  	glPushMatrix();								
	glTranslatef(h._x, h._y, h._z);	
	glRotatef(h._r, 0,1,0);	

	GLfloat MatAmbiant[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat MatDiffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat MatSpecular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat MatShininess[] = {5.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbiant);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess);
  };

  /// the method that draws the body of the house object
  void drawBase(house h){
  	Texture t;
  	for (int i=0;i<h._floor;i++){
  	glNormal3f(0.0f, 0.0f, 1.0f);
  	/// link the texture to certain vertices of the object
  	t.charger("./res/brickS.tga");
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(-h._width, h._length+i*h._length, h._length);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(-h._width, 0+i*h._length, h._length);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(h._width, 0+i*h._length, h._length);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(h._width, h._length+i*h._length, h._length);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	/// Back wall
	glNormal3f(0.0f, 0.0f, -1.0f);
	t.charger("./res/brickF.tga");
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(h._width, h._length+i*h._length, -h._length);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(h._width, 0+i*h._length, -h._length);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(-h._width, 0+i*h._length, -h._length);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(-h._width, h._length+i*h._length, -h._length);
	glEnd();
	

	/// Left Wall
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(-h._width, h._length+i*h._length, -h._length);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(-h._width, 0+i*h._length, -h._length);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(-h._width, 0+i*h._length,  h._length);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(-h._width, h._length+i*h._length,  h._length);
	glEnd();

	/// Right Wall
	glNormal3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(h._width, h._length+i*h._length, h._length);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(h._width, 0+i*h._length, h._length);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(h._width, 0+i*h._length, -h._length);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(h._width, h._length+i*h._length, -h._length);
	glEnd();
	}
  };

  /// method that draws the roof of the house
  void drawRoof(house h){
  	Texture t;
  	int _height = h._width+h._length;
  	
  	/// To construct a slanted roof of the house, this is the triangle before
	glNormal3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d( 0, _height+(h._floor-1)*h._length, h._length);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(-h._width, h._length+(h._floor-1)*h._length, h._length);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(h._width, h._length+(h._floor-1)*h._length, h._length);
	glEnd();

	/// Rear Triangle
	glNormal3f(1.0f, 0.0f, -1.0f);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d( 0, _height+(h._floor-1)*h._length, -h._length);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(h._width, h._length+(h._floor-1)*h._length, -h._length);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(-h._width, h._length+(h._floor-1)*h._length, -h._length);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	GLfloat MatAmbiantToit[4] = {0.5f, 0.0f, 0.0f, 1.0f};
	GLfloat MatDiffuseToit[4] = {0.8f, 0.0f, 0.0f, 1.0f};
	GLfloat MatSpecularToit[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat MatShininessToit[] = {5.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbiantToit);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuseToit);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecularToit);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininessToit);

	/// Roof slope right, use the normal vector to decide how tilted the roof is
	glNormal3f(0.71f, 0.71f, 0.0f);
	t.charger("./res/brickR.tga");
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(0, _height+(h._floor-1)*h._length, h._length);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(h._width, h._length+(h._floor-1)*h._length, h._length);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(h._width, h._length+(h._floor-1)*h._length, -h._length);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(0, _height+(h._floor-1)*h._length, -h._length);
	glEnd();

	/// Roof slope left
	glNormal3f(-0.71f, 0.71f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d( 0, _height+(h._floor-1)*h._length, -h._length);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3d(-h._width, h._length+(h._floor-1)*h._length, -h._length);		
	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(-h._width, h._length+(h._floor-1)*h._length, h._length);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d( 0, _height+(h._floor-1)*h._length, h._length);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
  };

  /// the method that combines all the above draw parts to draw a complete house object
  void draw(house h){
  	startDraw(h);
  	drawBase(h);
  	drawRoof(h);
  };

};
