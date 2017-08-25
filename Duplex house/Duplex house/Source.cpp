#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include<GL/glut.h>

double cameraAngle;

void grid_and_axes(){
	
	// draw the three major AXES
	
	glBegin(GL_LINES);
		//X axis
		glColor3f(0, 1, 0);	//100% Green
		glVertex3f(-150, 0, 0);
		glVertex3f( 150, 0, 0);
		
		//Y axis
		glColor3f(0, 0, 1);	//100% Blue
		glVertex3f(0, -150, 0);	// intentionally extended to -150 to 150, no big deal
		glVertex3f(0,  150, 0);
		
		//Z axis
		glColor3f(1, 1, 1);	//100% White
		glVertex3f( 0, 0, -150);
		glVertex3f(0, 0, 150);
	glEnd();
	
	//some gridlines along the field
	int i;

	glColor3f(0.5, 0.5, 0.5);	//grey
	glBegin(GL_LINES);
		for(i=-10;i<=10;i++){

			if(i==0)
				continue;	//SKIP the MAIN axes

			//lines parallel to Y-axis
			glVertex3f(i*10, -100, 0);
			glVertex3f(i*10,  100, 0);

			//lines parallel to X-axis
			glVertex3f(-100, i*10, 0);
			glVertex3f( 100, i*10, 0);
		}
	glEnd();
	
}

void garageHouse(){
    glColor3f(1, .8, .4); // 4
	glBegin(GL_QUADS);
		glVertex3f(0,0,0);
		glVertex3f(40,0,0);
		glVertex3f(37,0,30);
		glVertex3f(0,0,30);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex3f(0,0,30);
		glVertex3f(37,0,30);
		glVertex3f(17,0,60);
	glEnd();

	// black color border	
	glColor3f(0, 0, 0); // 4
	glBegin(GL_QUADS);
		glVertex3f(0,0,0);
		glVertex3f(40,0,0);
		glVertex3f(37,0,30);
		glVertex3f(0,0,30);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex3f(0,0,30);
		glVertex3f(37,0,30);
		glVertex3f(17,0,60);
	glEnd();

	// white color border	
	glColor3f(1, 1, 1); // 4
	
	glBegin(GL_LINE);
	   
		glVertex3f(-10,10,0);
		glVertex3f(-10,10,0);
	glEnd();


}
void windows(double x,double y,double z){
     glPushMatrix(); //  window
	     glColor3f(.4,.2,0);
	    glTranslatef(x,y,z);
		glScalef(10,1,20);
		glutSolidCube(1);
		glColor3f(1,1,1);
		glutWireCube(1);

	glPopMatrix();
}

