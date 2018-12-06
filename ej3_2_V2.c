#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 1001
#define NHILOS 1

void *productor(void *thread);
void *consumidor(void *thread);

int bufer[NHILOS];
sem_t mutex, full, empty; //Declaro los semaforos necesarios para el algoritmo productor-consumidor


int main(){
//	inicializo los semaforos
	sem_init(&mutex, 0, 1);
	sem_init(&full, 0, 0);  
	sem_init(&empty, 0, NHILOS*2);

	srand(time(NULL));
	int v[NHILOS];
	pthread_t idProd[NHILOS], idCon[NHILOS];
	
//	Creo los hilos que pruducen y los consumidores a la vez
	for(int i=0; i<NHILOS; i++){
		v[i] = i;
		pthread_create(&idProd[i], NULL, /*(void *)*/productor, (void *) &v[i]);
		pthread_create(&idCon[i], NULL, /*(void *)*/consumidor, (void *) &v[i]);
	}
	
//	Recibo tanto los hilos productores como los consumidores
	for(int i=0; i<NHILOS; i++){
		pthread_join(idProd[i], NULL);
		pthread_join(idCon[i], NULL);
	}
	return 0;
}

void *productor(void *thread){
	int *hilo;
	hilo = (int *)thread;
	extern int bufer[NHILOS];
	extern sem_t mutex, full, empty;

	for(int i=0; i<500; i++){
//		Produzco el dato
		bufer[*hilo] = rand()%MAX;
		printf("El valor del producido por %i es: %i\n", *hilo, bufer[*hilo]);
		sem_wait(&empty);
		sem_wait(&mutex);
//		Introduzco el dato
		sem_post(&mutex);
		sem_post(&full);

	}
	pthread_exit(NULL);
}

void *consumidor(void *thread){
	int *hilo;
	hilo = (int *)thread;
	extern int bufer[NHILOS];
	
	printf("El valor del consumido por %i es: %i\n", *hilo, bufer[*hilo]);
	pthread_exit(NULL);

}