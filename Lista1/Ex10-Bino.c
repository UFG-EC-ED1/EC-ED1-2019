#include <stdlib.h>
#include <stdio.h>

int main(){
	
	
	int qtd = 0;
	scanf("%d", &qtd);

	int array[qtd], i;

	for(i=0; i<qtd; i++){
		scanf("%d",&array[i]);
	}

	int multiplos2 = 0;
	int multiplos3 = 0;
	int multiplos4 = 0;
	int multiplos5 = 0;

	for (i=0; i<qtd; i++){
		if(array[i]%2 == 0)
			multiplos2++;
		if(array[i]%3 == 0)
			multiplos3++;
		if(array[i]%4 == 0)
			multiplos4++;
		if(array[i]%5 == 0)
			multiplos5++;
	}

	printf("%d Multiplo(s) de 2\n", multiplos2);
	printf("%d Multiplo(s) de 3\n", multiplos3);
	printf("%d Multiplo(s) de 4\n", multiplos4);
	printf("%d Multiplo(s) de 5\n", multiplos5);


	return 0;
}