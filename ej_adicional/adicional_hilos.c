#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define sz 3
#define al 4

int m[sz][sz];
int v[sz];

void rellenamatriz();
void vermatriz();
void rellenavector();
void vervector();

void *multiplica();

int main(){
	extern int m[sz][sz];
	extern int v[sz];
	int nhilos = sz, vec[sz]; //vec para pasarlo en vez de i porque la i al ser la direccion lo que se pasa puede cambiar
	pthread_t hilos[sz]; //Vector que guardara los identificadores de los hilos
	int *res, v_res[sz];


	srand(time(NULL));
	rellenamatriz(m);
	rellenavector(v);
	printf("La matriz 3x3 es:\n");
	vermatriz(m);
	printf("\nEl Vector:\n");
	vervector(v);

	//Creo los hilos
	for(int i  = 0; i<nhilos; i++){
		vec[i] = i;
		pthread_create(&hilos[i], NULL, (void*)multiplica, (void *)&vec[i]);
	}

	//Recojo los hilos
	for(int i=0; i<nhilos; i++){
		pthread_join(hilos[i], (void **) &res);
		v_res[i] = *res;
	}
	printf("\nEl resultado es:\n");
	vervector(v_res);


	return 0;
}


void rellenamatriz(int m[sz][sz]){
	for(int i=0; i<sz; i++){
		for(int j=0; j<sz; j++){
			m[i][j]=(rand()%al)+1;
		}
	}
}

void vermatriz(int m[sz][sz]){
	for(int i=0; i<sz; i++){
		for(int j=0; j<sz; j++){
			printf("%i\t", m[i][j]);
		}
		printf("\n");
	}
}

void rellenavector(int v[sz]){
	for(int i=0; i<sz; i++){
		v[i] = (rand()%al)+1;
	}
}

void vervector(int v[sz]){
	for(int i=0; i<sz; i++){
		printf("%i\t", v[i]);
	}
	printf("\n");
}

void *multiplica(void *thread){
	int *hilo = (int *)thread;
	printf("Hilo: %i\n", *hilo);
	extern int m[sz][sz];
	extern int v[sz];

	int *res = (int*)calloc(1, sizeof(int)); //Esta memoria hay que liberarla en el main despues de usarla en el pthread_join()
//	printf("Hilo[%i].PP_res: %i\n",*hilo, *res);

	for(int i=0; i<sz; i++){
//		printf("res<%i> += (m[%i][%i])<%i> * v[%i]<%i>\n", *res, *hilo, i, m[*hilo][i], i, v[i]);
		(*res) += (m[*hilo][i] * v[i]);
//		printf("Hilo[%i].P_res: %i\n",*hilo, *res);
	}
	pthread_exit((void*) res);
}