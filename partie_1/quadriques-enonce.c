#include "../base.c"
char name[]="Quadriques";
char message[200];
int scene = 0;
int f2;

void solidCylinder(double base,double height,int slice,int stack);
void wireCylinder(double base,double height,int slice,int stack);
void solidCone(double base,double height,int slice,int stack);
void wireCone(double base,double height,int slice,int stack);
void solidSphere(double radius, int slice,int stack);
void wireSphere(double radius,int slice,int stack);
void anime(){}
    
void description(){
    glColor3dv(ROUGE);
    switch (scene){
        case 0: wireCylinder(0.25,0.5,30,10);sprintf(message,"wireCylinder");break;
        case 1: solidCylinder(0.25,0.5,30,10);sprintf(message,"solidCylinder");break;
        case 2:	wireCone(0.25,0.5,30,10);sprintf(message,"wireCone");break;
        case 3:	solidCone(0.25,0.5,30,10);sprintf(message,"solidCone");break;
        case 4:	wireSphere(0.5,30,10);sprintf(message,"wireSphere");break;
        case 5:	solidSphere(0.5,30,10);sprintf(message,"solidSphere");break;
    }
    glutPostWindowRedisplay(f2); //Actualiser la fenetre f2
}
void description2(){
    char rien[]="pas de primitive GLUT";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslated(0,0,-2*coord); //reculer la scene
    glRotated(xr,1,0,0); //Rotation de la scene
    glRotated(yr,0,1,0);
    glRotated(zr,0,0,1);
    glColor3dv(ROUGE);
    switch (scene){
        case 0:  affiche_chaine(ORIGINE,rien,ROUGE);break;
        case 1:  affiche_chaine(ORIGINE,rien,ROUGE);break;
        case 2:	glutWireCone(0.25,0.5,30,10);break;
        case 3:	glutSolidCone(0.25,0.5,30,10);break;
        case 4:	glutWireSphere(0.5,30,10);break;
        case 5:	glutSolidSphere(0.5,30,10);break;
    }
    glFlush(); //valider les modification de la scene
    glutSwapBuffers(); //rendre l'affichage plus fluide
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
    glutAddMenuEntry("Cylindre fil de fer",0);
    glutAddMenuEntry("Cylindre plein",1);
    glutAddMenuEntry("Cone fil de fer",2);
    glutAddMenuEntry("Cone plein",3);
    glutAddMenuEntry("Sphere fil de fer",4);
    glutAddMenuEntry("Sphere pleine",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    char name2[]="glut..."; //Nom fenetre secondaire
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

void wireCylinder(double base,double height,int slice,int stack){
    // A ecrire
}

void solidCylinder(double base,double height,int slice,int stack){
    // A ecrire
}

void solidCone(double base,double height,int slice,int stack){
    // A ecrire
}

void wireCone(double base,double height,int slice,int stack){
    // A ecrire
}

void solidSphere(double radius, int slice,int stack){
    // A ecrire
}
void wireSphere(double radius, int slice,int stack){
    // A ecrire
}
