#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class No
{
public:
    int id;
    bool visitado;
    int grau_entrada;
    int grau_saida;
    vector<No *> vizinhos;

    No(int id);
};

class Grafo
{
private:
    int num_vertices;
    vector<No *> nos;

    vector<vector<int>> matrizPesos;

    void limpar_visitados();

    int obter_indice(int id_vertice);

public:
    Grafo(int n);
    Grafo(const std::string& nome_arquivo, bool direcionado);
    ~Grafo();

    void adicionar_aresta(int u, int v, bool direcionado = false, int peso = 0);
    void remover_aresta(int u, int v, bool direcionado = false);
    bool verificar_aresta(int u, int v, bool direcionado);
    void alterar_peso(int u, int v, bool direcionado, int peso);

    void imprimir();
    void imprimirPesos();
    void  adicionar_vertice();
    void remover_vertice(int n); 

    void imprimir_vizinhos(int u);

    int grau(int u);
    int grau_entrada(int u);
    int grau_saida(int u);
    int grau_total(int u);

    void dijkstra(int origem);

    void exportar_dot(const string& nome_arquivo, bool direcionado);

private:
    
};

#endif