



#include <stdlib.h>
#include <stdio.h>
#include <math.h>









int main(){
	

	int pid = fork();
	FILE *arq;
	const char arqFilho[] = "arqFilho.txt";	

	if(pid>0){
		//estamos no pai
	}
	else if(pid==0){
		//estamos no filho
		//inicializar arquivo
		arq = fopen(arqFilho, "w");
	}

	int vezes = 10000000;

	int hit=0;
	int miss=0;

	//"joga os dardos" e conta o numero de acertos e erros
	int cont = 0;
	for( ; cont<vezes; cont++){
		double x = (double)rand()/RAND_MAX;
		double y = (double)rand()/RAND_MAX;
		
		double dist;
		dist = sqrt(pow(x-0.5,2)+pow(y-0.5,2));
		
		if(dist>0.5){
			miss+=1;
		}
		else{
			hit+=1;
		}
	}

	if(pid==0){
		//estamos no filho
		//guarda os resultados do filho
		fprintf(arq, "%d", hit);
		fprintf(arq, "\n");
		fprintf(arq, "%d", miss);
	}
	else if(pid>0){
		//estamos no pai
		//espera o filho terminar
		int status_ret;
		wait(&status_ret);
		
		//obtem os dados do filho
		int hit2;
		int miss2;
		FILE *arq = fopen(arqFilho, "r");
		fscanf(arq, "%d\n%d", &hit2, &miss2);
		
		//calcula os dados totais (pai + filho)
		int hitTotal = hit2 + hit;
		int missTotal = miss2 + miss;
		int jogadasTotal = hitTotal + missTotal;		

		//calcula e imprime o resultado
		printf("hits=%d\nmiss=%d\n", hitTotal, missTotal);
		double pi = 4.0*((double)hitTotal)/(double)jogadasTotal;
		printf("PI=%lf\n", pi);
	}
	return(EXIT_SUCCESS);
}



