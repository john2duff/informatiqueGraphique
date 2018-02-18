#include "../base.c"
char name[]="Trace de droites !";
char message[200];
int typeDroite=0;
double gs( double); //Fonction pondération de Gupta-Sproull
void filtre(double,double *,double*); //Application fonction de pondération aux couleurs
void tracedroiteTheorique(int x0,int y0,int dx,int dy,double *c);
void traceDroite_v1(int x0,int y0,int dx,int dy,double *c);
void traceDroite_v2(int x0,int y0,int dx,int dy,double *c);
void traceDroite_v3(int x0,int y0,int dx,int dy,double *c);
void traceDroite_v4(int x0,int y0,int dx,int dy,double *c);
void description(){
	switch(typeDroite){
		case 0:
			tracedroiteTheorique(1,10,15,4,ROUGE);
			traceDroite_v1(1,10,15,4,ROUGE);
			tracedroiteTheorique(1,11,5,8,VERT);
			traceDroite_v1(1,11,5,8,VERT);
			tracedroiteTheorique(1,9,15,-4,BLEU);
			traceDroite_v1(1,9,15,-4,BLEU);
			tracedroiteTheorique(1,8,5,-8,NOIR);
			traceDroite_v1(1,8,5,-8,NOIR);
			break;
		case 1:
			tracedroiteTheorique(1,10,15,4,ROUGE);
			traceDroite_v2(1,10,15,4,ROUGE);
			tracedroiteTheorique(1,11,5,8,VERT);
			traceDroite_v2(1,11,5,8,VERT);
			tracedroiteTheorique(1,9,15,-4,BLEU);
			traceDroite_v2(1,9,15,-4,BLEU);
			tracedroiteTheorique(1,8,5,-8,NOIR);
			traceDroite_v2(1,8,5,-8,NOIR);
			break;
		case 2:
			tracedroiteTheorique(1,10,15,4,ROUGE);
			traceDroite_v3(1,10,15,4,ROUGE);
			tracedroiteTheorique(1,11,5,8,VERT);
			traceDroite_v3(1,11,5,8,VERT);
			tracedroiteTheorique(1,9,15,-4,BLEU);
			traceDroite_v3(1,9,15,-4,BLEU);
			tracedroiteTheorique(1,8,5,-8,NOIR);
			traceDroite_v3(1,8,5,-8,NOIR);
			break;
		case 3:
			tracedroiteTheorique(1,10,16,8,ROUGE);
			traceDroite_v4(1,10,16,8,ROUGE_FONCE);
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
void tracedroiteTheorique(int x0,int y0,int dx,int dy,double *couleur){
	double x1,y1,x2,y2,incr=2*coord/division,incr2=1-incr/2;
	x1 = incr * (double)x0 - incr2;
	y1 = incr * (double)y0 - incr2;
	x2 = incr * (double)(x0+dx) - incr2;
	y2 = incr * (double)(y0+dy) - incr2;
	glColor3dv(couleur);
	glBegin(GL_LINES);
	glVertex3d(x1,y1,0);
	glVertex3d(x2,y2,0);
	glEnd();
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
	if ((dx==0)&&(dy==0)){
	 	affichePseudoPixel(x0,y0,0,c);
		return;
	}
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
			affichePseudoPixel(x0+i,(int)(y0+m*i),0,c);
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
			affichePseudoPixel((int)(x0+m*i),y0+i,0,c);
		}
	}
}
//Trace de droite sur l'algorithme incremental
void traceDroite_v2(int x0,int y0,int dx,int dy,double *c){
	double m,y,x;
    int i;
	if ((dx==0)&&(dy==0)){
	 	affichePseudoPixel(x0,y0,0,c);
		return;	}
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
			affichePseudoPixel(x0+i,(int)(y),0,c);
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
			affichePseudoPixel((int)(x),y0+i,0,c);
			x = x + m;
		}
	}
}
//Trace de droite  sur l'algorithme demi-point
void traceDroite_v3(int x0,int y0,int dx,int dy,double *c){
    int i,d,inc,incA,incNA;
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
        affichePseudoPixel(x0,y0,0,c);
        for(i=1;i<=dx;i++){
            if (d<=0) {
                d=d+incA; }
            else{
                d=d+incNA;
                y0=y0+inc; }
            affichePseudoPixel(x0+i,y0,0,c);
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
        affichePseudoPixel(x0,y0,0,c);
        for(i=1;i<=dy;i++){
            if (d<=0){
                d=d+incA;}
            else{
                d=d+incNA;
                x0=x0+inc;}
            affichePseudoPixel(x0,y0+i,0,c);
        }
    }
}
//Trace de droite sur l'algorithme anti crenelage
void traceDroite_v4(int x0,int y0,int dx,int dy,double *c){
    int i,D1,dp,inc,incA,incNA;
    double denomimateur = 2.0 * sqrt(((double)dx *(double)dx)+((double)dy *(double)dy));
    double cf[3];
	if ((dx==0)&&(dy==0)){
	 	affichePseudoPixel(x0,y0,0,c);
		return;
	}
    if (abs(dx)>abs(dy)){
        if (dx<0){
			x0 = x0 + dx;
			y0 = y0 + dy;
			dx =   -  dx;
			dy =   -  dy;
        }
        inc=1;
        dp=2*dy-dx;
        incNA=2*(dy-dx);
        incA=2*dy;
        affichePseudoPixel(x0,y0,0,c);// v = 0 pour ce point initial
        filtre(2.0 *(double)dx / denomimateur,c,cf);
        affichePseudoPixel(x0,y0+1,0,cf); // v= 1 pour ce point initial
        affichePseudoPixel(x0,y0-1,0,cf);
        for(i=1;i<=dx;i++){
            if (dp<=0) {
                D1=dp+dx;
                dp=dp+incA;
            }
            else{
                D1=-dp-dx;
                dp=dp+incNA;
                y0=y0+inc;
            }
            filtre((double) D1 / denomimateur,c,cf);
     		affichePseudoPixel(x0+i,y0,0,cf);
            filtre((double) (2 *dx + D1) / denomimateur,c,cf);
     	 	affichePseudoPixel(x0+i,y0-1,0,cf);
            filtre((double) (2 *dx - D1) / denomimateur,c,cf);
            affichePseudoPixel(x0+i,y0+1,0,cf);
        }
	}
}
