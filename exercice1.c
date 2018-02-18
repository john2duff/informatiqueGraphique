#include "base.c"
char name[] = "Jooohn"; //Nom de la fenetre 
char message[200]; //Message fenetre

//Dessin de la fenetre principale
void description() {
	glColor3dv(BLEU);
	glutWireCube(1);
}
//Animation de la fenetre principale
void anime() {
	if (axe)
		sprintf(message, "Msg statique : Hello world - Msg dynamique : Axes affiches");
	else
		sprintf(message, "Msg statique : Hello world - Msg dynamique : Axes non affiches");
	glutPostRedisplay();
}
void initialisation() {}
void clavier(unsigned char key) {}
void redimension(int width, int height) {}