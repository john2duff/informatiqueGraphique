#include "../base.c"
char name[]="Tore !"; //Nom de la fenetre principale
char message[200];
//Dessin de la fenetre principale
void description(){
    glColor3dv(ORANGE);
    glutWireTorus(0.25,0.35,10,10);
}
void anime(void){
    xr=xr+0.1;
    yr=zr=xr;
    glutPostRedisplay();
}
void initialisation(){}
void clavier(unsigned char key){}
void redimension(int width, int height){}

