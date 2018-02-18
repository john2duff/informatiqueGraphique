#include "../base.c"
char name[]="RegarderVers";
char message[200];
int f2; //Identificateurs deuxieme fenetre

//Position oeil et du haut
double oeil[]={0,0,1};
double haut[]={0.707,0.707,0.0};
double centre[]={0.0,0.0,0.0};

void RegarderVers(GLdouble oeil_x, GLdouble oeil_y, GLdouble oeil_z,
                  GLdouble centre_x, GLdouble centre_y, GLdouble centre_z,
                  GLdouble haut_x, GLdouble haut_y, GLdouble haut_z);

void description(){
    glRotated(-zr,0,0,1); //Annuler les rotations precedentes...
    glRotated(-yr,0,1,0);
    glRotated(-xr,1,0,0);
    glTranslated(0,0,2*coord); //Remettre la scene en 0
    oeil[0]= xr/100.0;oeil[1]= yr/100.0;// Deplacement oeil (plutot que rotation)
	RegarderVers(oeil[0],oeil[1],oeil[2],
                 centre[0],centre[1],centre[2],
                 haut[0],haut[1],haut[2]);
    dessin_axes(ROUGE_FONCE,VERT_FONCE,BLEU_FONCE);
    glColor3dv(ORANGE);
	glutWireCube(0.5);
	glutPostWindowRedisplay(f2); //Actualiser la fenetre f2
}

void description2(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(oeil[0],oeil[1],oeil[2],
              centre[0],centre[1],centre[2],
              haut[0],haut[1],haut[2]);
    dessin_axes(ROUGE_FONCE,VERT_FONCE,BLEU_FONCE);
	glColor3dv(ORANGE);
	glutWireCube(0.5);
	glFlush(); //valider les modification de la scene
    glutSwapBuffers(); //rendre l'affichage plus fluide
}

void anime(){
    sprintf(message,"Position oeil x= %.2f, y= %.2f, z= %2f", oeil[0],oeil[1],oeil[2]);
	glutPostRedisplay();
}

void initialisation(){
	char name2[]="gluLookAt"; //Nom fenetre secondaire
	glutInitWindowSize(TAILLE_FENETRE,TAILLE_FENETRE);
    glutInitWindowPosition(POSITION_FENETRE+TAILLE_FENETRE,POSITION_FENETRE+TAILLE_FENETRE);
	f2=glutCreateWindow(name2); //Creer la fenetre
    glutReshapeFunc(resize); //fonction associee au redimensionnement de la fenetre
    glutDisplayFunc(description2); //fonction associee a l'affichage
	glClearColor(1,1,1,1); //Couleur du fond
    information=1;
}
void clavier(unsigned char key){}
void redimension(int width, int height){}

void RegarderVers(GLdouble oeil_x, GLdouble oeil_y, GLdouble oeil_z,
                  GLdouble centre_x, GLdouble centre_y, GLdouble centre_z,
                  GLdouble haut_x, GLdouble haut_y, GLdouble haut_z){
	GLdouble m[16];
    GLdouble x[3], y[3], z[3];
    GLdouble mag;
    // Vecteur Z normalise
    z[0] = (oeil_x - centre_x);
    z[1] = (oeil_y - centre_y);
    z[2] = (oeil_z - centre_z);
    mag = sqrt(z[0] * z[0] + z[1] * z[1] + z[2] * z[2]);
    if (mag!=0) {
		z[0] = z[0] /mag;
		z[1] = z[1] /mag;
		z[2] = z[2] /mag;}
    y[0] = haut_x; y[1] = haut_y; y[2] = haut_z;
    mag = sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);
    if (mag!=0) {
        y[0] = y[0] /mag;
        y[1] = y[1] /mag;
        y[2] = y[2] /mag;}
    // x  = y ^ z
    x[0] = y[1] * z[2] - y[2] * z[1];
    x[1] = -y[0] * z[2] + y[2] * z[0];
    x[2] = y[0] * z[1] - y[1] * z[0];
    mag = sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
    if (mag!=0) {
        x[0] = x[0] /mag;
        x[1] = x[1] /mag;
        x[2] = x[2] /mag;}
    // y = z ^ x
    y[0] = z[1] * x[2] - z[2] * x[1];
    y[1] = -z[0] * x[2] + z[2] * x[0];
    y[2] = z[0] * x[1] - z[1] * x[0];
    mag = sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);
    if (mag!=0) {
        y[0] = y[0] /mag;
        y[1] = y[1] /mag;
        y[2] = y[2] /mag;
    }
    #define M(row,col) m[col*4+row]
    M(0, 0) = x[0]; M(0, 1) = x[1]; M(0, 2) = x[2]; M(0, 3) = 0.0;// x = y^z
    M(1, 0) = y[0]; M(1, 1) = y[1]; M(1, 2) = y[2]; M(1, 3) = 0.0;// y = z^x
    M(2, 0) = z[0]; M(2, 1) = z[1]; M(2, 2) = z[2]; M(2, 3) = 0.0;// z = z
    M(3, 0) = 0.0; M(3, 1) = 0.0; M(3, 2) = 0.0; M(3, 3) = 1.0;
#undef M
    glMultMatrixd(m);
    // Translater les yeux a l'origine
    glTranslated(-oeil_x, -oeil_y, -oeil_z);
}
