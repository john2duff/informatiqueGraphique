#include "../base.c"
char name[]="Matrices !";
char message[200];
typedef double matrice[16];
int scene=-1;
matrice m,a,b,c,d;
//Multiplication de matrice 3eme param <- 1er param  x 2eme param
void produitMatriceMatrice(matrice,matrice,matrice);
//Matrice de translation
void Translation(double dx,double dy,double dz,matrice);
//Matrice de facteur d'echelle
void Echelle(double sx,double sy,double sz,matrice);
//Matrice de cisaillement
void Cisaillement(double cx,double cy,double cz,matrice);
//Matrice de rotation en X
void RotationX(double a,matrice);
//Matrice de rotation en Y
void RotationY(double a,matrice);
//Matrice de Rotation en Z
void RotationZ(double a,matrice);
//Description de la scene
void description(){
	switch (scene){
		case -1:
			glColor3dv(ORANGE);
			Translation(0,0,0,m); // Par initialiser m
			sprintf(message,"Position initiale");
			break;			
		case 0 :
			glColor3dv(ORANGE);
			Translation(0.5,0.75,-0.5,m);
			sprintf(message,"Translation(0.5,0.75,-0.5)");
			break;
		case 1:
			glColor3dv(JAUNE);
			RotationX(90,m);
			sprintf(message,"Rotation(90,1,0,0)");
			break;
		case 2:
			glColor3dv(ROSE);
			RotationY(90,m);
			sprintf(message,"Rotation(90,0,1,0)");
			break;
		case 3:
			glColor3dv(VERT_FONCE);
			RotationZ(90,m);
			sprintf(message,"Rotation(90,0,0,1)");
			break;
		case 4:
			glColor3dv(TURQUOISE);
			Cisaillement(0.5,0,0,m);
			sprintf(message,"Cisaillement(0.5,0,0)");
			break;
		case 5:
			glColor3dv(NOIR);
			Cisaillement(0,0.5,0,m);
			sprintf(message,"Cisaillement(0,0.5,0)");			
			break;
		case 6:
			glColor3dv(VIOLET);
			Echelle(1,2,1,a);
			RotationZ(90,b);
			produitMatriceMatrice(a,b,m);
			sprintf(message,"Echelle puis rotation z");
			break;
		case 7:
			glColor3dv(ORANGE);
			//Translation puis Rotation triangle exo theorique
			Translation(0.5,0.75,-0.5,a);
			RotationZ(90,b);
			produitMatriceMatrice(a,b,m);
			sprintf(message,"Translation puis rotation z");
			break;
		case 8:
			glColor3dv(VIOLET);
			//Rotation puis translation triangle exo theorique
			RotationZ(90,a);
			Translation(0.75,-0.5,-0.5,b);
			produitMatriceMatrice(a,b,m);
			sprintf(message,"Rotation z puis translation");
			break;
		case 9:
			//Translation puis Rotation puis Echelle triangle exo theorique
			glColor3dv(VIOLET);
			Translation(0.5,0.75,-0.5,a);
			RotationZ(90,b);	
			produitMatriceMatrice(a,b,c);
			Echelle(1,2,1,d);
			produitMatriceMatrice(c,d,m);
			sprintf(message,"Translation puis rotation z  puis echelle");
			break;
		case 10:
			//Echelle puis Translation puis Rotation triangle exo theorique
			glColor3dv(NOIR);
			Echelle(2,1,1,a);
			Translation(0.5/2,0.75/1,-0.5,b);
			produitMatriceMatrice(a,b,c);
			RotationZ(90,d);
			produitMatriceMatrice(c,d,m);
			sprintf(message,"Echelle puis translation puis rotation z");
			break;
	}
	glMultMatrixd((double*)m);
	dessin_axes(ROUGE,VERT,BLEU);
	glBegin(GL_POLYGON);
	glVertex3d(0,0,0);
	glVertex3d(0,0.5,0);
	glVertex3d(0.25,0,0);
	glEnd();
	glutPostRedisplay();
}
void menuScene(int selection){
	scene = selection;    }
//Mes initialisations 
void initialisation(){
	int mScene;
	mScene=glutCreateMenu(menuScene);
  glutAddMenuEntry("Triangle initial",-1);
  glutAddMenuEntry("Translation",0);
  glutAddMenuEntry("Rotation X",1);
  glutAddMenuEntry("Rotation Y",2);
  glutAddMenuEntry("Rotation Z",3);
  glutAddMenuEntry("Cisaillement en x",4);
  glutAddMenuEntry("Cisaillement en y",5);
	glutAddMenuEntry("Echelle",6);
  glutAddMenuEntry("T puis R",7);
	glutAddMenuEntry("R puis T",8);
	glutAddMenuEntry("T puis R puis E",9);
	glutAddMenuEntry(" E puis T puis R",10);
  glutAttachMenu(GLUT_RIGHT_BUTTON);}
void anime(){}
void clavier(unsigned char key){}
void redimension(int width, int height){}
//Multiplication de matrice c <- a x b
void produitMatriceMatrice(matrice a,matrice b,matrice c){
// A ajouter
}
//Matrice de translation
void Translation(double dx,double dy,double dz,matrice m){
	#define M(ligne,colonne) m[colonne*4+ligne]
	// A ecrire
	#undef M 
}
//Matrice de facteur d'echelle
void Echelle(double sx,double sy,double sz,matrice m){
	#define M(ligne,colonne) m[colonne*4+ligne]
	// A ecrire
	#undef M 
}	
//Matrice de cisaillement
void Cisaillement(double cx,double cy,double cz,matrice m){
	#define M(ligne,colonne) m[colonne*4+ligne]
	// A ecrire
	#undef M 
}	
//Matrice de rotation en X
void RotationX(double a,matrice m){
	#define M(ligne,colonne) m[colonne*4+ligne]
	// A ecrire
		#undef M 
}	
//Matrice de rotation en Y
void RotationY(double a, matrice m){
	#define M(ligne,colonne) m[colonne*4+ligne]
	// A ecrire
	#undef M 
}	
//Matrice de Rotation en Z
void RotationZ(double a, matrice m){
	#define M(ligne,colonne) m[colonne*4+ligne]
	// A ecrire
	#undef M 
}	
