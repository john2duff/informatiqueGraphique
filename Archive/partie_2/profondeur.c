#include "../base.c"
char name[]="Test profondeur ";
char message[200];
int elimination=0;
void description(){
  if (elimination==1)
		glEnable(GL_DEPTH_TEST); 
	else
		glDisable(GL_DEPTH_TEST); 
  glColor3dv(BLEU); 
  glutSolidCube(0.5);
  glTranslatef(0,0.5,-1);
  glColor3dv(ROUGE); 
  glutSolidSphere(0.5,100,100);
}
void clavier(unsigned char key){
	  switch (key) 
    {
    case 'e' :
				elimination=0;
				break;
		case 'E':
				elimination=1;
	}			 
}
void anime(){
	if (elimination==1)
		sprintf(message,"Avec elimination des parties cachees"); 
	else
		sprintf(message,"Sans elimination des parties cachees");
	glutPostRedisplay();
}
	
void initialisation(){
	information=1;}
void redimension(int width, int height){}
