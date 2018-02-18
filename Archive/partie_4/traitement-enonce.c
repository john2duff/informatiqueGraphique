#include "../base.c"
char name[]="Traitement d'image";
char message[200];
int f2;
int scene=0;

#define TAILLE 480

typedef double typeFiltre [3][3];
typedef GLubyte typeImage [TAILLE*TAILLE*3];
typedef double typeSpectre[256];

typeFiltre passe_bas={{0,1.0/5,0},{1.0/5,1.0/5,1.0/5},{0,1.0/5,0}};
typeFiltre croix={{0,1,0},{1,0,-1},{0,-1,0}};
typeFiltre laplacien_carre={{0,1,0},{1,-4,1},{0,1,0}};
typeFiltre laplacien_octogonal={{1,1,1},{1,-8,1},{1,1,1}};

typeImage image1,image2,image3; //image 3 <- image 1 op image 2

typeSpectre spectre ;

void affiche_spectre(typeImage src);
void lectureImage(char *fichier,typeImage image);
void filtreMatriciel(typeFiltre f,typeImage src,typeImage dest);
void monochrome(typeImage src,typeImage dest);
void operationBase(GLubyte (*operateur)(GLubyte,GLubyte),typeImage src1,
						typeImage src2,typeImage dest);

GLubyte ET (GLubyte a,GLubyte b);
GLubyte OU (GLubyte a,GLubyte b);
GLubyte XOU(GLubyte a,GLubyte b);
GLubyte NON(GLubyte a,GLubyte b);
GLubyte OUI(GLubyte a,GLubyte b);
GLubyte INVERSE(GLubyte a,GLubyte b);
GLubyte LUMM(GLubyte a,GLubyte b); // - luminosite
GLubyte LUMP(GLubyte a,GLubyte b); // + luminosite
GLubyte CONTM(GLubyte a,GLubyte b); // - contraste
GLubyte CONTP(GLubyte a,GLubyte b); // + constraste

void lectureImage(char *fichier,typeImage image) {
	int i,j;
  FILE *f = fopen(fichier,"rb") ;
  if ( f ) {		
		if (fread(image,3,TAILLE*TAILLE,f) != (TAILLE*TAILLE)) {
    	printf("Erreur taille \n");
    	exit(-1);
		}
    fclose(f);
	}
  else{
		printf("Fichier non trouve !");
  	exit(-1);
	}
}
void affiche_spectre(typeImage src){
	typeSpectre spectre;
	int x,y;
	for ( y = 0 ; y < 256 ; y++ ){
	  spectre[y]=0.0;
	}
	#define SRC(x,y,k)  src[3*((y)*TAILLE+(x)) + k]
  for ( y = 0 ; y < TAILLE ; y++ ){ //largeur 
  	for ( x = 0 ; x < TAILLE ; x++ ){ //hauteur
 			spectre[(SRC(x,y,0)+SRC(x,y,1)+SRC(x,y,2))/3]++;
 		}	
	}	
	#undef SRC
	double max=spectre[0];
	for(x=1;x<256;x++){
		if (spectre[x]> max){
			max = spectre[x];
		}
	}
	glColor3dv(ROUGE);
	for(x=0;x<256;x++){
		if (spectre[x]!=0.0){
			glBegin(GL_LINES);
				glVertex2d(-1.0+2.0/256.0*(double)x,-1.0);
				glVertex2d(-1.0+2.0/256.0*(double)x,
									 -1.0+2.0*spectre[x]/max);
			glEnd();
		}
	}
}
void description2(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity(); 
  glTranslated(0,0,-2*coord); //reculer la scene
  glRotated(xr,1,0,0); //Rotation de la scene 
  glRotated(yr,0,1,0);
  glRotated(zr,0,0,1);
	affiche_spectre(image3);
  glFlush(); //valider les modification de la scène 
  glutSwapBuffers(); //rendre l'affichage plus fluide
}
void menu(int selection){
	scene=selection;
	glutPostRedisplay();
}
void description(){
	switch (scene){
		//case 0: InitImage(image3);break;
		case 0: operationBase(OUI,image2,image1,image3);break;
		case 1: operationBase(OUI,image1,image2,image3);break;
		case 2: filtreMatriciel(croix,image1,image3); break;
		case 3: filtreMatriciel(laplacien_carre,image1,image3); break;
		case 4: filtreMatriciel(laplacien_octogonal,image1,image3);break;
		case 5: filtreMatriciel(passe_bas,image2,image3);break;
		case 6: operationBase(ET,image1,image2,image3);break;
		case 7: operationBase(OU,image1,image2,image3);break;
		case 8: operationBase(NON,image1,image2,image3);break;
		case 9: operationBase(XOU,image1,image2,image3);break;
		case 10: monochrome(image2,image3);break;
		case 11: operationBase(INVERSE,image2,image2,image3);break;
		case 12: operationBase(LUMM,image2,image2,image3);break;
		case 13: operationBase(LUMP,image2,image2,image3);break;
		case 14: operationBase(CONTM,image2,image2,image3);break;
		case 15: operationBase(CONTP,image2,image2,image3);break;
	}
	glDrawPixels(TAILLE,TAILLE,GL_RGB,GL_UNSIGNED_BYTE,image3);
	glutPostWindowRedisplay(f2);
}
void anime(){}
void initialisation(){
 	glutInitWindowPosition(490,10);
 	int m;
 	char name2[]="spectre";
  m=glutCreateMenu(menu);
  glutAddMenuEntry("besac.raw",0);
  glutAddMenuEntry("abc.raw",1);
  glutAddMenuEntry("Croix",2);
  glutAddMenuEntry("Laplacien carre",3);
  glutAddMenuEntry("Laplacien octogonale",4);
  glutAddMenuEntry("Passe bas carre",5);
  glutAddMenuEntry("ET",6);
  glutAddMenuEntry("OR",7); 
  glutAddMenuEntry("NOT",8);
  glutAddMenuEntry("XOR",9);
  glutAddMenuEntry("Monochrome",10);
  glutAddMenuEntry("Inverse",11);
  glutAddMenuEntry("- luminosite ",12);
  glutAddMenuEntry("+ luminosite ",13);
  glutAddMenuEntry("- contraste ",14);
  glutAddMenuEntry("+ contraste ",15);  
  
  glutAttachMenu(GLUT_RIGHT_BUTTON);  
  glutInitWindowSize(TAILLE_FENETRE/2,TAILLE_FENETRE/2);
  glutInitWindowPosition(POSITION_FENETRE,POSITION_FENETRE+TAILLE_FENETRE);
	f2=glutCreateWindow(name2); //Creer la fenetre
  glutReshapeFunc(resize); //fonction associee au redimensionnement de la fenetre
  glutDisplayFunc(description2); //fonction associee a l'affichage
	glClearColor(1,1,1,1); //Couleur du fond
  lectureImage("abc.raw",image1); //Charger image 
	lectureImage("besac.raw",image2); //Charger image
}
void clavier(unsigned char key){}
void redimension(int width, int height){}


