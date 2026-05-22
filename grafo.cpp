#include "grafo.hpp"
#include <vector>
No::No(int id) : id(id), visitado(false), grau_entrada(0), grau_saida(0) {}

Grafo::Grafo(int n) : num_vertices(n)
{

    for (int i = 0; i < n; i++)

    {

        nos.push_back(new No(i));
    }

    matrizPesos.assign(n, vector<int>(n, 0));
}

Grafo::~Grafo()
{
    for (No *no : nos)
    {
        delete no;
    }
}

void Grafo::limpar_visitados()
{
    for (No *no : nos)
    {
        no->visitado = false;
    }
}

void Grafo::adicionar_aresta(int u, int v, bool direcionado, int peso)
{
    nos[u]->vizinhos.push_back(nos[v]);
    nos[u]->grau_saida++;
    nos[v]->grau_entrada++;
    matrizPesos[u][v] = peso;
    if (!direcionado)
    {
        nos[v]->vizinhos.push_back(nos[u]);
        nos[v]->grau_saida++;
        nos[u]->grau_entrada++;
        matrizPesos[v][u] = peso;
    }
}
void Grafo::adicionar_vertice(){
    int n = nos.size() ; 
    nos.push_back(new No(n)) ; 
    n++ ; 
    num_vertices = n ; 
    for(int i = 0; i < matrizPesos.size(); i++) {
        matrizPesos[i].push_back(0);
    }
    matrizPesos.push_back(vector<int>(num_vertices, 0));
}

void Grafo::remover_vertice(int i) {
    No* no_remover = nullptr;
    int pos_grafo = 0;

    for(No* no : nos) {
        if(i == no->id) {
            no_remover = no;
            nos.erase(nos.begin() + pos_grafo); 
            matrizPesos.erase(matrizPesos.begin() + pos_grafo);
            for(int k = 0; k < matrizPesos.size(); k++) {
        matrizPesos[k].erase(matrizPesos[k].begin() + pos_grafo);
        num_vertices--;
    }
            break; 
        }
        pos_grafo++; 
    }

    if(no_remover == nullptr) {
        cout << "Vértice não existe" << endl ; 
        return;
    }

    for(No* vizinho : no_remover->vizinhos) {
        vizinho->grau_entrada--;
    }



    for(No* no : nos) {
        int pos_vizinho = 0;
        
        for(No* vizinho : no->vizinhos) { 
            if(i == vizinho->id) {
                no->vizinhos.erase(no->vizinhos.begin() + pos_vizinho);
                no->grau_saida--;
                break; 
            }
            pos_vizinho++;
        }
    }

    delete no_remover;
}

void Grafo::remover_aresta(int u, int v, bool direcionado)
{
    int pos = 0;
    for (No *viz : nos[u]->vizinhos)
    {
        if (viz->id == v)
        {
            nos[u]->vizinhos.erase(nos[u]->vizinhos.begin() + pos);
            nos[u]->grau_saida--;
            nos[v]->grau_entrada--;
            matrizPesos[v][u] = 0;
            break;
        }
        pos++;
    }

    if (!direcionado)
    {
        pos = 0;
        for (No *viz : nos[v]->vizinhos)
        {
            if (viz->id == u)
            {
                nos[v]->vizinhos.erase(nos[v]->vizinhos.begin() + pos);
                nos[v]->grau_saida--;
                nos[u]->grau_entrada--;
                matrizPesos[u][v] = 0;
                break;
            }
            pos++;
        }
    }
}

bool Grafo::verificar_aresta(int u, int v, bool direcionado)
{
    for (No *viz : nos[u]->vizinhos)
    {
        if (viz->id == v)
        {
            return 1;
        }
    }

    if (!direcionado)
    {
        for (No *viz : nos[v]->vizinhos)
        {
            if (viz->id == u)
            {
                return 1;
            }
        }
    }

    return 0;
}

void Grafo::alterar_peso(int u, int v, bool direcionado, int peso)
{

    matrizPesos[u][v] = peso;

    if (!direcionado)
        matrizPesos[v][u] = peso;
}

