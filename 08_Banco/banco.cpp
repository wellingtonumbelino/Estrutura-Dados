#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct Cliente{
    string id;
    int docs;
    int pac;

    Cliente(string id = ".", int docs = 0, int pac = 0){
        this->id = id;
        this->docs = docs;
        this->pac = pac;
    }
};

struct Banco{
    vector<Cliente*> caixas;
    list<Cliente*> fila_entrada;
    queue<Cliente*> fila_saida;
};

void ini_caixa(Banco * banco, int qtd_caixas){
    for(int i = 0; i < qtd_caixas; i++){
        (*banco).caixas.push_back(nullptr);
    }
}

void show_lista(Banco banco){
    cout << "in : { ";
    list<Cliente*>::iterator it;
    for(it = banco.fila_entrada.begin(); it != banco.fila_entrada.end(); it++){
        cout << (*it)->id << ":" << (*it)->docs << ":" << (*it)->pac << " ";
    }
    cout << "}" << endl;
}

void show_fila(Banco banco){
    cout << "out : { ";
    while (!banco.fila_saida.empty()){
        cout << banco.fila_saida.front()->id << ":" << banco.fila_saida.front()->docs << ":" << banco.fila_saida.front()->pac << " ";
        banco.fila_saida.pop();
    }
    cout << "}" << endl;
}

void show(Banco banco){
    for(int i = 0; i < (int)banco.caixas.size(); i++){
        cout << "[";
        if(banco.caixas[i] != nullptr)
            cout << banco.caixas[i]->id << ":" << banco.caixas[i]->docs << ":" << banco.caixas[i]->pac;
        cout << "]";
    }
    cout << endl;
    show_lista(banco);
    show_fila(banco);    
}

void tic(Banco * banco, int * docs_recebidos, int * docs_perdidos){
    while(!(*banco).fila_saida.empty()){
        (*banco).fila_saida.pop();
    }

    for(int i = 0; i < (int) (*banco).caixas.size(); i++){
        if((*banco).caixas[i] != nullptr){
            if((*banco).caixas[i]->docs > 0){
                (*banco).caixas[i]->docs--;
                *docs_recebidos += 1;
            }else{
                (*banco).fila_saida.push((*banco).caixas[i]);
                (*banco).caixas[i] = nullptr;
            }
        }else{
            if((*banco).fila_entrada.size()){
                (*banco).caixas[i] = (*banco).fila_entrada.front();
                (*banco).fila_entrada.pop_front();
            }
        }
    }

    for(auto it = (*banco).fila_entrada.begin(); it != (*banco).fila_entrada.end();){
        if((*it)->pac > 0){
            (*it)->pac--;
            it++;
        }else{
            (*banco).fila_saida.push((*it));
            *docs_perdidos += (*it)->docs;
            it = (*banco).fila_entrada.erase(it);
        }
    }
}

void tic_finalizar(Banco * banco, int * docs_recebidos, int * docs_perdidos){
    while((*banco).fila_entrada.begin() != (*banco).fila_entrada.end())
        for(int i = 0; i < (int) (*banco).caixas.size(); i++){
            if((*banco).caixas[i] != nullptr)
                tic(banco, docs_recebidos, docs_perdidos);
    }
}

int main() {
    int qtd_caixas = 0;
    int docs_recebidos = 0;
    int docs_perdidos = 0;
    int total_tics = 0;
    Banco banco;
    Cliente * cliente;

    cout << "Comandos: init, show, in, tic, finalizar, end" << endl;
    
    while(true){
        string line;
        getline(cin, line);
        stringstream input(line);
        string op;
        input >> op;
        if(op == "fim"){
            break;
        }else if(op == "init"){
            input >> qtd_caixas;
            ini_caixa(&banco, qtd_caixas);
        }else if(op == "show"){
            show(banco);
        }else if(op == "in"){
            string nome;
            int docs, pac;
            input >> nome >> docs >> pac;
            cliente = new Cliente(nome, docs, pac);
            banco.fila_entrada.push_back(cliente);
        }else if(op == "tic"){
            tic(&banco, &docs_recebidos, &docs_perdidos);
            total_tics++;
        }else if(op == "finalizar"){
            tic_finalizar(&banco, &docs_recebidos, &docs_perdidos);
            cout << "Documentos recebidos: " << docs_recebidos << endl;
            cout << "Documentos perdidos: " << docs_perdidos << endl;
            cout << "Total de tics: " << total_tics << endl;
            cout << "Quantidade ideal de caixas: " << (docs_recebidos - qtd_caixas) * 100 << endl;
        }
    }    
    return 0;
}