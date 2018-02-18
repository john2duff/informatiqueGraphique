#include "../base.c"
char name[]="Profondeur rectangle 3D";
char message[200];
int prof[DIVISION][DIVISION]; //tableau de profondeur
double coul[DIVISION][DIVISION][3]; //Tableau de couleurs de r,v,b
typedef double rec[9]; // rectangle x1,y1,z1,x2,y2,z2,r,v,b dans cet ordre !
rec  liste[]= {
    { 0, 0, 5,10,10,10, 1,0,0},
    { 5, 5, 15,15,15, 5, 0,1,0},
    {10,10,19,19,19, 5, 0,0,1}};
void remplirTab(rec r);
void initTab(double *fond,int arriere);
void initialisation(){
	int i;
	initTab(BLANC,0);
	for (i=0;i<sizeof(liste)/sizeof(rec);i++){
        remplirTab(liste[i]);
    }
}
void anime(){}
void clavier(unsigned char key){}
void redimension(int width, int height){}
void description(){
    int x,y;
    for (y=0;y<DIVISION;y++){
        for (x=0;x<DIVISION;x++){
            affichePseudoPixel(x,y,prof[x][y],coul[x][y]);
        }
    }
}
void initTab(double *fond,int arriere){
    int l,c;
    for(l=0;l<DIVISION;l++){
        for(c=0;c<DIVISION;c++){
            prof[l][c]=arriere;
            coul[l][c][0]=fond[0];
            coul[l][c][1]=fond[1];
            coul[l][c][2]=fond[2];
        }
    }
}
void remplirTab(rec r){
    int x,y,z;
    double m=(r[5]-r[2])/(r[4]-r[1]);//(z2-z1) / (y2-y1)
    for (y=r[1];y<=r[4];y++){
        z = (int)(r[2] + m*(double)(y-r[1])); // z<- z1 + m (y-y1)
        for(x=r[0];x<=r[3];x++){
            if (z>prof[x][y]){
                prof[x][y]=z;
                coul[x][y][0]=r[6];//r
                coul[x][y][1]=r[7];//v
                coul[x][y][2]=r[8];//b
            }
        }
    }
} 
