#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include<GL/glut.h>

double cameraAngle;
double move_X, move_Y, move_Z,helperX,helperY,helperZ,cameraHeightChangeFromKey;
int canDrawGrid, canDrawAxis,curtainOpen,fanFlow,fanFlowMeter,isLight,isWindow;

double cameraRadius, cameraHeight, cameraAngleDelta;

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




void chairPaya(double px,double py,double pz,double cx,double cy,double cz){
	double equ[4];
	equ[0] = 0;
	equ[1] = 0;
	equ[2] = 1;
	equ[3] = -1;
	glPushMatrix();
	glTranslatef(px,py,pz);


	glPushMatrix();
	glRotatef(180,1,0,0);
	glTranslatef(0,0,-10);
	glPushMatrix();
	glColor3f(cx,cy,cz);
	glClipPlane(GL_CLIP_PLANE0,equ);
	glEnable(GL_CLIP_PLANE0);
	glScalef(3,3,10);
	glutSolidSphere(1,10,10);
	glDisable(GL_CLIP_PLANE0);

	glPopMatrix();
	glPopMatrix(); 
	glPopMatrix(); 
}
void hatol(double px,double py,double pz,double cx,double cy,double cz){

	glPushMatrix(); // hatol
	glTranslatef(px,py,pz);
	glPushMatrix();
	glColor3f(cx,cy,cz);
	glScalef(2,1,12);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
}
void handleCover(double px,double py,double pz,double cx,double cy,double cz){
	glPushMatrix(); 
	glTranslatef(px,py,pz);
	glColor3f(cx,cy,cz);

	glPushMatrix(); 
	glScalef(2,17.5,1);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
}

void handleDesignStack(double px,double py,double pz,double cx,double cy,double cz){
	glPushMatrix(); 
	glColor3f(cx,cy,cz);
	glTranslatef(px,py,pz);
	glPushMatrix(); 
	glRotatef(-8,1,0,0);
	glScalef(2,0.5,5);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
}

