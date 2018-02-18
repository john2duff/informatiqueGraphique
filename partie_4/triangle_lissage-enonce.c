#include "../base.c"
#include "sys/time.h"

//Macro MIN et MAX pour calcul des intensites
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

char name[]="Triangle lissee Gouraud/Phong";
char message[200];
typedef double Point[3];
typedef	double Vecteur[3];
int typeLissage = 0 ; //  Meme normale 0 gouraud, 1 phong
//Normal diff    2 gouraud, 3 phong
int f2;

clock_t c1,c2; //Mesure du nombre de tics horloge pour afficher triangle

Vecteur N={0,0,1}; // Normale dans le premier cas
Vecteur N1={0.577,-0.577,0.577};	//Normale dans le deuxieme cas
Vecteur N2={0.577,0.577,0.577};
Vecteur N3={-0.577,0.577,0.577};

Point L={2,2,2};
Point O={0,0,2};

float LOpenGL[]={2,2,2,1}; //Position lumiere pour OpenGL
float OOpenGL[]={0,0,2,1};


void pixel2coord(int l,int c,int xf,int yf, double *x,double *y);
void PointVecteurNormaliser(Point p1,Point p2,Vecteur v);// v <- ^(p2p1)
double ProduitScalaire(Vecteur u,Vecteur v);// <- u . v
void MultiplicationScalaire(double alpha,Vecteur v1,Vecteur v);// v <- alpha . v1
void SoustractionVecteur(Vecteur v2,Vecteur v1,Vecteur v);//v <- v2 - v1
void AdditionVecteur(Vecteur v2,Vecteur v1,Vecteur v);//v <- v2 + v1
double Norme(Vecteur v);//  <- ||v||
void Normaliser(Vecteur v1,Vecteur v);//v <- ||v1||
void AffichePoint3D(Point p,double c);


double LumiereDiffuse(Vecteur N,Vecteur L);
double LumiereSpeculaire(Vecteur N,Vecteur L, Vecteur O);
//Meme normale sur le triangle
void Gouraud(Vecteur N, Point L, Point O);
void Phong(Vecteur N,Point L, Point O);
//Normales differents sur le triangle
void Gouraud2(Vecteur N1,Vecteur N2,Vecteur N3, Point L, Point O);
void Phong2(Vecteur N1,Vecteur N2,Vecteur N3,Point L, Point O);

//Interpolation lineaire sur valeur (Gouraud calcul intensite)
double interpolationReel(double y, double ymin, double ymax, double ipb,double iph);

//Interpolation lineaire sur vecteur (Phong calcul normale)
void interpolationVecteur(double y, double ymin, double ymax,
                          Vecteur vb,Vecteur vh,Vecteur res);

void PointVecteurNormaliser(Point p1,Point p2,Vecteur v){
    v[0] = p2[0] - p1[0];v[1] = p2[1] - p1[1];v[2] = p2[2] - p1[2];
    Normaliser(v,v);}
double ProduitScalaire(Vecteur u,Vecteur v){
	return (u[0] * v[0] + u[1] * v[1] + u[2] * v[2]);}
void MultiplicationScalaire(double alpha,Vecteur v1,Vecteur v){
	v[0] = v1[0] * alpha;v[1] = v1[1] * alpha; v[2] = v1[2] * alpha; }
void SoustractionVecteur(Vecteur v2,Vecteur v1,Vecteur v){
	v[0] = v2[0] - v1[0];	v[1] = v2[1] - v1[1];	v[2] = v2[2] - v1[2];}
void AdditionVecteur(Vecteur v2,Vecteur v1,Vecteur v){
	v[0] = v2[0] + v1[0];	v[1] = v2[1] + v1[1]; 	v[2] = v2[2] + v1[2];}
