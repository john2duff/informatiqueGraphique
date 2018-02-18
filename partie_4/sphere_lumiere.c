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
	switch(selection){
		case 0:
			lum_ambiante[0]=0;
			lum_ambiante[1]=0;
			lum_ambiante[2]=0;
            break;
		case 1:
			if (lum_ambiante[0]<1.0){
				lum_ambiante[0]+=0.25;
				lum_ambiante[1]+=0.25;
				lum_ambiante[2]+=0.25;
			}
			break;
		case 2:
			if (lum_ambiante[0]>0.0){
				lum_ambiante[0]-=0.25;
				lum_ambiante[1]-=0.25;
				lum_ambiante[2]-=0.25;
			}
			break;
    }
	glLightfv(GL_LIGHT0,GL_AMBIENT,lum_ambiante);
	glutPostRedisplay();
}
void LumiereDiffuse(int selection){
	switch(selection){
		case 0:
			lum_diffuse[0]=0;
			lum_diffuse[1]=0;
			lum_diffuse[2]=0;
            break;
		case 1:
			if (lum_diffuse[0]<1.0){
				lum_diffuse[0]+=0.25;
				lum_diffuse[1]+=0.25;
				lum_diffuse[2]+=0.25;
			}
			break;
		case 2:
			if (lum_diffuse[0]>0.0){
				lum_diffuse[0]-=0.25;
				lum_diffuse[1]-=0.25;
				lum_diffuse[2]-=0.25;
			}
			break;
    }
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lum_diffuse);
    glutPostRedisplay();
}
void LumiereSpeculaire(int selection){
	switch(selection){
		case 0:
			lum_speculaire[0]=0;
			lum_speculaire[1]=0;
			lum_speculaire[2]=0;
            break;
		case 1:
			if (lum_speculaire[0]<1.0){
				lum_speculaire[0]+=0.25;
				lum_speculaire[1]+=0.25;
				lum_speculaire[2]+=0.25;
			}
			break;
		case 2:
			if (lum_speculaire[0]>0.0){
				lum_speculaire[0]-=0.25;
				lum_speculaire[1]-=0.25;
				lum_speculaire[2]-=0.25;
			}
			break;
    }
    glLightfv(GL_LIGHT0,GL_SPECULAR,lum_speculaire);
    glutPostRedisplay();
}
void Lumiere(int selection){
	switch(selection){
		case 0:
			glDisable(GL_LIGHT0);
			break;
		case 1:
			glEnable(GL_LIGHT0);
			break;
	}
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
    glutAddSubMenu("Lumiere Ambiante",mAmbiante);
    glutAddSubMenu("Lumiere Diffuse",mDiffuse);
    glutAddSubMenu("Lumiere Speculaire",mSpeculaire);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
    glMaterialf(GL_FRONT,GL_SHININESS,shininess);
	glLightfv(GL_LIGHT0,GL_AMBIENT,lum_ambiante);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lum_diffuse);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,1.0); //Obligatoire pour pos observateur !
	information=1;
}
