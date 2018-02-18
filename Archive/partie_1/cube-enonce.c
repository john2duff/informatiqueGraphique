#include "../base.c"
char name[]="Cube avec les normales"; //Nom de la fenetre 
char message[200]; //Message fenetre
int scene=0;
int f2;

void wireCube(double taille);
void solidCube(double taille);
//Dessin de la fenetre principale
void description(){
	glColor3dv(ORANGE);
	switch(scene){
		case 0:
			wireCube(0.5);
			break;
		case 1:
			solidCube(0.5);
			break;
		}
	glutPostWindowRedisplay(f2); //Actualiser la fenetre f2
} 
void description2(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity(); 
  glTranslated(0,0,-2*coord); //reculer la scene
  glRotated(xr,1,0,0); //Rotation de la scene 
  glRotated(yr,0,1,0);
  glRotated(zr,0,0,1);
	glColor3dv(ORANGE);
	switch(scene){
		case 0:
			glutWireCube(0.5);
			break;
		case 1:
			glutSolidCube(0.5);
			break;
		}
	glFlush(); //valider les modification de la scène 
  glutSwapBuffers(); //rendre l'affichage plus fluide
}
void anime(){} 
void menuScene(int selection){
	scene = selection;    }
//Mes initialisations 
void initialisation(){
	int mScene;
	mScene=glutCreateMenu(menuScene);
  glutAddMenuEntry("wireCube",0);
  glutAddMenuEntry("solidCube",1);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
	perspective=1;
	
	char name2[]="glut...Cube"; //Nom fenetre secondaire
	glutInitWindowSize(TAILLE_FENETRE,TAILLE_FENETRE);
  glutInitWindowPosition(POSITION_FENETRE,POSITION_FENETRE+TAILLE_FENETRE);
	f2=glutCreateWindow(name2); //Creer la fenetre
  glutReshapeFunc(resize); //fonction associee au redimensionnement de la fenetre
  glutDisplayFunc(description2); //fonction associee a l'affichage
	glClearColor(1,1,1,1); //Couleur du fond
	glEnable(GL_DEPTH_TEST); //Etudie plus tard...
}
void clavier(unsigned char key){}
void redimension(int width, int height){}

void wireCube(double taille){
    double size = taille/2;
    double *c=VERT;
#define V(a,b,c) glVertex3d( a size, b size, c size ) // a,b,c : a remplacer pour + ou -
    glBegin( GL_LINE_LOOP );
    V(+,-,+);// glVertex3d(+ size,- size, + size)
    // A ecrire
    glEnd();

#undef V
    double o[]={0,0,0};
    double n0[]={ 1.0, 0.0, 0.0};
    affiche_vecteur(o,n0,c);
    // A ecrire
}

void solidCube(double taille){
    double *c=VERT;
    double size = taille/2;
#define V(a,b,c) glVertex3d( a size, b size, c size ) // a,b,c : a remplacer pour + ou -
    glBegin( GL_QUADS );
    V(+,-,+);
    // A ecrire
    glEnd();
#undef V
    double o[]={0,0,0};
    double n0[]={ 1.0, 0.0, 0.0};
    affiche_vecteur(o,n0,c);
    // A ecrire
}
