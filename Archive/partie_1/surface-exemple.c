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

void surfaceBicubique(int n,matrice m, matrice mp,
											matrice x,matrice y,matrice z,double *couleur);
void description(){
	matrice x={-3/4.0,-3/4.0,-3/4.0,-3/4.0, -1/4.0,-1/4.0,-1/4.0,-1/4.0,
						  1/4.0, 1/4.0,-1/4.0, 1/4.0,  3/4.0, 3/4.0, 3/4.0, 3/4.0};
	
	matrice y={0,0,0,0,  0,1,1,0, 0,1,1,0, 0,0,0,0};

	matrice z={-3/4.0,-1/4.0,1/4.0,3/4.0, -3/4.0,-1/4.0,1/4.0,3/4.0, -3/4.0,-1/4.0,1/4.0,3/4.0, -3/4.0,-1/4.0,1/4.0,3/4.0};
        
	matrice bezier={-1.0, 3.0,-3.0, 1.0,  3.0,-6.0, 3.0, 0.0,
						      -3.0, 3.0, 0.0, 0.0,  1.0, 0.0, 0.0, 0.0};


	surfaceBicubique(32,bezier, bezier,x,y,z,ROUGE);
}
void anime(){}
void initialisation(){}
void clavier(unsigned char key){}
void redimension(int width, int height){}

void surfaceBicubique(int n,matrice M, matrice MP,matrice X,matrice Y,matrice Z,
												double *couleur){
  matrice TX,MX,TY,MY,TZ,MZ,MT ;
  int i,j;
  transposeMatrice(N,MP,MT) ; // mt <- (mp)T
  produitMatriceMatrice(N,M,X,MX) ; //mx <- m . x 
  produitMatriceMatrice(N,MX,MT,TX) ;// tx <- m. x . mt
  produitMatriceMatrice(N,M,Y,MY) ;
	produitMatriceMatrice(N,MY,MT,TY);
  produitMatriceMatrice(N,M,Z,MZ) ; 
  produitMatriceMatrice(N,MZ,MT,TZ) ;
  glColor3dv(couleur);
    glPointSize(3.0);
  glBegin(GL_POINTS);
  for ( i = 0 ; i < n ; i++ ) {
    double s =(double) i/(double) (n-1) ;
    vecteur S = { s*s*s,s*s,s,1.0F } ; 
    for ( j = 0 ; j < n ; j++ ) {
      double t =(double) j/(double) (n-1) ;
      vecteur T = { t*t*t,t*t,t,1.0F } ; 
      vecteur D ;
      produitVecteurMatrice(N,S,TX,D) ; // d <- S . tx = S m .a . (mp)T
      double x = produitVecteurVecteur(N,D,T) ;
      produitVecteurMatrice(N,S,TY,D) ;
      double y = produitVecteurVecteur(N,D,T) ;
      produitVecteurMatrice(N,S,TZ,D) ;
      double z = produitVecteurVecteur(N,D,T) ;
      glVertex3d(x,y,z);
		} 
	}
	glEnd();
}
void produitMatriceMatrice(int taille,matrice a,matrice b, matrice r){
	int l,c,k;
	#define A(ligne,colonne) a[colonne*taille+ligne]
	#define B(ligne,colonne) b[colonne*taille+ligne]
	#define R(ligne,colonne) r[colonne*taille+ligne]
	//...
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
      v[l] = v[l]+  M(l,c)*v[c]; 
	}
	#undef M
}

void produitVecteurMatrice(int taille,vecteur v,matrice m,vecteur r) {
	int l,c;
	#define M(ligne,colonne) m[colonne*taille+ligne]
  for (l=0;l<taille;l++ ) {
    r[l] = 0 ; 
    for (c=0;c<taille;c++ ) 
      r[l] = r[l]+  M(c,l)*v[c]; 
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
