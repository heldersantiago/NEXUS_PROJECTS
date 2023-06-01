#include <stdio.h>
#include <stdlib.h>
#include<locale.h>

#define MAX_CANDIDATES 10
#define MAX_VOTERS 100

typedef struct {
    int candidato;
} Voto;

typedef struct {
    int id;
    char nome[100][100];
    Voto voto;
} Eleitor;

int main() {
    setlocale(LC_ALL,"");
    int totalEleitores, totalCandidatos;
    int votos[MAX_CANDIDATES] = {0}; // Inicializa o vetor de votos com zeros
    Eleitor eleitores[MAX_VOTERS];
    int i, j, vencedor = 0, maxVotos = 0;

    printf("\n");
	printf(" ---------------------------------------------------------\n");
	printf("|| SIMULACAO DE UM SISTEMA DE GERENCIAMENTO DE ELEICOES ||\n");
	printf(" ---------------------------------------------------------\n\n");

    // Solicita ao usuário o número total de eleitores registrados
    printf("Digite o numero total de eleitores registrados: ");
    scanf("%d", &totalEleitores);

    // Solicita ao usuário o número de candidatos concorrendo
    printf("Digite o numero de candidatos(PRESIDENTES) concorrendo: ");
    scanf("%d", &totalCandidatos);

    system("cls");
    printf("\t\t|| FASE DAS VOTACOES ||\n\n");
    // Registra os votos de cada eleitor
    for (i = 0; i < totalEleitores; i++) {
        printf("Eleitor %d:\n", i+1);

        eleitores[i].id = i+1;
        // Solicita ao eleitor o número do candidato escolhido
        printf("Digite o numero do candidato escolhido (1 a %d): ", totalCandidatos);
        scanf("%d", &eleitores[i].voto.candidato);

        // Verifica se o número do candidato é válido
        while (eleitores[i].voto.candidato < 1 || eleitores[i].voto.candidato > totalCandidatos) {
            printf("Numero do candidato invalido. Digite novamente: ");
            scanf("%d", &eleitores[i].voto.candidato);
        }
        // Incrementa o número de votos para o candidato escolhido
        votos[eleitores[i].voto.candidato - 1]++;
    }

    // Calcula o número total de votos recebidos por cada candidato e determina o vencedor
    for (i = 0; i < totalCandidatos; i++) {
        if (votos[i] > maxVotos) {
            maxVotos = votos[i];
            vencedor = i;
        }
    }

    // Exibe os resultados da eleição
    printf("\nResultados das Eleicoes\n");
    printf("---------------------\n");

    for (i = 0; i < totalCandidatos; i++) {
        printf("Candidato %d: %d votos\n", i+1, votos[i]);
    }

    printf("\nCandidato vencedor: Candidato %d\n", vencedor+1);

    return 0;
}
