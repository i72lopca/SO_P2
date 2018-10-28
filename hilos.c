#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

double counter = 0;

#define ITER	10
#define NHILOS	7

//Variables globales para el algoritmo de lamport
int Eligiendo[NHILOS]; //Bool no existe en C
int Numero[NHILOS]; //Aqui se guardara por que número va atendiendo la cpu

//Funcion para buscar el maximo de un vector de enteros
int max();

int main(){
//	Inicializo las varibles del algorimo de lamport
	for(int i=0; i<NHILOS; i++){
		Eligiendo[i] = 0;
		Numero[0] = 0; //Para conocer los números de turno, si el hilo i vale 0 significa que no esr¡ta interesado en entrar en zona critica
	}

	pthread_t hilos[NHILOS];
	int status, i, v[NHILOS];
	extern double counter;
	void *adder(void *);
	double *r_value;

	// Create NHILOS threads
	for (i = 0; i < NHILOS; i++){
	v[i] = i;
	if ((status = pthread_create(&hilos[i], NULL, adder, (void *) &i)))
		//pthread_create(pid del hilo, atributos de los hilos, funcion que ejecuta el hilo_tiene que ser void*, argumentos de la funcion)
		exit(status);
	}

	// Wait threads
	for (i = 0; i < NHILOS; i++) {
	pthread_join(hilos[i], (void **) &r_value); //Recibe un puntero
	printf("Value returned by %lu thread: %lf\n", hilos[i], *r_value);
	}

	// Final result
	fprintf(stdout, "%f\n", counter);

	return 0;
}

void *adder(void *p){ //p es el id del thread
	double l, *to_return;
	extern double counter;
	int *id, i;
	id = (int *) p;

	//Pidiendo ticket, o calculando turno (Lamport)
	do{
		Eligiendo[*id]=1;
		Numero[*id] = 1 + max(Numero);
	}
	while(1);
	//Ticket pedido

	//Si incluyese el for en la zona critica cada hilo se ejecutaria de uno en uno
	for (i = 0; i < ITER; i++) {
	l = counter;
	fprintf(stdout, "Hilo %d: %f\n", *id, counter);
	l++;
	counter = l;
	}

	to_return = malloc(sizeof(double));
	//devuelvo esto para poder saber cuanto se ha incrementado en cada funcion, si no usase un puntero al devolverlo se pierde al ser una variable local
	*to_return = counter;

	pthread_exit((void *) to_return);
}

int max(int *v){
	int maxval = v[0];
	for(int i = 0; i<NHILOS; i++){
		if(v[i] > maxval){
			maxval = v[i];
		}
	}
	return maxval;
}