#include "grafo.hpp"
#include <vector>
#include <climits>
#include <fstream>
#include <string>



No::No(int id) : id(id), visitado(false), grau_entrada(0), grau_saida(0) {}

Grafo::Grafo(int n) : num_vertices(n)
{

    for (int i = 0; i < n; i++)
        nos.push_back(new No(i));
    
    matrizPesos.assign(n, vector<int>(n, 0));
}


Grafo::Grafo(const string& nome_arquivo, bool direcionado) {
    ifstream arquivo(nome_arquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro: Nao foi possivel abrir o arquivo '" << nome_arquivo << "'!\n";
        this->num_vertices = 0; 
        return;
    }

    // pega a primeira linha
    arquivo >> this->num_vertices;

    
    for (int i = 0; i < this->num_vertices; i++) {
        nos.push_back(new No(i));
    }
    matrizPesos.assign(this->num_vertices, vector<int>(this->num_vertices, 0));

    // agora o resto do arquivo e insere as arestas
    int u, v, peso;
    while (arquivo >> u >> v >> peso) 
        adicionar_aresta(u, v, direcionado, peso); 
    

    arquivo.close();
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
    }
    num_vertices--;
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
            matrizPesos[u][v] = 0; 
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
                matrizPesos[v][u] = 0; 
                break;
            }
            pos++;
        }
    }
}
bool Grafo::verificar_aresta(int u, int v, bool direcionado)
{
    int idx_u = -1;
    int idx_v = -1;

    for (int k = 0; k < nos.size(); k++) {
        if (nos[k]->id == u) idx_u = k;
        if (nos[k]->id == v) idx_v = k;
    }

    if (idx_u == -1 || idx_v == -1) {
        return false;
    }

    for (No *viz : nos[idx_u]->vizinhos)
    {
        if (viz->id == v)
        {
            return true;
        }
    }

    if (!direcionado)
    {
        for (No *viz : nos[idx_v]->vizinhos)
        {
            if (viz->id == u)
            {
                return true;
            }
        }
    }

    return false;
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
        cout << no->id << ": ";
        for (No *viz : no->vizinhos)
        {
            cout << viz->id << " ";
        }
        cout << "\n";
    }
}

void Grafo::imprimirPesos()
{
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            cout << matrizPesos[i][j] << " ";
        }
        cout << "\n";
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
    int idx = obter_indice(u);
    if (idx == -1) return 0; 
    return nos[idx]->grau_saida;
}

int Grafo::grau_entrada(int u){
    int idx = obter_indice(u);
    if (idx == -1) return 0;
    return nos[idx]->grau_entrada;
}

int Grafo::grau_saida(int u){
    return grau(u); 
}

int Grafo::grau_total(int u){
    int idx = obter_indice(u);
    if (idx == -1) return 0;
    return nos[idx]->grau_saida + nos[idx]->grau_entrada;
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

    // fila de prioridade armazena pares (distancia, id_do_vertice)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;

    // vetores para rastrear as distancias e o caminho feito
    vector<int> dist(num_vertices, INT_MAX);
    vector<int> pai(num_vertices, -1); 

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
                pai[v] = u; 
                fila.push({dist[v], v});
            }
        }
    }

   
    cout << "\n[Dijkstra] Resultados a partir do vertice " << origem << ":\n";
    for (int i = 0; i < num_vertices; ++i) {
        if (dist[i] == INT_MAX) {
            cout << "  Vertice " << i << ": Inalcancavel\n";
        } else {
            cout << "  Vertice " << i << " | Custo total: " << dist[i] << " | Caminho: ";
            
            // Reconstruindo o caminho usando o vetor 'pai'
            vector<int> caminho;
            for (int atual = i; atual != -1; atual = pai[atual]) {
                caminho.push_back(atual);
            }
            
            // Como rastreamos de trás para frente, imprimimos na ordem reversa
            for (int k = caminho.size() - 1; k >= 0; --k) {
                cout << caminho[k] << (k == 0 ? "" : " -> ");
            }
            cout << "\n";
        }
    }
}




int Grafo::obter_indice(int id_vertice) {
    for (int i = 0; i < nos.size(); i++) {
        if (nos[i]->id == id_vertice) {
            return i; 
        }
    }
    return -1; 
}


void Grafo::exportar_dot(const string& nome_arquivo, bool direcionado) {
    ofstream arquivo(nome_arquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro ao criar o arquivo DOT.\n";
        return;
    }

    // inicia o cabeçalho dependendo do tipo do grafo
    if (direcionado) {
        arquivo << "digraph G {\n";
    } else {
        arquivo << "graph G {\n";
    }


    for (int u = 0; u < num_vertices; u++) {
        for (No* viz : nos[u]->vizinhos) {
            int v = viz->id;
            int peso = matrizPesos[u][v];

           
            // Para não desenhar a mesma linha duas vezes, só exportamos quando u < v.
            if (!direcionado && u > v) {
                continue; 
            }

            // Escreve a aresta no arquivo
            if (direcionado) {
                arquivo << "  " << u << " -> " << v << " [label=\"" << peso << "\"];\n";
            } else {
                arquivo << "  " << u << " -- " << v << " [label=\"" << peso << "\"];\n";
            }
        }
    }

    arquivo << "}\n";
    arquivo.close();
}