#include "../base.c"
#define  N 4 //taille des matrices et vecteurs
char name[]="Courbes parametriques bezier et Nrubs";
char message[]="Courbes parametriques bezier et Nrubs";
typedef double matrice[N*N];
typedef double vecteur[N];

void produitMatriceMatrice(int taille,matrice,matrice,matrice);
void produitVecteurMatrice(int taille,vecteur,matrice,vecteur);

void courbe(int n, matrice m,matrice G, GLdouble *couleur);
void description(){

	matrice bezier={-1.0, 3.0,-3.0, 1.0,  3.0,-6.0, 3.0, 0.0,
						      -3.0, 3.0, 0.0, 0.0,  1.0, 0.0, 0.0, 0.0};


	matrice nrubs={-1.0/6, 3.0/6,-3.0/6, 1.0/6,  3.0/6,-6.0/6,    0.0, 4.0/6,
						     -3.0/6, 3.0/6, 3.0/6, 1.0/6,  1.0/6,   0.0,    0.0,    0.0};

							
	matrice G0={-0.75,-0.50, 0.25, 0.50, 0.00, 0.50, 0.25,-0.50,
							0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

	matrice G1={ 0.50,0.625,-1.00,-0.75,-0.50,-1.00,-0.50, 0.00,
							 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};


	//Affiche les  points de controle 
	glColor3dv(NOIR);
	glBegin(GL_LINE_LOOP);
		glVertex2d(G0[0],G0[4]);
		glVertex2d(G0[1],G0[5]);
		glVertex2d(G0[2],G0[6]);
		glVertex2d(G0[3],G0[7]);
		glVertex2d(G1[1],G1[5]);
		glVertex2d(G1[2],G1[6]);
	glEnd();
	courbe(200,bezier,G0,BLEU); //Bezier 
	courbe(200,bezier,G1,ROUGE);
	courbe(200,nrubs,G0,BLEU); //B Spline 
	courbe(200,nrubs,G1,ROUGE);
}
void anime(){}
void initialisation(){}
void clavier(unsigned char key){}
void redimension(int width, int height){}

void courbe(int n, matrice M,matrice G,double *couleur){
	matrice MG;	
	vecteur Tr;
	int i;
	//MG <- M . g
	produitMatriceMatrice(N,M,G,MG);
	glBegin(GL_POINTS);
	glColor3dv(couleur);
	for(i=0;i<=n-1;i++){
		GLdouble t = (double) i / (double)(n-1);
		vecteur T={t*t*t,t*t,t,1};
		produitVecteurMatrice(N,T,MG,Tr);
 		glVertex3dv(Tr);
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
