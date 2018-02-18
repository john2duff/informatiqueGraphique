#include "../base.c"
char name[]="Notre cube eclaire"; //Nom de la fenetre
char message[200]; //Message fenetre
int f2;

float lum_pos[]        = {2.0,2.0,2.0,0.0};

float lum_ambiante[]   = {0.0,0.0,0.0,1.0};
float lum_diffuse[]    = {1.0,1.0,1.0,1.0};
float lum_speculaire[] = {1.0,1.0,1.0,1.0};
float mat_ambiante[]   = {0,0,0,0};
float mat_diffuse[]    = {1.0,1.0,1.0,1.0};
float mat_speculaire[] = {1.0,1.0,1.0,1.0};
float shininess =10;

void solidCube(double size);
void solidCube2(double size);

//Dessin de la fenetre principale
void description(){
	glLightfv(GL_LIGHT0,GL_POSITION,lum_pos);
	//solidCube(2);
	solidCube2(2);
	glutPostWindowRedisplay(f2); //Actualiser la fenetre f2
}

void description2(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    initprojection(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
    glTranslated(0,0,-2*coord); //reculer la scene
    glRotated(xr,1,0,0); //Rotation de la scene
    glRotated(yr,0,1,0);
    glRotated(zr,0,0,1);
 	glLightfv(GL_LIGHT0,GL_POSITION,lum_pos);
	glutSolidCube(2.0);
	glFlush(); //valider les modification de la scène
    glutSwapBuffers(); //rendre l'affichage plus fluide
}
void anime(){	}
void deplaceSouris(int x,int y){
	float res;
	int xf = glutGet(GLUT_WINDOW_WIDTH);
	int yf = glutGet(GLUT_WINDOW_HEIGHT);
	glReadPixels(x,yf-y,1,1,GL_RED,GL_FLOAT,&res);
	sprintf(message,"x=%d,y=%d,c=%f",x,y,res);
	glutPostRedisplay();
}
void initialisation(){
	glutPassiveMotionFunc(deplaceSouris);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float local = 1.0f;
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER,&local);
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
    glMaterialf(GL_FRONT,GL_SHININESS,shininess);
	glLightfv(GL_LIGHT0,GL_AMBIENT,lum_ambiante);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lum_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,lum_speculaire);
	glEnable(GL_NORMALIZE);
	char name2[]="glutWireCube"; //Nom fenetre secondaire
	glutInitWindowSize(TAILLE_FENETRE,TAILLE_FENETRE);
    glutInitWindowPosition(POSITION_FENETRE,POSITION_FENETRE+TAILLE_FENETRE);
	f2=glutCreateWindow(name2); //Creer la fenetre
    glutReshapeFunc(resize); //fonction associee au redimensionnement de la fenetre
    glutDisplayFunc(description2); //fonction associee a l'affichage
	glClearColor(1,1,1,1); //Couleur du fond
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER,&local);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
	glMaterialf(GL_FRONT,GL_SHININESS,shininess);
	glLightfv(GL_LIGHT0,GL_AMBIENT,lum_ambiante);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lum_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,lum_speculaire);
	information=1;
}
void clavier(unsigned char key){}
void redimension(int width, int height){}
void solidCube(double taille){
    double size = taille/2;
#   define V(a,b,c) glVertex3d( a size, b size, c size )
#   define N(a,b,c) glNormal3d( a, b, c );
    glBegin( GL_QUADS );
    N( 1.0, 0.0, 0.0); V(+,-,+); V(+,-,-); V(+,+,-); V(+,+,+);
    N( 0.0, 1.0, 0.0); V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+);
    N( 0.0, 0.0, 1.0); V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+);
    N(-1.0, 0.0, 0.0); V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-);
    N( 0.0,-1.0, 0.0); V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+);
    N( 0.0, 0.0,-1.0); V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-);
    glEnd();
#   undef V
#   undef N
}
void solidCube2(double taille){
    glPushMatrix();
    glRotated(-90,0,0,1);
    solidCube(taille);
    glPopMatrix();
}