GLubyte ET (GLubyte a,GLubyte b){ 
	// A ecrire
}
GLubyte OU (GLubyte a,GLubyte b){
	// A ecrire
}
GLubyte XOU(GLubyte a,GLubyte b){ 
		// A ecrire
}
GLubyte NON(GLubyte a,GLubyte b){		
	// A ecrire
}
GLubyte OUI(GLubyte a,GLubyte b){	
		// A ecrire
}
GLubyte INVERSE(GLubyte a,GLubyte b){	
		// A ecrire
}
GLubyte LUMM(GLubyte a,GLubyte b){	
	// A ecrire
}
GLubyte LUMP(GLubyte a,GLubyte b){	
	// A ecrire
}
GLubyte CONTM(GLubyte a,GLubyte b){
	if (a<127){
		// A ecrire
	}			
	else{
		// A ecrire
	}
}
GLubyte CONTP(GLubyte a,GLubyte b){
	if (r<0.5){
		// A ecrire
	}
	else{
	// A ecrire
	}
}

void monochrome(typeImage src,typeImage dest){
	#define SRC(x,y,k)  src[3*((y)*TAILLE+(x)) + k]  
	#define DEST(x,y,k) dest[3*((y)*TAILLE+(x)) + k]
	int x,y;
  for ( y = 0 ; y < TAILLE ; y++ ) //largeur
  	for ( x = 0 ; x < TAILLE ; x++ ){ //hauteur
		// A ecrire
	}
	#undef SRC
	#undef DEST
}

void operationBase(GLubyte (*operateur)(GLubyte,GLubyte),typeImage src1,typeImage src2,typeImage dest){
	#define SRC1(x,y,k)  src1[3*((y)*TAILLE+(x)) + k]  
	#define SRC2(x,y,k)  src2[3*((y)*TAILLE+(x)) + k]  
	#define DEST(x,y,k) dest[3*((y)*TAILLE+(x)) + k]
	int x,y;
  for ( y = 0 ; y < TAILLE ; y++ ) //largeur 
  	for ( x = 0 ; x < TAILLE ; x++ ){ //hauteur
  		// A ecrire
		}
	#undef SRC
	#undef DEST
}

void filtreMatriciel(typeFiltre f,typeImage src,typeImage dest){
	#define SRC(x,y,k)  src[3*((y)*TAILLE+(x)) + k]  
	#define DEST(x,y,k) dest[3*((y)*TAILLE+(x)) + k]
  int x,y;
  for ( y = 1 ; y < TAILLE-1 ; y++ ) //largeur 
  	for ( x = 1 ; x < TAILLE-1 ; x++ ){ //hauteur
  		// A ecrire
		}
	#undef SRC
	#undef DEST
}
