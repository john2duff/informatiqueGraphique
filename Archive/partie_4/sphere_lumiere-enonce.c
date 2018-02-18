#include "../base.c"
char name[]="Sphere eclairee";
char message[200];
static float shininess=10.0;
static float lum_ambiante[] = {0.5,0.5,0.5,0.5};
static float lum_diffuse[] = {0.5,0.5,0.5,0.5};
static float lum_speculaire[] = {0.5,0.5,0.5,0.5};
static float lum_pos[] = {2.0,2.0,2.0,1.0};
static float mat_ambiante[] =  {1.0,1.0,1.0,1.0};
static float mat_diffuse[]  =  {1.0,1.0,1.0,1.0};
static float mat_speculaire[] = {1.0,1.0,1.0,1.0};

void clavier(unsigned char key){}
void redimension(int width, int height){}
void anime(){
	sprintf(message,"ambiante=%1.3f,diffuse=%1.3f,speculaire=%1.3f",
            lum_ambiante[0],lum_diffuse[0],lum_speculaire[0]);
	glutPostRedisplay();
}

void description(){
	//Position de la lumiere (non fixe avec l'animation)
	glLightfv(GL_LIGHT0,GL_POSITION,lum_pos);
	glutSolidSphere(0.5,10,10);
}

void LumiereAmbiante(int selection){
	// A ecrire
	glutPostRedisplay();
}
void LumiereDiffuse(int selection){
	// A ecrire
    glutPostRedisplay();
}
void LumiereSpeculaire(int selection){
	// A ecrire
    glutPostRedisplay();
}
void Lumiere(int selection){
	// A ecrire
	glutPostRedisplay();
}

void initialisation(){
	int mAmbiante,mDiffuse,mSpeculaire,mLumiere;
    
	mAmbiante=glutCreateMenu(LumiereAmbiante);
    glutAddMenuEntry("Eteindre",0);
    glutAddMenuEntry("+",1);
    glutAddMenuEntry("-",2);
    
	mDiffuse=glutCreateMenu(LumiereDiffuse);
    glutAddMenuEntry("Eteindre",0);
    glutAddMenuEntry("+",1);
    glutAddMenuEntry("-",2);
	mSpeculaire=glutCreateMenu(LumiereSpeculaire);
    glutAddMenuEntry("Eteindre",0);
    glutAddMenuEntry("+",1);
    glutAddMenuEntry("-",2);
	mLumiere=glutCreateMenu(Lumiere);
    glutAddMenuEntry("Tout Eteindre",0);
    glutAddMenuEntry("Tout Allumer",1);
    glutAddSubMenu("Lumière Ambiante",mAmbiante);
    glutAddSubMenu("Lumière Diffuse",mDiffuse);
    glutAddSubMenu("Lumière Spéculaire",mSpeculaire);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	information=1;
	// Definir lumiere materiaux de la lumiere 0
	// A ecrire
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,1.0); //Obligatoire pour pos observateur !
}
