#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NCONS 5
#define TAMBUF 10
#define Nprod 20 //Numero de productos que se pruduciran y se consumiran por cada hilo

void *productor();
void *consumidor();

int bufer[TAMBUF];
sem_t mutex, full, empty; //Declaro los semaforos necesarios para el algoritmo productor-consumidor
int itC = 0, sumP = 0, sumC = 0; //Ahora como van a producir y consumir entre varios hilos hay compartir el iterador

int main(){
//	inicializo los semaforos
	sem_init(&mutex, 0, 1);
	sem_init(&full, 0, 0);  
	sem_init(&empty, 0, TAMBUF);

	srand(time(NULL));
	pthread_t idProd, idCon[NCONS];

	pthread_create(&idProd, NULL, productor, NULL);
	for(int i=0; i<NCONS; i++){
		pthread_create(&idCon[i], NULL, consumidor, NULL);
	}
	
	pthread_join(idProd, NULL);
	for(int i=0; i<NCONS; i++){
		pthread_join(idCon[i], NULL);
	}

	printf("Sumatorio del productor: %i\nSumatorio del consumidor: %i\n", sumP, sumC);
	printf("La diferencia es: %i\n", sumP - sumC);
	return 0;
}

void *productor(){
	extern int bufer[TAMBUF];
	extern sem_t mutex, full, empty;
	extern int sumP;
	int val;

	for(int i=0; i<(Nprod); i++){
		val = rand()%1001;
		sem_wait(&empty);
		sem_wait(&mutex);
		bufer[i%TAMBUF] = val;
		sumP += val;
		sem_post(&mutex);
		sem_post(&full);		
	}
	pthread_exit(NULL);
}

void *consumidor(){
	extern int bufer[TAMBUF];
	extern sem_t mutex, full, empty;
	extern int sumC, itC;

	for(int i=0; i<(Nprod / NCONS); i++){
		sem_wait(&full);
		sem_wait(&mutex);
		sumC += bufer[itC%TAMBUF];
		itC++;
		sem_post(&mutex);
		sem_post(&empty);
	}

	pthread_exit(NULL);
}