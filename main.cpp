#include "grafo.hpp"
#include <iostream>

using namespace std;

int main()
{
  cout << "========================================================\n";
  cout << "       TUTORIAL: TESTANDO A ESTRUTURA DO GRAFO          \n";
  cout << "========================================================\n\n";

  // ========================================================
  // PARTE 1: OPERAÇÕES BÁSICAS (GRAFO NÃO DIRECIONADO)
  // ========================================================
  cout << "--------------------------------------------------------\n";
  cout << " PARTE 1: OPERAÇÕES BÁSICAS E PESOS\n";
  cout << "--------------------------------------------------------\n";

  cout << "[ Passo 1 ] Criando grafo nao direcionado com 5 vertices (0 a 4)...\n";
  Grafo g(5);
  bool d = false;

  cout << "[ Passo 2 ] Adicionando arestas com pesos...\n";
  g.adicionar_aresta(0, 1, d, 1);
  g.adicionar_aresta(0, 2, d, 2);
  g.adicionar_aresta(1, 3, d, 3);
  g.adicionar_aresta(2, 4, d, 4);

  cout << "\n[ Lista de Adjacencia Inicial ]\n";
  g.imprimir();
  cout << "\n[ Matriz de Pesos Inicial ]\n";
  g.imprimirPesos();

  cout << "\n[ Passo 3 ] Alterando o peso da aresta (0 <-> 2) para 20...\n";
  g.alterar_peso(0, 2, d, 20);
  g.imprimirPesos();

  cout << "\n[ Passo 4 ] Removendo a aresta (0 <-> 1)...\n";
  g.remover_aresta(0, 1, d);
  cout << "Lista apos remocao da aresta:\n";
  g.imprimir();
  cout << "Pesos apos remocao da aresta (deve zerar a posicao):\n";
  g.imprimirPesos();

  // ========================================================
  // PARTE 2: ALTERAÇÃO DINÂMICA DE VÉRTICES
  // ========================================================
  cout << "\n--------------------------------------------------------\n";
  cout << " PARTE 2: INSERÇÃO E REMOÇÃO DINÂMICA DE VÉRTICES\n";
  cout << "--------------------------------------------------------\n";

  cout << "[ Passo 5 ] Adicionando um NOVO vertice no grafo...\n";
  cout << "(Como tinhamos 5 vertices [0 a 4], o novo sera o ID 5)\n";
  g.adicionar_vertice();

  cout << "\n[ Lista de Adjacencia ] (Note o vertice 5 isolado no fim):\n";
  g.imprimir();
  cout << "\n[ Matriz de Pesos ] (Agora ela deve ser uma matriz 6x6):\n";
  g.imprimirPesos();

  cout << "\n[ Passo 6 ] Conectando o novo vertice 5 ao vertice 2 com peso 99...\n";
  g.adicionar_aresta(5, 2, d, 99);
  cout << "\n[ Lista de Adjacencia Atualizada ]\n";
  g.imprimir();
  cout << "\n[ Matriz de Pesos Atualizada ]\n";
  g.imprimirPesos();

  cout << "\n[ Passo 7 ] Removendo o vertice 2 do grafo...\n";
  cout << "(Isso deve apagar o vertice 2, suas arestas e reorganizar a estrutura)\n";
  g.remover_vertice(2);

  cout << "\n[ Lista de Adjacencia Final ]\n";
  g.imprimir();
  cout << "\n[ Matriz de Pesos Final ] (Voltou a ser 5x5 e sem os pesos do antigo vertice 2):\n";
  g.imprimirPesos();

  cout << "\n========================================================\n";
  cout << "                FIM DO TUTORIAL                         \n";
  cout << "========================================================\n";

  return 0;
}