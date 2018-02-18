#include "../base.c"
char name[]="Notre scene";
char message[200]="Notre scene";
int scene=0;
void description(){
    int i;
    //Le plateau
    glColor3dv(ROUGE);
    glPushMatrix();
    // A ecrire
    glPopMatrix();
	//Les pieds
	glColor3dv(NOIR);
	glPushMatrix();
    // A ecrire
	glPopMatrix();
	//La theire 
	glColor3dv(VERT);
	glPushMatrix();
    // A ecrire
	glPopMatrix();
	//Les sieges 
	glColor3dv(VERT);
	glPushMatrix();
    // A ecrire
	glPopMatrix();
	//Le lampadaire
	glColor3dv(BLEU);
 	glPushMatrix();
    //A ecrire
	glPopMatrix();
	//Le plafonnier
 	glPushMatrix();
    // A ecrire
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
