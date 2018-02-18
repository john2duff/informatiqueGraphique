#include "../base.c"
#define N 3
char name[]="Calcul matriciel"; //Nom de la fenetre
char message[200]; //Message fenetre

typedef double matrice[N*N]; //Vecteur de N * N
typedef double vecteur[N];

int scene=0;

void afficheMatriceGraphique(matrice m, int nbl, int nbc, double *pos);
void produitMatriceMatrice(int taille,matrice a,matrice b, matrice r);
void produitMatriceVecteur(int taille,matrice m,vecteur v,vecteur vr);
void produitVecteurMatrice(int taille,vecteur v,matrice m,vecteur r);
double produitVecteurVecteur(int taille,vecteur vl, vecteur vc);
void transposeMatrice(int taille,matrice m,matrice r);

void afficheMatriceGraphique(double *m, int nbl, int nbc, double *pos){
	char message[10];
	double pos_locale[3];
	int l,c;	
	#define M(ligne,colonne) m[colonne*nbl+ligne]
	pos_locale[2] = pos[2];
	pos_locale[1] = pos[1]-0.1;
	for (l=0;l<nbl;l++){
		pos_locale[0] = pos[0];
		for (c=0;c<nbc;c++){
			sprintf(message,"%.2f",M(l,c));
			affiche_chaine(pos_locale,message,NOIR);
			pos_locale[0] = pos_locale[0] + 0.2; 
		}
		pos_locale[1] = pos_locale[1] - 0.1; 
	}	
	#undef M
	glBegin(GL_LINES);
	glVertex3dv(pos);
	glVertex3d(pos[0],pos[1]-l*0.1,pos[2]);
	glVertex3d(pos[0]+c*0.2,pos[1],pos[2]);
	glVertex3d(pos[0]+c*0.2,pos[1]-l*0.1,pos[2]);
	glEnd();
}

void description(){
	matrice A={1,4,7,2,5,8,3,6,9};
	matrice B={9,6,3,8,5,2,7,4,1};
	vecteur C={9,6,3}; //Vecteur cologne
	vecteur D={9,6,3}; //Vecteur ligne
	matrice R={0,0,0,0,0,0,0,0,0};
	
	double posM1[]={-1,1,0};
	double posM2[]={0,1,0};
	double posM3[]={0,0,0};
	double posfois[]={-0.1,0.9,0};
	double posegal[]={-0.1,-0.1,0};
	char transpose[]="T";
	char fois[]="x";
	char egal[]="=";	
	
	switch(scene){
		case 0:
			produitMatriceMatrice(N,A,B,R);
			afficheMatriceGraphique(A,N,N,posM1);
			affiche_chaine(posfois,fois,NOIR);
			afficheMatriceGraphique(B,N,N,posM2);
			affiche_chaine(posegal,egal,NOIR);
			afficheMatriceGraphique(R,N,N,posM3);
			break;
		case 1:
			produitMatriceMatrice(N,B,A,R);
			afficheMatriceGraphique(B,N,N,posM1);
			affiche_chaine(posfois,fois,NOIR);
			afficheMatriceGraphique(A,N,N,posM2);
			affiche_chaine(posegal,egal,NOIR);
			afficheMatriceGraphique(R,N,N,posM3);
			break;
		case 2:
			produitMatriceVecteur(N,A,C,R);
			afficheMatriceGraphique(A,N,N,posM1);
			affiche_chaine(posfois,fois,NOIR);
			afficheMatriceGraphique(C,N,1,posM2);
			affiche_chaine(posegal,egal,NOIR);
			afficheMatriceGraphique(R,N,1,posM3);
		break;
		case 3:
			produitVecteurMatrice(N,D,A,R);
			afficheMatriceGraphique(D,1,N,posM1);
			affiche_chaine(posfois,fois,NOIR);
			afficheMatriceGraphique(A,N,N,posM2);
			affiche_chaine(posegal,egal,NOIR);
			afficheMatriceGraphique(R,1,N,posM3);
		break;
		case 4:
			R[0] = produitVecteurVecteur(N,C,D);
			afficheMatriceGraphique(C,1,N,posM1);
			affiche_chaine(posfois,fois,NOIR);
			afficheMatriceGraphique(D,N,1,posM2);
			affiche_chaine(posegal,egal,NOIR);
			afficheMatriceGraphique(R,1,1,posM3);
		break;
		case 5:
			transposeMatrice(3,A,R);
			afficheMatriceGraphique(A,N,N,posM1);
			affiche_chaine(posfois,transpose,NOIR);
			affiche_chaine(posegal,egal,NOIR);
			afficheMatriceGraphique(R,N,N,posM3);
		break;
	}	
}

void anime(){
	switch(scene){
		case 0:
			sprintf(message,"A x B");
			break;
		case 1:
			sprintf(message,"B x A");
			break;
		case 2:
			sprintf(message,"A x C");
			break;
		case 3:
			sprintf(message,"D x A");
			break;
		case 4:
			sprintf(message,"C x D");
			break;
		case 5:
			sprintf(message,"Transposition matrice");
			break;
	}			 
	glutPostRedisplay();
}

void menuScene(int selection){
	scene = selection;    }

void initialisation(){
	int mScene;
	mScene=glutCreateMenu(menuScene);
  glutAddMenuEntry("A x B",0);
  glutAddMenuEntry("B x A",1);
  glutAddMenuEntry("A x C",2);
  glutAddMenuEntry("D x A",3);
  glutAddMenuEntry("C x D",4);
  glutAddMenuEntry("Transposition",5);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
	information=1;
}
	
void clavier(unsigned char key){}
void redimension(int width, int height){}

void produitMatriceMatrice(int taille,matrice a,matrice b, matrice r){
	int l,c,k;
	#define A(ligne,colonne) a[colonne*taille+ligne]
	#define B(ligne,colonne) b[colonne*taille+ligne]
	#define R(ligne,colonne) r[colonne*taille+ligne]
	for(l=0;l<taille;l++)
		for(c=0;c<taille;c++){
			R(l,c)=0;
			for(k=0;k<taille;k++)
					R(l,c)=R(l,c)+A(l,k)*B(k,c);
		}
	#undef A
	#undef B
	#undef R
}
void produitMatriceVecteur(int taille,matrice m,vecteur v,vecteur r) {
	int l,c;
	#define M(ligne,colonne) m[colonne*taille+ligne]
  for (l=0;l<taille;l++ ) {
    r[l] = 0 ; 
    for (c=0;c<taille;c++ ) 
      r[l] = r[l]+  M(l,c)*v[c]; 
	}
	#undef M
}
void produitVecteurMatrice(int taille,vecteur v,matrice m,vecteur r) {
	int l,c;
	#define M(ligne,colonne) m[colonne*taille+ligne]
  for (c=0;c<taille;c++ ) {
    r[c] = 0 ; 
    for (l=0;l<taille;l++ ) 
      r[c] = r[c]+  M(l,c)*v[l]; 
	}
	#undef M
}
double produitVecteurVecteur(int taille,vecteur vl, vecteur vc){
	int i;
	double r =0;
  for (i=0;i<taille;i++ ) 
    r = r+ vl[i]* vc[i];
  return r;
}
void transposeMatrice(int taille,matrice m,matrice r){
	int l,c;
	#define M(ligne,colonne) m[colonne*taille+ligne]
	#define R(ligne,colonne) r[colonne*taille+ligne]
  for (l=0;l<taille;l++ )
    for (c=0;c<taille;c++ ) 
      R(l,c) = M(c,l);
  #undef M
	#undef R
}
