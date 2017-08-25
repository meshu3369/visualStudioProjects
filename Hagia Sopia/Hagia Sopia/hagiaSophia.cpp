#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>  //add korte hobe..

#include<GL/glut.h>

double cameraAngle,helper_x,helper_y,helper_z;
double move_X, move_Y, move_Z;
int canDrawGrid, canDrawAxis;

double cameraRadius, cameraHeight, cameraAngleDelta;

int num_texture  = -1;
GLuint grassimg,ballimg,cylimg,blockWhite,blockTop,wall,pillar_wall,brick_wall,brick_wall2;

int LoadBitmapImage(char *filename)
{
	int i, j=0;
	FILE *l_file;
	unsigned char *l_texture;

	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;

	num_texture++;

	if( (l_file = fopen(filename, "rb"))==NULL) return (-1);

	fread(&fileheader, sizeof(fileheader), 1, l_file);

	fseek(l_file, sizeof(fileheader), SEEK_SET);
	fread(&infoheader, sizeof(infoheader), 1, l_file);

	l_texture = (byte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
	for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
		{
				fread(&rgb, sizeof(rgb), 1, l_file);

				l_texture[j+0] = rgb.rgbtRed;
				l_texture[j+1] = rgb.rgbtGreen;
				l_texture[j+2] = rgb.rgbtBlue;
				l_texture[j+3] = 255;
				j += 4;
		}
	fclose(l_file);

	glBindTexture(GL_TEXTURE_2D, num_texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

	free(l_texture);

	return (num_texture);

}

void loadImage()
{
	blockWhite = LoadBitmapImage("image/blockWhite.bmp");
	brick_wall = LoadBitmapImage("image/brick_wall.bmp");
	brick_wall2 = LoadBitmapImage("image/brick_wall2.bmp");
	wall = LoadBitmapImage("image/wall.bmp");
	pillar_wall = LoadBitmapImage("image/pillar_wall.bmp");
	blockTop = LoadBitmapImage("image/blockTop.bmp");
	ballimg = LoadBitmapImage("image/ball.bmp");
	cylimg = LoadBitmapImage("image/pilar.bmp");
	if(ballimg != -1)
		printf("Load successful!!\n");
	else printf("Image loading Failed!!\n");
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


void pilar(double px,double py,double pz,double cx,double cy,double cz,GLuint cycImage,GLuint image){
	glPushMatrix(); 
	   glTranslatef(px,py,pz);
	   if(cx != 0 )
	     glScalef(cx,cy,cz);

	    glPushMatrix(); 
		 glPushMatrix(); 
		   glTranslatef(0,0,10);
			glEnable(GL_TEXTURE_2D);
			   glBindTexture(GL_TEXTURE_2D,cycImage);

			   glColor3f(1,1,1);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj,GL_TRUE);
				gluCylinder(obj, 3,3,50,20,20);
			glDisable(GL_TEXTURE_2D);
		 glPopMatrix();

		 glPushMatrix(); 
		    glTranslatef(0,0,58);
		     glPushMatrix(); 
			   glColor3f(1,1,1);
			   glutSolidCone(3,20,10,10);
		     glPopMatrix();
         glPopMatrix();

		 
		 glPushMatrix(); 
		   glTranslatef(0,0,14);
		     glPushMatrix(); 
			   glColor3f(1,1,1);
			   glScalef(8,8,25);
			   glutSolidCube(1);
		     glPopMatrix(); // main

			  //texture
			 glPushMatrix(); 
			   glTranslatef(-4.1,-4.1,-12.5);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(0,0,25);
						
					    glTexCoord2f(1,1);
						glVertex3f(0,8,25);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,8,0);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();


			 glPushMatrix(); // right
			  glTranslatef(4.1,-4.1,-12.5);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(0,0,25);
						
					    glTexCoord2f(1,1);
						glVertex3f(0,8,25);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,8,0);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();


			 glPushMatrix();  // front
			    glTranslatef(-4,-4.1,-12.5);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(8,0,0);
						
					    glTexCoord2f(1,1);
						glVertex3f(8,0,25);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,0,25);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();

			  glPushMatrix();  // back
			     glTranslatef(-4,4.1,-12.5);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(8,0,0);
						
					    glTexCoord2f(1,1);
						glVertex3f(8,0,25);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,0,25);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();

			 glPushMatrix();  // up
			 glTranslatef(-4,-4.1,12.6);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(8,0,0);
						
					    glTexCoord2f(1,1);
						glVertex3f(8,8,0);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,8,0);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();
			

         glPopMatrix();

		 	glPopMatrix();
	glPopMatrix();
}


