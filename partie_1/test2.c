#include "../base.c"
char name[]="Big Teapot !"; //Nom de la fenetre principale
char message[200]="Deux fenetres"; //Message fenetre
int f2; //Identificateur fenetre secondaire
float xr2=0,yr2=0,zr2=0; //Position animation fenetre secondaire
//Dessin de la fenetre principale
void description(){
    glColor3dv(ORANGE);
    glutWireTeapot(0.5);
    glutPostWindowRedisplay(f2); //Actualiser la fenetre secondaire
}
//Dessin de la fenetre secondaire
void description2(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslated(0,0,-2*coord); //reculer la scene
    glRotated(xr2,1,0,0); //Rotation de la scene
    glRotated(yr2,0,1,0);
    glRotated(zr2,0,0,1);
    dessin_axes(NOIR,NOIR,NOIR);
    glColor3dv(BLEU); //Scene a afficher
    glutWireTorus(0.2,0.3,10,10);
    glFlush(); //valider les modification de la scene
    glutSwapBuffers(); //rendre l'affichage plus fluide
}
void anime(void){
    //Animation de la fenetre secondaire mouvement aleatoire
    xr2 = xr2+(float)(rand()%1000)/1000.0;
    yr2 = yr2+(float)(rand()%1000)/1000.0;
    zr2 = zr2+(float)(rand()%1000)/1000.0;
    glutPostRedisplay();
}
void initialisation(){
    //Nom et taille/position de la fenetre secondaire
    char name2[]="Tore !";
    glutInitWindowSize(TAILLE_FENETRE/2,TAILLE_FENETRE/2);
    glutInitWindowPosition(POSITION_FENETRE,POSITION_FENETRE+TAILLE_FENETRE);
    //Creer la fenetre
    f2=glutCreateWindow(name2);
    //fonction associee au redimensionnement de la fenetre
    glutReshapeFunc(resize);
    //fonction associee a l'affichage de la fenetre secondaire
    glutDisplayFunc(description2);
    glClearColor(1,1,1,1); //Couleur du fond
    information=1; //Informations sont affichees par defaut
    axe=1; //Afficher les axes
}
void clavier(unsigned char key){}
void redimension(int width, int height){}