#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NPROD 5
#define NCONS 5
#define TAMBUF 10
#define Nprod 20 //Numero de productos que se pruduciran y se consumiran por cada hilo

void *productor();
void *consumidor();

int bufer[TAMBUF];
sem_t mutex, full, empty; //Declaro los semaforos necesarios para el algoritmo productor-consumidor
int itP = 0, itC = 0, sumP = 0, sumC = 0; //Ahora como van a producir y consumir entre varios hilos hay compartir el iterador

int main(){
//	inicializo los semaforos
	sem_init(&mutex, 0, 1);
	sem_init(&full, 0, 0);  
	sem_init(&empty, 0, TAMBUF);

	srand(time(NULL));
	pthread_t idProd[NPROD], idCon[NCONS];

//	Creo los hilos que pruducen y los consumidores
	for(int i=0; i<NPROD; i++){
		pthread_create(&idProd[i], NULL, productor, NULL);
	}
	for(int i=0; i<NCONS; i++){
		pthread_create(&idCon[i], NULL, consumidor, NULL);
	}
	
//	Recibo tanto los hilos productores como los consumidores
	for(int i=0; i<NPROD; i++){
		pthread_join(idProd[i], NULL);
	}
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
	extern int sumP, itP;
	int val;
/*	
	while(itP<Nprod){
		val = rand()%1001;
		sem_wait(&empty);
		sem_wait(&mutex);
		bufer[itP%TAMBUF] = val;
		sumP += val;
		itP++;
		sem_post(&mutex);
		sem_post(&full);
	}
*/

	for(int i=0; i<Nprod; i++){//Si quisiera controlar el numero de productos total usaria i<(Nprod / NPROD)
		val = rand()%1001;
		sem_wait(&empty);
		sem_wait(&mutex);
		bufer[itP%TAMBUF] = val;
		sumP += val;
		itP++;
		sem_post(&mutex);
		sem_post(&full);		
	}
	pthread_exit(NULL);
}

void *consumidor(){
	extern int bufer[TAMBUF];
	extern sem_t mutex, full, empty;
	extern int sumC, itC;

/*	Con este bucle no funciona, creo que porque una vez se evalua la condicion y se pasar puede cambiar
	itC y ya no pasar la condicion, pero al ya estar dentro del while se ejecuta el codigo, mejor no hacer condiciones
	con variables compartidas
	while(itC<Nprod){
		sem_wait(&full);
		sem_wait(&mutex);
		sumC += bufer[itC%TAMBUF];
		bufer[itC%TAMBUF] = 0;
		itC++;
		sem_post(&mutex);
		sem_post(&empty);
	}
*/
	for(int i=0; i<Nprod; i++){
		sem_wait(&full);
		sem_wait(&mutex);
		sumC += bufer[itC%TAMBUF];
		bufer[itC%TAMBUF] = 0;
		itC++;
		sem_post(&mutex);
		sem_post(&empty);
	}

	pthread_exit(NULL);
}