void block (double px,double py,double pz,double degRotate, double rx,double ry,double rz,double deg, double cx,double cy,double cz,GLuint imageTop, GLuint image){
   glPushMatrix(); 
	   glTranslatef(px,py,pz);
	   if(degRotate != 0 )
	       glRotatef(degRotate,rx,ry,rz);

	   glScalef(cx,cy,cz);
		 
		 glPushMatrix(); 

		   glTranslatef(0,0,14);
		     glPushMatrix(); 
			   glColor3f(1,1,1);
			   glScalef(10,20,25);
			   glutSolidCube(1);
		     glPopMatrix();

			 //texture
			 glPushMatrix(); 
			    glTranslatef(-5.2,-10,-12);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(0,0,25);
						
					    glTexCoord2f(1,1);
						glVertex3f(0,20,25);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,20,0);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();


			 glPushMatrix(); // right
			    glTranslatef(5.1,-10,-12);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(0,0,25);
						
					    glTexCoord2f(1,1);
						glVertex3f(0,20,25);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,20,0);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();


			 glPushMatrix();  // front
			    glTranslatef(-5.2,-10.1,-12);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(10.3,0,0);
						
					    glTexCoord2f(1,1);
						glVertex3f(10.3,0,25);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,0,25);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();

			 glPushMatrix();  // back
			    glTranslatef(-5.2,10.1,-12);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(10.3,0,0);
						
					    glTexCoord2f(1,1);
						glVertex3f(10.3,0,25);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,0,25);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();


         glPopMatrix();  // main block

		 glPushMatrix(); 
		   glTranslatef(0,1,28.5);
		   glRotatef(deg,1,0,0);
		     glPushMatrix(); 
			 
			   glScalef(10,20,10);
			   glutSolidCube(1);
		     glPopMatrix();

			  glPushMatrix(); 
			     glTranslatef(-5,-10,5.1);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, imageTop);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(10,0,0);
						
					    glTexCoord2f(1,1);
						glVertex3f(10,20,0);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,20,0);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();

			 glPushMatrix(); 
			  glTranslatef(-5.1,-10,-5);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(0,0,10);
						
					    glTexCoord2f(1,1);
						glVertex3f(0,20,10);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,20,0);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();

			 glPushMatrix(); 
			  glTranslatef(5.1,-10,-5);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(0,0,10);
						
					    glTexCoord2f(1,1);
						glVertex3f(0,20,10);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,20,0);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();
			 
         glPopMatrix();

	glPopMatrix();
}


