#include "grafo.hpp"

using namespace std;

int main() {
  Grafo g(5);

  g.adicionar_aresta(0, 1);
  g.adicionar_aresta(0, 2);
  g.adicionar_aresta(1, 3);
  g.adicionar_aresta(2, 4);

  cout << "Grafo nao direcionado:" << endl;
  g.imprimir();

  cout << "Busca em profundidade (recursiva):" << endl;
  g.busca_profundidade_recursiva(0);

  cout << "Busca em profundidade (iterativa):" << endl;
  g.busca_profundidade_iterativa(0);

  cout << "Busca em largura:";
  g.busca_largura(0);

  cout << endl;

  Grafo g_dir(6);

  g_dir.adicionar_aresta(5, 2, true);
  g_dir.adicionar_aresta(5, 0, true);
  g_dir.adicionar_aresta(4, 0, true);
  g_dir.adicionar_aresta(4, 1, true);
  g_dir.adicionar_aresta(2, 3, true);
  g_dir.adicionar_aresta(3, 1, true);

  cout << "Grafo direcionado:" << endl;
  g_dir.imprimir();

  cout << "Ordenacao topologica:" << endl;
  g_dir.ordenacao_topologica();

  cout << "";

  return 0;
}