
#include <stdio.h>
#include <stdlib.h>


#define MAX 100


typedef unsigned char byte;

byte mem[MAX];




void* aloca(int size){

    int i=0;
    for(i=0; i<MAX-size-4-1; i++){
        if(mem[i]==1){
           int tamanho=(int)mem[i+1];
           i+=4;
           i+=tamanho;
        }
        else if(mem[i]==0){
            int livre=1;
            int j=0;  
            for(j=i; j<i+4+1+size; j++){
                if(mem[j]==1){
                    livre=0;
                    int tamanho=(int)mem[j+1];
                    i=j+tamanho+4; 
                }
            }
            if(livre){
                mem[i]=1;
                mem[i+1]=size;
                void *p;
                p = mem+i+4;
                return p;
            }
        }

    }

}


void desaloca(void* p){


    byte* p2 = (byte *)p; 
    p2 = p2 - 5;
    printf("ENDERECO = %d, VALOR = %c\n", p2, *p2); 
    *p2 = (byte)0; 

}



int main(){
    int j=0;
    for(j=0; j<2; j++){
        int i=0;
        printf("N=%d",j);
        int *p[5];
        for(i=0; i<5; i++){
            p[i] = aloca(sizeof(int));
           *p[i] = i;
        }
        for(i=0; i<5; i++){
            printf("Valor: %d\n", *p[i]);
        }
        for(i=0; i<5; i++){
            desaloca(p[i]);
        }
    }
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



