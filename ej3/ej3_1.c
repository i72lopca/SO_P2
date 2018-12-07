#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TAMBUF 10 //Tamaño del vector buffer
#define Nprod 200 //Numero de elementos que se produciraran y consumiran

void *productor();
void *consumidor();


int bufer[TAMBUF];
sem_t mutex, full, empty; //Declaro los semaforos necesarios para el algoritmo productor-consumidor
int sumP , sumC;

int main(){
	srand(time(NULL));
//	inicializo los semaforos
	sem_init(&mutex, 0, 1);
	sem_init(&full, 0, 0);  
	sem_init(&empty, 0, TAMBUF);

	pthread_t idProd, idCon;
	
	pthread_create(&idProd, NULL,productor,NULL);
	pthread_create(&idCon, NULL,consumidor,NULL);
	
//	Recibo tanto los hilos productores como los consumidores
	pthread_join(idProd, NULL);
	pthread_join(idCon, NULL);

	printf("Sumatorio del productor: %i\nSumatorio del consumidor: %i\n", sumP, sumC);
	printf("La diferencia es: %i\n", sumP - sumC);
	return 0;
}

void *productor(){
	extern int bufer[TAMBUF];
	extern sem_t mutex, full, empty;
	extern int sumP;
	int val;
	sumP = 0;

	for(int i=0; i<Nprod; i++){
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
	extern int sumC;
	sumC = 0;

	for(int i=0; i<Nprod; i++){
		sem_wait(&full);
		sem_wait(&mutex);
		sumC += bufer[i%TAMBUF];
		bufer[i%TAMBUF] = 0;
		sem_post(&mutex);
		sem_post(&empty);
	}

	pthread_exit(NULL);

}