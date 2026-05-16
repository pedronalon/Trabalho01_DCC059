#include "grafo.hpp"

using namespace std;

int main()
{

  int d = 0;
  Grafo g(5);

  cout << "inserir aresta" << endl;
  g.adicionar_aresta(0, 1, d, 1);
  g.adicionar_aresta(0, 2, d, 2);
  g.adicionar_aresta(1, 3, d, 3);
  g.adicionar_aresta(2, 4, d, 4);


  cout << "pesos" << endl;
  g.imprimirPesos();

  g.remover_aresta(0, 1, d);
  cout << "Grafo nao direcionado:" << endl;
  g.imprimir();
  cout << "pesos" << endl;
  g.imprimirPesos();

  cout << "verificar aresta" << endl;
  cout << g.verificar_aresta(0, 1, d) << endl;
  cout << g.verificar_aresta(0, 2, d) << endl;

  g.alterar_peso(0, 2, d, 20);
  cout << "imprimir pesos alterados" << endl;
  g.imprimirPesos();

  Grafo gdir(5);
  d = 1;
  cout << "inserir aresta" << endl;
  gdir.adicionar_aresta(0, 1, d, 1);
  gdir.adicionar_aresta(0, 2, d, 2);
  gdir.adicionar_aresta(1, 3, d, 3);
  gdir.adicionar_aresta(2, 4, d, 4);

  cout << "Grafo nao direcionado:" << endl;
  gdir.imprimir();

  cout << "pesos" << endl;
  gdir.imprimirPesos();

  gdir.remover_aresta(0, 1, d);
  cout << "Grafo nao direcionado:" << endl;
  gdir.imprimir();
  cout << "pesos" << endl;
  gdir.imprimirPesos();

  cout << "verificar aresta" << endl;
  cout << gdir.verificar_aresta(0, 1, d) << endl;
  cout << gdir.verificar_aresta(0, 2, d) << endl;

  gdir.alterar_peso(0, 2, d, 20);
  cout << "imprimir pesos alterados" << endl;
  gdir.imprimirPesos();

  return 0;
}