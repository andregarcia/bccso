
#include <stdio.h>
#include <stdlib.h>


#define MAX 20


typedef unsigned char byte;

byte mem[MAX];

void* aloca(int size){

    int i=0;
    while(i<MAX-size-5){
        if(mem[i]==1){
           int tamanho=(int)mem[i+1];
           i+=5;
           i+=tamanho;
        }
        else if(mem[i]==0){
            int livre=1;
            int j=0;  
            for(j=i; j<MAX-size-5 && j<i+5+size; j++){
                if(mem[j]==1){
                    livre=0;
                    int tamanho=(int)mem[j+1];
                    i=j+tamanho+5;
                }
            }
            if(livre){
                mem[i]=1;
                mem[i+1]=size;
                void *p;
                p = mem+i+5;
                return p;
            }
        }

    }

}


void desaloca(void* p){

    //pega o tamanho da alocacao
    int *p1 = (int *)p;
    p1 = p1 - 1;
    int tamanho = *p1;


    byte* p2 = (byte *)p; 

    //seta 0 para todos os bytes a serem desalocados
    int i=0;
    for(i=0; i<tamanho; i++){
        *p2 = 0;
        p2++;
    }
    //volta p2 para o inicio do espaco alocado
    p2 = p2 - tamanho;

    //seta o controle como 0
    for(i=0; i<5; i++){
        p2--;
        *p2=0;
    }


}

int main(){
    double *p1 = aloca(sizeof(double));
    double *p2 = aloca(sizeof(double));
    desaloca(p1);
    desaloca(p2);
}

int xmain(){

    char *p = (char*) aloca(sizeof(char));
    *p = 'a';
    printf("VALOR_P1 = %c\tENDERECO = %d\n", *p, p);
    
    int *p2 = (int*) aloca(sizeof(int));
    *p2 = 10;
    printf("VALOR_P2 = %d\tENDERECO = %d\n", *p2, p2);

    double *p3 = (double*) aloca(sizeof(double));
    *p3 = 0.35;
    printf("VALOR_P3 = %lf\tENDERECO = %d\n", *p3, p3);

    printf("LIBERANDO P2\n");
    desaloca(p2);

    int *p4 = (int*) aloca(sizeof(int));
    *p4 = 40;
    printf("VALOR REALOCADO = %d\tENDERECO = %d\n", *p4, p4);

    printf("VALOR_P3 (VERIFICANDO SE ESTA IGUAL) = %lf\tENDERECO = %d\n", *p3, p3);


    exit(EXIT_SUCCESS);

}



