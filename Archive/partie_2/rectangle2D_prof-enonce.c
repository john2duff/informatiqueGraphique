#include "../base.c"
char name[]="Profondeur rectangle";
char message[200];
int prof[DIVISION][DIVISION]; //tableau de profondeur
double coul[DIVISION][DIVISION][3]; //Tableau de DIVISION x DIVISION de r,v,b
typedef double rec[9]; // rectangle x1,y1,z1,x2,y2,z2,r,v,b dans cet ordre !
rec  liste[]= {
    { 0, 0, 5,10,10,10, 1,0,0},
    { 5, 5, 15,15,15, 5, 0,1,0},
    {10,10,19,19,19, 5, 0,0,1}}; //Ici z1 utilise seulement.
void remplirTab(rec r);
void initTab(double *fond,int arriere);
void anime(){}
void clavier(unsigned char key){}
void redimension(int width, int height){}
void initialisation(){
	int i;
	initTab(BLANC,0); //0 point le plus loin et 19 le plus proche
	for (i=0;i<sizeof(liste)/sizeof(rec);i++){
        remplirTab(liste[i]);
    }
}
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
            //A ecrire
        }
    }
}
void remplirTab(rec r){
    int x,y;
    for (y=r[1];y<=r[4];y++){
        for(x=r[0];x<=r[3];x++){
            if (??? ){ //meme profondeur ici !!!
                // A ecrire
            }
        }
    }
} 

