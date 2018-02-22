#include "base.c"
#define ATTENTE 3 //ajuster la vitesse des animations
char name[] = "Primitives graphiques OpenGL"; //Nom de la fenetre 
char message[200]; //Message fenetre
int scene = 0;
int parcours = 1; //démarrage avec l'animation des primitives
int attente = 300; //temps d'attente en cours

//points de la scene
double p0[] = { -0.5,0.5,0 }, p1[] = { -0.35,-0.35,0 }, p2[] = { -0.25,-0.35,0 }, p3[] = { 0,-0.5,0 };
double p4[] = { 0.25,-0.35,0 }, p5[] = { 0.55,0.25,0 }, p6[] = { 0.75,0.25,0 }, p7[] = { 0.85,0.75,0 };

//fenêtre principale
void description() {
	switch (scene) {
	case 0: glPointSize(5); glBegin(GL_POINTS); sprintf(message, "GL_POINT"); break;
	case 1: glBegin(GL_LINES); sprintf(message, "GL_LINES"); break;
	case 2: glBegin(GL_LINE_STRIP); sprintf(message, "GL_LINE_STRIP"); break;
	case 3: glBegin(GL_LINE_LOOP); sprintf(message, "GL_LINE_LOOP"); break;
	case 4: glBegin(GL_QUADS); sprintf(message, "GL_QUADS"); break;
	case 5: glBegin(GL_QUAD_STRIP); sprintf(message, "GL_QUAD_STRIP"); break;
	case 6: glBegin(GL_POLYGON); sprintf(message, "GL_POLYGON"); break;
	case 7: glBegin(GL_TRIANGLES); sprintf(message, "GL_TRIANGLES"); break;
	case 8: glBegin(GL_TRIANGLE_STRIP); sprintf(message, "GL_TRIANGLE_STRIP"); break;
	case 9: glBegin(GL_TRIANGLE_FAN); sprintf(message, "GL_TRIANGLE_FAN"); break;
	}

	//Affiche la primitive 
	glColor3dv(ROUGE), glVertex3dv(p0); glColor3dv(VERT); glVertex3dv(p1); glColor3dv(BLEU); glVertex3dv(p2);
	glColor3dv(JAUNE); glVertex3dv(p3); glColor3dv(NOIR); glVertex3dv(p4); glColor3dv(ORANGE); glVertex3dv(p5);

	glColor3dv(VIOLET); glVertex3dv(p6); glColor3dv(TURQUOISE); glVertex3dv(p7); glEnd();
	//Affiche les points 
	glPointSize(5); glBegin(GL_POINTS);
	glColor3dv(ROUGE), glVertex3dv(p0);
	glColor3dv(VERT); glVertex3dv(p1);
	glColor3dv(BLEU); glVertex3dv(p2);
	glColor3dv(JAUNE); glVertex3dv(p3);
	glColor3dv(NOIR); glVertex3dv(p4);
	glColor3dv(ORANGE); glVertex3dv(p5);
	glColor3dv(VIOLET); glVertex3dv(p6);
	glColor3dv(TURQUOISE); glVertex3dv(p7); glEnd();
	//Affiche numero des points 
	affiche_caractere(p0, '0', NOIR); affiche_caractere(p1, '1', NOIR);
	affiche_caractere(p2, '2', NOIR); affiche_caractere(p3, '3', NOIR);
	affiche_caractere(p4, '4', NOIR); affiche_caractere(p5, '5', NOIR);
	affiche_caractere(p6, '6', NOIR); affiche_caractere(p7, '7', NOIR);
}

//Animation de la fenetre principale
void anime() {
	if (parcours == 1) {
		if (attente > ATTENTE) {
			scene = (scene + 1) % 9; 
			attente = 0;//reinitailisation attente
			glutPostRedisplay();//Rafraichir l’affichage de la scene
		}
		else attente++;//attendre
	}
}
void menuScene(int selection) {
	scene = selection;
	parcours = 0;//arreter l’animation
	if (selection == 10) {
		parcours = 1;//lancer l’animation
		scene = 0;//premiere primitive de l’animation 
	}
	glutPostRedisplay();//Rafraichir l’affichage de la scene
}
void initialisation() {
	//Creation du menu bouton droit de la souris 
	int mScene;
	mScene = glutCreateMenu(menuScene);
	glutAddMenuEntry("GL_POINTS", 0);
	glutAddMenuEntry("GL_LINES", 1);
	glutAddMenuEntry("GL_LINE_STRIP", 2);
	glutAddMenuEntry("GL_LINE_LOOP", 3);
	glutAddMenuEntry("GL_QUADS", 4);
	glutAddMenuEntry("GL_QUAD_STRIP", 5);
	glutAddMenuEntry("GL_POLYGON", 6);
	glutAddMenuEntry("GL_TRIANGLES", 7);
	glutAddMenuEntry("GL_TRIANGLE_STRIP", 8);
	glutAddMenuEntry("GL_TRIANGLE_FAN", 9);
	glutAddMenuEntry("ANIMATION", 10);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	information = 1; //affiche les infos des boutons
}
void clavier(unsigned char key) {}
void redimension(int width, int height) {}