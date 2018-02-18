#include "../base.c"
char name[]="Mappemonde et globe !";
char message[200];

#define L 512
#define H 512
char filename1[]="monde.raw";

int carte=0;

static GLubyte image [L*H*3];

void mappemonde();
void globe(float r,float slice);

void lectureTexture(char *fichier,int dx,int dy) {
    int i,j;
    FILE *f = fopen(fichier,"rb") ;
    if ( f ) {
        for ( i = 0 ; i < dx ; i++ )
            for ( j = 0 ; j < dy ; j++ )
                if (fread(&image[(j*dy+i)*3],1,3,f) !=3) {
                    printf("Erreur taille \n");
                    exit(-1);}
        fclose(f) ; }
    else{
        printf("Fichier non trouve !");
        exit(-1);}}




void description(){
    information=0; //Bloquer les informations probleme texture et caractères
    if (carte==0)
        mappemonde(0.75,10);
    else
        globe(0.5,20);
}
void anime(){}
void menu(int selection){
    carte = selection;
    glutPostRedisplay();
}
void initialisation(){
    lectureTexture(filename1,L,H);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,L,H,0,GL_RGB,GL_UNSIGNED_BYTE,image);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    //glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
    int m;
    m=glutCreateMenu(menu);
    glutAddMenuEntry("Mappemonde",0);
    glutAddMenuEntry("Globe",1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void clavier(unsigned char key){}
void redimension(int width, int height){}


void mappemonde(){
    // A ecrire
}

void globe(float r,float slice){
    // A ecrire
}
