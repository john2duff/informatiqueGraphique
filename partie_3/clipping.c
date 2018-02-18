#include "../base.c"
char name[]="Cohen Sutherland !";
char message[200];
typedef struct position{
    double x,y;} Position;
typedef struct segment{
    Position p1,p2;}Segment;
typedef struct {
    Position gb,hd;}Fenetre;
Segment souris;
typedef char Code;
void echange(double *,double *);
Code codepos(Fenetre, Position);
double intersectionX(Segment, double);
double intersectionY(Segment, double);
void TraceSegment(Segment,double*);
void clipping(Fenetre, Segment,double*);
void TraceFenetre(Fenetre,double *);
void echange(double *a,double *b) {
    double c; c=*a; *a=*b; *b=c; }
void TraceSegment(Segment s,double *c){
	glColor3dv(c);
	glBegin(GL_LINES);
	glVertex2d(s.p1.x,s.p1.y);
	glVertex2d(s.p2.x,s.p2.y);
	glEnd();
}
void TraceFenetre(Fenetre f,double *c){
	glColor3dv(c);
	glBegin(GL_LINE_LOOP);
	glVertex2d(f.gb.x,f.gb.y);
	glVertex2d(f.hd.x,f.gb.y);
	glVertex2d(f.hd.x,f.hd.y);
	glVertex2d(f.gb.x,f.hd.y);
	glEnd();
}
void Souris(int bouton,int etat, int x,int y){
	double xf,yf,c=coord+0.1;
	if (bouton == GLUT_RIGHT_BUTTON){
		xf = (double) glutGet(GLUT_WINDOW_WIDTH);
		yf = (double) glutGet(GLUT_WINDOW_HEIGHT);
		if (etat == GLUT_DOWN){
			//Coordonnees souris entre 0 et xf, 0 et yf (0,0) coin supérieur-gauche
			//Coordonnees ecran entre -coord-0.1 et coord+0.1
			// x=-coord-0.1 pour xf=0  et x=coord+0.1 pour xf=taille fenetre
			// y=-coord-0.1 pour yf=taille fenetre et y=coord+0.1 pour yf=0
			souris.p1.x= 2*c*x /xf - c;
			souris.p1.y=  -2 *c*y /yf + c;
		}
		else{
			souris.p2.x= 2*c*x /xf - c;
			souris.p2.y= -2 *c*y /yf + c;
			glutPostRedisplay();
		}
	}
}
void initialisation(){
	glutMouseFunc(Souris);
}
void description(){
	Fenetre f ={-0.75,-0.75,0.75,0.75};
	TraceFenetre(f,BLEU);
	clipping(f,souris,VERT);
}
void redimension(int x,int y){}
void clavier(unsigned char x){}
void anime(){}
Code codepos(Fenetre f, Position p){
    Code c;
    c=0;
    if (p.x < f.gb.x) c=c+1;
    if (p.x > f.hd.x) c=c+2;
    if (p.y < f.gb.y) c=c+4;
    if (p.y > f.hd.y) c=c+8;
    return c;
}
double intersectionX(Segment s, double y){
	double a,b;
	a = (s.p2.x - s.p1.x)/ (s.p2.y - s.p1.y);
	b = s.p1.x - a * s.p1.y;
	return a * y + b;
}
double intersectionY(Segment s, double x){
	double a,b;
	a = (s.p2.y - s.p1.y)/(s.p2.x - s.p1.x);
	b = s.p1.y - a *s.p1.x;
	return a * x + b;
}
void clipping(Fenetre f, Segment s,double *c){
	Code c1,c2;
	c1 = codepos(f,s.p1) ;
	c2 = codepos(f,s.p2) ;
	while( ((c1!=0) || (c2!=0)) && ((c1 & c2)==0) ){
		if(c1==0) {
			echange(&s.p1.x,&s.p2.x);
			echange(&s.p1.y,&s.p2.y);
			c1=c2;
		}
		//s.p1 a gauche de la fenêtre
		if((c1 & 1) == 1 ) {
            s.p1.y = intersectionY(s,f.gb.x);
            s.p1.x = f.gb.x;
		}
        else{
			// s.p1 a droite de la fenetre
			if((c1 & 2) == 2) {
				s.p1.y = intersectionY(s,f.hd.x);
				s.p1.x=f.hd.x;}
            else{
				//s.p1 en bas de la fenetre
                if((c1 & 4)==4) {
					s.p1.y = intersectionX(s,f.gb.y);
					s.p1.y=f.gb.y;
				}
                else{
					//s.p1 en haut de la fenetre
                    if((c1 & 8 )== 8) {
						s.p1.y = intersectionX(s,f.hd.y);
						s.p1.y=f.hd.y;
					}
				}
			}
		}
        c1 = codepos(f,s.p1) ;
        c2 = codepos(f,s.p2) ;}
    //s dans la fenetre
  	if((c1==0) && (c2==0)){
        TraceSegment(s,c);
    }
}

