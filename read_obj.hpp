#include "gamehead.hpp"

#define MAX_VERTICES 8000 // Max number of vertices (for each object)
#define MAX_POLYGONS 8000 // Max number of polygons (for each object)

GLenum mode=GL_TRIANGLES;

///This is the struct of the vertex which includes the coordinates of the vertex
typedef struct{
float x,y,z;
}vertex_type;


///This is the struct of the polygon whihc includes the index of the face
typedef struct{
int f1,f2,f3;
}polygon_type;



//GLuint object;
//float xangle,yangle,zangle;



///This is the class of the object which record all the information of a object file

class obj{

public:
	GLfloat x_scale;
	GLfloat y_scale;
	GLfloat z_scale;
	int ivertex;
	int ipolygon;
	float xmin; 
	float xmax; 
	float ymin;
	float ymax;
	float zmin;
	float zmax;
	float xcenter,ycenter;
	vertex_type vertex[MAX_VERTICES]; 
	polygon_type polygon[MAX_POLYGONS];
	


public:
	/// default constructor which initials all the private value
	obj(){
		
		x_scale=1.0;
		y_scale=1.0;
		z_scale=1.0;
		ivertex=0;
		ipolygon=0;
		xmin=0.0; 
		xmax=0.0; 
		ymin=0.0;
		ymax=0.0;
		zmin=0.0;
		zmax=0.0;
		
	}
	
	///default deconstructor of the object
	~obj(){
		
	}
	
	///This function read the vertex and the index of face from the obj file acording to the first character of each line
	void loadObj(char *fname)
	{
	   FILE *fp;
	   int read;
	   //GLfloat x, y, z;
	   char ch[2];
	  // object=glGenLists(1);
	   fp=fopen(fname,"r");
	   if (!fp)
	   {
		printf("can't open file %s\n", fname);
		//exit(1);
	   }
		glPushMatrix();
		while(!(feof(fp)))
		{
		 read=fscanf(fp,"%c%c",&ch[0],&ch[1]);
		 int tmp[9];
		 //switch(ch[0])
		 
		 if(ch[0]=='v' && ch[1]==' '){
		  //case 'v':
			  fscanf(fp,"%f %f %f",&vertex[ivertex].x,&vertex[ivertex].y,&vertex[ivertex].z);
			  ivertex++;
			//  break;
		  //case 'f':	
			}
		 else if(ch[0]=='f'){	
			  fscanf(fp,"%d/%d/%d %d/%d/%d %d/%d/%d",&tmp[0],&tmp[1],&tmp[2],&tmp[3],&tmp[4],&tmp[5],&tmp[6],&tmp[7],&tmp[8]);
			  polygon[ipolygon].f1 = tmp[0];
			  polygon[ipolygon].f2 = tmp[3];
			  polygon[ipolygon].f3 = tmp[6];
			
			 // fscanf(fp,"%d %d %d",&polygon[ipolygon].f1,&polygon[ipolygon].f2,&polygon[ipolygon].f3);
			  ipolygon++;
	//	      break;  
			}	
		}
		 
	   glPopMatrix();
	   fclose(fp);
	}



	///This function calculate the center coordinate of the object
	void findobjcenter()
	{
		for(int i=0;i<ivertex;i++)
		{
			if(xmin>vertex[i].x)
			{
				xmin = vertex[i].x;
			}
			if(xmax<vertex[i].x)
			{
				xmax = vertex[i].x;
			}
			if(ymin>vertex[i].y)
			{
				ymin = vertex[i].y;
			}
			if(ymax<vertex[i].y)
			{
				ymax = vertex[i].y;
			}
			if(zmin>vertex[i].z)
			{
				zmin = vertex[i].z;
			}
			if(ymax<vertex[i].y)
			{
				zmax = vertex[i].z;
			}
			xcenter=(xmin+xmax)/2;
			ycenter=(ymin+ymax)/2;
		}
	}


	
};


