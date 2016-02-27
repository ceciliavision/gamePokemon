#include "gamehead.hpp"
#include "tga.h"
#include "snake.hpp"
#include "house.hpp"
#include "tree.hpp"
#include "car.hpp"
#include "read_obj.hpp"

#ifdef __APPLE__
#include "glut.h"
#endif


#define WIDTH   800										
#define HEIGHT  600		

#define KEY_ESC 27										
using namespace std;

/// default font
void *font = GLUT_BITMAP_TIMES_ROMAN_24;

int sign_back;
/// Initialize the camera view
float	xpos = 0, zpos = -100;
int		angle_x = 45, angle_y = -180;					
int		mouse_x = 0, mouse_y = 0;	
float xs=0.0f, ys=2.5f, zs=0.0f; /// Initial position of the snaks
float r = 0.0f;
GLfloat position[4] = {0.0, 20.0, 0.0, 1.0};

float xf=35.0f, yf=2.6f, zf=-35.0f; ///Initialize position of the first Pikachu
float xb=10.0f, yb=2.5f, zb=0.0f;


snake sn(xs,ys,zs,xf,yf,zf,xb,yb,zb); ///initialize the snake
obj ob1;
obj ob2;

/// Declare the main function in order to restart the game later
int main(int argc, char *argv[]);

/// InitGL method that initializes the scene lighting and color
GLvoid initGL()
{
	glClearColor(0, 0, 0, 1);				
    glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);		
	glDepthFunc(GL_LEQUAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glLightfv(GL_LIGHT1, GL_POSITION, position);

	GLfloat Light1Amb[4] = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat Light1Dif[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat Light1Spec[4] = {0.2f, 0.2f, 0.2f, 1.0f};

	glLightfv(GL_LIGHT1, GL_AMBIENT, Light1Amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light1Dif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Light1Spec);

	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.005f);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
}


/// Method that displays the floor
void display_floor()
{

	GLfloat MatAmbiant[4] = {0.0f, 0.5f, 0.0f, 1.0f};
	GLfloat MatDiffuse[4] = {0.0f, 0.8f, 0.0f, 1.0f};
	GLfloat MatSpecular[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat MatShininess[] = {5.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbiant);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess);


	glNormal3f(0.0f, 1.0f, 0.0f);

	Texture t;
	t.charger("./res/grass.tga");

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-50, 0, -50);
	
	glTexCoord2f(0.0f, 10.0f);
	glVertex3f(-50, 0,  50);

	glTexCoord2f(10.0f, 10.0f);
	glVertex3f(50, 0,  50);

	glTexCoord2f(10.0f, 0.0f);
	glVertex3f(50, 0, -50);
	glEnd();

	glDisable(GL_TEXTURE_2D);

}

/// Method that displays a sun object
void display_sun()
{
	GLfloat MatAmbiant[4] = {0.5f, 0.5f, 0.0f, 1.0f};
	GLfloat MatDiffuse[4] = {0.8f, 0.8f, 0.0f, 1.0f};
	GLfloat MatSpecular[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat MatShininess[] = {5.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbiant);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess);

	glPushMatrix();
	glTranslatef(-10, 30, 10);
	glRotatef(r,0,1,0);
	
	glutSolidSphere(5.0, 30, 20);
	glPopMatrix();
}

/// Method that draws a snake
void draw_body(float xs, float ys, float zs, float r){
	Texture t;
	t.charger("./res/images.tga");
	glPushMatrix();
	glTranslatef(xs, ys, zs);
	glRotatef(r,0,1,0);	
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glutSolidSphere(2.0, 20, 20);
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glPopMatrix();
	
}

/// Method that displays a snake object
void display_snake()
{

	GLfloat MatAmbiant[4] = {0.5f, 0.5f, 0.0f, 1.0f};
	GLfloat MatDiffuse[4] = {0.8f, 0.0f, 0.0f, 0.0f};
	GLfloat MatSpecular[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat MatShininess[] = {5.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbiant);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess);
	
	//initialize the snake	
	snake_node tmp;
	
	for(int i=0;i<sn.get_length();i++){
		tmp=sn.get_node(i);
		draw_body(tmp.x, tmp.y, tmp.z, r);
	}

}

/// Method that draws a pikachu object
void draw_pikachu(float xs, float ys, float zs)
{  
   glPushMatrix();
   ob1.findobjcenter();
   glTranslatef(-ob1.xcenter,-ob1.ycenter,0.0);
   glTranslatef(xs,ys,zs);
   glColor3f(1.0,1.0,0.0);
   glScalef(ob1.x_scale,ob1.y_scale,ob1.z_scale);
   glRotatef(90,0,1,0);
   for (int i=0;i<ob1.ipolygon;i++)
	 {
		 glBegin(mode);
		 glVertex3d(ob1.vertex[ob1.polygon[i].f1-1].x,ob1.vertex[ob1.polygon[i].f1-1].y,ob1.vertex[ob1.polygon[i].f1-1].z);
		 glVertex3d(ob1.vertex[ob1.polygon[i].f2-1].x,ob1.vertex[ob1.polygon[i].f2-1].y,ob1.vertex[ob1.polygon[i].f2-1].z);
		 glVertex3d(ob1.vertex[ob1.polygon[i].f3-1].x,ob1.vertex[ob1.polygon[i].f3-1].y,ob1.vertex[ob1.polygon[i].f3-1].z);
		 glVertex3d(ob1.vertex[ob1.polygon[i].f1-1].x,ob1.vertex[ob1.polygon[i].f1-1].y,ob1.vertex[ob1.polygon[i].f1-1].z);
		 glEnd();
	 }
   glPopMatrix();
}

