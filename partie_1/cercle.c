#include "../base.c"
#define N 20
char name[]="Cercle";
char message[200];
void description(){
    double p0[]={0,0,0}; //centre
    int i;
    glColor3dv(ROUGE);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3dv(p0);
    for(i=0 ;i<= N;i++){
        glVertex3d(cos((double)i/N*2*M_PI),sin((double)i/N*2*M_P),0);
    }
    glEnd();
}
void initialisation(){}
void clavier(unsigned char key){}
void redimension(int width, int height){}
void anime(){}
