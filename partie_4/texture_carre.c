#include "../base.c"
char name[]="Texture carre!";
char message[200];

#define H 32
#define L 32
GLubyte image [L][H][3];

void makeImage(void) {
   int i,j,c;
   for( i = 0 ; i < L ; i++ ) {
      for(j = 0 ; j < H ; j++ ) {
         c = (((i&0x8)==0)^ ((j&0x8)==0))*255;
         image[i][j][0] =(GLubyte) c;
         image[i][j][1] =(GLubyte) c;
         image[i][j][2] =(GLubyte) c; } } }
void anime(){}
void clavier(unsigned char key){}
void redimension(int width, int height){}

void description(){
   glBegin(GL_POLYGON);
   glTexCoord2f(0.0,0.0);
   glVertex2f(-0.75,-0.75);
   glTexCoord2f(0.0,1.0);
   glVertex2f(-0.75,0.75);
   glTexCoord2f(1.0,1.0);
   glVertex2f(0.75,0.75);
   glTexCoord2f(1.0,0.0);
   glVertex2f(0.75,-0.75);
   glEnd();
}
void initialisation(){
   makeImage(); 
   glTexImage2D(GL_TEXTURE_2D ,0,GL_RGB,L,H,0,GL_RGB,GL_UNSIGNED_BYTE,image);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	 glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
   glEnable(GL_TEXTURE_2D);
}

