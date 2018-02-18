#include "../base.c"
char name[]="Trace de polygone";
char message[200];
//Position des coordonnees dans le tableau arrete
#define XBAS 0
#define YBAS 1
#define XHAUT 2
#define YHAUT 3
//arete Inutilisee si YBAS=-1
#define INUTILISE -1
#define POS_INUTILISE 1
//Position dans tableau des aretes
#define GAUCHEDROITE 0
//Position dans tableau des aretes actives
#define DROITE 1
//Nombre d'aretes max dans les tables
typedef int arete[4];
arete taa[4];
double xpos[4]; //coordonnees x associees aux aretes actives
double    m[4];    //pentes associees aux aretes actives
arete ta[DIVISION][2];
arete poygone[]={{7,1,2,4},{2,4,2,13},{7,6,2,13},{7,6,12,10},{12,4,12,10},{7,1,12,4}};
//Tracer un polygone sans les aretes horizontales
void tracePolygone(arete p[],int taille,GLdouble* couleur);
//Copier une arete dans une autre
void copieArete(arete src,arete dest);
void supprimeAretes(int y);
void ajouteArete(arete a);
void ajouteAretes(int y);
//Remplir un polygone
void remplirPolygoneQuelconque(arete *p,int taille,GLdouble *couleur);
void tracePolygone(arete p[],int taille,GLdouble* couleur){
	int i;
	double x1,y1,x2,y2,incr=2*coord/division,incr2=1-incr/2;
	glColor3dv(couleur);
	glBegin(GL_LINES);
	for(i=0;i<taille;i++){
		x1 = incr * (double)p[i][XBAS] - incr2; //x,y,z entre 0 et DIVISION-1
		y1 = incr * (double)p[i][YBAS] - incr2; //xr,yr,zr entre -1 et 1
		x2 = incr * (double)p[i][XHAUT] - incr2; //x,y,z entre 0 et DIVISION-1
		y2 = incr * (double)p[i][YHAUT] - incr2; //xr,yr,zr entre -1 et 1
		glVertex3d(x1,y1,0);
		glVertex3d(x2,y2,0);
	}
	glEnd();
}
void copieArete(arete src,arete dest){
	int i;
	for(i=0;i<sizeof(arete)/sizeof(int);i++){
		dest[i]=src[i];
	}
}
void description(){
	tracePolygone(poygone,sizeof(poygone)/sizeof(arete),ROUGE);
	remplirPolygoneQuelconque(poygone,sizeof(poygone)/sizeof(arete),ROUGE);
}
void anime(){}
void initialisation(){}
void clavier(unsigned char key){}
void redimension(int width, int height){}
void supprimeAretes(int y){
	int i,j;
	for (i=0;i<4;i++){//Parcourir toutes les arretes.
		if (taa[i][YHAUT]==y){
			// Si l'arete est a son maximum la supprimer
			//Supprimer en decalant les aretes de droite
			for(j=i;j<4;j++){
				copieArete(taa[j+1],taa[j]);
				xpos[j]=xpos[j+1]; //decaler x
				m[j]=m[j+1]; //decaler pente
			}
			taa[3][POS_INUTILISE]=INUTILISE; //Dernier inutilise
			i = i-1; //regarder l'arete supprimee!
		}
	}
}
void ajouteArete(arete a){
	int i=0,j;
	while((taa[i][POS_INUTILISE]!=INUTILISE) &&
          (xpos[i] <= (double)(a[XBAS]))) // <= il faudra placer l'arete gauche en premier !!!
		i++;
	//Faire de la place pour l'arrete en decalant celles de droite
	for (j=2;j>=i;j--){
		copieArete(taa[j],taa[j+1]); //decaler arrete
		xpos[j+1]=xpos[j]; //decaler x
		m[j+1]=m[j]; //decaler pente
	}
	copieArete(a,taa[i]); //decaler arrete
	xpos[i]=a[XBAS];
	m[i]=(double)(a[XHAUT]-a[XBAS])/(double)(a[YHAUT]-a[YBAS]);
}
void ajouteAretes(int y){
	if(ta[y][GAUCHEDROITE][POS_INUTILISE]!=INUTILISE)
		ajouteArete(ta[y][GAUCHEDROITE]);
	if(ta[y][DROITE][POS_INUTILISE]!=INUTILISE)
		ajouteArete(ta[y][DROITE]);
}
void remplirPolygoneQuelconque(arete *p,int taille,GLdouble *couleur){
	int i,x,y,ymin = DIVISION-1,ymax=0;
	//initialisation table des aretes
	for (i=0;i<DIVISION;i++){
        ta[i][DROITE][POS_INUTILISE]=INUTILISE;
        ta[i][GAUCHEDROITE][POS_INUTILISE]=INUTILISE;
	}
	//remplissage de la table des aretes et recherche min et max
	for (i=0;i<taille;i++){
		if (ta[p[i][YBAS]][GAUCHEDROITE][POS_INUTILISE] ==INUTILISE){ //Si rien a gauche
			copieArete(p[i],ta[p[i][YBAS]][GAUCHEDROITE]);
		}
		else {
			copieArete(p[i],ta[p[i][YBAS]][DROITE]);
		}
		//recherche ymin et ymax
		if (p[i][YBAS]<ymin) ymin = p[i][YBAS];
		if (p[i][YHAUT]>ymax) ymax = p[i][YHAUT];
	}
	for (i=0;i<4;i++)
		taa[i][POS_INUTILISE]=INUTILISE;
	for(y=ymin;y<ymax;y++){
		supprimeAretes(???);
		ajouteAretes(???);
		for(x=(int)(ceil(xpos[0]));x<(int)(floor(xpos[1]));x++) {
			affichePseudoPixel(x,y,10,couleur);
		}
		if ((double) x != xpos[1]){ //Ne pas afficher le point de droite s'il est sur l'arete
			affichePseudoPixel(x,y,10,couleur);
		}
		if (xpos[0]==xpos[1]) //Afficher le point bas
			affichePseudoPixel(x,y,10,couleur);
		if (taa[2][POS_INUTILISE]!=INUTILISE){
			for(x=(int)(ceil(xpos[2]));x<(int)(floor(xpos[3]));x++) {
				affichePseudoPixel(x,y,10,couleur);
			}
			if ((double) x != xpos[3]){ //Ne pas afficher le point de droite s'il est sur l'arete
				affichePseudoPixel(x,y,10,couleur);
			}
			if (xpos[2]==xpos[3]) //Afficher le point bas isole
				affichePseudoPixel(x,y,10,couleur);
		}
		for (i=0;i<4;i++){
			xpos[i]=xpos[i]+???;
		}
	}
}