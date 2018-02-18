#include "../base.c"
char name[]="Texture marbre !";
char message[200];

#define L 128
#define H 128
char filename1[]="marbre.raw";

static GLubyte image [L*H*3];

void anime(){}
void clavier(unsigned char key){}
void redimension(int width, int height){}

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
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);
    glVertex2f(-0.5,-0.5);
    glTexCoord2f(0.0,1.0);
    glVertex2f(-0.5,0.5);
    glTexCoord2f(1.0,1.0);
    glVertex2f(0.5,0.5);
    glTexCoord2f(1.0,0.0);
    glVertex2f(0.5,-0.5);
    glEnd();
}
void initialisation(){
    lectureTexture(filename1,L,H);
    glTexImage2D(GL_TEXTURE_2D ,0,GL_RGB,L,H,0,GL_RGB,GL_UNSIGNED_BYTE,image);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glEnable(GL_TEXTURE_2D);
}
