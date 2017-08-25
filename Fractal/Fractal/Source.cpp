#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include<GL/glut.h>

double cameraAngle;
double move_X, move_Y, move_Z;
int canDrawGrid, canDrawAxis;

double cameraRadius, cameraHeight, cameraAngleDelta;

double x;
double y;
double direction;
int kochGeneration;

void reset(){
	x = -50;
	y = 0;
	direction = 0;
}

void leftTurn(double angle){
	direction += angle;
}

void rightTurn(double angle){
	direction -= angle;
}

void drawStraightLine(double length){
	double newX;
	double newY;
	newX = x + length*cos(3.1416*direction/180);
	newY = y + length*sin(3.1416*direction/180);

	glBegin(GL_LINES);
		glVertex2f(x,y);
		glVertex2f(newX,newY);
	glEnd();

	x = newX;
	y = newY;
}

void drawKoch(int generation, double length){
	if(generation == 0)
		drawStraightLine(length);
	else{
		drawKoch(generation - 1, length/3.0);
		leftTurn(-60);
		drawKoch(generation - 1, length/3.0);
		rightTurn(-120);
		drawKoch(generation - 1, length/3.0);
		leftTurn(-60);
		drawKoch(generation - 1, length/3.0);
	}
}

void drawSnowFlake(int generation, double length){
	drawKoch(generation, length);
	leftTurn(120);
	drawKoch(generation, length);
	leftTurn(120);
	drawKoch(generation, length);
}

void drawGridAndAxes(){
	
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

void drawQuadKochCurve(int generation, double length){
	if(generation == 0)
		drawStraightLine(length);

	else{
		drawQuadKochCurve(generation-1, length/4.0);
		leftTurn(90);
		drawQuadKochCurve(generation-1, length/4.0);
		leftTurn(90);
		drawQuadKochCurve(generation-1, length/4.0);
		rightTurn(90);
		drawQuadKochCurve(generation-1, length/4.0);
		drawQuadKochCurve(generation-1, length/4.0);
		leftTurn(90);
		drawQuadKochCurve(generation-1, length/4.0);
		leftTurn(90);
		drawQuadKochCurve(generation-1, length/4.0);
		rightTurn(90);
		drawQuadKochCurve(generation-1, length/4.0);


	}

}
void drawDragonCurve(int generation, double length, double game){

	if(generation == 0)
		drawStraightLine(length);

	
	else {
		
		//game=game*(-1);
		
		rightTurn(45*game);
		drawDragonCurve(generation-1, length/sqrt(2.0),1);
		//game=game*(-1);
		rightTurn((-90)*game);
		drawDragonCurve(generation-1, length/sqrt(2.0),-1);
		rightTurn(45*game);
		

	
	}
	

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
	gluLookAt(cameraRadius*sin(cameraAngle), -cameraRadius*cos(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	
	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/**************************************************
	/ Grid and axes Lines(You can remove them if u want)
	***************************************************/
	//drawGridAndAxes();

	/****************************
	/ Add your objects from here
	****************************/
	reset();
	glLineWidth(2.0);
	glColor3f(0,0,1);
	glRotatef(90,1,0,0);
	
	//drawDragonCurve(3,100,1);
	
	//drawSnowFlake(0,100);
	
	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate(){
	//codes for any changes in Models, Camera
	
	//cameraAngle += cameraAngleDelta;	// camera will rotate at 0.002 radians per frame.
	
	//codes for any changes in Models

	//MISSING SOMETHING? -- YES: add the following
	glutPostRedisplay();	//this will call the display AGAIN

}

void init(){
	//codes for initialization
	kochGeneration = 0;
	
	move_X = 0;
	move_Y = 0;
	move_Z = 0;
	canDrawGrid = 1;
	canDrawAxis = 1;

	cameraAngleDelta = .001;


	cameraAngle = 0;	//angle in radian
	cameraRadius = 150;
	cameraHeight = 50;

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

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			move_X += 1;
			break;

		case '2':	
			move_X -= 1;
			break;
			
		case '3':	
			move_Y += 1;
			break;
		case '4':	
			move_Y -= 1;
			break;
			
		case '5':	
			move_Z += 1;
			break;
		case '6':	
			move_Z -= 1;
			break;
		case '8':	

			break;

		case 'g':
			canDrawGrid ^= 1;
			break;
			
		case 'h':
			canDrawAxis ^= 1;
			break;

		case 'p':
			kochGeneration++;
			break;

		case 'r':
			if(kochGeneration>0)
				kochGeneration--;
			break;

		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraRadius += 10;
			break;
		case GLUT_KEY_UP:		// up arrow key
			if(cameraRadius > 10)
				cameraRadius -= 10;
			break;

		case GLUT_KEY_RIGHT:
			cameraAngle += 0.01;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle -= 0.01;
			break;

		case GLUT_KEY_PAGE_UP:
			cameraHeight += 10;
			break;
		case GLUT_KEY_PAGE_DOWN:
			cameraHeight -= 10;
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			cameraAngle = 0;	
			cameraRadius = 150;
			cameraHeight = 50;
			break;
		case GLUT_KEY_END:
		
			break;

		default:
			break;
	}
}

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				cameraAngleDelta = -cameraAngleDelta;	
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}

int main(int argc, char **argv){
	
	glutInit(&argc,argv);							//initialize the GLUT library
	
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	
	/*
		glutInitDisplayMode - inits display mode
		GLUT_DOUBLE - allows for display on the double buffer window
		GLUT_RGBA - shows color (Red, green, blue) and an alpha
		GLUT_DEPTH - allows for depth buffer
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	

	glutCreateWindow("Some Title");

	printf("Camera Control\n");
	printf("_____________\n");
	printf("Zoom In-Out: UP and DOWN arrow\n");
	printf("Camera Rotate: LEFT and RIGHT arrow\n");
	printf("Up-Down: PAGEUP and PAGEDOWN\n");
	printf("Reset Camera: HOME\n");

	init();						//codes for initialization

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);

	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
