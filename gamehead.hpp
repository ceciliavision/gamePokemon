#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <string.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else

#ifdef _WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#define WIDTH   800										
#define HEIGHT  600	

#define FLOOR_WIDTH 100
#define FLOOR_HEIGHT 100
#define NODE_WIDTH 4.0f //2*r

#define STEP_SIZE 4.0;
#define UP 10 
#define DOWN -10
#define LEFT -1
#define RIGHT 1

#define KEY_ESC 27										
using namespace std; 