void singleSofa(double px,double py,double pz){
	glPushMatrix(); // Single Chair 

	glTranslatef(px,py,pz);

	glPushMatrix(); // pichoner helano side
	glColor3f(.4,.2,0);
	glTranslatef(0,13,20);
	glRotatef(-20,1,0,0);
	glScalef(20,1,20);
	glutSolidCube(1);
	glPopMatrix();


	glPushMatrix(); // chair er basement.
	glColor3f(.4,.2,0);
	glTranslatef(0,0,10);
	glScalef(20,20,1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // chair er basement 2
	glColor3f(.4,.2,0);
	glTranslatef(0,0,12);
	glScalef(16,20,1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // chair er base sofa
	glColor3f(1,0.6,0.4);
	glTranslatef(0,0,15);
	glScalef(16,20,4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // pichoner helano soofa
	glColor3f(1,0.6,0.4);
	glTranslatef(0,12,24);
	glRotatef(-20,1,0,0);
	glScalef(16,4,16);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();  //design cover
	glTranslatef(-9,1,18);
	glColor3f(.4,.2,0);

	glPushMatrix(); 
	glScalef(2,17,1);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	hatol(-9,-7,16,.4,.2,0);
	hatol(-9,9,16,.4,.2,0);
	hatol(9,-7,16,.4,.2,0);
	hatol(9,9,16,.4,.2,0);

	//handleDesign(-9,1,16,1,0,0);   

	handleDesignStack(-9,-5,15,0.8,0.4,0);
	handleDesignStack(-9,-3,15,0.8,0.4,0);
	handleDesignStack(-9,-1,15,0.8,0.4,0);
	handleDesignStack(-9,1,15,0.8,0.4,0);
	handleDesignStack(-9,3,15,0.8,0.4,0);
	handleDesignStack(-9,5,15,0.8,0.4,0);
	handleDesignStack(-9,7,15,0.8,0.4,0);



	handleCover(-9,1,22,.4,.2,0);
	handleCover(9,1,22,.4,.2,0);


	chairPaya(7,-7,0,.4,.2,0);
	chairPaya(-7,-7,0,.4,.2,0);
	chairPaya(7,7,0,.4,.2,0);
	chairPaya(-7,7,0,.4,.2,0);

	glPopMatrix();
}

void jointSofa(double px,double py,double pz){
	glPushMatrix(); // Single Chair 

	glTranslatef(px,py,pz);

	glPushMatrix(); // pichoner helano side
	glColor3f(.4,.2,0);
	glTranslatef(0,13,20);
	glRotatef(-20,1,0,0);
	glScalef(20,1,20);
	glutSolidCube(1);
	glPopMatrix();


	glPushMatrix(); // pichoner helano side
	glColor3f(.4,.2,0);
	glTranslatef(20,13,20);
	glRotatef(-20,1,0,0);
	glScalef(20,1,20);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // pichoner helano side
	glColor3f(.4,.2,0);
	glTranslatef(10,13,20);
	glRotatef(-20,1,0,0);
	glScalef(20,1,20);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // chair er basement.
	glColor3f(.4,.2,0);
	glTranslatef(0,0,10);
	glScalef(20,20,1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // chair er basement.
	glColor3f(.4,.2,0);
	glTranslatef(10,0,10);
	glScalef(20,20,1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // chair er basement.
	glColor3f(.4,.2,0);
	glTranslatef(20,0,10);
	glScalef(20,20,1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // chair er basement 2
	glColor3f(.4,.2,0);
	glTranslatef(10,0,12);
	glScalef(16,20,1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // chair er basement 2
	glColor3f(.4,.2,0);
	glTranslatef(10,0,12);
	glScalef(16,20,1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // chair er basement 2
	glColor3f(.4,.2,0);
	glTranslatef(20,0,12);
	glScalef(16,20,1);
	glutSolidCube(1);
	glPopMatrix();



	glPushMatrix(); // chair er base sofa
	glColor3f(1,0.6,0.4);
	glTranslatef(0,0,15);
	glScalef(14,20,4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // chair er base sofa
	glColor3f(1,0.6,0.4);
	glTranslatef(10.5,0,15);
	glScalef(14,20,4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // chair er base sofa
	glColor3f(1,0.6,0.4);
	glTranslatef(20,0,15);
	glScalef(14,20,4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // pichoner helano soofa
	glColor3f(1,0.6,0.4);
	glTranslatef(0,12,24);
	glRotatef(-20,1,0,0);
	glScalef(14,4,16);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // pichoner helano soofa
	glColor3f(1,0.6,0.4);
	glTranslatef(10,12,24);
	glRotatef(-20,1,0,0);
	glScalef(14,4,16);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // pichoner helano soofa
	glColor3f(1,0.6,0.4);
	glTranslatef(20,12,24);
	glRotatef(-20,1,0,0);
	glScalef(14,4,16);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();  //design cover
	glTranslatef(-9,1,18);
	glColor3f(.4,.2,0);

	glPushMatrix(); 
	glScalef(2,17,1);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	hatol(-9,-7,16,.4,.2,0);
	hatol(-9,9,16,.4,.2,0);
	hatol(29,-7,16,.4,.2,0);
	hatol(29,9,16,.4,.2,0);

	//handleDesign(-9,1,16,1,0,0);   

	handleDesignStack(-9,-5,15,0.8,0.4,0);
	handleDesignStack(-9,-3,15,0.8,0.4,0);
	handleDesignStack(-9,-1,15,0.8,0.4,0);
	handleDesignStack(-9,1,15,0.8,0.4,0);
	handleDesignStack(-9,3,15,0.8,0.4,0);
	handleDesignStack(-9,5,15,0.8,0.4,0);
	handleDesignStack(-9,7,15,0.8,0.4,0);



	handleCover(-9,1,22,.4,.2,0);
	handleCover(29,1,22,.4,.2,0);


	chairPaya(27,-7,0,.4,.2,0);
	chairPaya(-7,-7,0,.4,.2,0);
	chairPaya(27,7,0,.4,.2,0);
	chairPaya(-7,7,0,.4,.2,0);

	glPopMatrix();
}

void displayInit(){
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

	//gluLookAt(0,-150,20,	0,0,0,	0,0,1);
	gluLookAt(cameraRadius*sin(cameraAngle), -cameraRadius*cos(cameraAngle), cameraHeight,		0,0,0,		0,0,1);

	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/**************************************************
	/ Grid and axes Lines(You can remove them if u want)
	***************************************************/
	drawGridAndAxes();

}
void windowGrillHorizontal(double px,double py,double pz){
	glPushMatrix();  
	glTranslatef(px,py,pz);
	glPushMatrix();  
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f( .9, .9, .9,.5);	
	glRotatef(30,1,0,0);
	glScalef(21,2,0.2);
	glutSolidCube(1);
	glDisable(GL_BLEND);
	glPopMatrix();
	glPopMatrix();
}

void windowGrillVertical(double px,double py,double pz){
	glPushMatrix();    
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f( 0.5, 0.5, 0.5,.7);
	glTranslatef(px,py,pz);
	glScalef(.2,.8,20);
	glutSolidCube(1);
	glDisable(GL_BLEND);
	glPopMatrix();
}
void windowHandle(double px,double py,double pz,double cubeColor[]){
	glPushMatrix();   
	glTranslatef(px,py,pz);
	glPushMatrix();    
	glTranslatef(0,0.5,-0.5);
	//glColor3f( 0.9, 0.89, 0.96);
	glColor3f( cubeColor[0], cubeColor[1], cubeColor[2]);
	glRotatef(45,0,1,0);
	glScalef(0.7,1,.7);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();    
	glTranslatef(0,0,-2);
	glColor3f( 1, 0.89, 0.96);
	glScalef(-0.5,1,1);
	glBegin(GL_POLYGON);
	glVertex3f(-1,0,0);
	glVertex3f(0,0,2);
	glVertex3f(1,0,0);
	glVertex3f(0,0,-2);
	glEnd();
	glPopMatrix();

	glPushMatrix();    
	glTranslatef(0,-0.1,-2);
	glScalef(-0.5,1,1);
	glColor3f(0.8, 0.16, 0.13);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5,0,0);
	glVertex3f(0,0,1);
	glVertex3f(0.5,0,0);
	glVertex3f(0,0,-1);
	glEnd();
	glPopMatrix();
	glPopMatrix();
}

void windowSingle(double px,double py,double pz,int leftx){
	glPushMatrix(); 
	glTranslatef(px,py,pz);

	glPushMatrix();  // window back
	glColor3f(0.24, 0.16, 0.13);
	glTranslatef(0,1,0);
	glScalef(24,1,24);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();    // window back border
	glColor3f(0.35, 0.25, 0.25);
	glTranslatef(0,0.9,0);
	glScalef(24,1,24);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();       
	glColor3f( 0.72, 0.89, 0.96);
	glScalef(20,1,20);
	glutSolidCube(1);
	glPopMatrix();

	windowGrillHorizontal(0,-1,10);
	windowGrillHorizontal(0,-1,8);
	windowGrillHorizontal(0,-1,6);
	windowGrillHorizontal(0,-1,4);
	windowGrillHorizontal(0,-1,2);
	windowGrillHorizontal(0,-1,0);
	windowGrillHorizontal(0,-1,-2);
	windowGrillHorizontal(0,-1,-4);
	windowGrillHorizontal(0,-1,-6);
	windowGrillHorizontal(0,-1,-8);

	windowGrillVertical(9,-2,0);
	windowGrillVertical(-9,-2,0);	

	double clr[3] ={0.9, 0.89, 0.96}; 
	if(leftx == 1){

		windowHandle(11.2,0,2,clr);
	}else{
		windowHandle(-11.2,0,2,clr);
	}
	glPopMatrix();
}

void windowPack(double px,double py,double pz){
	glPushMatrix();    
	glTranslatef(px,py,pz);
	glPushMatrix();   
	glTranslatef(0,0,30);

	glPushMatrix(); 
	glColor3f(1, 1, 1);
	glTranslatef(2,0,12);
	glScalef(48,3,0.4);
	glutSolidCube(1);
	glPopMatrix();


	glPushMatrix(); 
	glColor3f(1, 1, 1);
	glTranslatef(26.2,0,0);
	glRotatef(90,0,1,0);
	glScalef(24,3,0.4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); 
	glColor3f(1, 1, 1);
	glTranslatef(-22,0,0);
	glRotatef(90,0,1,0);
	glScalef(24,3,0.4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); 
	glColor3f(1, 1, 1);
	glTranslatef(2,0,-12);
	glScalef(48,3,0.4);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	windowSingle(-10,0,30,1);
	windowSingle(14.2,0,30,0);
	glPopMatrix();
}
void windowCover(double px,double py,double pz,int rotate){
	glPushMatrix(); 
	glTranslatef(px,py,pz);
	if(rotate == 1){
		glRotatef(180,0,0,1);
	}
	/*if(isWindow){
		glScalef(-5,1,1);
	}*/

	glPushMatrix(); 

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 0.8,.9);
	//glColor4f(0.65, 0.57, 0.49,.9);
	double equ[4];
	equ[0] = 10;
	equ[1] = -30;
	equ[2] = 0;
	equ[3] = 0;
	glClipPlane(GL_CLIP_PLANE0,equ);
	glEnable(GL_CLIP_PLANE0);

	GLUquadricObj *cyl = gluNewQuadric();
	
	gluCylinder(cyl,2,2,55,40,40);
	glDisable(GL_BLEND);
	glDisable(GL_CLIP_PLANE0);
	glPopMatrix();
	glPopMatrix();
}
void windowCoverPack(double px,double py,double pz,int scale){
	glPushMatrix(); 

	glTranslatef(px,py,pz);
	if(scale == 1){
		glScalef(-0.6,1,1);
	}else
		glScalef(-0.9,1,1);

	glPushMatrix();
	windowCover(0,-1,0,1);
	windowCover(3.5,0,0,0);
	windowCover(7.5,0,0,0);
	windowCover(11,0,0,0);
	windowCover(13.5,0,0,1);
	windowCover(16,0,0,1);
	windowCover(18,0,0,0);
	windowCover(20,0,0,1);

	glPopMatrix();
	glPopMatrix();
}

void showCaseLowerBox(double px,double py,double pz){
	glPushMatrix(); 
	glTranslatef(px,py,pz);


	glPushMatrix(); 

	double clr[3] ={0.91, 0.84, 0.65}; 

	windowHandle(-7,-8,14,clr);

	glColor3f(0.57, 0.40, 0.31);
	glPushMatrix(); //1 outer border

	glTranslatef(-15,-7.7,12);
	glScalef(2,0.5,8);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //1 outer border

	glTranslatef(-7,-7.7,12);
	glScalef(2,0.5,8);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //1 outer border

	glTranslatef(-11,-7.7,16);
	glRotatef(90,0,1,0);
	glScalef(2,0.5,10);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //1 outer border

	glTranslatef(-11,-7.7,8);
	glRotatef(90,0,1,0);
	glScalef(2,0.5,10);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //1

	glTranslatef(-11,-7.7,12);
	glScalef(4,1,4);
	glutSolidCube(1);
	glPopMatrix();

	double gap = 0.01;
	for (int i = 0; i < 20; i++)
	{
		glPushMatrix(); //last border
		glColor3f(0.47, 0.30, 0.21);
		glTranslatef(-11+gap,-7.5,12-gap);
		glScalef(10-gap,1,10-gap);
		glutWireCube(1);
		glPopMatrix();
		gap += 0.01;
	}



	glPopMatrix();
	glPopMatrix();
}

void sideDesign(double px,double py,double pz){
	glPushMatrix(); // left side design
	glTranslatef(px,py,pz);
	glPushMatrix(); // left side design
	//glColor3f(0.35, 0.25, 0.20);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(0.23, 0.15, 0.10,0.6);
	glRotatef(90,0,1,0);
	glScalef(15,9,1);
	glutSolidCube(1);
	glDisable(GL_BLEND);
	glPopMatrix();
	glPushMatrix(); // left side design wire
	glColor3f(0.30, 0.25, 0.20);
	glRotatef(90,0,1,0);
	glScalef(15,9,1);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
}

void showCaseTopSelfMiddlePart(double px,double py,double pz){
	glPushMatrix(); 
	glTranslatef(px,py,pz);
	glPushMatrix(); // back left	
	glColor3f(0.9,0.9,.9);
	glTranslatef(0,-1,7);
	glScalef(2,12,38);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
}
void showCaseMiddle(double px,double py,double pz){
	glPushMatrix(); 
	glTranslatef(px,py,pz);
	//glTranslatef(0,0,30);

	glPushMatrix(); 

	double clr[3] ={0.91, 0.84, 0.65}; 

	windowHandle(-5.5,-8,14,clr);

	glColor3f(0.57, 0.40, 0.31);
	glPushMatrix(); // left			
	glTranslatef(-14.5,-7.4,8);
	glScalef(2,0.5,36.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // left			
	glTranslatef(-5.5,-7.4,8);
	glScalef(2,0.5,36.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //up
	glTranslatef(-10,-7.4,26.5);
	glRotatef(90,0,1,0);
	glScalef(2.5,0.5,11);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //bottom
	glTranslatef(-10,-7.4,-11);
	glRotatef(90,0,1,0);
	glScalef(2.5,0.5,11);
	glutSolidCube(1);
	glPopMatrix();


	showCaseTopSelfMiddlePart(-14.5,2,0);


	double gap = 0.01;
	for (int i = 0; i < 30; i++)
	{
		glPushMatrix(); //bottom
		glColor3f(0.47, 0.30, 0.21);
		glTranslatef(-10+gap,-7.5,8-gap);
		glScalef(10.9-gap,0.5,39-gap);
		glutWireCube(1);
		glPopMatrix();
		gap += 0.01;
	}

	glPushMatrix(); 
	glColor3f(1,1,1);
	glPushMatrix(); // back left	

	glTranslatef(-9.5,0,18);
	glScalef(8,11,1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // back left	

	glTranslatef(-9.5,0,8);
	glScalef(8,11,2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // back left	

	glTranslatef(-9.5,0,-3);
	glScalef(8,11,1.3);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix(); // rek

	glPopMatrix();
	glPopMatrix();

}
void showCase(double px,double py,double pz,double scale[],int isScale){
	glPushMatrix(); 
	glTranslatef(px,py,pz);
	glRotatef(90,0,0,1);

	if(isScale){
		glScalef(scale[0],scale[1],scale[2]);
	}

	//glTranslatef(0,0,0);
	glPushMatrix();
	glPushMatrix(); // basement 
	glColor3f(0.24, 0.17, 0.12);
	glTranslatef(0,0,2);
	glScalef(36,15,5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // 2nd basement
	glColor3f(0.29, 0.20, 0.15);
	glTranslatef(0,0,10);
	glScalef(35,15,12);
	glutSolidCube(1);
	glPopMatrix();

	showCaseLowerBox(0,0,-2);
	showCaseLowerBox(11,0,-2);
	showCaseLowerBox(22,0,-2);


	glPushMatrix(); // 3rd basement 
	glColor3f(0.29, 0.20, 0.15);
	glTranslatef(0,-0.5,16);
	glScalef(36,16.5,0.5);
	glutSolidCube(1);
	glPopMatrix();

	/* top self ------------------------------------- */

	glPushMatrix(); // bottom side
	glColor3f(0.6, 0.20, 0.15);
	glTranslatef(0,0,17);
	glScalef(35,15,2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // right side
	glColor3f(0.29, 0.20, 0.15);
	glTranslatef(16,0,38);
	glRotatef(90,0,1,0);
	glScalef(40,15,1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // left side
	glColor3f(0.29, 0.20, 0.15);
	glTranslatef(-16,0,38);
	glRotatef(90,0,1,0);
	glScalef(40,15,1);
	glutSolidCube(1);
	glPopMatrix();

	sideDesign(-16.2,0,48);
	sideDesign(-16.2,0,30);
	sideDesign(16.2,0,48);
	sideDesign(16.2,0,30);


	double gap=0.1;
	for(int i=0;i<30;i++){
		glPushMatrix(); // upper side
		glColor3f(0.29, 0.20, 0.15);
		glTranslatef(0,0,58+gap);
		glScalef(35+gap,15,0.8);
		glutSolidCube(1);
		glPopMatrix();
		gap+= 0.1;
	}

	glPushMatrix(); // back side
	glColor3f(.8, .8, .8);
	glTranslatef(0,7,38);
	glScalef(31,1,40);
	glutSolidCube(1);
	glPopMatrix();
	/* -------------------------------------------------------- */
	// top self side ready....

	// top self middle box

	showCaseMiddle(-0.9,0,30);
	showCaseMiddle(10,0,30);
	showCaseMiddle(21,0,30);
	showCaseTopSelfMiddlePart(15,0,30);

	glPopMatrix();	
	glPopMatrix();	
}

void fanBlade(double px){
	 glPushMatrix(); // fan blade
				glColor3f(0.93, 0.73, 0.46);
				glRotatef(px,0,0,1);

				glPushMatrix(); // fan blade
				
				glTranslatef(13,0,0);
					glRotatef(-10,1,0,0);
					glScalef(14,4,0.2);
					glutSolidCube(1);
			    glPopMatrix();

			double gap=0.01;
			for (int i = 0; i < 30; i++)
			{
				glPushMatrix(); // lower border
					glColor3f(0.83, 0.63, 0.36);
					glTranslatef(13+gap,0,0);
					glRotatef(-10,1,0,0);
					glScalef(10+gap,2+gap,0.2);
					glutWireCube(1);
				glPopMatrix();
				gap = gap + 0.01;
			}

			glPushMatrix(); // fan blade
				glTranslatef(6,0,0);
				glRotatef(-10,1,0,0);

				glScalef(2,1,0.2);
				glutSolidCube(1);
			glPopMatrix();

			glPopMatrix(); //end fan blade 3
}

void fanFull(double px,double py,double pz){
   glPushMatrix(); 
	 glTranslatef(px,py,pz);
	 if(fanFlowMeter > 360) fanFlowMeter = 0;
	
	 if(fanFlow == 1){
	   glRotatef(fanFlowMeter,0,0,1);
	   fanFlowMeter -= 2;
	 }
	 else if(fanFlow == 2){
	   glRotatef(fanFlowMeter,0,0,1);
	   fanFlowMeter -= 3;
	 }
	  else if(fanFlow == 3){
	   glRotatef(fanFlowMeter,0,0,1);
	   fanFlowMeter -= 5;
	 }
     else if(fanFlow == 4){
	   glRotatef(fanFlowMeter,0,0,1);
	   fanFlowMeter -= 6;
	 }
	  //glTranslatef(0,0,30);
	    glPushMatrix();

	      glPushMatrix(); // back side
			glColor3f(0.24, 0.15, 0.10);
			glTranslatef(0,0,0);
			//glRotatef(180,1,0,0);
			//glScalef(5,1,1);
			glutSolidTorus(2,3,20,30);
			glPopMatrix();

			double gap=0.01;
			for (int i = 0; i < 10; i++)
			{
				glPushMatrix(); // back side
					glColor3f(0.93, 0.73, 0.46);
					glTranslatef(0,0,1+gap);
					glutWireTorus(2,2.8-gap,1,30);
				glPopMatrix();
				gap = gap + 0.01;
			}

			gap=0.01;
			for (int i = 0; i < 10; i++)
			{
				glPushMatrix(); // lower border
				glColor3f(0.93, 0.73, 0.46);
				glTranslatef(0,0,-1-gap);
				glutWireTorus(2,2.8+gap,1,30);
				glPopMatrix();
				gap = gap + 0.01;
			}

			fanBlade(180);
			fanBlade(62);
			fanBlade(-62);

			glPushMatrix(); // fan stire
				glTranslatef(0,0,0);
			    glColor3f(0.24, 0.15, 0.10);
				//glScalef(2,1,0.2);
				GLUquadricObj *cyl = gluNewQuadric();
	            gluCylinder(cyl,0.5,0.5,10,30,30);
			glPopMatrix();

		   glPushMatrix(); // fan stire bottom design
				glTranslatef(0,0,1);
			    glColor3f(0.60, 0.35, 0.20);
				//glScalef(2,1,0.2);
				GLUquadricObj *cyl1 = gluNewQuadric();
	            gluCylinder(cyl,2,0.5,3,30,30);
			glPopMatrix();

			 glPushMatrix(); // fan stire bottom design
				glTranslatef(0,0,8);
			    glColor3f(0.60, 0.35, 0.20);
				//glScalef(2,1,0.2);
				GLUquadricObj *cyl2 = gluNewQuadric();
	            gluCylinder(cyl,0.5,2,3,30,30);
			glPopMatrix();

			glPopMatrix();	
	glPopMatrix();
}
void chandelierStand(double px,double py,double pz,double deg){
     glPushMatrix(); 
	glTranslatef(px,py,pz);
	    
	 glRotatef(deg,0,0,1);
	    glPushMatrix();
		    glColor3f(0.24, 0.16, 0.13);
		   //glColor3f(0.29, 0.25, .15);

	       glPushMatrix(); // chandelier
				//glTranslatef(0,0,0);		   
				glScalef(1,0.5,10);
				glutSolidCube(1);
			glPopMatrix();
		   glPushMatrix(); // chandelier
		   glTranslatef(0,-0.1,-5);
			   glRotatef(-8,1,0,0);
			   
				glScalef(1,0.5,3);
				glutSolidCube(1);
			glPopMatrix();
		
			  glPushMatrix(); 
			  glTranslatef(0,-0.5,-7);
			  glRotatef(-18,1,0,0);	  
				glScalef(1,0.5,3);
				glutSolidCube(1);
			glPopMatrix();

	      glPushMatrix(); 
			  glTranslatef(0,-1.8,-9);
			  glRotatef(-41,1,0,0);
				glScalef(1,0.5,3);
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix(); 
			  glTranslatef(0,-3.5,-10.2);
			  glRotatef(-74,1,0,0);
				glScalef(1,0.5,2);
				glutSolidCube(1);
			glPopMatrix(); //chandelier stand end

			glPushMatrix(); 
			 glTranslatef(0,-4,-9);
			
			    glColor3f(0.8, 0.8, 0.8);
				//glScalef(2,1,0.2);
				GLUquadricObj *cyl2 = gluNewQuadric();
	            gluCylinder(cyl2,1,2,5.5,30,30);
			
			glPopMatrix();

			if(isLight){
				glPushMatrix(); 
				 glTranslatef(0,-4,-9);
					glColor3f(1, 1, 1);
					GLUquadricObj *cyl4 = gluNewQuadric();
					gluCylinder(cyl4,1.1,2.1,5,30,30);
				glPopMatrix();
			}
		

		  glPushMatrix(); 
			 glTranslatef(0,-4,-10);
			    glColor3f(0.29, 0.25, .15);
				//glScalef(2,1,0.2);
				GLUquadricObj *cyl3 = gluNewQuadric();
	            gluCylinder(cyl3,0.5,1,3,30,30);
			glPopMatrix();


		glPopMatrix();	
	glPopMatrix();
}
void chandelier(double px,double py,double pz){
  glPushMatrix(); 
	 glTranslatef(px,py,pz);
	    
	   //glTranslatef(0,0,30);
	    glPushMatrix();
		    glColor3f(0.6, 0.6, 0.6);
	       
		   chandelierStand(0,0,0,20);
		   chandelierStand(0,0,0,100);
		   chandelierStand(0,0,0,-50);
		   chandelierStand(0,0,0,-120);
		   chandelierStand(0,0,0,180);
		  

		glPopMatrix();	
	glPopMatrix();
}
void teaTable(double px,double py,double pz){
   glPushMatrix(); 
	  glTranslatef(px,py,pz);
	    
	   glRotatef(90,0,0,1);
	    	  
	  glPushMatrix();
		  glColor3f(0.43, 0.29, 0.22);

	       glPushMatrix(); // upper
			   	glTranslatef(0,0,7);	   
				glScalef(15,10,2);
				glutSolidCube(1);
			glPopMatrix();

			double g=0.01;
			for (int i = 0; i < 120; i++)
			{
				glPushMatrix(); // upper
			     glColor3f(0.25, 0.15, .10);
			   	glTranslatef(0,0,7+g);	   
				glScalef(15-g,10-g,2-g);
				glutWireCube(1);
		    	glPopMatrix();
				g+=0.01;
			}
			 
		  
		   glPushMatrix(); // bottom
			 glColor3f(0.43, 0.29, 0.22);	   
				glScalef(15,10,1);
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix(); // middle
	           glColor3f(0.25, 0.15, .10);
			   	glTranslatef(0,0,3);
				glScalef(1,8,6);
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix(); // side
			 glTranslatef(0,4,3);
			   glColor3f(0.35, 0.25, .15);
				glScalef(12,1,6);
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix(); // side wire
			 glTranslatef(0,4,3);
			   glColor3f(0.25, 0.15, .10);
				glScalef(12,1,6);
				glutWireCube(1);
			glPopMatrix();
		glPopMatrix();	
	glPopMatrix();
}
void tvStandBox(double px,double py,double pz,int isShort){
     glPushMatrix(); 
        glTranslatef(px,py,pz);	 
		if(isShort)
		 glScalef(1,1,-0.7);
	   glPushMatrix(); 
		    
	        glPushMatrix(); 
			   	glTranslatef(0,0,0);	   
				glScalef(10,6,10);
				glutSolidCube(1);
			glPopMatrix();
			 glPushMatrix(); 
			   	glTranslatef(0,0,0);	
				glColor3f(0.26, 0.16, 0.15);
				glScalef(10.1,6.1,10.1);
				glutWireCube(1);
			glPopMatrix();

			 glPushMatrix(); 
			   glColor3f(0.36, 0.26, 0.25);
			   glTranslatef(0,0,5.5);	
				glScalef(10,6,1);
				glutSolidCube(1);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
void bookSelf(double px,double py,double pz){
    glPushMatrix(); 
	    glTranslatef(px,py,pz);
	    
	    // glRotatef(deg,0,0,1);
	   //glTranslatef(0,0,15);	  

	  glPushMatrix();
		  glColor3f(0.16, 0.13, 0.12);

	        glPushMatrix(); 
			   	glTranslatef(0,0,0);	   
				glScalef(20,0.5,10);
				glutSolidCube(1);
			glPopMatrix();
			
			
	        glPushMatrix(); 
			    glColor3f(0.36, 0.33, 0.32);
      			glTranslatef(0,-2,2.5);	
				glScalef(18,4,0.5);
				glutSolidCube(1);
			glPopMatrix();
		
			glPushMatrix(); 
			   glColor3f(0.36, 0.33, 0.32);
      			glTranslatef(0,-2,-2.5);	
				glScalef(18,4,0.5);
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix(); 
			glTranslatef(-7,-3,-2.5);
			    glColor3f(0.58, 0.42, 0.32);
				GLUquadricObj *cyl6 = gluNewQuadric();
	            gluCylinder(cyl6,0.5,1,2.5,30,30);
			glPopMatrix();

		    glPushMatrix(); 
			glTranslatef(-3,-3,-2.5);
			    glColor3f(0.58, 0.42, 0.32);
				GLUquadricObj *cyl7 = gluNewQuadric();
	            gluCylinder(cyl7,0.5,1,2.5,30,30);
			glPopMatrix();

			glPushMatrix(); 
			    glColor3f(1, 0.36, 0.35);
				glTranslatef(3,-2,-0.5);	
				glScalef(0.5,3,4);
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix(); 
			    glColor3f(1, 0, 0.35);
				glTranslatef(4,-2,-0.5);	
				glScalef(0.5,3,4);
				glutSolidCube(1);
			glPopMatrix();

			
			glPushMatrix(); 
			    glColor3f(1, 0, 0);
				glTranslatef(5,-2,-0.5);	
				glScalef(0.5,3,4.2);
				glutSolidCube(1);
			glPopMatrix();

			
			glPushMatrix(); 
			    glColor3f(0, 0, 0.35);
				glTranslatef(6,-2,-0.5);	
				glScalef(0.5,3,3.8);
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix(); 
			    glColor3f(1, 0, 0.7);
				glTranslatef(7,-2,-0.5);	
				glScalef(0.5,3,3.8);
				glutSolidCube(1);
			glPopMatrix();
		glPopMatrix();	
	glPopMatrix();
}

void tvStand(double px,double py,double pz){
glPushMatrix(); 
	    glTranslatef(px,py,pz);
	    
	    // glRotatef(deg,0,0,1);
	     //glTranslatef(0,0,15);	   
	  glPushMatrix();
		  glColor3f(0.36, 0.26, 0.25);


	      tvStandBox(0,0,0,0);
		  tvStandBox(10,0,0,0);
		  tvStandBox(20,0,-1,1);
		  tvStandBox(30,0,-1,1);
		  tvStandBox(40,0,-1,1);
			
		   glPushMatrix(); 
		   glTranslatef(29,0,6);	
		      glPushMatrix(); 
			   glColor3f(0, 0, 0);
			   glTranslatef(0,0,5.5);	
				glScalef(16,1,12);
				glutSolidCube(1);
			  glPopMatrix();

		
			  double gapp=0.01;
			  for (int i = 0; i < 50; i++)
			  {
				  	 glPushMatrix(); 
					  glColor3f(.39, .38, .38);
					   glTranslatef(0,-0.2,6+gapp);	
					   glScalef(19.7+gapp,1,14-gapp);
						glutWireCube(1);
					  glPopMatrix();
	               gapp = gapp + 0.01;
			  }

	          gapp=0.1;
			  for (int i = 0; i < 20; i++)
			  {
				   glPushMatrix(); 
					   glColor3f(1, 1, 1);
					   glTranslatef(0,-0.2,-1-gapp);	
					   glScalef(19.7+gapp,1,1);
					   glutSolidCube(1);
					  glPopMatrix();  	 
	               gapp = gapp + 0.1;
			  }
			  

			  glPushMatrix(); //left
			   glColor3f(.29, .28, .28);
			   glTranslatef(-9,-0.2,5.5);	
				glScalef(2,1,13);
				glutSolidCube(1);
			  glPopMatrix();

			  glPushMatrix(); //right
			   glColor3f(.29, .28, .28);
			   glTranslatef(9,-0.2,6.4);	
				glScalef(2,1,14);
				glutSolidCube(1);
			  glPopMatrix();

			  glPushMatrix(); //up
			   glColor3f(.29, .28, .28);
			   glTranslatef(-0.8,-0.2,12.5);	
				glScalef(18.5,1,2);
				glutSolidCube(1);
			  glPopMatrix();

			  
			 glPushMatrix(); //bottom
			   glColor3f(.29, .28, .28);
			   glTranslatef(0.8,-0.2,0);	
				glScalef(18.5,1,2);
				glutSolidCube(1);
			  glPopMatrix();

			glPopMatrix();
	        
		glPopMatrix();	
	glPopMatrix();

}

void tvSide(double px,double py,double pz){
 glPushMatrix(); 
	    glTranslatef(px,py,pz);
	    
	    // glRotatef(deg,0,0,1);
	    //	glTranslatef(0,0,15);	   
	  glPushMatrix();
		 	
		      glPushMatrix(); 
			   glColor3f(0.39, .25, 0.18);
			   glTranslatef(0,0,3);	
				glScalef(70,1,50);
				glutSolidCube(1);
			  glPopMatrix();


			  double gapp=0.09;
			  for (int i = 0; i < 30; i++)
			  {
				  	glPushMatrix(); 
					   glColor3f(1, 1, 1);
					   glTranslatef(0,0,28+gapp);	
						glScalef(70+gapp,1,1);
						glutSolidCube(1);
					  glPopMatrix();
	               gapp = gapp + 0.09;
			  }
			  	  glPushMatrix();  //bottom
					   glColor3f(1, 1, 1);
					   glTranslatef(0,-0.3,-22);	
						glScalef(72,1,3);
						glutSolidCube(1);
					  glPopMatrix();
	        

					  tvStand(-19,-3.5,-19);
					  bookSelf(0,-1,14);

		glPopMatrix();	
	glPopMatrix();

}
void windowArea(double px,double py,double pz){
   glPushMatrix(); 
	     glTranslatef(px,py,pz);
	    
	   glRotatef(-90,0,0,1);
	  //glTranslatef(0,0,24);	   
	  glPushMatrix();
		 	
		      glPushMatrix(); // white background
			   glColor3f(1, 1, 1);
			   glTranslatef(0,1,7.5);	
				glScalef(100,2,62);
				glutSolidCube(1);
			  glPopMatrix();

			   

			 glPushMatrix(); 
			   glColor3f(0.39, .25, 0.18);
			   glTranslatef(0,0,5.5);	
				glScalef(80,1,60);
				glutSolidCube(1);
			  glPopMatrix();

			 glPushMatrix(); 
			   glColor3f(1, 1, 1);
			   glTranslatef(0,-2,35);	
			   glScalef(80,8,2);
				glutSolidCube(1);
			  glPopMatrix();

			  double gapp=0.1;
			  for (int i = 0; i < 35; i++)
			  {
				  	glPushMatrix(); 
					   glColor3f(0.35, 0.25, 0.25);
					   glTranslatef(0,-7,33+gapp);	
						glScalef(80+gapp,1,1);
						glutSolidCube(1);
					  glPopMatrix();
	               gapp = gapp + 0.1;
			  }
			  	
			  windowPack(0,-2,-15);
			  windowCoverPack(33,-5,-21,0);
			  windowCoverPack(-24,-5,-21,1);
			  	if(isWindow){
				
					windowCoverPack(20,-5,-21,0);
			        windowCoverPack(-14,-5,-21,1);
				}
		glPopMatrix();	
	glPopMatrix();
}
void mettres(double px,double py,double pz){
	glPushMatrix(); 
	    glTranslatef(px,py,pz);
	   
	  glRotatef(-90,1,0,0);
	  //glTranslatef(0,0,24);	   
	  glPushMatrix();
		 	
		      glPushMatrix(); // white background
			  glColor3f(0.24, 0.16, 0.13);
			   glTranslatef(0,1,5.5);	
				glScalef(80,0.5,60);
				glutSolidCube(1);
			  glPopMatrix();

			   
			 glPushMatrix(); // white background
			 glColor3f(0.43, 0.29, 0.22);
			   glTranslatef(0,0.8,5.5);	
				glScalef(70,0.5,50);
				glutSolidCube(1);
			  glPopMatrix();
			 
			  glPushMatrix(); // white background
			  glColor3f(0.24, 0.16, 0.13);
			   glTranslatef(0,0.7,5.5);	
				glScalef(60,0.5,40);
				glutSolidCube(1);
			  glPopMatrix();

			  /*double gapp=0.1;
			  for (int i = 0; i < 35; i++)
			  {
				  	glPushMatrix(); 
					   glColor3f(.9, .9, 0.9);
					   glTranslatef(0,-7,33+gapp);	
						glScalef(80+gapp,1,1);
						glutSolidCube(1);
					  glPopMatrix();
	               gapp = gapp + 0.1;
			  }*/
			  	
			

		glPopMatrix();	
	glPopMatrix();
}
void display(){
	displayInit();
	/****************************
	/ Add your objects from here
	****************************/
	/*
	window white color: 183,226,244 =>  0.72, 0.89, 0.96

	*/

	

	//windowCoverPack(0,0,0,1);
	//windowCoverPack(30,0,0,0);

	//fanFull(0,0,30);	

	 //chandelier(0,0,30);

	  glPushMatrix(); 
	    // glTranslatef(px,py,pz);
	    
	    // glRotatef(deg,0,0,1);
	  glTranslatef(0,0,0);	   
	  
	  glPushMatrix();
		 	
		     glPushMatrix(); // white background pichoner ta
			  glColor3f(0.88, 0.81, 0.65);
			   glTranslatef(0,20,0);	
			   glRotatef(-90,1,0,0);
				glScalef(150,1,100);
				glutSolidCube(1);
			  glPopMatrix();

			

			 glPushMatrix(); // white background
			  glColor3f(1, 1, 1);
			   glTranslatef(0,20,64);	
			   glRotatef(-90,1,0,0);
				glScalef(150,1,110);
				glutSolidCube(1);
			  glPopMatrix();


			  windowArea(73,20,25);

			  tvSide(0,67,25);

			 glPushMatrix(); // white background
			  glColor3f(0.9, 0.9, 0.9);
			  glTranslatef(0,68,32);	
			   //glRotatef(90,1,0,0);
				glScalef(150,2,63);
				glutSolidCube(1);
			  glPopMatrix();

			  //double gapp=10,x=60,y=50;

			  //for (int i = 0; i < 35; i++)
			  //{
				 //  glPushMatrix(); // white background
					// glColor3f(0.53, 0.39, 0.32);
					//
					// if(x <= -60){
					//    y -= 20;
					//	x = 60;
					// }
					// x -= gapp;
					//  glTranslatef(x,y,1);

					//   glRotatef(-90,1,0,0);
					//	glScalef(20,1,20);
					//	glutSolidCube(1);
					//  glPopMatrix();
	    //           gapp = gapp + 20;
			  //}
			  //	
			
			
			  showCase(-62,30,0,0,0);

			  glPushMatrix(); // white background
			  glColor3f(0.9, 0.9, 0.9);
			  glTranslatef(-74,18,32);	
			    //glRotatef(90,1,0,0);
				glScalef(2,100,63);
				glutSolidCube(1);
			  glPopMatrix();

			  mettres(4,5,2);


			  glPushMatrix();
			   glScalef(-0.8,-0.8,0.8);
			    glPushMatrix();
			     glRotated(-90,0,0,1);
			     jointSofa(0,35,0);
			    glPopMatrix();
			  glPopMatrix();

			  glPushMatrix();
			   glScalef(-0.8,-0.8,0.8);
			    glPushMatrix();
			     glRotated(90,0,0,1);
				 singleSofa(5,35,0);
				 singleSofa(-26,35,0);
			    glPopMatrix();
			  glPopMatrix();
			   

			  teaTable(0,0,2);

			  fanFull(0,30,52);

			  chandelier(0,0,60);

		glPopMatrix();	
	glPopMatrix();
			
	//teaTable(0,0,20);
	


	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(.9,.9,.9, .5);
	glutSolidCube(1);	
	glDisable(GL_BLEND); */
	glutSwapBuffers();
}

void animate(){
	glutPostRedisplay();	//this will call the display AGAIN
}

void init(){
	//codes for initialization

	helperX = 0;
	helperY = 0;
	helperZ = 0;

	fanFlowMeter=0;
	fanFlow = 0;
	isLight = 0;

	isWindow = 0;

	move_X = 0;
	move_Y = 0;
	move_Z = 0;
	canDrawGrid = 1;
	canDrawAxis = 1;

	cameraAngleDelta = .001;

	cameraHeightChangeFromKey = 0;
	cameraAngle = 0;	//angle in radian
	cameraRadius = 150;
	cameraHeight = 50+cameraHeightChangeFromKey;

	glClearColor(0,0,0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
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
		helperX += 1;

		break;

	case 'o':
		helperX -= 1;
		break;

	case 'i':
		helperY += 0.1;

		break;

	case 'u':
		helperY -= 0.1;
		break;

	case 'y':
		helperZ += 1;

		break;

	case 't':
		helperZ -= 1;
		break;
	case 'x':
		cameraHeight += 1;
		break;

	case 'z':
		cameraHeight -=1;
		break;

	case 'f':
		if(fanFlow == 0)
		   fanFlow = 1;
		else 
			fanFlow = 0;
		break;

	case 'd':
		if(fanFlow == 1)
		   fanFlow = 2;
		break;
	case 's':
		if(fanFlow == 1)
		   fanFlow = 3;
		break;
    case 'a':
		if(fanFlow == 1)
		   fanFlow = 4;
		break;
    case 'l':
		if(isLight == 0)
			isLight = 1;
		else 
			isLight = 0;
		break;
	case 'w':
		if(isWindow == 0)
			isWindow = 1;
		else 
			isWindow = 0;
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
		cameraAngle += 0.1;
		break;
	case GLUT_KEY_LEFT:
		cameraAngle -= 0.1;
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

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	

	glutCreateWindow("Some Title");

	printf("Camera Control\n");
	printf("_____________\n");
	printf("Zoom In-Out: UP and DOWN arrow\n");
	printf("Camera Rotate: LEFT and RIGHT arrow\n");
	printf("Up-Down: PAGEUP and PAGEDOWN\n");
	printf("x=> ",helperX);
	printf("y=> ",helperY);
	printf("z=> ",helperZ);
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
