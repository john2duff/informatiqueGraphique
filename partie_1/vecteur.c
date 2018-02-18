#include "../base.c"
char name[]="Vecteur !"; 
char message[100];
int scene=0;
typedef double vecteur[];//[0] pour x,[1] pour y,[2] pour z.
//Addition de  deux vecteurs v <- v1 + v2
void Addition(vecteur v1,vecteur v2,vecteur v);
//Multiplication d'un vecteur par un scalaire v<- alpha v1
void MultiplicationScalaire(double alpha,vecteur v1,vecteur v);
//Produit scalaire de deux vecteurs <- u .v
double ProduitScalaire(vecteur u ,vecteur v );
//Norme d'un vecteur
double Norme(vecteur);
//Normaliser un vecteur v <- ||u||
void Normaliser(vecteur u,vecteur v);
//Produit vectoriel w <- u ^ v
void ProduitVectoriel(vecteur u,vecteur v,vecteur w);

vecteur v1={0.577350,0.577350,0.577350};
vecteur v2={0.577350,0.707106,0.0};
vecteur v3={0.0,0.0,0.0};
//Description de notre scene
void description(){
    switch (scene){
        case 0 :
            Addition(v1,v2,v3);
            affiche_vecteur(ORIGINE,v1,JAUNE);
            affiche_vecteur(ORIGINE,v2,ORANGE);			
            affiche_vecteur(ORIGINE,v3,VIOLET);
            break;
        case 1:
            Normaliser(v2,v3);
            affiche_vecteur(ORIGINE,v2,ORANGE);			
            affiche_vecteur(ORIGINE,v3,VIOLET);
            break;
        case 2:
            ProduitVectoriel(v1,v2,v3);
            affiche_vecteur(ORIGINE,v1,JAUNE);
            affiche_vecteur(ORIGINE,v2,ORANGE);			
            affiche_vecteur(ORIGINE,v3,VIOLET);
            break;
    }
}
void menuScene(int selection){
    scene=selection;
    glutPostRedisplay();
}
//Mes initialisations 
void initialisation(){
    //Creation du menu bouton droit de la souris
    int mScene;
    mScene=glutCreateMenu(menuScene);
    glutAddMenuEntry("Addition 2 vecteurs",0);
    glutAddMenuEntry("Normaliser vecteurs",1);
    glutAddMenuEntry("Produit vectoriel",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    information=1;
    coord=2.0;
}
void clavier(unsigned char key){}
void redimension(int width, int height){}

void anime(){
    switch(scene){
        case 0 :
            sprintf(message,"Addition - resultat x=%.2f, y=%.2f, z=%.2f, norme=%.2f",
                v3[0],v3[1],v3[2],Norme(v3)); 
            break;
        case 1 :
            sprintf(message,"Normaliser - resultat x=%.2f, y=%.2f, z=%.2f, norme=%.2f",
                v3[0],v3[1],v3[2],Norme(v3));
                break;
        case 2 :
            sprintf(message,"Produit vectoriel - resultat x=%.2f, y=%.2f, z=%.2f, norme=%.2f",
                v3[0],v3[1],v3[2],Norme(v3));
            break;
    }
    glutPostRedisplay();	
}
//Addition de deux vecteurs
void Addition(vecteur v1,vecteur v2,vecteur v){
    v[0] = v2[0] + v1[0];
    v[1] = v2[1] + v1[1];
    v[2] = v2[2] + v1[2]; }
//Multiplication d'un vecteur par un scalaire
void MultiplicationScalaire(double alpha,vecteur v1,vecteur v){
    v[0] = v1[0] * alpha;
    v[1] = v1[1] * alpha;
    v[2] = v1[2] * alpha; }
//Produit scalaire de deux vecteurs
double ProduitScalaire(vecteur u,vecteur v){
    return (u[0] * v[0] + u[1] * v[1] + u[2] * v[2]);}
//Norme d'un vecteur
double Norme(vecteur v){
    return sqrt(ProduitScalaire(v,v));}
//Normaliser un vecteur
void Normaliser(vecteur v1,vecteur v){
    MultiplicationScalaire(1/Norme(v1),v1,v);}
//Produit vectoriel
void ProduitVectoriel(vecteur u,vecteur v,vecteur w){
    w[0] = u[1] * v[2] - v[1] * u[2];
    w[1] = u[2] * v[0] - v[2] * u[0];
    w[2] = u[0] * v[1] - v[0] * u[1]; }