void blockNormal (double px,double py,double pz, double cx,double cy,double cz, GLuint imageTop, GLuint image){
   glPushMatrix(); 
	   glTranslatef(px,py,pz);
	   
	   glScalef(cx,cy,cz);
		 
		 glPushMatrix(); 
		   glTranslatef(0,0,14);
		     glPushMatrix(); 
			   glColor3f(1,1,1);
			   glScalef(10,20,25);
			   glutSolidCube(1);
		     glPopMatrix();

			 //texture
			 glPushMatrix(); 
			    glTranslatef(-5.2,-10,-12);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(0,0,25);
						
					    glTexCoord2f(1,1);
						glVertex3f(0,20,25);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,20,0);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();


			 glPushMatrix(); // right
			    glTranslatef(5.1,-10,-12);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(0,0,25);
						
					    glTexCoord2f(1,1);
						glVertex3f(0,20,25);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,20,0);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();


			 glPushMatrix();  // front
			    glTranslatef(-5.2,-10.1,-12);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(10.3,0,0);
						
					    glTexCoord2f(1,1);
						glVertex3f(10.3,0,25);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,0,25);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();

			  glPushMatrix();  // back
			    glTranslatef(-5.2,10.05,-12);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(10.3,0,0);
						
					    glTexCoord2f(1,1);
						glVertex3f(10.3,0,25);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,0,25);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();

			 glPushMatrix();  // up
			   glTranslatef(-5.2,-10.1,13);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, imageTop);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(10,0,0);
						
					    glTexCoord2f(1,1);
						glVertex3f(10,20,0);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,20,0);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();


         glPopMatrix();  // main block

		 

	glPopMatrix();
}

void middleZone(double px,double py,double pz){
  glPushMatrix(); 
	   glTranslatef(px,py,pz);

	    glPushMatrix(); 
		
		 
		/*glPushMatrix(); 
		   glTranslatef(0,0,10);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,pillar_wall);

			   glColor3f(1,1,1);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj,GL_TRUE);
				gluCylinder(obj, 5,10,20,20,20);
			glDisable(GL_TEXTURE_2D);
		 glPopMatrix();
		 */
		glEnable(GL_TEXTURE_2D);
		  glBindTexture(GL_TEXTURE_2D,pillar_wall);

		   glColor3f(1,1,1);
			GLUquadricObj *obj = gluNewQuadric();
			gluQuadricTexture(obj,GL_TRUE);
			gluSphere(obj,20,30,30);
		glDisable(GL_TEXTURE_2D);


	  glPopMatrix();
	glPopMatrix();
}

void upperGombuje(double px,double py,double pz,double sx,double sy,double sz,GLuint imageTop,GLuint image){
             glPushMatrix();
			   glTranslatef(px,py,pz);
			   glScalef(sx,sy,sz);

			        double equ[4];
						equ[0] = 0;
						equ[1] = 0;
						equ[2] = 1;
						equ[3] = -1;
						glClipPlane(GL_CLIP_PLANE0,equ);
						glEnable(GL_CLIP_PLANE0);
				       glEnable(GL_TEXTURE_2D);
					   glBindTexture(GL_TEXTURE_2D,imageTop);

					   glColor3f(1,1,1);
						GLUquadricObj *obj = gluNewQuadric();
						gluQuadricTexture(obj,GL_TRUE);
						gluSphere(obj,20,20,20);
					glDisable(GL_TEXTURE_2D);
					glDisable(GL_CLIP_PLANE0);
			 glPopMatrix(); // upper gombuje
}

void sideHouse(double px,double py,double pz,double sx,double sy,double sz){
	 glPushMatrix(); 
	   glTranslatef(px,py,pz);
	   glScalef(sx,sy,sz);

	    glPushMatrix(); 
		
		 glPushMatrix(); 
		   glTranslatef(0,0,10);
			glEnable(GL_TEXTURE_2D);
			   glBindTexture(GL_TEXTURE_2D,wall);

			   glColor3f(1,1,1);
				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj,GL_TRUE);
				gluCylinder(obj, 10,10,30,40,40);
			glDisable(GL_TEXTURE_2D);
		 glPopMatrix();

		glPushMatrix(); 
		   glTranslatef(0,0,10);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,wall);

			   glColor3f(1,1,1);
				GLUquadricObj *obj1 = gluNewQuadric();
				gluQuadricTexture(obj1,GL_TRUE);
				gluCylinder(obj1, 11,11,25,40,40);
			glDisable(GL_TEXTURE_2D);
		 glPopMatrix();

		 upperGombuje(0,0,39,0.5,0.5,0.5,pillar_wall,wall);

	  glPopMatrix();
	glPopMatrix();
}

