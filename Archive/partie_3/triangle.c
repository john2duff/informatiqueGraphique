#include "../base.c"
wwwwchar name[]="Remplissage polygones convexes";
char message[200];
//Position des coordonnees dans le tableau arete
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
#define GAUCHE 0
//Position dans tableau des aretes et aretes actives
#define DROITE 1

typedef int arete[4];
arete taa[2];
arete ta[DIVISION][2];

//Les aretes horizontales ne sont pas presentes
arete convexe1[]={{4,1,1,4},{1,4,3,7},{3,7,6,10},{9,5,6,10},{4,1,9,5}};
arete convexe2[]={{9,5,6,10},{14,5,6,10}}; //sans les horizontales !
arete convexe3[]={{4,10,4,15},{14,10,14,15}}; //sans les horizontales !

//Tracer un polygone sans les aretes horizontales
void tracePolygone(arete p[],int taille,GLdouble* couleur);
//Copier une arete dans une autre
void copieArete(arete src,arete dest);
//Remplir un polygone
void remplirPolygone(arete *p,int taille,GLdouble *couleur);

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
	tracePolygone(convexe1,sizeof(convexe1)/sizeof(arete),ROUGE);
	tracePolygone(convexe2,sizeof(convexe2)/sizeof(arete),BLEU);
	tracePolygone(convexe3,sizeof(convexe3)/sizeof(arete),VERT);
	remplirPolygone(convexe1,sizeof(convexe1)/sizeof(arete),ROUGE);
	remplirPolygone(convexe2,sizeof(convexe2)/sizeof(arete),BLEU);
	remplirPolygone(convexe3,sizeof(convexe3)/sizeof(arete),VERT);
}
void anime(){}
void initialisation(){}
void clavier(unsigned char key){}
void redimension(int width, int height){}
void remplirPolygone(arete *p,int taille,GLdouble *couleur){
	int i,x,y,ymin = DIVISION-1,ymax=0;
	double xg,xd,mg,md;
	//initialisation table des aretes
	for (i=0;i<DIVISION;i++){
        ta[i][DROITE][POS_INUTILISE]=INUTILISE;
        ta[i][GAUCHEDROITE][POS_INUTILISE]=INUTILISE;
	}
	//remplissage de la table des aretes et recherche min et max
	for (i=0;i<taille;i++){
		if (ta[p[i][YBAS]][GAUCHEDROITE][POS_INUTILISE] ==INUTILISE) //Si rien a gauche
			copieArete(p[i],ta[p[i][YBAS]][GAUCHEDROITE]);
		else
			copieArete(p[i],ta[p[i][YBAS]][DROITE]);
		//recherche ymin et ymax
		if (p[i][YBAS]<ymin) ymin = p[i][YBAS];
		if (p[i][YHAUT]>ymax) ymax = p[i][YHAUT];
	}
	//initialisation TAA au point le plus bas des points xg et xd mg et md
	copieArete(ta[ymin][GAUCHEDROITE],taa[GAUCHE]);
	copieArete(ta[ymin][DROITE],taa[DROITE]);
	xg=(double)(taa[GAUCHE][XBAS]);xd=(double)(taa[DROITE][XBAS]);
	mg=	(double)(taa[GAUCHE][XHAUT]-taa[GAUCHE][XBAS])/
    (double)(taa[GAUCHE][YHAUT]-taa[GAUCHE][YBAS]);
	md=	(double)(taa[DROITE][XHAUT]-taa[DROITE][XBAS])/
    (double)(taa[DROITE][YHAUT]-taa[DROITE][YBAS]);
	for(y=ymin;y<ymax;y++){
		//Remplacer aretes gauche si besoin
		if(taa[GAUCHE][YHAUT]==y){
			copieArete(ta[y][GAUCHEDROITE],taa[GAUCHE]);
			xg=	(double)(taa[GAUCHE][XBAS]);
			mg=	(double)(taa[GAUCHE][XHAUT]-taa[GAUCHE][XBAS])/
            (double)(taa[GAUCHE][YHAUT]-taa[GAUCHE][YBAS]);
		}
		//Remplacer aretes droite si besoin
		if(taa[DROITE][YHAUT]==y){
			if(ta[p[i][YBAS]][DROITE][POS_INUTILISE] ==INUTILISE){
				copieArete(ta[y][GAUCHEDROITE],taa[DROITE]);
			}
			else {
				copieArete(ta[y][DROITE],taa[DROITE]);
			}
			xd=(double)(taa[DROITE][XBAS]);
			md=	(double)(taa[DROITE][XHAUT]-taa[DROITE][XBAS])/
            (double)(taa[DROITE][YHAUT]-taa[DROITE][YBAS]);
		}
		for(x=(int)(ceil(xg));x<(int)(floor(xd));x++) {
			affichePseudoPixel(x,y,10,couleur);
		}
		if ((double) x != xd){ //Ne pas afficher le point de droite s'il est sur l'arete
            affichePseudoPixel(x,y,10,couleur);
		}
		if (xg==xd){ //Afficher le point isole arete base
            affichePseudoPixel(x,y,10,couleur);
		}
		xd=xd+md;xg=xg+mg;
	}
}
