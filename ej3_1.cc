#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 1001
#define NHILOS 1

void *productor(void *thread);
void *consumidor(void *thread);

int bufer[NHILOS];

int main(){
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
	bufer[*hilo] = rand()%MAX;
	printf("El valor del producido por %i es: %i\n", *hilo, bufer[*hilo]);
	pthread_exit(NULL);
}

void *consumidor(void *thread){
	int *hilo;
	hilo = (int *)thread;
	extern int bufer[NHILOS];
	printf("El valor del consumido por %i es: %i\n", *hilo, bufer[*hilo]);
	pthread_exit(NULL);

}