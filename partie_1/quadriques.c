#include "../base.c"
char name[]="Quadriques";
char message[200];
int scene = 0;
int f2;

void solidCylinder(double base,double height,int slice,int stack);
void wireCylinder(double base,double height,int slice,int stack);
void solidCone(double base,double height,int slice,int stack);
void wireCone(double base,double height,int slice,int stack);
void solidSphere(double radius, int slice,int stack);
void wireSphere(double radius,int slice,int stack);
void anime(){}

void description(){
	glColor3dv(ROUGE);
	switch (scene){
		case 0: wireCylinder(0.25,0.5,30,10);
						sprintf(message,"wireCylinder");break;
		case 1: solidCylinder(0.25,0.5,30,10);
						sprintf(message,"solidCylinder");break;
		case 2:	wireCone(0.25,0.5,30,10);
						sprintf(message,"wireCone");break;
		case 3:	solidCone(0.25,0.5,30,10);
						sprintf(message,"solidCone");break;
		case 4:	wireSphere(0.5,30,10);
						sprintf(message,"wireSphere");break;
		case 5:	solidSphere(0.5,30,10);
						sprintf(message,"solidSphere");break;
	}
	glutPostWindowRedisplay(f2); //Actualiser la fenetre f2
}
void description2(){
    char rien[]="pas de primitive GLUT";
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslated(0,0,-2*coord); //reculer la scene
    glRotated(xr,1,0,0); //Rotation de la scene
    glRotated(yr,0,1,0);
    glRotated(zr,0,0,1);
	glColor3dv(ROUGE);
	switch (scene){
		case 0:  affiche_chaine(ORIGINE,rien,ROUGE);break;
		case 1:  affiche_chaine(ORIGINE,rien,ROUGE);break;
		case 2:	glutWireCone(0.25,0.5,30,10);break;
		case 3:	glutSolidCone(0.25,0.5,30,10);break;
		case 4:	glutWireSphere(0.5,30,10);break;
		case 5:	glutSolidSphere(0.5,30,10);break;
	}
	glFlush(); //valider les modification de la scène 
  glutSwapBuffers(); //rendre l'affichage plus fluide
}

void menuScene(int selection){
	scene=selection;
	glutPostRedisplay();
}
//Mes initialisations 
void initialisation(){
	//Creation du menu bouton droit de la souris
	int mScene;
	mScene=glutCreateMenu(menuScene);
  glutAddMenuEntry("Cylindre fil de fer",0);
  glutAddMenuEntry("Cylindre plein",1);
  glutAddMenuEntry("Cone fil de fer",2);
  glutAddMenuEntry("Cone plein",3);
  glutAddMenuEntry("Sphere fil de fer",4);
  glutAddMenuEntry("Sphere pleine",5);  
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  char name2[]="glut..."; //Nom fenetre secondaire
	glutInitWindowSize(TAILLE_FENETRE,TAILLE_FENETRE);
  glutInitWindowPosition(POSITION_FENETRE,POSITION_FENETRE+TAILLE_FENETRE);
	f2=glutCreateWindow(name2); //Creer la fenetre
  glutReshapeFunc(resize); //fonction associee au redimensionnement de la fenetre
  glutDisplayFunc(description2); //fonction associee a l'affichage
	glClearColor(1,1,1,1); //Couleur du fond
	glEnable(GL_DEPTH_TEST); //Etudie plus tard...
}
void clavier(unsigned char key){}
void redimension(int width, int height){}

