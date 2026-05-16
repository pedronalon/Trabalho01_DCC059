#include "grafo.hpp"

using namespace std;

int main() {
//   Grafo g(5);

//   g.adicionar_aresta(0, 1);
//   g.adicionar_aresta(0, 2);
//   g.adicionar_aresta(1, 3);
//   g.adicionar_aresta(2, 4);
//   g.adicionar_vertice() ; 


//   cout << "Grafo inicial" << endl;
//   g.imprimir();


//   cout << endl ; 
//   g.adicionar_aresta(5,0);
//   g.imprimir() ; 

//   cout << endl;
//   g.remover_vertice(0);
//   g.imprimir(); 

//   cout << endl;

  Grafo g_dir(6);

  g_dir.adicionar_aresta(5, 2, true);
  g_dir.adicionar_aresta(5, 0, true);
  g_dir.adicionar_aresta(4, 0, true);
  g_dir.adicionar_aresta(4, 1, true);
  g_dir.adicionar_aresta(2, 3, true);
  g_dir.adicionar_aresta(3, 1, true);

  
  cout << "Grafo direcionado:" << endl;
  g_dir.imprimir();
  
  g_dir.remover_vertice(1) ;
  cout << endl ; 
  
  g_dir.imprimir();


//   cout << "";

  return 0;
}