#include "../base.c"
char name[]="2 triangles reels avec z buffer";

char message[200];
double p1t1[3]={-0.5,-0.5,-0.5};
double p2t1[3]={0,0,0};
double p3t1[3]={0.5,-0.25,0.5};

double p1t2[3]={-0.25,-0.75,0.75};
double p2t2[3]={0,0,0};
double p3t2[3]={0.25,-0.75,-0.5};

//Tableaux lies au z-buffer
double *profondeur; //z le plus proche
double *couleurR,*couleurV,*couleurB; //couleur le plus proche
//Acces aux tableaux
#define PROF(ligne,colonne) profondeur[(colonne*taille_fenetre_x+ligne)]
#define COULR(ligne,colonne) couleurR[(colonne*taille_fenetre_x+ligne)]
#define COULV(ligne,colonne) couleurV[(colonne*taille_fenetre_x+ligne)]
#define COULB(ligne,colonne) couleurB[(colonne*taille_fenetre_x+ligne)]

//Remplir tableau pour un triangle forme de trois points
void remplirRec(double *p1,double *p2,double *p3,double *coul);
//Initailiser tableaux couleur et profondeur
void iniTab();
//Afficher les tableaux
void afficheTab();

void anime(){}
void clavier(unsigned char key){}
void initialisation(){}
void redimension(int width, int height){}
void description(){
    iniTab();
    remplirRec(p1t1,p2t1,p3t1,ROUGE);
    remplirRec(p1t2,p2t2,p3t2,VERT);
    afficheTab();
    free(couleurR);free(couleurV);free(couleurB);free(profondeur);
}

void iniTab(){
    int i,j;
    if ((profondeur = (double *)malloc(taille_fenetre_x *  taille_fenetre_y * sizeof(double)))==NULL){
        exit(-1);
    }
    if((couleurR = (double *)malloc(taille_fenetre_x *  taille_fenetre_y * sizeof(double)))==NULL){
        exit(-1);
    }
    if((couleurV = (double *)malloc(taille_fenetre_x *  taille_fenetre_y * sizeof(double)))==NULL){
        exit(-1);
    }
    if((couleurB = (double *)malloc(taille_fenetre_x *  taille_fenetre_y * sizeof(double)))==NULL){
        exit(-1);
    }
    
    for (i=0;i<taille_fenetre_x;i++)
        for (j=0;j<taille_fenetre_y;j++){
            // A ecrire
            PROF(i,j)=???; // Le plus loin
            COULR(i,j)=???;//rouge
            COULV(i,j)=???;//vert
            COULB(i,j)=???;//bleu
        }
}

void afficheTab(){
    int i,j;
    glPointSize(2.0);
    glBegin(GL_POINTS);
    for (i=0;i<taille_fenetre_x;i++)
        for (j=0;j<taille_fenetre_y;j++){
            //A ecrire
            glColor3d(???);
            glVertex3d(???)
        }
    glEnd();
}

void echange(double *p1,double *p2){
    int c;
    p1[0]=c;p1[0]=p2[0];p2[0]=c;
    p1[1]=c;p1[1]=p2[1];p2[1]=c;
    p1[2]=c;p1[2]=p2[2];p2[2]=c;
}

void remplirRec(double *p1,double *p2,double *p3,double *coul){
    double x,y;
    //recherche de x le plus petit en p1 x median p2, x le plus grand p3
    if (p1[0]>p2[0]) echange(p1,p2);
    if (p2[0]>p3[0]) echange(p2,p3);
    if (p1[0]>p2[0]) echange(p1,p2);
    
    double yp12 = (p2[1]-p1[1]) / (p2[0]-p1[0]); //Pente y entre p1 et p2
    double yp13 = (p3[1]-p1[1]) / (p3[0]-p1[0]); //Pente y entre p1 et p3
    double yp23 = (p3[1]-p2[1]) / (p3[0]-p2[0]); //Pente y entre p1 et p3
    
    double zp12 = (p2[2]-p1[2]) / (p2[0]-p1[0]); //Pente z entre p1 et p2
    double zp13 = (p3[2]-p1[2]) / (p3[0]-p1[0]); //Pente z entre p1 et p3
    double zp23 = (p3[2]-p2[2]) / (p3[0]-p2[0]); //Pente z entre p1 et p3
    
    //Parcours entre p1 et p2
    for (x=p1[0];x<p2[0];x=x+2.0/taille_fenetre_x){
        double y1 = p1[1]+yp12*(x-p1[0]);
        double y2 = p1[1]+yp13*(x-p1[0]);
        double z1 = p1[2]+zp12*(x-p1[0]);
        double z2 = p1[2]+zp13*(x-p1[0]);
        
        if (y1>y2){
            double c;
            c=y1;y1=y2;y2=c;
            c=z1;z1=z2;z2=c;
        }
        double zpab = (z1-z2)/(y1-y2);

        for (y=y1;y<y2;y=y+2.0/taille_fenetre_y){
            double z = z1 + zpab * (y-y1);
            // A ecrire
            if (PROF(???)< ???){
                PROF(???)= ??;
                COULR(???)= coul[0];
                COULV(???)= coul[1];
                COULB(???)= coul[2];
            }
        }
    }
    //Parcours entre p2 et p3
    for (x=p2[0];x<=p3[0];x=x+2.0/taille_fenetre_x){
        double y1 = p2[1]+yp23*(x-p2[0]);
        double y2 = p1[1]+yp13*(x-p1[0]);
        double z1 = p2[2]+zp23*(x-p2[0]);
        double z2 = p1[2]+zp13*(x-p1[0]);

        if (y1>y2){
            double c;
            c=y1;y1=y2;y2=c;
            c=z1;z1=z2;z2=c;
        }
        double zpab = (z1-z2)/(y1-y2);
        
        for (y=y1;y<y2;y=y+2.0/taille_fenetre_y){
            double z = z1 + zpab * (y-y1);
            // A ecrire
            if (PROF(???)< ???){
                PROF(???)= ??;
                COULR(???)= coul[0];
                COULV(???)= coul[1];
                COULB(???)= coul[2];
            }
        }
    }
}