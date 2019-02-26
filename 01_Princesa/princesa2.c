#include <stdio.h>
#include <stdbool.h>

const int MORTO = 0;

int achar_vivo(int vetor[], int size, int inicio, int escolhido){
    int posicao = (inicio + 1) % size;
    while(vetor[posicao] == MORTO){
        if((escolhido - vetor[posicao]) < 0)
            posicao = (posicao + 1) % size; 
        else
            posicao = (posicao + size - 1) % size;
         
    }
    return posicao;
}

void mostrar_vetor(int vetor[], int size){
    printf("[");
    bool teste_primeiro = true;
    for(int i = 0; i < size; i++){
        if(vetor[i] !=  MORTO){
            if(teste_primeiro)
                teste_primeiro = false;
            else
                printf(" ");
            printf("%d", vetor[i]);
        }
    }
    printf("]\n");
}

int main(){
    int size = 0;
    scanf("%d", &size);
    int vetor[size];
    int escolhido = 0; //valor que inicia com a espada
    scanf("%d", &escolhido);
    int fase = 0;
    scanf("%d", &fase);
    for(int i = 0; i < size; i++){
        vetor[i] = (i + 1) * fase;
        fase *= -1;
    }
    int indice = 0;
    for(int i = 0; i < size; i++)
        if(vetor[i] == escolhido)
            indice = i;

    mostrar_vetor(vetor, size);
    int qtd = size;
    while(qtd--){
        int vai_morrer = achar_vivo(vetor, size, indice, escolhido);
        vetor[vai_morrer] = 0;
        indice = achar_vivo(vetor, size, vai_morrer, escolhido);
        escolhido = vetor[indice];
        mostrar_vetor(vetor, size);
    }
}