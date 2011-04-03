



#include <stdlib.h>
#include <stdio.h>
#include <math.h>









int main(){
	

	int pid = fork();

	FILE *arq;
	
	const char arqFilho[] = "arqFilho.txt";	

	if(pid>0){
		//estamos no pai
		//inicializar arquivo
		//const char nome[] = "arqPai.txt";
		//arq = fopen(nome, "w");
	}
	else if(pid==0){
		//estamos no filho
		//inicializar arquivo
		arq = fopen(arqFilho, "w");
	}

	int vezes = 10000000;

	int hit=0;
	int miss=0;

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
		fprintf(arq, "%d", hit);
		fprintf(arq, "\n");
		fprintf(arq, "%d", miss);
	}
	else if(pid>0){
		int status_ret;
		wait(&status_ret);
		
		int hit2;
		int miss2;
		FILE *arq = fopen(arqFilho, "r");
		fscanf(arq, "%d\n%d", &hit2, &miss2);
		
		int hitTotal = hit2 + hit;
		int missTotal = miss2 + miss;
		int jogadasTotal = hitTotal + missTotal;		

		printf("hits=%d\nmiss=%d\n", hitTotal, missTotal);
		double pi = 4.0*((double)hitTotal)/(double)jogadasTotal;
		printf("PI=%lf\n", pi);
	}
	
	

	return(EXIT_SUCCESS);


}



