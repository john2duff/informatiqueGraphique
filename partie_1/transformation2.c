#include "../base.c"
char name[]="Rotation Translation et facteur d'echelle !";
char message[200];
int scene=0;
void menuScene(int selection){
	scene = selection;    }
//Mes initialisations 
void initialisation(){
	int mScene;
	mScene=glutCreateMenu(menuScene);
	glutAddMenuEntry("E puis R",0);
	glutAddMenuEntry("R puis E",1);
  glutAddMenuEntry("T puis R",2);
	glutAddMenuEntry("R puis T",3);
	glutAddMenuEntry("T puis R puis E",4);
	glutAddMenuEntry(" E puis T puis R",5);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  coord = 2;
  information=1;
  division=16;
  quadrillage=1;
	}
void anime(){
		switch (scene){
		case 0:
			sprintf(message,"Echelle puis rotation");
			break;
		case 1:
			sprintf(message,"Rotation puis echelle");
			break;
		case 2:
			sprintf(message,"Translation puis rotation z");
			break;
		case 3:
			sprintf(message,"Rotation z puis translation");
			break;
		case 4:
			sprintf(message,"Translation puis rotation z  puis echelle");
			break;
		case 5:
			sprintf(message,"Echelle puis translation puis rotation z");
			break;
	}
	glutPostRedisplay();
}
void clavier(unsigned char key){}
void redimension(int width, int height){}
//Description de la scene
void description(){
	switch (scene){
		case 0:
			glColor3dv(VIOLET);
			glScaled(1,2,1);
			dessin_axes(ORANGE,VIOLET,BLEU);
			glRotated(90,0,0,1);
			break;
		case 1:
			glColor3dv(VIOLET);
			glRotated(90,0,0,1);
			dessin_axes(ORANGE,VIOLET,BLEU);
			glScaled(1,2,1);
			break;
		case 2:
			glColor3dv(ORANGE);
			//Translation puis Rotation triangle exo theorique
			glTranslated(0.5,0.75,-0.5);
			dessin_axes(ORANGE,VIOLET,BLEU);
			glRotated(90,0,0,1);
			break;
		case 3:
			glColor3dv(VIOLET);
			//Rotation puis translation triangle exo theorique
			glRotated(90,0,0,1);
			dessin_axes(ORANGE,VIOLET,BLEU);
			glTranslated(0.75,-0.5,-0.5);
			break;
		case 4:
			//Translation puis Rotation puis Echelle triangle exo theorique
			glColor3dv(VIOLET);
			glTranslated(0.5,0.75,-0.5);
			dessin_axes(ORANGE,VIOLET,BLEU);
			glRotated(90,0,0,1);
			dessin_axes(ORANGE,VIOLET,BLEU);
			glScaled(1,2,1);
			break;
		case 5:
			//Echelle puis Translation puis Rotation triangle exo theorique
			glColor3dv(NOIR);
			glScaled(2,1,1);
			dessin_axes(ORANGE,VIOLET,BLEU);
			glTranslated(0.5/2,0.75/1,-0.5);
			dessin_axes(ORANGE,VIOLET,BLEU);
			glRotated(90,0,0,1);
			break;
	}
	dessin_axes(ROUGE,VERT,BLEU);
	glBegin(GL_POLYGON);
	glVertex3d(0,0,0);
	glVertex3d(0,0.5,0);
	glVertex3d(0.25,0,0);
	glEnd();
	glutPostRedisplay();
}
