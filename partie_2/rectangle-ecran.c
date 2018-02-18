#include <stdio.h>

int p1[3]={10,10,0};
int p2[3]={20,20,0};
int p3[3]={30,15,0};

void remplirRec(int *p1,int *p2,int *p3);
int main(){
    remplirRec(p1,p2,p3);
    return 0;
}

void echange(int *p1,int *p2){
    int c;
    p1[0]=c;p1[0]=p2[0];p2[0]=c;
    p1[1]=c;p1[1]=p2[1];p2[1]=c;
    p1[2]=c;p1[2]=p2[2];p2[2]=c;
}


void remplirRec(int *p1,int *p2,int *p3){
    int x,y;
    //recherche de x le plus petit en p1 x median p2, x le plus grand p3
    if (p1[0]>p2[0]) echange(p1,p2);
    if (p2[0]>p3[0]) echange(p2,p3);
    if (p1[0]>p2[0]) echange(p1,p2);
    
    double p12 = (double)(p2[1]-p1[1]) / (double)(p2[0]-p1[0]); //Pente entre p1 et p2
    double p13 = (double)(p3[1]-p1[1]) / (double)(p3[0]-p1[0]); //Pente entre p1 et p3
    double p23 = (double)(p3[1]-p2[1]) / (double)(p3[0]-p2[0]); //Pente entre p1 et p3
    
    //Parcours entre p1 et p2
    for (x=p1[0];x<p2[0];x++){
        int y1 = p1[1]+p12*(double)(x-p1[0]);
        int y2 = p1[1]+p13*(double)(x-p1[0]);
        if (y1>y2){
            int c=y1;y1=y2;y2=c;
        }
        //printf("x = %d entre y=%d et %d avec pente de %f et %f\n",x,y1,y2,p12,p13);
        for (y=y1;y<y2;y++){
        }
    }
    //Parcours entre p2 et p3
    for (x=p2[0];x<=p3[0];x++){
        int y1 = p2[1]+p23*(double)(x-p2[0]);
        int y2 = p1[1]+p13*(double)(x-p1[0]);
        if (y1>y2){
            int c=y1;y1=y2;y2=c;
        }
        printf("x = %d entre y=%d et %d avec pente de %f et %f\n",x,y1,y2,p23,p13);
        for (y=y1;y<y2;y++){
        }
    }

}