void middleHouse(double px,double py,double pz,double sx,double sy,double sz,GLuint imageTop,GLuint image){
  glPushMatrix(); 
	   glTranslatef(px,py,pz);
	   glScalef(sx,sy,sz);

	    glPushMatrix(); 
		
		glPushMatrix(); //mansion
			glTranslatef(0,0,25);
		  	 glScalef(30,30,50);
			 glutSolidCube(1);
			glPopMatrix();
          
			blockNormal(0,0,0,3.5,2,1.2,pillar_wall,wall);
			sideHouse(-18,0,0,0.8,0.8,1);
			sideHouse( 18,0,0,0.8,0.8,1);
          //texture
			 glPushMatrix(); 
			    glTranslatef(-15.1,-15,0);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(0,0,50);
						
					    glTexCoord2f(1,1);
						glVertex3f(0,30,50);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,30,0);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();


			 glPushMatrix(); // right
			 glTranslatef(15.1,-15,0);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(0,0,50);
						
					    glTexCoord2f(1,1);
						glVertex3f(0,30,50);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,30,0);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();


			 glPushMatrix();  // front
			 glTranslatef(-15,-15.1,0);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(30.3,0,0);
						
					    glTexCoord2f(1,1);
						glVertex3f(30.3,0,50);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,0,50);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();

			  glPushMatrix();  // back
			    glTranslatef(-15,15.1,0);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, image);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(30.3,0,0);
						
					    glTexCoord2f(1,1);
						glVertex3f(30.3,0,50);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,0,50);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();

			 glPushMatrix();  // up
			 glTranslatef(-15.1,-15,50.1);
				 glEnable(GL_TEXTURE_2D);
				 glBindTexture(GL_TEXTURE_2D, imageTop);

					glColor3f(1,1,1);
					glBegin(GL_QUADS);
					    glTexCoord2f(0,0);
						glVertex3f(0,0,0);
					    glTexCoord2f(0,1);
						glVertex3f(30,0,0);
						
					    glTexCoord2f(1,1);
						glVertex3f(30,30,0);
						
					    glTexCoord2f(1,0);
						glVertex3f(0,30,0);
					glEnd();

				glDisable(GL_TEXTURE_2D);
		     glPopMatrix();

			 upperGombuje(0,0,49,0.7,0.7,0.7,pillar_wall,wall);

			 // gombuje cone
			  glPushMatrix();  // minar

			  glTranslatef(0,0,59);
				 glPushMatrix();
				  glEnable(GL_TEXTURE_2D);
				  glBindTexture(GL_TEXTURE_2D,wall);
		 		  glutSolidCone(1,15,20,20);
				  glDisable(GL_TEXTURE_2D);
				 glPopMatrix();
		     glPopMatrix(); // minar end


	  glPopMatrix();
	glPopMatrix();
}


