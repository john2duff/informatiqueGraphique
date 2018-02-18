#include "../base.c"
char name[]="Translation et rotation  !";
int scene = 0;
char message[200];

void maisonPleine(GLdouble x,GLdouble y);
void maisonLigne(GLdouble x,GLdouble y);

void description(){
	//Repere lie a l'objet
  //Maison a l'origine
  glColor3d(1,0,0);
  maisonPleine(0,0);
  switch (scene){
		case 0: //T puis R 
  		glPushMatrix();
  		glTranslated(0.75,0,0);
  		dessin_axes(ORANGE,VIOLET,BLEU);
  		maisonLigne(0,0);
  		glRotatef(45,0,0,1);
  		dessin_axes(ROUGE,VERT,BLEU);  		
  		glColor3d(1,0,1);
  		maisonPleine(0,0);  
  		glPopMatrix();
  		break;
  	case 1: //R puis T
  		glPushMatrix();
  		glRotatef(45,0,0,1);
			maisonLigne(0,0);
  		dessin_axes(ORANGE,VIOLET,BLEU);
  		glTranslatef(0.75,0,0);
  		glColor3d(1,1,0);
  		maisonPleine(0,0); 
  		dessin_axes(ROUGE,VERT,BLEU);
  		glPopMatrix();
		}	
}

void menuScene(int selection){
	scene=selection;
	glutPostRedisplay();
}

//Mes initialisations 
void initialisation(){
	//Creation du menu bouton droit de la souris
	int mScene;
	mScene=glutCreateMenu(menuScene);
  glutAddMenuEntry("Translation puis rotation",0);
  glutAddMenuEntry("Rotation puis translation",1);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  information=1;
}

void maisonPleine(double x,double y){
  glPushMatrix();
  glTranslatef(x,y,0);
  glutSolidCube(0.25);
  glTranslatef(0,0.25/2,0);
  glRotatef(45,0,0,1);
  glutSolidCube(0.25/sqrt(2));
  glPopMatrix();
}

void maisonLigne(double x,double y){
  glPushMatrix();
  glTranslatef(x,y,0);
  glutWireCube(0.25);
  glTranslatef(0,0.25/2,0);
  glRotatef(45,0,0,1);
  glutWireCube(0.25/sqrt(2));
  glPopMatrix();
}

void anime(){
	switch(scene){
		case 0 :
			sprintf(message,"Translation puis rotation"); 
			break;
		case 1 :
			sprintf(message,"Rotation puis translation");
			break;
	}
}

void clavier(unsigned char key){}
void redimension(int width, int height){}
