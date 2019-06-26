#include <iostream>

using namespace std;

struct Node
{
    int value;
    Node * next;
    Node * prev;
    Node(int value){
        this->value = value;
        this->next = this;
        this->prev = this;
    }
};

void insert(Node * ref, int value){
    Node * node = new Node(value);
    node->next = ref->next;
    node->prev = ref;
    ref->next = node;
    node->next->prev = node;
}

void remove(Node * ref){
    ref->prev->next = ref->next;
    ref->next->prev = ref->prev;
}

void show(Node * ref, Node * espada = nullptr){
    cout << "[";
    if(ref != nullptr){
        Node * aux = ref;
        do{
            if((espada != nullptr) && (aux == espada)){
                if(aux->value > 0){
                    cout << " " << aux->value;
                    printf(">");
                }else{
                    printf(" <");
                    cout << aux->value;
                }
            }else{
                cout << " " << aux->value;
            }
            aux = aux->next;
        } while (aux != ref);
        
    }
    cout << " ]\n";
}

Node * search(Node * ref,int init){
    Node * aux = ref;
    int i = 1;
    do{
        if(i == init)
            return aux;
        aux = aux->next;
        i++;
    } while (aux != ref);
    return aux;
}

void show_ordenar(Node * ref){
    Node * menor = ref;
    Node * aux = ref;
    do{
        int m = menor->value > 0 ? menor->value : -menor->value;
        int n = aux->value > 0 ? aux->value : -aux->value;
        if(m < n)
            menor = aux;
        aux = aux->next;
    }while(aux != ref);
    show(menor->next, ref);
}


int main(){
    int tam = 0;
    int init = 0;
    int fase = 1;
    Node * lista = nullptr;

    printf("tamanho_; inicial_; fase_ (1/2)\n");
    cin >> tam >> init >> fase;

    for(int i = 2; i <= tam; i++){
        if (lista == nullptr) {
            lista = new Node((1 * fase));
            fase *= -1;
        }
        
        insert(lista->prev,(i * fase));
        fase *= -1;
    }

    Node * found = search(lista,init);
    show(lista, found);
    
    for(int i = 0; i < tam-1; i++){
        int direcao = found->value > 0 ? 1 : -1;
        int andar = found->value > 0 ? found->value : -found->value;

        if(direcao == 1)
            remove(found->next);
        else
            remove(found->prev);
        
        for(int j = 0; j < andar; j++){
            if(direcao == 1)
                found = found->next;
            else
                found = found->prev;
        }

        show_ordenar(found);
    }
    return 0;
}