/// Method that displays a pikachu object
void display_pikachu(){
	
	GLfloat MatAmbiant[4] = {0.5f, 0.5f, 0.0f, 1.0f};
	GLfloat MatDiffuse[4] = {1.0f, 1.0f, 0.0f, 1.0f};
	GLfloat MatSpecular[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat MatShininess[] = {5.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbiant);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess);
	glDisable(GL_LIGHTING);
	
	snake_node tmp_food;
	
	tmp_food=sn.get_food();

	draw_pikachu(tmp_food.x, tmp_food.y, tmp_food.z);
	glEnable(GL_LIGHTING);
	
}

/// Method that draws a meowthy object
void draw_meowth(float xs, float ys, float zs)
{
   
   glPushMatrix();
   ob2.findobjcenter();
   glTranslatef(-ob2.xcenter,-ob2.ycenter,0.0);
   glTranslatef(xs,ys,zs);
   glColor3f(1.0,1.0,1.0);
   glScalef(ob2.x_scale,ob2.y_scale,ob2.z_scale);
   glRotatef(135,0,1,0);
   for (int i=0;i<ob2.ipolygon;i++)
	 {
		 glBegin(mode);
		 glVertex3d(ob2.vertex[ob2.polygon[i].f1-1].x,ob2.vertex[ob2.polygon[i].f1-1].y,ob2.vertex[ob2.polygon[i].f1-1].z);
		 glVertex3d(ob2.vertex[ob2.polygon[i].f2-1].x,ob2.vertex[ob2.polygon[i].f2-1].y,ob2.vertex[ob2.polygon[i].f2-1].z);
		 glVertex3d(ob2.vertex[ob2.polygon[i].f3-1].x,ob2.vertex[ob2.polygon[i].f3-1].y,ob2.vertex[ob2.polygon[i].f3-1].z);
		 glVertex3d(ob2.vertex[ob2.polygon[i].f1-1].x,ob2.vertex[ob2.polygon[i].f1-1].y,ob2.vertex[ob2.polygon[i].f1-1].z);
		 glEnd();
	 }
   glPopMatrix();
}

/// Method that displays a meowthy object
void display_meowth(){
	
	GLfloat MatAmbiant[4] = {0.5f, 0.5f, 0.0f, 1.0f};
	GLfloat MatDiffuse[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat MatSpecular[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat MatShininess[] = {5.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbiant);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess);
	glDisable(GL_LIGHTING);
	
	snake_node tmp_bug;
	
	tmp_bug=sn.get_bug();
	draw_meowth(tmp_bug.x, tmp_bug.y, tmp_bug.z);

	glEnable(GL_LIGHTING);
}

/// Display the different objects in the scene
void display_scene()
{
	
	display_floor();
	display_snake();

	/// Create 6 houses into the scene
	house h1(-30, 0, -35, 0, 5, 5, 2, "house1");
	house h2(-10, 0, -10, 0, 6, 5, 1, "house2");	
	house h3(30, 0, 15, 90, 5, 4, 2, "house3");
	house h4(0, 0, 20, 90, 5, 5, 2, "house4");
	house h5(-30, 0, 35, 0, 5, 6, 2, "house5");	
	house h6(5, 0, -35, 90, 5, 4, 2, "house6");	
	h1.draw(h1);
	h2.draw(h2);
	h3.draw(h3);
	h4.draw(h4);
	h5.draw(h5);
	h6.draw(h6);

	/// Create 7 tree objects into the scene
	tree t1(-40, 0, -5, 2.0, 4.0, 10.0, 1, "tree1");
	tree t3(-5, 0, 40, 2.0, 4.0, 8.0, 1, "tree3");
	tree t4(-15, 0, 20, 2.0, 3.0, 7.0, 1, "tree4");
	tree t5(12, 0, -20, 2.0, 3.0, 12.0, 2, "tree5");
	tree t6(42, 0, -10, 2.0, 2.0, 8.0, 2, "tree6");
	tree t7(32, 0, 35, 2.0, 5.0, 8.0, 2, "tree7");
	tree t8(5, 0, 5, 2.0, 4.0, 12.0, 2, "tree8");
	t1.draw(t1);
	t3.draw(t3);
	t4.draw(t4);
	t5.draw(t5);
	t6.draw(t6);
	t7.draw(t7);
	t8.draw(t8);

	/// Create one cart object into the scene
	car c1(20, 1, -20, 90, 1, 3, 2, "car1");
	c1.draw(c1);

	display_sun();
	display_meowth();
	
	display_pikachu();
	glutSwapBuffers();	
}

/// Call-back: display the window
GLvoid callback_display()
{
	/// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	/// We apply a translation and a rotation to the scene to simulate a camera move.
	glTranslatef(xpos,0,zpos);
	glRotatef(angle_x, 1,0,0);
	glRotatef(angle_y, 0,1,0);

	/// Display the scene.
	display_scene();
	glFlush();
}

/// Call-back: function called when the window resizes
GLvoid callback_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);
	glMatrixMode(GL_MODELVIEW);
}

