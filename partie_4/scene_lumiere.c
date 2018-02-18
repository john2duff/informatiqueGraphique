#include "../base.c"
char name[]="Notre scene en lumiere";
char message[200];
int lampadaire=0,plafonnier=0,fenetre=0;
//Materiaux tous noirs pour simplifier
static float mat_ambiante[] =   {1.0,1.0,1.0,1.0};
static float mat_diffuse[]  =   {1.0,1.0,1.0,1.0};
static float mat_speculaire[] = {1.0,1.0,1.0,1.0};
static float shininess=10.0;

//La lumiere ambiante bleue
static float lum_pos_fenetre[] = {0,0,1.0,1.0};
static float lum_ambiante_fenetre[] = {0.0,0.5,1.0,1.0};

//Lampadaire jaune
static float lum_pos_lampadaire[] = {-0.85,0.55+0.1,-0.85,1.0};
static float lum_ambiante_lampadaire[] = {0,0,0,1.0};
static float lum_diffuse_lampadaire[] = {1.0,1.0,0.0,1.0};
static float lum_speculaire_lampadaire[] = {1.0,1.0,0,1.0};

//Plafonnier blanc
static float lum_pos_plafonnier[] = {0.0,0.95,0.0,1.0};
static float lum_ambiante_plafonnier[] = {0,0,0,1.0};
static float lum_diffuse_plafonnier[] = {1,1,1,1.0};
static float lum_speculaire_plafonnier[] = {1,1,1,1.0};

void cylinder(GLdouble rayon,GLdouble hauteur,int slices);

void description(){
    int i;
    glClearColor(0,0,0,1) ;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //Le plateau
    glPushMatrix();
   	glScaled(0.9,0.1,0.9);
  	glutSolidCube(1);
    glPopMatrix();
    //Les pieds
    glPushMatrix();
    glRotated(45,0,1,0);
    for(i=0;i<4;i++){
        glPushMatrix();
        glTranslated(0.35*sqrt(2),-0.3,0.0);
        glScaled(0.05,0.5,0.1);
  		glutSolidCube(1);
        glPopMatrix();
        glRotated(90,0,1,0);
    }
    glPopMatrix();
    //La theire
    glPushMatrix();
    glTranslated(-0.0,0.12,0.0);
  	glutSolidTeapot(0.1);
    glPopMatrix();
    //Les sieges
    glPushMatrix();
    for(i=0;i<4;i++){
        glRotated(90,0,1,0);
        glPushMatrix();
        glTranslated(0.75,-0.45,0.0);
        glRotated(45,0,1,0);
        glScaled(0.2,0.2,0.2);
  		glutSolidCube(1);
        glPopMatrix();
    }
    glPopMatrix();
    //Le lampadaire
    glPushMatrix();
    glTranslated(-0.85,-0,-0.85);
    cylinder(0.01,1.1,10);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-0.85,0.55+0.1,-0.85);
  	glutSolidSphere(0.1,10,10);
    glPopMatrix();
    //Le plafonnier
    glPushMatrix();
    glTranslated(0,0.95,0);
    glRotated(90,1,0,0);
  	glutSolidTorus(0.05,0.1,10,10);
    glPopMatrix();
}

void menu(int selection){
    switch(selection){
		case 0 : lampadaire=1;glEnable(GL_LIGHT1);break;
		case 1 : lampadaire=0;glDisable(GL_LIGHT1);break;
		case 2 : plafonnier=1;glEnable(GL_LIGHT2);break;
		case 3 : plafonnier=0;glDisable(GL_LIGHT2);break;
		case 4 : fenetre=1;glEnable(GL_LIGHT0);break;
		case 5 : fenetre=0;glDisable(GL_LIGHT0);break;
	}
    glutPostRedisplay();
}

void initialisation(){
    int m;
    m=glutCreateMenu(menu);
    glutAddMenuEntry("Allumer lampadaire",0);
    glutAddMenuEntry("Eteindre lampadaire",1);
    glutAddMenuEntry("Allumer plafonnier",2);
    glutAddMenuEntry("Eteindre plafonnier",3);
    glutAddMenuEntry("Ouvrir fenetre",4);
    glutAddMenuEntry("Fermer Fenetre",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
 	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiante);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
 	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
 	glMaterialf(GL_FRONT,GL_SHININESS,shininess);
    
	//Caracteristique fenetre
	glLightfv(GL_LIGHT0,GL_AMBIENT,lum_ambiante_fenetre);
	glLightfv(GL_LIGHT0,GL_POSITION,lum_pos_fenetre);
	//Caracteristique lampadaire
	glLightfv(GL_LIGHT1,GL_AMBIENT,lum_ambiante_lampadaire);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,lum_diffuse_lampadaire);
	glLightfv(GL_LIGHT1,GL_SPECULAR,lum_speculaire_lampadaire);
	glLightfv(GL_LIGHT1,GL_POSITION,lum_pos_lampadaire);
	//Caracteristique plafonnier
	glLightfv(GL_LIGHT2,GL_AMBIENT,lum_ambiante_plafonnier);
	glLightfv(GL_LIGHT2,GL_DIFFUSE,lum_diffuse_plafonnier);
	glLightfv(GL_LIGHT2,GL_SPECULAR,lum_speculaire_plafonnier);
	glLightfv(GL_LIGHT2,GL_POSITION,lum_pos_plafonnier);
}


void cylinder(double rayon,double hauteur,int slices){
    int i;
    for(i=0;i<=slices;i++){
        glBegin(GL_QUADS );
        glVertex3d(rayon*sin(2*M_PI/slices*i),-hauteur/2,
                   rayon*cos(2*M_PI/slices*i));
        glVertex3d(rayon*sin(2*M_PI/slices*i),hauteur/2,
                   rayon*cos(2*M_PI/slices*i));
        glVertex3d(rayon*sin(2*M_PI/slices*(i+1)),hauteur/2,
                   rayon*cos(2*M_PI/slices*(i+1)));
        glVertex3d(rayon*sin(2*M_PI/slices*(i+1)),-hauteur/2,
                   rayon*cos(2*M_PI/slices*(i+1)));
        glEnd();
    }
}
void clavier(unsigned char key){}
void redimension(int width, int height){}
void anime(){
	sprintf(message,"Lampadaire=%d, plafonnier=%d, fenetre=%d",
            lampadaire,plafonnier,fenetre);
    glutPostRedisplay();
}
