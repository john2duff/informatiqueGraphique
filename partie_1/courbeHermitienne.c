#include "../base.c"
#define  N 4 //taille des matrices et vecteurs
char name[]="Courbes parametriques Hermitienne";
char message[]="Courbes parametriques Hermitienne";
typedef double matrice[N*N];
typedef double vecteur[N];

void produitMatriceMatrice(int taille,matrice,matrice,matrice);
void produitVecteurMatrice(int taille,vecteur,matrice,vecteur);

void courbe(int n, matrice m,matrice G, GLdouble *couleur);
void description(){

    vecteur P1={0,0,0},P4={0.5,0.5,0},N1={0.5,-0.5,0},N4={0.0,-0.5,0};
    
    matrice hermitienne={ 2.0, -3.0,0.0, 1.0,  -2.0,3.0, 0.0, 0.0,
                              1.0, -2.0, 1.0, 0.0,  1.0, -1.0, 0.0, 0.0};
                            
    matrice G0;
    
    G0[0]=P1[0];G0[1]=P4[0];G0[2]=N1[0];G0[3]=N4[0];
    G0[4]=P1[1];G0[5]=P4[1];G0[6]=N1[1];G0[7]=N4[1];
    G0[8]=P1[2];G0[9]=P4[3];G0[10]=N1[3];G0[11]=N4[3];
    
    affiche_vecteur2(P1,N1,NOIR);//tangente en P1
    affiche_vecteur2(P4,N4,NOIR); //tangente en P4
    courbe(200,hermitienne,G0,BLEU); //Hermitienne
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