/// Call-back: managing keyboard events
GLvoid callback_keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case KEY_ESC:
			exit(1);
			break;
	}
}

/// Call-back: management of special keys that zoom in or out the scene
GLvoid callback_special(int key, int x, int y)
{
	float aa = 1.0f;	

	switch (key)
	{
		case GLUT_KEY_UP:
			zpos += aa;			
			glutPostRedisplay();
			break;

		case GLUT_KEY_DOWN:
			zpos -= aa;	
			glutPostRedisplay();
			break;

		case GLUT_KEY_LEFT:	
			xpos += aa;	
			glutPostRedisplay();
			break;

		case GLUT_KEY_RIGHT:	
			xpos -= aa;	
			glutPostRedisplay();
			break;
	}
}

/// Sprint method that displays a string onto the screen using bitmap
void sprint(float x,
		float y,
		float z,char *st){
	int l,i;
	l = strlen(st);

	glRasterPos3f(x,y,z);
	for (i = 0;i<l;i++){
		glutBitmapCharacter(font, st[i]);
	}
}

/// Render text onto the screen
void renderText(void) {

	/// Clear Color and Depth Buffers
	glClearColor(0.0, 0.0, 0.0, 0.5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();

	/// Display text to interact with the user
	glTranslatef(-2.0f, 1.0f, -20.0f);;
	sprint(0.0f, 0.0f, 0.0f,"Game Over :(");
	glTranslatef(0.0f, -1.0f, 0.0f);
	sprint(0.0f, 0.0f, 0.0f,"Press 'ESC' to exit");

	glPopMatrix();
	glutSwapBuffers();
}

/// Call-back: mouse clicks management
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_x = x;
		mouse_y = y;
	}
}

/// Call-back: management of mouse movements
GLvoid callback_motion(int x, int y)
{
	/// change the camera view of the scene as the user moves the mouse
	angle_x += y - mouse_y;
	angle_y += x - mouse_x;	
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();
}

/// management of keys
GLvoid window_key(unsigned char key, int x, int y) 
{ 
switch (key) {
	/// exit key that exits the game
	case KEY_ESC:
		exit(1);
	break;
	/// keys that control the snake's movements
	case 'a':
		sign_back=sn.step(RIGHT);
	break;
	case 'd':
		sign_back=sn.step(LEFT);
	break;
	case 's':
		sign_back=sn.step(DOWN);
	break;
	case 'w':
		sign_back=sn.step(UP);
	break;
	/// backup key that creates a meowsy
	case 'm':
	 	sn.new_bug();
	break;
	/// backup key that creates a pikachu
	case 'p':
		sn.new_food();
	break;
	/// other undefined keys that are not active in this game
	default:
		cerr<<"The key "<<key<<" is not active\n";
	break;
	}
	position[0] = xs;
	position[1] = ys;
	position[2] = zs;
	position[3] = 1.0;
	glutPostRedisplay();
}

/// Time function
void time_func(int a)
{
    sign_back=sn.step(direct);
    glutPostRedisplay();

    /// Die, ask user whether to end the game or not
    if(sign_back==1){
		glutDisplayFunc(renderText);
		return;
	}
	/// Continue the game using glutTimeFunc with input of the snake's speed
	else{
		glutTimerFunc(1000,time_func,0);
	}    
}

/// Main function of the program
int main(int argc, char *argv[])
{
	srand(time(NULL));

	/// Initialize parameters Glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Pokemon Village ^.^");

	/// Intitialisation of OpenGL settings
	initGL();

	/// Declare the call-back functions.
	glutDisplayFunc(&callback_display);
	glutReshapeFunc(&callback_reshape);
	glutKeyboardFunc (&callback_keyboard);
	glutSpecialFunc(&callback_special);
	
	/// Load the external .obj files and place into the scene
	ob1.loadObj("./res/Pikachu.obj");
	ob2.loadObj("./res/Meowth.obj");
	
	glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);
	glutKeyboardFunc(&window_key);
	
	glutTimerFunc(1000,time_func,0); ///timer
	
	/// Main loop Glut.
	glutMainLoop();

	/// Return code
	return 1;
}
