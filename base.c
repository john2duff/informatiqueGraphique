//Didier Teifreto - Janvier 2017
//Base pour les exercices IG Master 1 EAD
//Pour utiliser ce fichier
//#include "../base.c" //Si dans repertoire au dessus
// A ecrire obligatoirement meme vide
//char name[]="Nom de la fenetre"; //Nom de votre fenetre
//char message[]="Hello World";    //Afficher une variable ou message dans partie superieure
//void description(){} //Ma description de la scene
//void initialisation(){} //Mes initialisations
//void clavier(unsigned char key){} //Fonction associe au clavier;
//void redimension(int width, int height){} //Fonction pour redimensionner
//void anime(){} //Fonction animation de la scene
//Si compilation MAC OS X
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
// Si compilation autre
#include <GL/glut.h>
#include <GL/gl.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define ANGLE 0.5 //Pas angle animation manuel de 5 degres
#define VITESSE 0.1 //Pas angle animation automatique 0.1 degre
#define COORD  1.0 //Amplitude fenetre initiale 1.0
#define DIVISION 20 //Nombre de divisions quadrillage
#define POSITION_FENETRE 10//Position fenetre ecran
#define TAILLE_FENETRE 480

//Date de la version du fichier base
char version[255]="base 07/01/17-";


//Couleurs utiles
double ROUGE[]={1,0,0};
double ROUGE_FONCE[]={0.5,0,0};
double ROUGE_CLAIR[]={1,0.5,0.5};
double VERT[]={0,1,0};
double VERT_FONCE[]={0,0.5,0};
double VERT_CLAIR[]={0.5,1,0.5};
double BLEU[]={0,0,1};
double BLEU_FONCE[]={0,0,0.5};
double BLEU_CLAIR[]={0.5,0.5,1};
double BLANC[]={1,1,1};
double JAUNE[]={1,1,0};
double NOIR[]={0,0,0};
double GRIS[]={0.5,0.5,0.5};
double ORANGE[]={1,0.5,0};
double VIOLET[]={0.5,0,1};
double TURQUOISE[]={0,1,1};
double ROSE[]={1,0.5,0.5};
//Axes
double AXE_X[]={1,0,0};
double AXE_Y[]={0,1,0};
double AXE_Z[]={0,0,1};
double ORIGINE[]={0,0,0};

//Doivent etre instanciees dans notre programme
//Fonction de description de la scene
extern void description(void);
//Fonction contenant nos initialisation
extern void initialisation(void);
//Fonction contenant nos touches affectee au clavier
extern void clavier(unsigned char);
//Fonction redimension de la fenetre.
extern void  redimension(int,int);
//Fonction animation de la fenetre.
extern void anime();

void dessin_axes(double*,double*,double*);
void dessin_quadrillage(void);
void affiche_caractere(double p[3],char c,double *couleur);
void affiche_chaine(double p[3],char *c,double *couleur);
//Affiche vecteur entre p0 et p1
void affiche_vecteur(double p0[3],double p1[3],double *c);
//Affiche vecteur v avec son origine en p0
void affiche_vecteur2(double p0[3],double v[3],double *c);
void affichePseudoPixel(int x,int y,int z,double *c);
//Conversion coordonnees fenetre en point (GL_POINTS) (comprise entre 0 et taille_fenetre_x-1)
int xcoord2int(double c);
//Conversion coordonnees fenetre en point (comprise entre 0 et taille_fenetre_y-1)
int ycoord2int(double c);
//Conversion coordonnees pixel en coordonnees fenetre (comprise entre -coord et coord)
double xint2coord(int i);
double yint2coord(int i);


void initprojection(int,int);
void resize(int,int);
void display(void);
void idle(void);

//Variables globales
//Nom de la fenetre
extern char name[];
extern char message[];
double xr=0,yr=0,zr=0; //Angles de rotation en degres
int axe; //Tracer les axes 0 non par defaut, 1 oui
int quadrillage; //Tracer quadrillage 0 non par defaut, 1  1/20 fenetre
int animation;  //animer  1 oui, 0 non
int information;// 0 pas d'information, 1 information
int perspective; //Projection 0 parallele par defaut, 1 perspective
double coord=COORD; //Coordonnees fenetre (-1<=x,y,z<=+1)
double division=DIVISION; //Nombre de division du quadrillage
double vitesse=VITESSE;//Vitesse d'animation 0.1 degre par defaut
int   taille_fenetre_x = TAILLE_FENETRE;
int   taille_fenetre_y = TAILLE_FENETRE;

