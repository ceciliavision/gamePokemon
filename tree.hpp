#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

/// This is a tree class that creates a tree object onto the scene
class tree{
private:
  float _x; /// the x-position of the tree object
  float _y; /// the y-position of the tree object
  float _z; /// the z-position of the tree object
  float _r1; /// the radius of the tree trunk
  float _r2; /// the radius of the tree leaf
  float _h;  /// the height of the tree
  int _leaf;  /// the number of leaves on a tree object
  string _name; // name of the matrix for later reference

public:

// default constructor
  tree(){
    cout << "In: default vector constructor" 
	 << endl;
    _x = 0;
    _y = 0;
    _z = 0;
    _r1 = 2;
    _r1 = 2;
    _h = 5;
    _leaf = 1;
    _name = "";
  };

  //constructor with input tree size, position and number of leaves on the tree and the name of the object
  tree(float xp, float yp, float zp, float r1, float r2, float h, int leaf, string name){
    _x = xp;
  	_y = yp;
  	_z = zp;
    _r1 = r1;
    _r2 = r2;
    _h = h;
    _leaf = leaf;
    _name = name;
  };

  /// the method that starts the draw of the tree object
  void startDraw(tree t){
  	glPushMatrix();		
	glTranslatef(t._x, 0, t._z);
	glRotatef(-90.0,1,0,0);

	GLfloat MatAmbiant[4] = {0.5f, 0.25f, 0.0f, 1.0f};
	GLfloat MatDiffuse[4] = {0.5f, 0.25f, 0.0f, 1.0f};
	GLfloat MatSpecular[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat MatShininess[] = {2.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbiant);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess);

	glutSolidCone(t._r1, t._h, 20, 20);

	GLfloat MatAmbiant1[4] = {0.0f, 1.0f, 0.1f, 1.0f};
	GLfloat MatDiffuse1[4] = {0.0f, 1.0f, 0.1f, 1.0f};
	GLfloat MatSpecular1[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat MatShininess1[] = {2.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbiant1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular1);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess1);
	glTranslatef(0, 0, t._h+1);
	glutSolidSphere(t._r2, 20, 20);

  };

  /// the method that draws the body of the tree object
  void drawBody(tree t){

  	for (int i=1;i<t._leaf;i++){

		GLfloat MatAmbiant1[4] = {0.0f, 1.0f, 0.1f, 1.0f};
		GLfloat MatDiffuse1[4] = {0.0f, 1.0f, 0.1f, 1.0f};
		GLfloat MatSpecular1[4] = {0.2f, 0.2f, 0.2f, 1.0f};
		GLfloat MatShininess1[] = {2.0f};

		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbiant1);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse1);
		glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular1);
		glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess1);
		glTranslatef(0, -t._r1*i, 0.5*t._r1);
		glutSolidSphere(t._r2, 20, 20);

		GLfloat MatAmbiant2[4] = {0.0f, 1.0f, 0.1f, 1.0f};
		GLfloat MatDiffuse2[4] = {0.0f, 1.0f, 0.1f, 1.0f};
		GLfloat MatSpecular2[4] = {0.2f, 0.2f, 0.2f, 1.0f};
		GLfloat MatShininess2[] = {2.0f};

		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbiant2);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse2);
		glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular2);
		glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess2);
		glTranslatef(0, t._r1*i, 1);
		glutSolidSphere(t._r2, 20, 20);
	}

	glPopMatrix();
  };

  /// the method that combines all the above draw parts to draw a complete tree object
  void draw(tree t){
  	startDraw(t);
  	drawBody(t);
  };

};