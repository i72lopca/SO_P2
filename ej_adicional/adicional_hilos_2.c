#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NHILOS = 4

void *incrementa();

int counter;

int main(){
	extern int counter = 0;
	pthread_t hilos[NHILOS];
	int v[NHILOS];

	for(int i=0; i<NHILOS; i++){
		v[i] = i;
		pthread_create(&hilos[i], NULL, incrementa, &v[i]);
	}

	for(int i=0; i<NHILOS; i++){
		
	}




	return 0;
}

void *incrementa(void *thread){
	int *hilo = (int *)thread;
	

}