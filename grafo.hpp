#ifndef GRAFO_HPP
#define GRAFO_HPP

#include<vector> 
#include <queue>
#include <stack>
#include <iostream>

using namespace std ; 

class No {
public:
    int id;
    bool visitado;
    int grau_entrada;
    int grau_saida;
    vector<No*> vizinhos;

    No(int id);
};

class Grafo {
private:
    int num_vertices;
    vector<No*> nos;

    void limpar_visitados();

public:
    Grafo(int n);
    ~Grafo();

    void adicionar_aresta(int u, int v, bool direcionado = false);
    void imprimir();
    void  adicionar_vertice();
    void remover_vertice(int n); 

    void busca_profundidade_recursiva(int inicio);
    void busca_profundidade_iterativa(int inicio);
    void busca_largura(int inicio);
    void ordenacao_topologica();

private:
    void aux_profundidade_recursiva(No* no);
};


#endif