#include "../base.c"
char name[]="Notre scene";
char message[200]="Notre scene";
int scene=0;
void description(){
	 int i;
	 //Le plateau
	 glColor3dv(ROUGE);
	 glPushMatrix();
     glScaled(0.9,0.1,0.9);
	 if (scene==0){
 		glutWireCube(1);}
	 else{
  		glutSolidCube(1);
	}
	glPopMatrix();
	//Les pieds
	glColor3dv(NOIR);
	glPushMatrix();
	glRotated(45,0,1,0);
	for(i=0;i<4;i++){
 		glPushMatrix();
 		glTranslated(0.35*sqrt(2),-0.3,0.0);
 		glScaled(0.05,0.5,0.1);
		 if (scene==0){
 			glutWireCube(1);}
	 	else{
  			glutSolidCube(1);
		}
 		glPopMatrix();
 		glRotated(90,0,1,0);
	}
	glPopMatrix();
	//La theire 
	glColor3dv(VERT);
	glPushMatrix();
	glTranslated(-0.0,0.12,0.0);
	 if (scene==0){
 		glutWireTeapot(0.1);;}
	 else{
  		glutSolidTeapot(0.1);
	}
	glPopMatrix();
	//Les sieges 
	glColor3dv(VERT);
	glPushMatrix();
	for(i=0;i<4;i++){
		glRotated(90,0,1,0);
		glPushMatrix();
		glTranslated(0.75,-0.45,0.0);
		glRotated(45,0,1,0);
		glScaled(0.2,0.2,0.2);
		if (scene==0){
 			glutWireCube(1);}
	 	else{
  			glutSolidCube(1);
		}
		glPopMatrix();
	}
	glPopMatrix();
	//Le lampadaire
	glColor3dv(BLEU);
 	glPushMatrix();
 	glTranslated(-0.85,-0.55,-0.85);
 	glRotated(-90,1,0,0);
	if (scene==0){
		glutWireCone(0.05,1.1,10,10);}
	else{
		glutSolidCone(0.05,1.1,10,10);
	}
 	glPopMatrix();
	glPushMatrix();
	glTranslated(-0.85,0.55+0.1,-0.85);	
	if (scene==0){
 		glutWireSphere(0.1,10,10);;}
	else{
  		glutSolidSphere(0.1,10,10);
	}
	glPopMatrix();
	//Le plafonnier
 	glPushMatrix();
	glTranslated(0,0.95,0);
	glRotated(90,1,0,0);
	 if (scene==0){
 		glutWireTorus(0.05,0.1,10,10);}
	 else{
  		glutSolidTorus(0.05,0.1,10,10);
	}
 	glPopMatrix();
}
void menu(int selection){
     scene = selection;
     	glutPostRedisplay();
}
void initialisation(){
     int m;
     m=glutCreateMenu(menu);
     glutAddMenuEntry("Fils de Fer",0);
     glutAddMenuEntry("Plein",1);
     glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void clavier(unsigned char key){}
void redimension(int width, int height){}
void anime(){}
