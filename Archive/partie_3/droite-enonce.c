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
//Tracede droite base sur l'algorithme naif
void traceDroite_v1(int x0,int y0,int dx,int dy,double *c){
	// A ecrire
}
//Trace de droite base sur l'algorithme incrémental
void traceDroite_v2(int x0,int y0,int dx,int dy,double *c){
	// A ecrire
}
//Trace de droite  base sur l'algorithme demi-point
void traceDroite_v3(int x0,int y0,int dx,int dy,double *c){
	// A ecrire
}
//Trace de droite sur l'algorithme anti crenelage
void traceDroite_v4(int x0,int y0,int dx,int dy,double *c){
	// A ecrire
}
