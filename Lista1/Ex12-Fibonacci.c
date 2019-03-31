#include <stdio.h>
#include <stdlib.h>


int main(){


	int n,i;
	scanf("%d", &n);
	
	unsigned long long int aux;
	
	while(n>0){
		scanf("%lld", &aux);

		long long int vet[aux+1];
		vet[0]=0;
		vet[1]=1;


			if(aux>1)

			for(i=2; i<=aux; i++)
				vet[i] = vet[i-1]+vet[i-2];

			printf("Fib(%llu) = %lld\n", aux, vet[aux]); 

		n--;
	}


	return 0;
}