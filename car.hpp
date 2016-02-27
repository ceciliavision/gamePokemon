#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

/// This is a car class
class car{
private:
  float _x; /// the x-position of the car object
  float _y; /// the y-position of the car object
  float _z; /// the z-position of the car object
  float _r; /// the rotation angle of the car object
  float _rad; /// the radius of the wheel of the car object
  int _width; /// the width of the car body
  int _length; /// the length of the car body
  string _name; /// name of the car object for later reference

public:

  /// default constructor of the car object
  car(){
    cout << "In: default vector constructor" 
	 << endl;
    _x = 0;
    _y = 0;
    _z = 0;
    _rad = 1;
    _r = 0;
    _width = 5;
  	_length = 4;
    _name = "";
  };

  ///constructor with input object position, wheel and body size and the object name
  car(float xp, float yp, float zp, float yr, int rad, int l, int w, string name){
    _x = xp;
  	_y = yp;
  	_z = zp;
  	_r = yr;
  	_rad = rad;
  	_width = w;
  	_length = l;
  	_name = name;
  };

  /// the method that starts the draw of the car object
  void startDraw(car c){
  	glPushMatrix();								
	glTranslatef(c._x, c._y, c._z);
	glRotatef(c._r, 0,1,0);

	/// object lighting and color information of the car's 4 wheels
	GLfloat MatAmbiant1[4] = {0.0f, 1.0f, 1.0f, 1.0f};
	GLfloat MatDiffuse1[4] = {0.0f, 1.0f, 0.1f, 1.0f};
	GLfloat MatSpecular1[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat MatShininess1[] = {2.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbiant1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular1);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess1);
	glTranslatef(c._width, 0, c._length);
	glutSolidSphere(c._rad, 20, 20);

	GLfloat MatAmbiant2[4] = {0.0f, 1.0f, 1.0f, 1.0f};
	GLfloat MatDiffuse2[4] = {0.0f, 1.0f, 0.1f, 1.0f};
	GLfloat MatSpecular2[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat MatShininess2[] = {2.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbiant2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular2);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess2);
	glTranslatef(-2*c._width, 0, 0);
	glutSolidSphere(c._rad, 20, 20);

	GLfloat MatAmbiant3[4] = {0.0f, 1.0f, 1.0f, 1.0f};
	GLfloat MatDiffuse3[4] = {0.0f, 1.0f, 0.1f, 1.0f};
	GLfloat MatSpecular3[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat MatShininess3[] = {2.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbiant3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular3);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess3);
	glTranslatef(0, 0, -2*c._length);
	glutSolidSphere(c._rad, 20, 20);

	GLfloat MatAmbiant4[4] = {0.0f, 1.0f, 1.0f, 1.0f};
	GLfloat MatDiffuse4[4] = {0.0f, 1.0f, 0.1f, 1.0f};
	GLfloat MatSpecular4[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat MatShininess4[] = {2.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbiant4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular4);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess4);
	glTranslatef(2*c._width, 0, 0);
	glutSolidSphere(c._rad, 20, 20);

  };

  /// draw the car's body (a rectangle)
  void drawBody(car c){

  	/// object lighting and color information of the car's body
  	GLfloat MatAmbiant[4] = {0.5f, 0.1f, 0.5f, 1.0f};
	GLfloat MatDiffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat MatSpecular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat MatShininess[] = {5.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbiant);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTranslatef(-c._width, 0, c._length);

	/// start to draw the rectangle using the car object's size information
	glBegin(GL_QUADS);
	glVertex3d(-c._width, c._rad, c._length);
	glVertex3d(c._width, c._rad, c._length);
	glVertex3d(c._width, c._rad, -c._length);
	glVertex3d(-c._width, c._rad, -c._length);
	glEnd();
	glPopMatrix();

  };

  /// the draw method that combines the above drawing procedure
  void draw(car c){
  	startDraw(c);
  	drawBody(c);
  };

};