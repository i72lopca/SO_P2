#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

double counter = 0;

#define ITER    1000
#define NHILOS  3

//Variables globales para el algoritmo de lamport
int Eligiendo[NHILOS]; //Controla que solo uno elija a la misma vez ,bool no existe en C
int Numero[NHILOS]; //Aqui se guardara por que número va atendiendo la cpu

void *adder();
int max();
void pideticket();

int main(){
//  Inicializo las varibles del algorimo de lamport
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
	for (i = 0; i < NHILOS; i++) {
	v[i] = i;
	if ((status = pthread_create(&hilos[i], NULL, adder, (void *) &v[i])))
		exit(status);
	}

	// Wait threads
	for (i = 0; i < NHILOS; i++) {
		pthread_join(hilos[i], (void **) &r_value);
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

	for (i = 0; i < ITER; i++){
		pideticket(*id); //Inicio de la zona critica, pido un ticket
		
		l = counter;
		fprintf(stdout, "Hilo %d: %f\n", *id, counter);
		l++;
		counter = l;
		
		Numero[*id] = 0;//Fin de la seccion critica, elimino el ticket
	}

	to_return = malloc(sizeof(double));

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

void pideticket(int tid){
	Eligiendo[tid] = 1;
	Numero[tid] = 1 + max(Numero);
	Eligiendo[tid] = 0;
	for(int j=0; j>NHILOS; j++){
		while(Eligiendo[j]);//Si hay otro eligiendo hay que esperar
		/*Si el hilo j tiene mas prioridad, espera que su numero se ponga a cero, j tiene mas prioridad si
		su numero de turno es mas bajo que el de tid(para el que se esta pidiendo el ticket), o bien si es
		el mismo numero y ademas j es meno que tid*/
		while(Numero[j] != 0 && ((Numero[j]<Numero[tid]) || ((Numero[j]) == Numero[tid] && j<tid)));
	}
}