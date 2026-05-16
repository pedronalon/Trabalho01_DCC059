#include "grafo.hpp"

No::No(int id) : id(id), visitado(false), grau_entrada(0), grau_saida(0) {}

Grafo::Grafo(int n) : num_vertices(n) {
    for (int i = 0; i < n; i++) {
        nos.push_back(new No(i));
    }
}

Grafo::~Grafo() {
    for (No* no : nos) {
        delete no;
    }
}

void Grafo::limpar_visitados() {
    for (No* no : nos) {
        no->visitado = false;
    }
}

void Grafo::adicionar_aresta(int u, int v, bool direcionado) {
    nos[u]->vizinhos.push_back(nos[v]);
    nos[u]->grau_saida++;
    nos[v]->grau_entrada++;

    if (!direcionado) {
        nos[v]->vizinhos.push_back(nos[u]);
        nos[v]->grau_saida++;
        nos[u]->grau_entrada++;
    }
}

void Grafo::imprimir() {
    for (No* no : nos) {
        std::cout << no->id << ": ";
        for (No* viz : no->vizinhos) {
            std::cout << viz->id << " ";
        }
        std::cout << "\n";
    }
}
// ------------------------------------
// EXEMPLO:
// Busca em profundidade (recursiva)
// ------------------------------------

void Grafo::busca_profundidade_recursiva(int inicio) {
    limpar_visitados();
    aux_profundidade_recursiva(nos[inicio]);
}

void Grafo::aux_profundidade_recursiva(No* no) {
    no->visitado = true;
    std::cout << no->id << " ";

    for (No* viz : no->vizinhos) {
        if (!viz->visitado) {
            aux_profundidade_recursiva(viz);
        }
    }
}

// ------------------------------------
// Exercício 01
// Busca em profundidade (iterativa)
// ------------------------------------

void Grafo::busca_profundidade_iterativa(int inicio) {
    limpar_visitados();

}


// ------------------------------------
// Exercício 02
// Busca em largura
// ------------------------------------

void Grafo::busca_largura(int inicio) {
    limpar_visitados();

}



// ------------------------------------
// Exercicio 03
// Ordenação topológica 
// ------------------------------------

void Grafo::ordenacao_topologica() {

}