void wireCylinder(double base,double height,int slice,int stack){
	double theta,z=-height/2;
	int i,j;
	double zStep = height / (double)stack;
	double tStep = 2 * M_PI / (double) slice;
	//Les stacks
	for(i=0;i<=stack;i++){ 
		glBegin(GL_LINE_LOOP);
			theta =  M_PI /2;
				for(j=0;j<=slice;j++){
					glVertex3d(base*cos(theta),base*sin(theta),z);
					theta = theta + tStep;
				}
				z = z + zStep;
		glEnd();
	}
	//Les slides
	theta =  M_PI /2;
	glBegin(GL_LINES);
		for(i=0;i<=slice;i++){
			glVertex3d(base*cos(theta),base*sin(theta),height/2);
			glVertex3d(base*cos(theta),base*sin(theta),-height/2);
			theta = theta + tStep;
		}
	glEnd();
}
void solidCylinder(double base,double height,int slice,int stack){
	double theta=0,z=-height/2;
	int i,j;
	double zStep = height / (double)stack;
	double tStep = 2 * M_PI / (double) slice;
	glBegin(GL_TRIANGLE_FAN);
		glVertex3d(0,0,z);
		for(i=0;i<=slice;i++){
			glVertex3d(base*cos(theta),base*sin(theta),z);
			theta = theta + tStep;
		}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
		glVertex3d(0,0,-z);
		for(i=0;i<=slice;i++){
			glVertex3d(base*cos(theta),base*sin(theta),-z);
			theta = theta + tStep;
		}
	glEnd();
	for(i=0;i<stack;i++){
		glBegin(GL_QUAD_STRIP);
			theta = - M_PI;
				for(j=0;j<=slice;j++){
					glVertex3d(base*cos(theta),base*sin(theta),z);
					glVertex3d(base*cos(theta),base*sin(theta),z+zStep);
					theta = theta + tStep;
				}
				z = z + zStep;
		glEnd();
	}
}
void solidCone(double base,double height,int slice,int stack){
	double theta=0,z=0,r=base;
	int i,j;
	double zStep = height / (double)stack;
  double rStep = base / (double)stack;
	double tStep = 2 * M_PI / (double) slice;
	glBegin(GL_TRIANGLE_FAN);
		glVertex3d(0,0,z);
		for(i=0;i<=slice;i++){
			glVertex3d(r*cos(theta),r*sin(theta),z);
			theta = theta + tStep;
		}
	glEnd();
	for(i=0;i<stack;i++){
		glBegin(GL_QUAD_STRIP);
			theta = - M_PI;
				for(j=0;j<=slice;j++){
					glVertex3d(r*cos(theta),r*sin(theta),z);
					glVertex3d((r-rStep)*cos(theta),(r-rStep)*sin(theta),z+zStep);
					theta = theta + tStep;
				}
				z = z + zStep;
				r = r - rStep;
		glEnd();
	}
}

void wireCone(double base,double height,int slice,int stack){
	double theta,z=0,r=base;
	int i,j;
	double zStep = height / (double)stack;
  double rStep = base / (double)stack;
	double tStep = 2 * M_PI / (double) slice;
	//Les stacks
	for(i=0;i<stack;i++){ 
		glBegin(GL_LINE_LOOP);
			theta =  M_PI /2;
				for(j=0;j<=slice;j++){
					glVertex3d(r*cos(theta),r*sin(theta),z);
					theta = theta + tStep;
				}
				z = z + zStep;
				r = r - rStep;
		glEnd();
	}
	//Les slides
	theta =  M_PI /2;
	glBegin(GL_LINES);
		for(i=0;i<=slice;i++){
			glVertex3d(0,0,height);
			glVertex3d(base*cos(theta),base*sin(theta),0);
			theta = theta + tStep;
		}
	glEnd();
}
void solidSphere(double radius, int slice,int stack){
	double theta,phi,cost,costs,sint,sints,sinp,sinps,z,zs;
	int i,j;
	double incrSlice =  2 * M_PI / (double) slice;
	double incrStack =   M_PI / (double) stack;
	phi = 0; // Angle stack
	theta = 0; //Angle slice 
	for(i=0;i<slice;i++){
		cost=radius*cos(theta);sint=radius*sin(theta);
		costs=radius*cos(theta+incrSlice);sints=radius*sin(theta+incrSlice);
		phi=0;
		glBegin(GL_QUAD_STRIP);
		for(j=0;j<=stack;j++){
			z = radius * cos(phi); sinp = sin(phi);
			zs = radius * cos(phi+incrStack);sinps=sin(phi+incrStack);
				glVertex3d(cost*sinp,sint*sinp,z);
				glVertex3d(costs*sinp,sints*sinp,z);

			phi= phi + incrStack;
		}
		glEnd();
		theta = theta + incrSlice;
	}
}
void wireSphere(double radius, int slice,int stack){
	double theta,phi,cost,costs,sint,sints,sinp,sinps,z,zs;
	int i,j;
	double incrSlice =  2 * M_PI / (double) slice;
	double incrStack =   M_PI / (double) stack;
	phi = 0; // Angle stack
	theta = 0; //Angle slice 
	for(i=0;i<slice;i++){
		cost=radius*cos(theta);sint=radius*sin(theta);
		costs=radius*cos(theta+incrSlice);sints=radius*sin(theta+incrSlice);
		phi=0;
		for(j=0;j<=stack;j++){
			z = radius * cos(phi); sinp = sin(phi);
			zs = radius * cos(phi+incrStack);sinps=sin(phi+incrStack);
			glBegin(GL_LINE_LOOP);
				glVertex3d(cost*sinp,sint*sinp,z);
				glVertex3d(cost*sinps,sint*sinps,zs);
				glVertex3d(costs*sinps,sints*sinps,zs);
				glVertex3d(costs*sinp,sints*sinp,z);
			glEnd();
			phi= phi + incrStack;
		}
		theta = theta + incrSlice;
	}
}
