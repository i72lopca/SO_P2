#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//hola

double counter = 0;

#define ITER	10
#define NHILOS	7

int main()
{
	pthread_t hilos[NHILOS];
	int status, i, v[NHILOS];
	extern double counter;
	void *adder(void *);
	double *r_value;

	// Create NHILOS threads
	for (i = 0; i < NHILOS; i++){
	v[i] = i;
	if ((status = pthread_create(&hilos[i], NULL, adder, (void *) &i)))
		//pthread_create(pid del hilo, atributos de los hilos, funcion que jecuta el hilo_tiene que ser void*, argumentos de la funcion)
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

void *adder(void *p)
{
	double l, *to_return;
	extern double counter;
	int *id, i;

	id = (int *) p;

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