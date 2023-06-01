#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int aleatorio(int);

int main()
{
	int i, eleitores, candidatos, matriz[100][1];
	int candidato =0, max = 0, indice=0;
	printf("\n");
	printf(" ------------------------------------------------------\n");
	printf(" |        SISTEMA DE GERENCIAMENTO DE ELEICOES        |\n");
	printf(" ------------------------------------------------------\n\n");
	
	// Pede a quantidade de eleitores
	printf("\tDigite o numero total de eleitores..: ");
	scanf("%d", &eleitores);
	// Pede a quantidade de candidatos a eleição
	printf("\tDigite o numero total de candidatos.: ");
	scanf("%d", &candidatos);
	
	// Vetor que armazena os votos de cada candidato
	int voto[candidatos];
	// Incializa o vetor com 0 em todas as suas posições
	for(i = 0; i < candidatos ; i++){
		voto[i] = 0;
	}

	srand(time(NULL));
	// Votação dos eleitores
	for(i = 0; i < eleitores; i++){
		candidato = aleatorio(candidatos);
		voto[candidato] += 1; 
	}
	
	// Armazena os resultados em uma matriz e mostra na tela
	for(i = 0; i < candidatos; i++){
		//printf("\nCandidato[%d] - %d Votos", i+1, voto[i]);
		matriz[i][0] = i+1; 
		matriz[i][1] = voto[i];
		printf("\n\tCandidato[%d] - %d Votos", matriz[i][0], matriz[i][1]);
	}
	
	// Identifica o candidato vencedor
	for(i = 0; i < candidatos; i++)
	{
	    if (voto[i] > max) {
	        max = voto[i];
	        indice = i+1;
	    }
	}
	
	// Mostra o candidato vencedor
	printf("\n\n\t\t[VENCEDOR]\n");
	printf("\n\tCandidato[%d] com %d Votos\n\n", indice, max);
	
	system("pause");
	return 0;
}

int aleatorio(int candt)
{
		int v_aleat;
		v_aleat = rand() % candt;
		return v_aleat;
}