int f1;//Identificateur premiere fenetre

/* Fonction callback gestion clavier */
void  key(unsigned char key, int x, int y) {
    switch (key)
    {
            // Fin du programme
        case 27 :
        case 'q':
        case 'Q':
            exit(0);
            break;
            //Afficher les axes à l'origine
        case 'A': axe = 1; break;
            //Ne pas afficher les axes à l'origine
        case 'a': axe = 0; break;
            //Modifier l'amplitude de la fenetre de coord * 2
        case 'C':
			coord=coord*2;
			initprojection(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
			break;
            //Modifier l'amplitude de la fenetre de coord / 2
		case 'c':
            coord=coord/2;
            initprojection(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
			break;
        case 'D':
			division=division+2;
			break;
            //Modifier l'amplitude de la fenetre de - COORD (minimum 1)
		case 'd':
			if (division >= 4){
                division=division-2;
			}
			break;
            //Plein ecran
        case 'f': glutReshapeWindow(TAILLE_FENETRE,TAILLE_FENETRE);break;
        case 'F': glutFullScreen(); break;
            //Diminuer la taille du quadrillage
        case 'G': quadrillage=1; break;
            //Ne pas tracer le quadrillage
        case 'g': quadrillage=0; break;
            //Remise dans l'etat initial
		case 'O':
        case 'o':
            xr=0;yr=0;zr=0;coord=COORD;axe=0;quadrillage=0;animation=0;
			initprojection(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
            break;
            // Projection perspective
        case 'P':
            perspective = 1;
			initprojection(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
            break;
            // Projection parallèle
        case 'p':
            perspective = 0;
			initprojection(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
            break;
            // Animation
        case 'B': animation=1; break;
            // Arreter l'animation
        case 'b': animation=0; break;
            // Modification de l'angle de vue X de +ANGE
        case 'X': xr+=ANGLE; break;
            // Modification de l'angle de vue X de -ANGE
        case 'x': xr-=ANGLE; break;
            // Modification de l'angle de vue Y de +ANGE
        case 'Y': yr+=ANGLE; break;
            // Modification de l'angle de vue Y de -ANGE
        case 'y': yr-=ANGLE; break;
            // Modification de l'angle de vue Z de +ANGE
        case 'Z': zr+=ANGLE; break;
            // Modification de l'angle de vue Z de -ANGE
        case 'z': zr-=ANGLE;break;
            //Afficher les informations
        case 'I': information = 1; break;
            //Ne pas afficher les informations
        case 'i': information = 0; break;
	}
    clavier(key);
    glutPostRedisplay();
}

void menuAfficher(int selection){
    switch (selection)
    {
        case 0 : key('A',0,0); break;
        case 1 : key('a',0,0); break;
        case 2 : key('G',0,0); break;
        case 3 : key('g',0,0); break;
        case 4 : key('P',0,0); break;
        case 5 : key('p',0,0); break;
		case 6 : key('C',0,0); break;
		case 7 : key('c',0,0); break;
		case 8 : key('D',0,0); break;
		case 9 : key('d',0,0); break;
        case 10 : key('F',0,0); break;
        case 11 : key('f',0,0); break;
        case 12 : key('I',0,0); break;
        case 13 : key('i',0,0); break;
    }
}
void menuAnimer(int selection){
    switch(selection)
    {
        case 0: key('B',0,0); break;
        case 1: key('b',0,0); break;
        case 2: key('O',0,0); break;
        case 3: key('X',0,0); break;
        case 4: key('x',0,0); break;
        case 5: key('Y',0,0); break;
        case 6: key('y',0,0); break;
        case 7: key('Z',0,0); break;
        case 8: key('z',0,0); break;
        case 9 : key('Q',0,0); break;
    }
}


/* Point d'entree du programme  */
int  main(int argc, char *argv[])
{
    int mAnime,mAffiche,f1;
    strcat(version, name);
    glutInit(&argc, argv);
    glutInitWindowSize(TAILLE_FENETRE,TAILLE_FENETRE);
    glutInitWindowPosition(POSITION_FENETRE,POSITION_FENETRE);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
    f1=glutCreateWindow(version); //Creer la fenetre
    glutReshapeFunc(resize); //fonction associee au redimensionnement de la fenetre
    glutDisplayFunc(display); //fonction associee a l'affichage
    glutKeyboardFunc(key); //fonction associee a la gestion du clavier
    
    mAffiche=glutCreateMenu(menuAfficher); //creation des menus
    glutAddMenuEntry("(A)Tracer axes",0);
    glutAddMenuEntry("(a)Pas d axes",1);
    glutAddMenuEntry("(G)Tracer grille",2);
    glutAddMenuEntry("(g)Pas de grille",3);
    glutAddMenuEntry("(P)Perspective",4);
    glutAddMenuEntry("(p)parallele",5);
    glutAddMenuEntry("(C)+ coord fenetre",6);
    glutAddMenuEntry("(c)- coord fenetre",7);
    glutAddMenuEntry("(D)+ division",8);
    glutAddMenuEntry("(d)- divisions",9);
    glutAddMenuEntry("(F)Plein ecran",10);
    glutAddMenuEntry("(f)Fenetre origine",11);
    glutAddMenuEntry("(I)Informations",12);
    glutAddMenuEntry("(i)Pas d'information",13);
    
    mAnime = glutCreateMenu(menuAnimer);
    
    glutAddSubMenu("Options Affichage",mAffiche);
    glutAddMenuEntry("(B)Animer ",0);
    glutAddMenuEntry("(b)Arreter",1);
    glutAddMenuEntry("(oO)Origine",2);
    glutAddMenuEntry("(X)Rotation +x",3);
    glutAddMenuEntry("(x)Rotation -x",4);
    glutAddMenuEntry("(Y)Rotation +y",5);
    glutAddMenuEntry("(y)Rotation -y",6);
    glutAddMenuEntry("(Z)Rotation +z",7);
    glutAddMenuEntry("(Z)Rotation -z",8);
    glutAddMenuEntry("(qQ)Quitter",9);
    
    glutAttachMenu(GLUT_LEFT_BUTTON); //associe menu au bouton gauche
    glClearColor(1,1,1,1);
    glEnable(GL_DEPTH_TEST);
    glutIdleFunc(idle); //fonction associee a l'animation de l'affichage
    initialisation(); //appel de nos initialisations
    glutMainLoop(); //boucle principale
    return EXIT_SUCCESS;
}
/* Dessiner axes x rouge,y vert,z bleue */
void dessin_axes(double *cx, double *cy, double *cz){
	double couleur[4];
	glGetDoublev(GL_CURRENT_COLOR,couleur);
	affiche_vecteur(ORIGINE,AXE_X,cx);
	affiche_vecteur(ORIGINE,AXE_Y,cy);
	affiche_vecteur(ORIGINE,AXE_Z,cz);
    //Afficher x
    affiche_caractere(AXE_X,'x',NOIR);
    //Afficher y
    affiche_caractere(AXE_Y,'y',NOIR);
    //Afficher z
    affiche_caractere(AXE_Z,'z',NOIR);
    glColor3dv(couleur);
}
void initprojection(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (perspective==1){
        glFrustum(-0.55*coord,0.55*coord,-0.55*coord,0.55*coord, coord, 3*coord);
    }
    else {
        glOrtho(-1.1*coord,1.1*coord,-1.1*coord,1.1*coord, coord, 3*coord);
    }
    glViewport(0, 0, width, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
// Fonction callback de resize
void resize(int width, int height) {
    initprojection(width,height);
    redimension(width,height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    taille_fenetre_x=width;
    taille_fenetre_y=height;
}
// Fonction callback d'affichage
void  display(void) {
	double pos_information[3]={-1.1*coord,-1.1*coord,0};
	double pos_message[3]={-1.1*coord,1.04*coord,0};
	char chaine[200];
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslated(0,0,-2*coord); //reculer la scene
    glRotated(xr,1,0,0);
    glRotated(yr,0,1,0);
    glRotated(zr,0,0,1);
    if (quadrillage==1){ dessin_quadrillage(); }
    if (axe==1){ dessin_axes(ROUGE,VERT,BLEU); }
    description(); //appel fonction description de la scene utilisateur
    if (information==1){
		affiche_chaine(pos_message,message,NOIR);
        if (perspective==1){
			sprintf(chaine,"Perspective, coord=%.2f, div=%d, xr=%d, yr=%d, zr=%d",
                    coord,(int)division,(int)xr,(int)yr,(int)zr);
		}
		else{
			sprintf(chaine,"Parallele, coord=%.2f, div=%d, xr=%d, yr=%d, zr=%d",
                    coord,(int)division,(int)xr,(int)yr,(int)zr);
		}
		affiche_chaine(pos_information,chaine,NOIR);
	}
    glFlush(); //valider les modification de la scene
    glutSwapBuffers(); //rendre l'affichage plus fluide
}
/* Fonction callback animation */
void idle(void)
{
    anime(); //appel de la fonction animation de l'utilisateur
    if (animation) { //si l'animation menu validee
        if ((xr<=360) && (yr==0) && (zr==0))
            xr=xr+vitesse;
        else{
            xr=0;
            yr=yr+vitesse;
        }
        if ((xr==0) && (yr<=360) && (zr==0))
            yr=yr+vitesse;
        else{
            yr=0;
            zr=zr+vitesse;
        }
        if ((xr==0) && (yr==0) && (zr<=360))
            zr=zr+vitesse;
        else{
            zr=0;
            xr=xr+vitesse;
        }
        glutPostRedisplay(); //Rafraichir affichage scene
    }
}
void dessin_quadrillage(){
	int compteur;
	double pos_mx[3]={-1.1*coord,0,0};
	double pos_px[3]={coord,0,0};
	double pos_my[3]={0,-coord,0};
	double pos_py[3]={0,0.9*coord,0};
	char chaine[20];
    double i,pos=-coord,incr= 2.0 * coord/division;
	double couleur[4]; //couleur courante
	glGetDoublev(GL_CURRENT_COLOR,couleur);//enregistrer couleur courante
    glColor3dv(NOIR); //couleur quadrillage
	for(compteur=0;compteur<=division;compteur++){
		glBegin(GL_LINES);
		glVertex3d( pos  ,-coord,0);
		glVertex3d( pos  ,coord,0);
		glVertex3d(-coord,pos  ,0);
		glVertex3d(coord,pos   , 0);
		glVertex3d(0    ,pos   ,-coord);
		glVertex3d(0    ,pos   ,coord);
		glVertex3d(0    ,-coord,pos);
		glVertex3d(0    , coord,pos);
		glEnd();
		pos = pos + incr;
	}
	sprintf(chaine,"-%d",(int)coord);
	affiche_chaine(pos_mx,chaine,NOIR);
	affiche_chaine(pos_my,chaine,NOIR);
	sprintf(chaine,"%d",(int)coord);
	affiche_chaine(pos_px,chaine,NOIR);
	affiche_chaine(pos_py,chaine,NOIR);
	glColor3dv(couleur); //restituer couleur courante
}
void affiche_caractere(double p[3],char c,double *coul){
	double couleur[4]; //couleur courante
	glGetDoublev(GL_CURRENT_COLOR,couleur);//enregistrer couleur courante
    glColor3dv(coul); //couleur quadrillage
	glPushMatrix();
	glTranslated(p[0],p[1],p[2]);
	glScaled(0.0005,0.0005,0.0005);
    glPointSize(1);
	glutStrokeCharacter(GLUT_STROKE_ROMAN,c);
	glPopMatrix();
}
void affichePseudoPixel(int x,int y,int z,double *c){
	double xr,yr,zr,incr=2*coord/division,incr2=1-incr/2;
	xr = incr * (double)(x) - incr2; //x,y,z entre 0 et DIVISION-1
	yr = incr * (double)(y) - incr2; //xr,yr,zr entre -1 et 1
	zr = incr * (double)(z) - incr2;
	glColor3dv(c);
	glPushMatrix();
	glTranslated(xr,yr,zr);
	glutSolidSphere(incr/2,8,8);
	glPopMatrix();
}
void affiche_chaine(double p[3],char *chaine,double *coul){
	double couleur[4]; //couleur courante
	glGetDoublev(GL_CURRENT_COLOR,couleur);//enregistrer couleur courante
    glColor3dv(coul); //couleur quadrillage
	glPushMatrix();
	glLoadIdentity();
	glTranslated(p[0],p[1],-2*coord+p[2]);
	glScaled(0.0005*coord,0.0005*coord,0.0005*coord);
	while (*chaine!=0){
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*chaine);
		glTranslated(0.0005,0,0);
		chaine++;
	}
	glPopMatrix();
}
//Affiche vecteur entre deux points oriente de p0 vers p1
void affiche_vecteur(double p0[3],double p1[3],double *c){
	double d[3]={p1[0]-p0[0],p1[1]-p0[1],p1[2]-p0[2]};
	glColor3dv(c);
	glBegin(GL_LINES);
	glVertex3dv(p0);
	glVertex3dv(p1);
	glEnd();
	glPushMatrix();
	glTranslated(p0[0],p0[1],p0[2]);
	//Placez le point dans le plan Oyz (avec z>0)
	// 0/0 indefini -> deja place' dans le plan Oyz si x=0 et z=0
	if ((d[0]!=0) || (d[2]!=0)){
		if (d[2]>=0){
			glRotated(180.0/M_PI*atan(d[0]/d[2]), 0, 1, 0);
		}
		else{
			glRotated(180.0+180.0/M_PI*atan(d[0]/d[2]), 0, 1, 0);
		}
	}
    glRotated(-180.0/M_PI*atan(d[1] / sqrt(d[0]*d[0]+d[2]*d[2])),1,0,0);
	glTranslated(0, 0,sqrt(d[0]*d[0]+d[1]*d[1]+d[2]*d[2])-0.05);
	glutSolidCone(0.025, 0.05, 10, 10);
	glPopMatrix();
}
//Affiche vecteur v en un point p0
void affiche_vecteur2(double p0[3],double v[3],double *c){
	double p1[3];
	p1[0]=p0[0]+v[0];p1[1]=p0[1]+v[1];p1[2]=p0[2]+v[2];
	affiche_vecteur(p0,p1,c);
}
int xcoord2int(double c){
    // c = -coord, retourne 0
    //c  = coord  , retourne TAILLE_FENETRE_X-1
    // 0 = - a * coord  + b (1)
    // TAILLE_FENETRE_X-1 = a * coord + b (2)
    // TAILLE_FENETRE_X-1 = 2 b (1 + 2) => b = (TAILLE_FENETRE_X-1) /2
    // TAILLE_FENETRE_X = 2a coord  (2 -1)  => a = (TAILLE_FENETRE_X-1) /(2 * coord)
    //  -coord * (TAILLE_FENETRE_X-1) /(2 * coord) + (TAILLE_FENETRE_X-1) /2 =>0
    // coord * TAILLE_FENETRE_X /(2 * coord) + TAILLE_FENETRE_X /2 => TAILLE_FENETRE_X
    int resultat = c *(double)(taille_fenetre_x-1) /(2.0 * coord)+ (double)(taille_fenetre_x-1) /2.0;
    if (resultat<=0)
        return 0;
    else
        if (resultat >= taille_fenetre_x-1)
            return taille_fenetre_x-1;
        else
            return resultat;
}
int ycoord2int(double c){
    int resultat = c *(double)(taille_fenetre_y-1) /(2.0 * coord)+ (double)(taille_fenetre_y-1) /2.0;
    if (resultat<=0)
        return 0;
    else
        if (resultat >= taille_fenetre_y-1)
            return taille_fenetre_y-1;
        else
            return resultat;
}

double xint2coord(int i){
    //-coord = 0 a + b   => b = -coord
    //coord  = (TAILLE_FENETRE_X-1) a -coord => a = (2 * coord) / (TAILLE_FENETRE-1)
    double resultat = 2.0 *coord *(double)i /(double)(taille_fenetre_x-1) -coord;
    if (resultat<=-coord)
        return -coord;
    else
        if (resultat>=coord)
            return coord;
        else
            return resultat;
}

double yint2coord(int i){
    double resultat = 2.0 * coord * (double)i /(double)(taille_fenetre_y-1) -coord;
    if (resultat<=-coord)
        return -coord;
    else
        if (resultat>=coord)
            return coord;
        else
            return resultat;
    
}



