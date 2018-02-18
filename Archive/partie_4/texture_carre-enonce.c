#include "../base.c"
char name[]="Texture carre !";
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
		// A ecrire
   glVertex2f(-0.75,-0.75);
		// A ecrire
   glVertex2f(-0.75,0.75);
		// A ecrire
   glVertex2f(0.75,0.75);
		// A ecrire
   glVertex2f(0.75,-0.75);
   glEnd();
}
void initialisation(){
   makeImage();
	 //Parametre texture 
	// A ecrire
}
