#include "../base.c"
char name[]="Nos fonctions";
char message[200];
int typeProjection=0; 
int f2; //Identificateur deuxieme fenetre

void perspectiveFonction( double gauche, double droite,
		      		    double bas, double haut,
					        double proche, double loin);
void perspectiveFocaleFonction(double focy,double aspect, 
                       double proche, double loin);
void paralleleFonction(	double gauche,double droite,
				        double bas, double haut,
		    	      double proche, double loin );

void redimension(int width, int height) {
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
  	switch (typeProjection){
		case 0:
			paralleleFonction(-1.1*coord,1.1*coord,-1.1*coord,1.1*coord, 
												coord, 3*coord);
			sprintf(message,"Projection parallele");	    
			break;
		case 1 : 
    	perspectiveFonction(-0.55*coord,0.55*coord,-0.55*coord,0.55*coord, 
													coord, 3*coord);
			sprintf(message,"Projection perspective");
			break;
		case 2 :
			perspectiveFocaleFonction(2*180/M_PI*atan(0.55),1,coord, 3*coord);
			sprintf(message,"Projection perspective focale");
			break;
		}
		glMatrixMode(GL_MODELVIEW);
}

void redimension2(int width, int height) {
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
  	switch (typeProjection){
		case 0:
			glOrtho(-1.1*coord,1.1*coord,-1.1*coord,1.1*coord, 
												coord, 3*coord);	    
			break;
		case 1 : 
    	glFrustum(-0.55*coord,0.55*coord,-0.55*coord,0.55*coord, 
													coord, 3*coord);
			break;
		case 2 :
			gluPerspective(2*180/M_PI*atan(0.55),1,coord, 3*coord);
			break;
		}
		glMatrixMode(GL_MODELVIEW);
}
void description2(){
	redimension(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity(); 
  glTranslated(0,0,-2*coord); //reculer la scene
  glRotated(xr,1,0,0); //Rotation de la scene 
  glRotated(yr,0,1,0);
  glRotated(zr,0,0,1);
 	glColor3dv(BLEU); //Scene a afficher
 	dessin_axes(ROUGE,VERT,BLEU);
	glutWireCube(1);
  glFlush(); //valider les modification de la scène 
  glutSwapBuffers(); //rendre l'affichage plus fluide
}

void menuScene(int selection){
	typeProjection = selection;
	redimension(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
	glutPostRedisplay();
}
void initialisation(){
	int mScene;
	mScene=glutCreateMenu(menuScene);
  glutAddMenuEntry("Parallele",0);
  glutAddMenuEntry("Perspective",1);
  glutAddMenuEntry("Perspective focale",2);  	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	char name2[]="Fonction glut / glu"; //Nom fenetre secondaire
	glutInitWindowSize(TAILLE_FENETRE,TAILLE_FENETRE);
  glutInitWindowPosition(POSITION_FENETRE,POSITION_FENETRE+TAILLE_FENETRE);
	f2=glutCreateWindow(name2); //Creer la fenetre
  glutReshapeFunc(resize); //fonction associee au redimensionnement de la fenetre
  glutDisplayFunc(description2); //fonction associee a l'affichage
	glClearColor(1,1,1,1); //Couleur du fond
	information=1; //Informations affichees par defaut
	axe=1; //Afficher les axes
	information=1;
}
void description(){
	glColor3dv(ROUGE);
	glutWireCube(1);
	glutPostWindowRedisplay(f2); //Actualiser la fenetre f2
}
void clavier(unsigned char touche){}
void anime(){}

void perspectiveFonction( double gauche, double droite,
		      		    double bas, double haut,
					        double proche, double loin ) {
	double m[16];
	#define M(row,col)  m[col*4+row]
	// A ecrire
	#undef M
	glMultMatrixd(m);
}
void paralleleFonction(	double gauche,double droite,
				        double bas, double haut,
		    	      double proche, double loin )
{
  double m[16];
	#define M(row,col)  m[col*4+row]
// A ecrire
	#undef M
	glMultMatrixd(m);
}

void perspectiveFocaleFonction(double focy,double aspect, 
                       double proche, double loin){
		//A ecrire
}
