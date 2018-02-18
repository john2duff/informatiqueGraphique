#include "../base.c"
char name[]="Trace de droites reelles !";
char message[200];
int typeDroite=1;
double gs( double); //Fonction ponderation de Gupta-Sproull
void filtre(double,double *,double*); //Application fonction de ponderation aux couleurs

void tracedroiteTheorique(int x0,int y0,int dx,int dy,double *c);
void traceDroite_v1(int x0,int y0,int dx,int dy,double *c);
void traceDroite_v2(int x0,int y0,int dx,int dy,double *c);
void traceDroite_v3(int x0,int y0,int dx,int dy,double *c);
void traceDroite_v4(int x0,int y0,int dx,int dy,double *c);


void description(){
    int x0=xcoord2int(-1.0),y0=ycoord2int(-1.0);
    int dx0=xcoord2int(-0.75)-x0,dy0=ycoord2int(0)-y0;
    
    int x1=xcoord2int(0.0),y1=ycoord2int(0.0);
    int dx1=xcoord2int(1.0)-x1,dy1=ycoord2int(0.75)-y1;

	switch(typeDroite){
		case 0:
			traceDroite_v1(x0,y0,dx0,dy0,ROUGE);
			traceDroite_v1(x1,y1,dx1,dy1,ROUGE_FONCE);
			break;
		case 1:
			traceDroite_v2(x0,y0,dx0,dy0,ROUGE);
			traceDroite_v2(x1,y1,dx1,dy1,ROUGE_FONCE);
			break;
		case 2:
			traceDroite_v3(x0,y0,dx0,dy0,ROUGE);
			traceDroite_v3(x1,y1,dx1,dy1,ROUGE_FONCE);
			break;
		case 3:
			traceDroite_v4(x1,y1,dx1,dy1,ROUGE_FONCE);
			break;

    }
}
void redimension(int x,int y){}
void anime(){
	switch(typeDroite){
		case 0:
			sprintf(message,"Algorithme naif");
			break;
		case 1:
			sprintf(message,"Algorithme incremental");
			break;
		case 2:
			sprintf(message,"Algorithme du demi-point");
			break;
		case 3:
			sprintf(message,"Algorithme anti-aliasing");
			break;
	}
	glutPostRedisplay();
}
void clavier(unsigned char c){}
void filtre(double d,double *c,double *cf){
	d = gs(fabs(d));
	cf[0]=c[0]*d;
	cf[1]=c[1]*d;
	cf[2]=c[2]*d;
}
double gs( double d) {
    if( d >= 1.40)
        return 22/8.0;
    else
        if( (d >= 1.20) && (d <= 1.40))
            return 20/8.0;
        else
            if( (d >= 1.08) && (d <= 1.20))
                return 18/8.0;
            else
                if((d >= 1.00) && (d <= 1.08))
                    return 16/8.0;
                else
                    if( (d >= 0.92) && (d <= 1.00))
                        return 14/8.0;
                    else
                        if((d >= 0.80 && d <= 0.92))
                            return 12/8.0;
                        else
                            if((d >= 0.60) && (d <= 0.80))
                                return 10/8.0;
                            else
                                return 8.0/8.0;
}
void menuScene(int selection){
	typeDroite = selection;
	glutPostRedisplay();
}
void initialisation(){
	int mScene;
	mScene=glutCreateMenu(menuScene);
    glutAddMenuEntry("Algorithme naif",0);
    glutAddMenuEntry("Algorithme incremental",1);
    glutAddMenuEntry("Algorithme du demi-point",2);
    glutAddMenuEntry("Algorithme Anti aliasing",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	information=1;
}
//Trace de droite sur l'algorithme naif
void traceDroite_v1(int x0,int y0,int dx,int dy,double *c){
	double m;
	int i;
    glColor3dv(c);
	if ((dx==0)&&(dy==0)){
        glBegin(GL_POINTS);
        // A modifier
        glVertex2d(xint2coord(???),yint2coord(???));
        glEnd();
		return;
	}
    glBegin(GL_POINTS);
	if (abs(dx) > abs(dy)){
        //Parcours en x
		if (dx < 0) { //inverser x et y
			x0 = x0 + dx;
			y0 = y0 + dy;
			dx =   -  dx;
			dy =   -  dy;
		}
		m = (double)(dy) / (double)(dx);
		for (i=0;i<=dx;i++){
            // A modifier
            glVertex2d(xint2coord(???),yint2coord(???));
		}
    }
	else{
		//Parcours en y
		if (dy<0){
			x0 = x0 + dx;
			y0 = y0 + dy;
			dx =   -  dx;
			dy =   -  dy;
		}
		m = (double) dx / (double) dy;
		for (i=0;i<=dy;i++){
            // A modifier
            glVertex2d(xint2coord(???),yint2coord(???));
		}
	}
    glEnd();
}
//Trace de droite sur l'algorithme incremental
void traceDroite_v2(int x0,int y0,int dx,int dy,double *c){
	double m,y,x;
    int i;
    glColor3dv(c);
	if ((dx==0)&&(dy==0)){
        glBegin(GL_POINTS);
        // A modifier
        glVertex2d(xint2coord(???),yint2coord(???));
        glEnd();
		return;
    }
    glBegin(GL_POINTS);
	if (abs(dx) > abs(dy)){
        //Parcours en x
		if (dx < 0) {
			x0 = x0 + dx;
			y0 = y0 + dy;
			dx =   -  dx;
			dy =   -  dy;
		}
		m = (double) dy / (double) dx;
        y = (double) y0;
		for (i=0;i<=dx;i++){
            // A modifier
            glVertex2d(xint2coord(???),yint2coord(???));
			y=y + m;
		}
    }
	else{
		//Parcours en y
		if (dy<0){
			x0 = x0 + dx;
			y0 = y0 + dy;
			dx =   -  dx;
			dy =   -  dy;
		}
		m = (double) dx / (double) dy;
        x = (double) x0;
		for (i=0;i<=dy;i++){
            // A modifier
            glVertex2d(xint2coord(???),yint2coord(???));
			x = x + m;
		}
	}
    glEnd();
}
//Trace de droite  sur l'algorithme demi-point
void traceDroite_v3(int x0,int y0,int dx,int dy,double *c){
    int i,d,inc,incA,incNA;
    glColor3dv(c);
    glBegin(GL_POINTS);
    if (abs(dx)>abs(dy)){
        if (dx<0){
			x0 = x0 + dx;
			y0 = y0 + dy;
			dx =   -  dx;
			dy =   -  dy;
        }
        if(dy>0){
            inc=1;
            d=2*dy-dx;
            incNA=2*(dy-dx);
            incA=2*dy;
        }
        else{
            inc=-1;
            d=-2*dy-dx;
            incNA=-2*(dy+dx);
            incA=-2*dy;
        }
        // A modifier
        glVertex2d(xint2coord(???),yint2coord(???));
        for(i=1;i<=dx;i++){
            if (d<=0) {
                d=d+incA; }
            else{
                d=d+incNA;
                y0=y0+inc; }
            // A modifier
            glVertex2d(xint2coord(???),yint2coord(???));
		}
	}
    else {
        if (dy<0){
			x0 = x0 + dx;
			y0 = y0 + dy;
			dx =   -  dx;
			dy =   -  dy;
		}
        if(dx>0) {
            inc=1;
            d=2*dx-dy;
            incNA=2*(dx-dy);
            incA=2*dx;}
        else {
            inc=-1;
            d=-2*dx-dy;
            incNA=-2*(dy+dx);
            incA=-2*dx; }
        // A modifier
        glVertex2d(xint2coord(???),yint2coord(???));
        for(i=1;i<=dy;i++){
            if (d<=0){
                d=d+incA;}
            else{
                d=d+incNA;
                x0=x0+inc;}
            // A modifier
            glVertex2d(xint2coord(???),yint2coord(???));
        }
    }
    glEnd();
}
//Trace de droite sur l'algorithme anti crenelage
void traceDroite_v4(int x0,int y0,int dx,int dy,double *c){
    int i,D,d=0,inc,incA,incNA;
    double cf[3];
    glBegin(GL_POINTS);
    if (abs(dx)>abs(dy)){
        if (dx<0){
			x0 = x0 + dx;
			y0 = y0 + dy;
			dx =   -  dx;
			dy =   -  dy;
        }
        inc=1;
        d=2*dy-dx;
        incNA=2*(dy-dx);
        incA=2*dy;
        glColor3dv(c);
        // A modifier
        glVertex2d(xint2coord(???),yint2coord(???));
        filtre((double)dx / sqrt((double)(dx*dx)+(double)(dy*dy)),c,cf);
        glColor3dv(???);
        glVertex2d(xint2coord(???),yint2coord(???));
        glColor3dv(???);
        glVertex2d(xint2coord(???),yint2coord(???));
        for(i=1;i<=dx;i++){
            if (d<=0) {
                D=d+dx;
                d=d+incA;
            }
            else{
                D=-d-dx;
                d=d+incNA;
                y0=y0+inc;
            }
            filtre((double) D / (2.0 * sqrt((double)(dx*dx)+(double)(dy*dy))),c,cf);
            // A modifier
            glColor3dv(???);
            glVertex2d(xint2coord(???),yint2coord(???));
            filtre((double) (2 *dx + D) / (2.0 * sqrt((double)(dx*dx)+(double) (dy*dy))),c,cf);
            glColor3dv(???);
            glVertex2d(xint2coord(???),yint2coord(???));
            filtre((double) (2 *dx - D) / (2.0 * sqrt((double)(dx*dx)+(double)(dy*dy))),c,cf);
            glColor3dv(???);
            glVertex2d(xint2coord(???),yint2coord(???));
        }
	}
    glEnd();
}
