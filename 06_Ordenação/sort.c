#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//ordenando vetor usando o método bubbly sort
void bubbly(int vet[], int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size - 1; j++){
            if(vet[j] > vet[j + 1]){
                int aux = vet[j + 1];
                vet[j + 1] = vet[j];
                vet[j] = aux;
            }
        }
    }
}

//ordenando vetor usando o método insertion sort
void insertion(int vet[], int size){
    for(int i = 1; i < size; i++){
        int j = i;
        while(vet[j] < vet[j - 1]){
            int aux = vet[j];
            vet[j] = vet[j - 1];
            vet[j - 1] = aux;
            j--;

            if(j == 0)
                break;
        }
    }
}

//ordenando vetor usando o método selection sort
void selection(int vet[], int size){
    for(int i = 0; i < size - 1; i++){
        int menor = i; //atribui o campor contendo o valor de 'i' a variavel 'menor' 
        for(int j = i + 1; j < size; j++){
            if(vet[j] < vet[menor]){
                menor = j;
            }
        }

        if(menor != i){
            int aux = vet[i];
            vet[i] = vet[menor];
            vet[menor] = aux;
        }
    }
}

//mostrando o vetor
void show(int vet[], int size){
    printf("[ ");
    for(int i = 0; i < size; i++){
        printf("%d ", vet[i]);
    }
    puts("]");
}

int main(){
    int vet[6];

    while(true){
        for(int i = 0; i < 6; i++){
            scanf("%d", &vet[i]);
        }

        char entrada;
        scanf("%c", &entrada);

        if(entrada == 'm'){
            show(vet, 6);
        }else if(entrada == 'b'){
            bubbly(vet, 6);
        }else if(entrada == 'i'){
            insertion(vet, 6);
        }else if(entrada == 's'){
            selection(vet, 6);
        }else if(entrada == 'f'){
            break;
        }else{
            puts("Comando inválido!");
        }
    }
}