void display(){
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glMatrixMode(GL_MODELVIEW);		
	glLoadIdentity();				
	gluLookAt(cameraRadius*sin(cameraAngle), -cameraRadius*cos(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	glMatrixMode(GL_MODELVIEW);
	drawGridAndAxes();

 

	/*
	glEnable(GL_TEXTURE_2D);
	   glBindTexture(GL_TEXTURE_2D,ballimg);

	   glColor3f(1,1,1);
		GLUquadricObj *obj = gluNewQuadric();
		gluQuadricTexture(obj,GL_TRUE);
		gluSphere(obj,20,30,30);
	glDisable(GL_TEXTURE_2D); */
	
	
	
	blockNormal(-40,0,0,0.5,3,1,pillar_wall,wall);
	blockNormal(-32.5,0,0,1,3,0.9,pillar_wall,wall);
	
	block(-46,0,0,-90,0,0,1,35,4,.5,0.7,pillar_wall,wall);

	blockNormal(-48.5,-3,1,1.2,2.5,0.3,pillar_wall,blockWhite);

	pilar(-46,-24,0,1,1,1,cylimg,brick_wall2);

	blockNormal(-56,-26,1,1.2,0.4,0.7,pillar_wall,blockWhite);

	block(-50,-10,1,-90,0,0,1,35,0.3,1,0.5,blockTop,blockWhite);
	block(-50, 0,1,-90,0,0,1,35,0.3,1,0.5,blockTop,blockWhite);
	block(-50, 10,1,-90,0,0,1,35,0.3,1,0.5,blockTop,blockWhite);

	//left back pillar
	pilar(-46, 24,0,1,1,1,cylimg,brick_wall2);
	blockNormal(-55,22,0,1,0.1,0.7,pillar_wall,blockWhite);
	blockNormal(-60,22,0.5,0.7,0.1,0.4,pillar_wall,blockWhite);
	// left side complete 

	// front side
	block(-5,-25,0,0,0,0,1,35,0.7,1,0.8,pillar_wall,blockWhite);
	block(10,-25,0,0,0,0,1,35,0.6,1.1,0.8,pillar_wall,blockWhite);
	block(25,-25,0,0,0,0,1,35,1,1,0.8,pillar_wall,blockWhite);

	block(41,-25,0,0,0,0,1,35,2,1,0.4,pillar_wall,blockWhite);

	blockNormal(41,-23,10,0.5,0.8,0.8,pillar_wall,blockWhite);
	blockNormal(48,-20,0,0.5,0.2,1.2,pillar_wall,blockWhite);

	// right side pillar

	pilar(58, -20,0,1,1,1,cylimg,brick_wall2);

	block(50,-13,0,90,0,0,1,35,0.5,1.2,0.7,pillar_wall,blockWhite);
	blockNormal(58,-20,0,1,0.5,0.7,pillar_wall,blockWhite);

	// big panel
	blockNormal(55,0,0,0.4,3,0.3,pillar_wall,blockWhite);
	block(50,-5,0,90,0,0,1,35,0.3,1.2,0.7,pillar_wall,blockWhite);
	
	block(50,5,0,90,0,0,1,35,0.3,1.2,0.7,pillar_wall,blockWhite);
    
	block(50,15,0,90,0,0,1,35,0.8,1.2,0.7,pillar_wall,blockWhite);

	// back side
	pilar(58, 28,0,1,1,1,cylimg,brick_wall2);

	block(47,28,0,90,0,0,1,35,0.9,0.6,0.7,pillar_wall,blockWhite);

	// back side started
	block(25,30,0,180,0,0,1,35,0.8,1,0.7,pillar_wall,blockWhite);
	block(10,28,0,180,0,0,1,35,0.6,0.7,0.7,pillar_wall,blockWhite);
	block(-5,30,0,180,0,0,1,35,0.9,1,0.7,pillar_wall,blockWhite); 


	middleHouse(0,15,0,0.8,0.8,1,brick_wall2,wall);

	

	glutSwapBuffers();
}

void animate(){

	//cameraAngle += cameraAngleDelta;
	glutPostRedisplay();	//this will call the display AGAIN

}

void init(){
	//codes for initialization
	loadImage();
	
	helper_x = 0;
	helper_y = 0;
	helper_z = 0;

	move_X = 0;
	move_Y = 0;
	move_Z = 0;
	canDrawGrid = 1;
	canDrawAxis = 1;

	cameraAngleDelta = .1;


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
			helper_x += 1;
			break;

		case 'o':
			helper_x -= 1;
			break;
		case 'i':
			helper_y += 1;
			break;

		case 'u':
			helper_y -= 1;
			break;

		case 'y':
			helper_z += 1;
			break;

		case 't':
			helper_z -= 1;
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
	
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(100, 100);

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