double Norme(Vecteur v){ return sqrt(ProduitScalaire(v,v));}
void Normaliser(Vecteur v1,Vecteur v){ MultiplicationScalaire(1/Norme(v1),v1,v);}
void AffichePoint3D(Point p,double c){
	glColor3d(c,c,c);
	glPointSize(1);
	glBegin(GL_POINTS);
	glVertex3d(p[0],p[1],p[2]);
	glEnd();
}
//Conversion coordonnee souris en coordonnee reelle [-1,=1]
//pour affichage position souris dans message
void pixel2coord(int l,int c,int xf,int yf, double *x,double *y){
	double co=coord+0.1;
	*x= 2*co*l /(double)xf - co;
	*y=  -2 *co*c /(double)yf + co;
}
//Fonction callback deplacement souris, mdification message
void deplaceSouris(int x,int y){
	float res;
	double xcoord,ycoord;
	int xf = glutGet(GLUT_WINDOW_WIDTH);
	int yf = glutGet(GLUT_WINDOW_HEIGHT);
	glReadPixels(x,yf-y,1,1,GL_RED,GL_FLOAT,&res);
	pixel2coord(x,y,xf,yf,&xcoord,&ycoord);
	switch (typeLissage){
		case 0:
			sprintf(message,"Gouraud meme normale x=%f,y=%f,c=%f",xcoord,ycoord,res);
			break;
		case 1:
			sprintf(message,"Phong meme normale x=%f,y=%f,c=%f",xcoord,ycoord,res);
			break;
		case 2:
			sprintf(message,"Gouraud normale diff x=%f,y=%f,c=%f",xcoord,ycoord,res);
			break;
		case 3:
			sprintf(message,"Phong normale diff x=%f,y=%f,c=%f",xcoord,ycoord,res);
	}
	glutPostRedisplay();
}
void description(){
	char temps[100]; //Pour afficher le temps en tics d'horloge
	Point ptemps={-1,-1,1};
	c1 = clock();
	switch (typeLissage){
		case 0: Gouraud(N,L,O); break;
		case 2: Gouraud2(N1,N2,N3,O,O); break;
		case 1: Phong(N,L,O); break;
		case 3: Phong2(N1,N2,N3,O,O); break;
	}
	c2 = clock();
	c2 = c2-c1;
	sprintf(temps,"Temps calcul facette : %d",(int)c2);
	affiche_chaine(ptemps,temps,NOIR);
	glutPostWindowRedisplay(f2);
}
void description2(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslated(0,0,-2*coord); //reculer la scene
    glRotated(xr,1,0,0); //Rotation de la scene
    glRotated(yr,0,1,0);
    glRotated(zr,0,0,1);
	switch (typeLissage){
		case 0:
		case 1:
			glLightfv(GL_LIGHT0,GL_POSITION,LOpenGL);
			glBegin(GL_TRIANGLES);
			glNormal3dv(N);
			glVertex3d(1,-1,1);
			glVertex3d(-1,1,1);
			glVertex3d(1,1,1);
			glEnd();
			break;
		case 2:
		case 3:
			glLightfv(GL_LIGHT0,GL_POSITION,OOpenGL);
			glBegin(GL_TRIANGLES);
			glNormal3dv(N1);
			glVertex3d(1,-1,1);
			glNormal3dv(N3);
			glVertex3d(-1,1,1);
			glNormal3dv(N2);
			glVertex3d(1,1,1);
			glEnd();
			break;
	}
	glFlush(); //valider les modification de la scène
    glutSwapBuffers(); //rendre l'affichage plus fluide
}

void anime(){}
void initialisation(){
	glutPassiveMotionFunc(deplaceSouris);
	information=1;
	char name2[]="OpenGL"; //Nom fenetre secondaire
	glutInitWindowSize(TAILLE_FENETRE,TAILLE_FENETRE);
    glutInitWindowPosition(POSITION_FENETRE,POSITION_FENETRE+TAILLE_FENETRE);
	f2=glutCreateWindow(name2); //Creer la fenetre
    glutReshapeFunc(resize); //fonction associee au redimensionnement de la fenetre
    glutDisplayFunc(description2); //fonction associee a l'affichage
	glClearColor(1,1,1,1); //Couleur du fond
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float ambiante[]={0,0,0,1};
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambiante);
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambiante);
	float diffuse_speculaire[]={1,1,1,1};
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_speculaire);
    glMaterialfv(GL_FRONT,GL_SPECULAR,diffuse_speculaire);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse_speculaire);
	glLightfv(GL_LIGHT0,GL_SPECULAR,diffuse_speculaire);
 	glMaterialf(GL_FRONT,GL_SHININESS,10.0);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,1.0); //Obligatoire pour pos observateur !
}
//Touche L pour modifier le type de lissage
void clavier(unsigned char key){
	if (key=='L') typeLissage = (typeLissage + 1)%4;
	deplaceSouris(0,0); //Pour modifier la chaine message
	glutPostRedisplay(); //Relancer l'affichage
}
void redimension(int width, int height){}

double interpolationReel(double y, double ymin, double ymax, double ipb,double iph){
	// y=ymin retourner ipb , y=ymax retourner iph
	// A ecrire
}

