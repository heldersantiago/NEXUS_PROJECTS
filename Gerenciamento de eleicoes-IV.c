#include <stdio.h>
#include <stdlib.h>

int main()
{
	int vencedor = 0, indice_vencedor = 0;
	int numeroEleitores;
	int numeroCandidatos;
	int n_candidato = 0;
	int i = 0,j = 0;
	int n_voto = 0;

    printf("\n");
	printf(" ------------------------------------------------------\n");
	printf(" |        SISTEMA DE GERENCIAMENTO DE ELEICOES        |\n");
	printf(" ------------------------------------------------------\n\n");

    printf("Digite o numero de ELEITORES\n");
    scanf("%d",&numeroEleitores);
    printf("Digite o numero de CANDIDATOS\n");
    scanf("%d",&n_candidato);

    int voto[n_candidato]; //Inicializa todos os enderecos do vector com 0
    for(int i = 0; i<n_candidato; i++)
    {
        voto[i] = 0;
    }

    printf("\n\n");
    //Loop que realiza as votacoes
    while(i<numeroEleitores){
		printf("Eleitor %d, Digite o seu voto (1 a %d)",i+1,n_candidato);
		scanf("%d",&n_voto);
        voto[n_voto-1] +=1;
        i++;
	}

    printf("\n\n"); //Mostrando os votos de cada um
    for(i = 0; i<n_candidato;i++)
    {
        printf("Candidato %d , VOTO = %d \n",i+1,voto[i]);
    }
    for(i = 0; i<n_candidato;i++){
        if(voto[i]> vencedor){
            vencedor = voto[i];
            indice_vencedor = i+1;
        }
    }
    //Mostrando o vencedor
    printf(" O vencedor e %d, com %d votos",indice_vencedor,vencedor);
    return 0;
}
