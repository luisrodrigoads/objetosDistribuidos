#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include <stdlib.h>

void *multiplosde3(void *th){
	int y;
	FILE *file;
	printf("executando a thread nro %d\n", th);
	file = fopen("multiplosde3.txt","w+");
	for(y=1;y <= 9000000;y++){
		if(y%3 == 0)
		fprintf(file,"%d\n",y);
	}
	fclose(file);
	printf("thread %d finalizou\n",th);
	pthread_exit(NULL);	
}

void *multiplosde5(void *th){
	int y;
	FILE *file;
	printf("executando a thread nro %d\n", th);
	file = fopen("multiplosde5.txt","w+");
	for(y=1;y <= 9000000;y++){
		if(y%5 == 0)
		fprintf(file,"%d\n",y);
	}
	fclose(file);
	printf("thread %d finalizou\n",th);
	pthread_exit(NULL);	
}

void *multiplosde7(void *th){
	int y;
	FILE *file;
	printf("executando a thread nro %d\n", th);
	file = fopen("multiplosde7.txt","w+");
	for(y=1;y <= 9000000;y++){
		if(y%7 == 0)
		fprintf(file,"%d\n",y);
	}
	fclose(file);
	printf("thread %d finalizou\n",th);
	pthread_exit(NULL);	
}

void *multiplosde9(void *th){
	int y;
	FILE *file;
	printf("executando a thread nro %d\n", th);
	file = fopen("multiplosde9.txt","w+");
	for(y=1;y <= 9000000;y++){
		if(y%9 == 0)
		fprintf(file,"%d\n",y);
	}
	fclose(file);
	printf("thread %d finalizou\n",th);
	pthread_exit(NULL);	
}

int main(){
	
	pthread_t programas[4];
	
	printf("Criando a thread nro 0\n");
	pthread_create(&programas[0],NULL,multiplosde3,(void *)0);
	printf("Criando a thread nro 1\n");
	pthread_create(&programas[1],NULL,multiplosde5,(void *)1);
	printf("Criando a thread nro 2\n");
	pthread_create(&programas[2],NULL,multiplosde7,(void *)2);
	printf("Criando a thread nro 3\n");
	pthread_create(&programas[3],NULL,multiplosde9,(void *)3);
			
	pthread_exit(NULL);
	return 0;
}
