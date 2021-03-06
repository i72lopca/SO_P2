#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TAMBUF 10 //Tamaño del vector buffer
#define Nprod 200 //Numero de elementos que se producirary consumiran

void *productor();
void *consumidor();


int bufer[TAMBUF];
sem_t mutex, full, empty; //Declaro los semaforos necesarios para el algoritmo productor-consumidor


int main(){
	srand(time(NULL));
//	inicializo los semaforos
	sem_init(&mutex, 0, 1);
	sem_init(&full, 0, 0);  
	sem_init(&empty, 0, TAMBUF);

	pthread_t idProd, idCon;
//	Para probar el retorno de variables se utilizaran estas, en lugar de varibles globales
	int *sumC = malloc(sizeof(int)); 
	int *sumP = malloc(sizeof(int));
	
	
	pthread_create(&idProd, NULL,productor,NULL);
	pthread_create(&idCon, NULL,consumidor,NULL);
	
//	Recibo tanto los hilos productores como los consumidores
	pthread_join(idProd, (void **)&sumP);
	pthread_join(idCon, (void **)&sumC);

	printf("Sumatorio del productor: %i\nSumatorio del consumidor: %i\n", *sumP, *sumC);
	return 0;
}

void *productor(){
	extern int bufer[TAMBUF];
	extern sem_t mutex, full, empty;
	int sum = 0, val;

	for(int i=0; i<Nprod; i++){
		val = rand()%1001;
		sem_wait(&empty);
		sem_wait(&mutex);
		bufer[i%TAMBUF] = val;
		sum += val;
		sem_post(&mutex);
		sem_post(&full);
	}

	int *toReturn = malloc(sizeof(int));
	*toReturn = sum;
	pthread_exit(&sum);
}

void *consumidor(){
	extern int bufer[TAMBUF];
	extern sem_t mutex, full, empty;
	int sum = 0;

	for(int i=0; i<Nprod; i++){
		sem_wait(&full);
		sem_wait(&mutex);
		sum += bufer[i%TAMBUF];
		bufer[i%TAMBUF] = 0;
		sem_post(&mutex);
		sem_post(&empty);
	}

	int *toReturn = malloc(sizeof(int));
	*toReturn = sum;
	pthread_exit(&sum);

}