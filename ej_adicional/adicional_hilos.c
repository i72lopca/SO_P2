#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define sz 3

int m[sz][sz];
int v[sz];

void rellenamatriz();
void vermatriz();

int main(){
	extern int m[sz][sz];
	extern int v[sz]

	srand(time(NULL));
	rellenamatriz(m);
	printf("La matriz szxsz es:\n");
	vermatriz(m);






	return 0;
}


void rellenamatriz(int m[sz][sz]){
	for(int i=0; i<sz; i++){
		for(int j=0; j<sz; j++){
			m[i][j]=rand()%50;
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