void interpolationVecteur(double y, double ymin, double ymax,
                          Vecteur vb,Vecteur vh,Vecteur res){
	// Si y=ymin retourner vb , si y=ymax retourner vh
	double coeff=(y-ymin)/(ymax-ymin);
	// A ecrire
	Normaliser(res,res);
}

double LumiereDiffuse(Vecteur N,Vecteur L){
	// A ecrire
}
double LumiereSpeculaire(Vecteur N,Vecteur L, Vecteur O){
	// A ecrire
}

void Gouraud(Vecteur N, Point L, Point O){
	Point p1={1,-1,1}; Point p2={1,1,1}; Point p3={-1,1,1};
	Point pp={0,0,1};
	int xf = glutGet(GLUT_WINDOW_WIDTH);
	int yf = glutGet(GLUT_WINDOW_HEIGHT);
	double incl = 2*(coord+0.1)/ (double)xf; //Increment d'un pixel
	double incc = 2*(coord+0.1)/ (double)yf;
    
	//Calcul Li et Oi
	// A ecrire
    
	//Calcul Id et Is au trois points
	// A ecrire
    
	//Parcours du triangle
	double i,j;
	for (i=-1;i <= 1; i=i+incl){
		//Calcul intensité en pA et pB diffuse et spéculaire
		// A ecrire
		for (j=-i;j <= 1; j=j+incc){
			//Position de point courant
			pp[0]=j;pp[1]=i;
			//Intensité au point courant
			// A ecrire
			AffichePoint3D(pp,ppi);
		}
	}
}

void Gouraud2(Vecteur N1,Vecteur N2,Vecteur N3, Point L, Point O){
	Point p1={1,-1,1}; Point p2={1,1,1}; Point p3={-1,1,1};
	Point pp={0,0,1};
	int xf = glutGet(GLUT_WINDOW_WIDTH);
	int yf = glutGet(GLUT_WINDOW_HEIGHT);
	double incl = 2*(coord+0.1)/ (double)xf; //Increment d'un pixel
	double incc = 2*(coord+0.1)/ (double)yf;
    
	//Calcul Li et Oi
	// A ecrire
    
	//Calcul Id et Is au trois points
	// A ecrire
    
	//Parcours du triangle
	double i,j;
	for (i=-1;i <= 1; i=i+incl){
		//Calcul intensité en pA et pB diffuse et spéculaire
        // A ecrire
		for (j=-i;j <= 1; j=j+incc){
			//Position de point courant
			pp[0]=j;pp[1]=i;
			//Intensité au point courant
			// A ecrire
			AffichePoint3D(pp,ppi);
		}
	}
}

void Phong(Vecteur N,Point L, Point O){
	Point p1={1,-1,1}; Point p2={1,1,1}; Point p3={-1,1,1};
	Point pp={0,0,1};
	int xf = glutGet(GLUT_WINDOW_WIDTH);
	int yf = glutGet(GLUT_WINDOW_HEIGHT);
	double incl = 2*(coord+0.1)/ (double)xf;
	double incc = 2*(coord+0.1)/ (double)yf;
	double i,j;
	Vecteur Lp,Op;
	for (i=-1;i <= 1; i=i+incl){
		for (j=-i;j <= 1; j=j+incc){
			pp[0]=j;pp[1]=i;
			//Vecteur lumiere et observateur.
			// A ecrire
			AffichePoint3D(pp,MIN(1,ppis+ppid));
		}
	}
}

void Phong2(Vecteur N1,Vecteur N2,Vecteur N3,Point L, Point O){
	Point p1={1,-1,1}; Point p2={1,1,1}; Point p3={-1,1,1};
	Point pp={0,0,1};
	int xf = glutGet(GLUT_WINDOW_WIDTH);
	int yf = glutGet(GLUT_WINDOW_HEIGHT);
	double incl = 2*(coord+0.1)/ (double)xf;
	double incc = 2*(coord+0.1)/ (double)yf;
	double i,j;
	Vecteur Lp,Op,Na,Nb,Np;
	for (i=-1;i <= 1; i=i+incl){
		//Calcul Na et Nb
		// A ecrire
		for (j=-i;j <= 1; j=j+incc){
			pp[0]=j;pp[1]=i;
			//Vecteur lumiere et observateur.
			// A ecrire
			//Interpolation des normales
			// A ecrire
			//Calcul Id et Is
			// A ecrire
			AffichePoint3D(pp,MIN(1,ppid));
		}
	}
}
