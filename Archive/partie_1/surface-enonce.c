#include "../base.c"
#define  N 4 //taille des matrices et vecteurs
char name[]="Surface bicubique";
char message[]="Surface bicubique";
typedef double matrice[N*N];
typedef double vecteur[N];

void produitMatriceMatrice(int taille,matrice a,matrice b, matrice r);
void produitMatriceVecteur(int taille,matrice m,vecteur v,vecteur r);
void produitVecteurMatrice(int taille,vecteur v,matrice m,vecteur r);
double produitVecteurVecteur(int taille,vecteur vl, vecteur vc);
void transposeMatrice(int taille,matrice m,matrice r);

void surfaceBicubique(int n,matrice m, matrice mp,matrice x,matrice y,matrice z,double *couleur);
void description(){
	matrice x={-3/4.0,-3/4.0,-3/4.0,-3/4.0, -1/4.0,-1/4.0,-3/4.0,-1/4.0,1/4.0, 1/4.0,-3/4.0,1/4.0,3/4.0,3/4.0,3/4.0,3/4.0};
	matrice y={-3/4.0,-1/4.0, 1/4.0, 3/4.0, -1/4.0,-1/4.0, 1/4.0, 3/4.0,1/4.0,-1/4.0,1/4.0,3/4.0,3/4.0,-1/4.0,1/4.0,3/4.0};
	matrice z={-1/4.0, 3/4.0,-1/4.0,-2/4.0,1/4.0,2/4.0,-1/4.0,1/4.0,2/4.0,-1/4.0,1/4.0,3/4.0,-1/4.0,1/4.0,-1/4.0,3/4.0};
	matrice bezier={-1.0, 3.0,-3.0,1.0,3.0,-6.0,3.0,0.0,-3.0,3.0,0.0,0.0,1.0,0.0,0.0, 0.0};
	matrice nrubs={-1.0/6,3.0/6,-3.0/6,1.0/6,3.0/6,-6.0/6,0.0,4.0/6,-3.0/6,3.0/6,3.0/6,1.0/6,1.0/6,0.0,0.0, 0.0};
	surfaceBicubique(50,bezier, nrubs,x,y,z,ROUGE);
}
void anime(){}
void initialisation(){}
void clavier(unsigned char key){}
void redimension(int width, int height){}

void surfaceBicubique(int n,matrice M, matrice MP,matrice X,matrice Y,matrice Z,double *couleur){
// A ecrire
}