void Grafo::imprimir()
{
    for (No *no : nos)
    {
        std::cout << no->id << ": ";
        for (No *viz : no->vizinhos)
        {
            std::cout << viz->id << " ";
        }
        std::cout << "\n";
    }
}

void Grafo::imprimirPesos()
{
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            std::cout << matrizPesos[i][j] << " ";
        }
        std::cout << "\n";
    }
}


void Grafo::imprimir_vizinhos(int u){
    for(No* v : nos[u]->vizinhos)
        cout<<v->id<<" ";

    cout<<endl;
}
// ------------------------------------
// GRAU
// ------------------------------------

int Grafo::grau(int u){
    return nos[u]->grau_saida;
}

int Grafo::grau_entrada(int u){
    return nos[u]->grau_entrada;
}

int Grafo::grau_saida(int u){
    grau(u);
}

int Grafo::grau_total(int u){
    return nos[u]->grau_saida + nos[u]->grau_entrada;
}

// ------------------------------------
// DIJKSTRA
// ------------------------------------

void Grafo::dijkstra(int origem) {
    // vê se o vértice existe
    if (origem < 0 || origem >= num_vertices) {
        cout << "vertice invalido.\n";
        return;
    }

    // Fila de prioridade: armazena pares (distancia, id_do_vertice)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;

    // Vetores para rastrear as distâncias e o caminho feito
    vector<int> dist(num_vertices, INT_MAX);
    vector<int> pai(num_vertices, -1); // Guarda de qual vértice viemos para chegar no atual

    dist[origem] = 0;
    fila.push({0, origem});

    while (!fila.empty()) {
        int d_atual = fila.top().first;
        int u = fila.top().second;
        fila.pop();

        if (d_atual > dist[u]) continue;

        // percorre os vizinhos
        for (No* viz : nos[u]->vizinhos) {
            int v = viz->id; 
            
            // busca o peso entre u e v na matriz 
            int peso = matrizPesos[u][v]; 

            // se encontrar caminho menor, atualizamos pi*
            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pai[v] = u; // Registramos que para chegar em 'v' rápido, viemos de 'u'
                fila.push({dist[v], v});
            }
        }
    }

    // --- Impressão dos Resultados ---
    std::cout << "\n[ Dijkstra ] Resultados a partir do vertice " << origem << ":\n";
    for (int i = 0; i < num_vertices; ++i) {
        if (dist[i] == INT_MAX) {
            std::cout << " -> Vertice " << i << ": Inalcancavel\n";
        } else {
            std::cout << " -> Vertice " << i << " | Custo total: " << dist[i] << " | Caminho: ";
            
            // Reconstruindo o caminho usando o vetor 'pai'
            vector<int> caminho;
            for (int atual = i; atual != -1; atual = pai[atual]) {
                caminho.push_back(atual);
            }
            
            // Como rastreamos de trás para frente, imprimimos na ordem reversa
            for (int k = caminho.size() - 1; k >= 0; --k) {
                std::cout << caminho[k] << (k == 0 ? "" : " -> ");
            }
            std::cout << "\n";
        }
    }
}

// ------------------------------------
// EXEMPLO:
// Busca em profundidade (recursiva)
// ------------------------------------

void Grafo::busca_profundidade_recursiva(int inicio)
{
    limpar_visitados();
    aux_profundidade_recursiva(nos[inicio]);
}

void Grafo::aux_profundidade_recursiva(No *no)
{
    no->visitado = true;
    std::cout << no->id << " ";

    for (No *viz : no->vizinhos)
    {
        if (!viz->visitado)
        {
            aux_profundidade_recursiva(viz);
        }
    }
}

// ------------------------------------
// Exercício 01
// Busca em profundidade (iterativa)
// ------------------------------------

void Grafo::busca_profundidade_iterativa(int inicio)
{
    limpar_visitados();
}

// ------------------------------------
// Exercício 02
// Busca em largura
// ------------------------------------

void Grafo::busca_largura(int inicio)
{
    limpar_visitados();
}

// ------------------------------------
// Exercicio 03
// Ordenação topológica
// ------------------------------------

void Grafo::ordenacao_topologica()
{
}