void display(){
	//codes for Models, Camera
	
	//clear the display
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//clear buffers to preset values

	/***************************
	/ set-up camera (view) here
	****************************/ 
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);		//specify which matrix is the current matrix

	//initialize the matrix
	glLoadIdentity();				//replace the current matrix with the identity matrix [Diagonals have 1, others have 0]

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(0,-150,20,	0,0,0,	0,0,1);
	gluLookAt(150*sin(cameraAngle), -150*cos(cameraAngle), 70,		0,0,0,		0,0,1);
	
	
	/*************************
	/ Grid and axes Lines
	**************************/
	grid_and_axes();


	/****************************
	/ Add your objects from here
	****************************/
	//garageHouse();

	
	glPushMatrix(); // garage basement
	    glColor3f(1,1,.6);
	    glTranslatef(28,0,16);
		glScalef(40,0,32);
		glutSolidCube(1);
	
	glPopMatrix();
	
	glPushMatrix();
	    glTranslatef(9,0,32);
		glColor3f(1,1,.6); // garage triangle front face
		glBegin(GL_TRIANGLES);
			glVertex3f(0, 0, 0);
			glVertex3f( 37, 0, 0);
			glVertex3f( 17, 0, 35);
		glEnd();
	glPopMatrix();
	
	glPushMatrix(); // garage left sunset
	    glColor3f(1,1,1);
	    glTranslatef(20,15,50);
		glRotatef(25,0,1,0);
		glRotatef(-10,0,0,1);
		glScalef(2,30,40);
		
		glutSolidCube(1);
		
		 
	glPopMatrix();

	glPushMatrix(); // garage right sunset
	    glColor3f(1,1,1);
	    glTranslatef(38,13,50);
		glRotatef(-30,0,1,0);
		glRotatef(-6,0,0,1);
		glRotatef(-6,1,0,0);
		glScalef(2,30,40);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // garage right sunset texture
	    glColor3f(.6,.4,0);
	    glTranslatef(39,13,50); // just +x
		glRotatef(-30,0,1,0);
		glRotatef(-6,0,0,1);
		glRotatef(-7,1,0,0);
		glScalef(1,30,40);
		glutSolidCube(1);
	glPopMatrix();

	
	glPushMatrix(); // garage top sunset 
	    glColor3f(.6,.4,0);
	    glTranslatef(30,10,60); 
		glRotatef(5,0,1,0);
		glRotatef(-20,1,0,0);
		glScalef(33,2,50);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // garage top sunset border
	    glColor3f(1,1,1);
	    glTranslatef(31,11,60); 
		glRotatef(5,0,1,0);
		glRotatef(-20,1,0,0);
		glScalef(33,1,50);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // garage top sunset backside
	    glColor3f(1,1,1);
	    glTranslatef(33,33,77); 
		//glRotatef(5,0,1,0);
		glRotatef(70,1,0,0);
		glRotatef(0,0,1,0);
		glRotatef(-5,0,0,1);
		glScalef(33,1,30);
		glutSolidCube(1);

	glPopMatrix();

	glPushMatrix(); // garage top right side
	    glColor3f(1,1,.6);
	    glTranslatef(45.5,26,57); 
		glRotatef(-20,1,0,0);
		glRotatef(.5,0,1,0);
		glScalef(1,30,40);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // garage left bottom right side 
	    glColor3f(1,1,.6);
	    glTranslatef(48,14,17); 
		glRotatef(-5,0,1,0);
		glScalef(1,30,35);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // garage right bottom right side 
	    glColor3f(1,1,.6);
	    glTranslatef(47,37,35); 
		glRotatef(-3,0,1,0);
		glScalef(1,20,72);
		glutSolidCube(1);
	glPopMatrix();


	// left side of the garage 
	
	glPushMatrix(); // 1st window block
	    glColor3f(.6,.2,0);
	    glTranslatef(-2,2,15); 
		glScalef(20,2,30);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // 2nd window block
	    glColor3f(.6,.2,0);
	    glTranslatef(-20,5,15); 
		glScalef(15,2,30);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // 3rd window block
	    glColor3f(.6,.2,0);
	    glTranslatef(-38,10,15); 
		glScalef(20,2,30);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // 1st piller
	    glColor3f(1,1,1);
		glTranslatef(-38,2,4); 
		GLUquadricObj *cyl = gluNewQuadric();
		gluCylinder(cyl,1,1,28,20,20);
		 glColor3f(0,0,0);
	
	glPopMatrix();

	glPushMatrix(); // 1st piller bottom
	    glColor3f(1,1,1);
		glTranslatef(-38,2,4); 
		GLUquadricObj *cyls = gluNewQuadric();
		gluCylinder(cyls,1.5,1.5,5,20,20);
	
	glPopMatrix();
	

	glPushMatrix(); // 2nd piller
	    glColor3f(1,1,1);
		glTranslatef(-55,2,4); 
		GLUquadricObj *cyl1 = gluNewQuadric();
		gluCylinder(cyl,1,1,28,20,20);
		 glColor3f(0,0,0);
	
	glPopMatrix();

	glPushMatrix(); // 2nd piller bottom
	    glColor3f(1,1,1);
		glTranslatef(-55,2,4); 
		GLUquadricObj *cyls1 = gluNewQuadric();
		gluCylinder(cyls,1.5,1.5,5,20,20);
	glPopMatrix();

	// piller sunset
	glPushMatrix(); // piller joint
	    glColor3f(.5,.5,.5);
		glTranslatef(-23,2,31); 
		glScalef(65,.5,1);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // sunset of left side
	     glColor3f(.6,.4,0);
	    glColor3f(1,1,1);
	    glTranslatef(-22,8,36); 
		glRotatef(25,1,0,0);
		glScalef(75,20,2);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // sunset of left side cover
	     glColor3f(.6,.4,0);
	    glTranslatef(-22,8,37); 
		glRotatef(25,1,0,0);
		glScalef(74.9,20,2);
		glutSolidCube(1);
	glPopMatrix();


	// ************************* 2nd floor working ***************

	// 2nd floor similar house like garage

	glPushMatrix(); //  basement
	    glColor3f(1,1,.6);
	    glTranslatef(-23,13,50);
		glScalef(73,0,26);
		glutSolidCube(1);
	
	glPopMatrix();
	
	glPushMatrix();
	    glTranslatef(-35,10,60);
		glColor3f(1,1,.6); //  triangle front face
		glBegin(GL_TRIANGLES);
			glVertex3f(0, 0, 0);
			glVertex3f( 50, 0, 0);
			glVertex3f( 25, 0, 35);
		glEnd();
	glPopMatrix();
	
	glPushMatrix(); //  left sunset
	    glColor3f(1,1,1);
	    glTranslatef(-22,18,80);
		glRotatef(35,0,1,0);
		glRotatef(10,0,0,1);
		glScalef(1,20,38);
		
		glutSolidCube(1);
		
		 
	glPopMatrix();

	glPushMatrix(); // left sunset texture
	     glColor3f(.6,.4,0);
	     glTranslatef(-22.2,18.5,80);
		glRotatef(35,0,1,0);
		glRotatef(10,0,0,1);
		glScalef(1,20,38);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //  right sunset
	    glColor3f(1,1,1);
	    glTranslatef(1,18,79);
		glRotatef(-35,0,1,0);
		glRotatef(-2,0,0,1);
	
		glScalef(1,20,38);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //  right sunset texture
	    glColor3f(.6,.4,0);
	    glTranslatef(1.5,18,79);
		glRotatef(-35,0,1,0);
		glRotatef(-2,0,0,1);
		glScalef(1,20,38);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // middle box
	    glColor3f(.8,.4,0);
	    glTranslatef(-19,8,50);
		glScalef(25,5,30);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //  window
	    glColor3f(.4,.2,0);
	    glTranslatef(-22,0,18);
		glScalef(5,1,20);
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix(); //  window
	    glColor3f(.4,.2,0);
	    glTranslatef(-2,0,18);
		glScalef(10,1,20);
		glutSolidCube(1);
	glPopMatrix();

	  glPushMatrix(); // sunset of 2nd floor left side
			 glColor3f(.6,.4,0);
			glTranslatef(-38,22,72); 
			glRotatef(40,1,0,0);
			glScalef(40,40,1);		
			glutSolidCube(1);
		glPopMatrix();


		glPushMatrix(); //  left sunset for middle box
			glColor3f(1,1,1);
			glTranslatef(-26,15,75);
			glRotatef(35,0,1,0);
			glRotatef(10,0,0,1);
			glScalef(1,20,23);
		glutSolidCube(1);
	   glPopMatrix();

	  glPushMatrix(); //  right sunset
	    glColor3f(1,1,1);
	    glTranslatef(-12,15,74);
		glRotatef(-35,0,1,0);
		glRotatef(-2,0,0,1);
		glScalef(1,20,23);
		glutSolidCube(1);
	glPopMatrix();

	 glPushMatrix(); //  left sunset texture
	        glColor3f(.6,.4,0);
			glTranslatef(-26.5,15,75);
			glRotatef(35,0,1,0);
			glRotatef(10,0,0,1);
			glScalef(1,20,23);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //  window
	    glColor3f(1,1,1);
	    glTranslatef(20,0,20);
		glScalef(10,1,20);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //  window
	    glColor3f(1,1,1);
	    glTranslatef(40,0,20);
		glScalef(10,1,20);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //  window
	     glColor3f(.4,.2,0);
	    glTranslatef(-38,8,20);
		glScalef(10,1,20);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //  left side area
	    glColor3f(1,1,.6);
	    glTranslatef(-50,33,35);
		glScalef(1,25,70);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //  
	    glColor3f(1,1,.6);
	    glTranslatef(0,45,35);
		glScalef(100,5,75);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //  
	    glColor3f(.9,.9,.9);
	    glTranslatef(-5,20,0);
		glScalef(120,58,5);
		glutSolidCube(1);
	glPopMatrix();


     glPushMatrix(); //  window top left
	     glColor3f(.4,.2,0);
	    glTranslatef(-45,10,50);
		glScalef(10,1,15);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //  window top left
	     glColor3f(.4,.2,0);
	    glTranslatef(-18,5,52);
		glScalef(10,1,20);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //  window top left
	     glColor3f(.4,.2,0);
	    glTranslatef(2,5,54);
		glScalef(10,1,20);
		glutSolidCube(1);
	glPopMatrix();

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate(){
	//codes for any changes in Models, Camera
	
	//cameraAngle = -21.5;	
	cameraAngle += 0.001;
	//codes for any changes in Models

	//MISSING SOMETHING? -- YES: add the following
	glutPostRedisplay();	//this will call the display AGAIN

}

void init(){
	//codes for initialization

	//cameraAngle = 0;	//angle in radian
	//clear the screen
	glClearColor(0,0,0, 0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);
	
	//initialize the matrix
	glLoadIdentity();

	/*
		gluPerspective() — set up a perspective projection matrix

		fovy -         Specifies the field of view angle, in degrees, in the y direction.
        aspect ratio - Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
        zNear -        Specifies the distance from the viewer to the near clipping plane (always positive).
        zFar  -        Specifies the distance from the viewer to the far clipping plane (always positive).
    */
	
	gluPerspective(70,	1,	0.1,	10000.0);
	
}

int main(int argc, char **argv){
	
	glutInit(&argc,argv);							//initialize the GLUT library
	
	glutInitWindowSize(1200, 600);
	glutInitWindowPosition(10, 50);
	
	/*
		glutInitDisplayMode - inits display mode
		GLUT_DOUBLE - allows for display on the double buffer window
		GLUT_RGBA - shows color (Red, green, blue) and an alpha
		GLUT_DEPTH - allows for depth buffer
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	

	glutCreateWindow("Duplex house");

	init();						//codes for initialization

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
