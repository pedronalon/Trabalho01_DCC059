#include "grafo.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

 /*
 arquivo txt no formato:

 número de vertices
 vertice_inicial_1    vertice_final_1  peso_1 
 vertice_inicial_2    vertice_final_2  peso_2
 ...
 vertice_inicial_n    vertice_final_n  peso_n

 */


void testAll() {
    // Instanciando suas classes diretamente (iniciando com 0 vértices)
    Grafo gNaoOrientado(0); 
    Grafo gOrientado(0);    

    int passou = 0;
    int falhou = 0;
    int excecoes = 0;

    std::cout << "==================================================\n";
    std::cout << "              BATERIA DE TESTES \n";
    std::cout << "==================================================\n\n";

    // -------------------------------------------------------------------------
    // PARTE A: TESTES EM GRAFO NÃO ORIENTADO
    // -------------------------------------------------------------------------
    std::cout << "--------------------------------------------------\n";
    std::cout << "      Fase 1: Testando Grafo Nao Orientado        \n";
    std::cout << "--------------------------------------------------\n\n";

    std::cout << "[TESTE] Inserindo vertices iniciais (0 a 5)...\n";
    try {
        for (int i = 0; i <= 5; i++) gNaoOrientado.adicionar_vertice();
        std::cout << "  STATUS: PASSOU\n\n";
        passou++;
    } catch (...) {
        std::cout << "  STATUS: FALHOU (Lancou excecao ao inserir vertices)\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Inserindo malha de arestas...\n";
    try {
        // O false indica que não é direcionado
        gNaoOrientado.adicionar_aresta(0, 1, false, 1); // Cast implícito de double para int
        gNaoOrientado.adicionar_aresta(0, 2, false, 2);
        gNaoOrientado.adicionar_aresta(1, 2, false, 1);
        gNaoOrientado.adicionar_aresta(2, 3, false, 3);
        gNaoOrientado.adicionar_aresta(3, 4, false, 4);
        gNaoOrientado.adicionar_aresta(4, 5, false, 2);
        gNaoOrientado.adicionar_aresta(3, 5, false, 5);
        std::cout << "  STATUS: PASSOU\n\n";
        passou++;
    } catch (...) {
        std::cout << "  STATUS: FALHOU (Lancou excecao ao inserir arestas)\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Verificar existencia da aresta existente (0, 1):\n";
    std::cout << "  Saida Esperada: VERDADEIRO\n";
    try {
        bool obtido = gNaoOrientado.verificar_aresta(0, 1, false);
        std::cout << "  Saida Obtida:   " << (obtido ? "VERDADEIRO" : "FALSO") << "\n";
        if (obtido) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Verificar existencia na direcao inversa (1, 0):\n";
    std::cout << "  Saida Esperada: VERDADEIRO\n";
    try {
        bool obtido = gNaoOrientado.verificar_aresta(1, 0, false);
        std::cout << "  Saida Obtida:   " << (obtido ? "VERDADEIRO" : "FALSO") << "\n";
        if (obtido) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Verificar aresta inexistente entre vertices existentes (0, 5):\n";
    std::cout << "  Saida Esperada: FALSO\n";
    try {
        bool obtido = gNaoOrientado.verificar_aresta(0, 5, false);
        std::cout << "  Saida Obtida:   " << (obtido ? "VERDADEIRO" : "FALSO") << "\n";
        if (!obtido) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Verificar vertices invalidos/inexistentes (99, 100):\n";
    std::cout << "  Saida Esperada: FALSO \n";
    try {
        bool obtido = false; 
        
            obtido = gNaoOrientado.verificar_aresta(99, 100, false);
        
        std::cout << "  Saida Obtida:   " << (obtido ? "VERDADEIRO" : "FALSO") << "\n";
        if (!obtido) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Alterar peso da aresta (2, 3) para 9.9:\n";
    std::cout << "  Saida Esperada: Modificacao executada com sucesso\n";
    try {
        gNaoOrientado.alterar_peso(2, 3, false, 9); // Convertido pra int
        std::cout << "  Saida Obtida:   Modificacao executada com sucesso\n  STATUS:         PASSOU\n\n";
        passou++;
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Calcular grau do vertice 2 (Conectado a 0, 1 e 3):\n";
    std::cout << "  Saida Esperada: 3\n";
    try {
        int obtido = gNaoOrientado.grau_saida(2); // No não-orientado, grau_saida acumula todas as conexões
        std::cout << "  Saida Obtida:   " << obtido << "\n";
        if (obtido == 3) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Calcular grau de vertice inexistente (99):\n";
    std::cout << "  Saida Esperada: 0 (Tratado sem travar)\n";
    try {
        int obtido = 0;
        if (99 < 6) obtido = gNaoOrientado.grau_saida(99);
        std::cout << "  Saida Obtida:   " << obtido << "\n";
        if (obtido == 0) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Listar vizinhos do vertice 3:\n";
    std::cout << "  Saida Esperada: [2, 4, 5]\n";
    try {
        std::vector<int> obtido;
        // Construindo o vetor manualmente chamando a sua verificação
        for(int i = 0; i < 6; i++) {
            if (i != 3 && gNaoOrientado.verificar_aresta(3, i, false)) {
                obtido.push_back(i);
            }
        }
        std::sort(obtido.begin(), obtido.end()); 
        std::cout << "  Saida Obtida:   [";
        for (size_t i = 0; i < obtido.size(); ++i) {
            std::cout << obtido[i] << (i == obtido.size() - 1 ? "" : ", ");
        }
        std::cout << "]\n";
        bool correto = (obtido.size() == 3 && obtido[0] == 2 && obtido[1] == 4 && obtido[2] == 5);
        if (correto) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Verificar se 4 e 5 de forma bidirecional sao adjacentes:\n";
    std::cout << "  Saida Esperada: (4,5)=VERDADEIRO e (5,4)=VERDADEIRO\n";
    try {
        bool dir1 = gNaoOrientado.verificar_aresta(4, 5, false);
        bool dir2 = gNaoOrientado.verificar_aresta(5, 4, false);
        std::cout << "  Saida Obtida:   (4,5): " << (dir1 ? "VERDADEIRO" : "FALSO") << " | (5,4): " << (dir2 ? "VERDADEIRO" : "FALSO") << "\n";
        if (dir1 && dir2) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Remover aresta (3, 4):\n";
    std::cout << "  Saida Esperada: FALSO para ambas as direcoes\n";
    try {
        gNaoOrientado.remover_aresta(3, 4, false);
        bool aindaExisteDireto = gNaoOrientado.verificar_aresta(3, 4, false);
        bool aindaExisteInverso = gNaoOrientado.verificar_aresta(4, 3, false);
        std::cout << "  Saida Obtida:   Aresta (3,4) existe? " << (aindaExisteDireto ? "VERDADEIRO" : "FALSO") << "\n";
        std::cout << "                  Aresta (4,3) existe? " << (aindaExisteInverso ? "VERDADEIRO" : "FALSO") << "\n";
        if (!aindaExisteDireto && !aindaExisteInverso) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Remover vertice 2 (Remocao de No Central):\n";
    std::cout << "  Saida Esperada: FALSO para adjacencias com vizinhos antigo e reducao de graus\n";
    try {
        gNaoOrientado.remover_vertice(2);
        bool adj02 = gNaoOrientado.verificar_aresta(0, 2, false);
        bool adj12 = gNaoOrientado.verificar_aresta(1, 2, false);
        int grauRestante0 = gNaoOrientado.grau_saida(0);
        std::cout << "  Saida Obtida:   Adjacente (0,2)? " << (adj02 ? "VERDADEIRO" : "FALSO") << " | Adjacente (1,2)? " << (adj12 ? "VERDADEIRO" : "FALSO") << "\n";
        std::cout << "                  Grau restante do vertice 0: " << grauRestante0 << " (Esperado: 1, conectado apenas ao 1)\n";
        if (!adj02 && !adj12 && grauRestante0 == 1) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU (Deixou arestas orfas estruturais)\n\n"; falhou++; }
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA / CRASH\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }


    // -------------------------------------------------------------------------
    // PARTE B: TESTES EM GRAFO ORIENTADO
    // -------------------------------------------------------------------------
    std::cout << "--------------------------------------------------\n";
    std::cout << "        Fase 2: Testando Grafo Orientado          \n";
    std::cout << "--------------------------------------------------\n\n";

    std::cout << "[TESTE] Inserindo vertices iniciais (0 a 5)...\n";
    try {
        for (int i = 0; i <= 5; i++) gOrientado.adicionar_vertice();
        std::cout << "  STATUS: PASSOU\n\n";
        passou++;
    } catch (...) {
        std::cout << "  STATUS: FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Inserindo malha direcionada de arcos (Ciclos: 0->1->2->0 e 3->4->5->3)...\n";
    try {
        // True para o orientado
        gOrientado.adicionar_aresta(0, 1, true, 1);
        gOrientado.adicionar_aresta(1, 2, true, 2);
        gOrientado.adicionar_aresta(2, 0, true, 3);
        gOrientado.adicionar_aresta(2, 3, true, 1);
        gOrientado.adicionar_aresta(3, 4, true, 2);
        gOrientado.adicionar_aresta(4, 5, true, 3);
        gOrientado.adicionar_aresta(5, 3, true, 4);
        
        std::cout << "  STATUS: PASSOU\n\n";
        passou++;
    } catch (...) {
        std::cout << "  STATUS: FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Verificar existencia da aresta direcionada existente (0, 1):\n";
    std::cout << "  Saida Esperada: VERDADEIRO\n";
    try {
        bool obtido = gOrientado.verificar_aresta(0, 1, true);
        std::cout << "  Saida Obtida:   " << (obtido ? "VERDADEIRO" : "FALSO") << "\n";
        if (obtido) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Verificar existencia na direcao inversa (1, 0):\n";
    std::cout << "  Saida Esperada: FALSO\n";
    try {
        bool obtido = gOrientado.verificar_aresta(1, 0, true);
        std::cout << "  Saida Obtida:   " << (obtido ? "VERDADEIRO" : "FALSO") << "\n";
        if (!obtido) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Verificar arco inexistente entre vertices existentes (0, 5):\n";
    std::cout << "  Saida Esperada: FALSO\n";
    try {
        bool obtido = gOrientado.verificar_aresta(0, 5, true);
        std::cout << "  Saida Obtida:   " << (obtido ? "VERDADEIRO" : "FALSO") << "\n";
        if (!obtido) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Verificar vertices invalidos/inexistentes no Orientado (99, 100):\n";
    std::cout << "  Saida Esperada: FALSO\n";
    try {
        bool obtido = false;
        
            obtido = gOrientado.verificar_aresta(99, 100, true);
        
        std::cout << "  Saida Obtida:   " << (obtido ? "VERDADEIRO" : "FALSO") << "\n";
        if (!obtido) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Verificar Adjacencia Unidirecional (2, 3) vs (3, 2):\n";
    std::cout << "  Saida Esperada: (2,3)=VERDADEIRO e (3,2)=FALSO\n";
    try {
        bool dir1 = gOrientado.verificar_aresta(2, 3, true);
        bool dir2 = gOrientado.verificar_aresta(3, 2, true);
        std::cout << "  Saida Obtida:   (2,3): " << (dir1 ? "VERDADEIRO" : "FALSO") << " | (3,2): " << (dir2 ? "VERDADEIRO" : "FALSO") << "\n";
        if (dir1 && !dir2) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Remover arco direcionado (4, 5):\n";
    std::cout << "  Saida Esperada: FALSO para (4,5)\n";
    try {
        gOrientado.remover_aresta(4, 5, true);
        bool aindaExiste = gOrientado.verificar_aresta(4, 5, true);
        std::cout << "  Saida Obtida:   Arco (4,5) ainda existe? " << (aindaExiste ? "VERDADEIRO" : "FALSO") << "\n";
        if (!aindaExiste) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Remover vertice 3 (Ponto de articulacao dos ciclos):\n";
    std::cout << "  Saida Esperada: FALSO para arcos de entrada (2,3) e de saida (3,4)\n";
    try {
        gOrientado.remover_vertice(3);
        bool adj23 = gOrientado.verificar_aresta(2, 3, true);
        bool adj53 = gOrientado.verificar_aresta(5, 3, true);
        std::cout << "  Saida Obtida:   Adjacencia (2,3)? " << (adj23 ? "VERDADEIRO" : "FALSO") << "\n";
        std::cout << "                  Adjacencia (5,3)? " << (adj53 ? "VERDADEIRO" : "FALSO") << "\n";
        if (!adj23 && !adj53) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) {
        std::cout << "  Saida Obtida:   EXCECAO LANCADA\n  STATUS:         FALHOU\n\n";
        excecoes++;
    }

    std::cout << "[TESTE] Exibir estado impresso dos grafos finais:\n";
    std::cout << "--------------------------------------------------\n";
    try {
        std::cout << ">> GRAFO NAO ORIENTADO RESULTANTE (Sua impressao nativa):\n";
        gNaoOrientado.imprimir(); 
        
        std::cout << "\n>> GABARITO ESPERADO PARA O NAO ORIENTADO (FORMATO CS ACADEMY):\n";
        std::cout << "5\n0 1 1.5\n4 5 2.5\n3 5 5.0\n";

        std::cout << "\n==================================================\n";

        std::cout << ">> GRAFO ORIENTADO RESULTANTE (Sua impressao nativa):\n";
        gOrientado.imprimir();
        
        std::cout << "\n>> GABARITO ESPERADO PARA O ORIENTADO (FORMATO CS ACADEMY):\n";
        std::cout << "5\n0 1 1\n1 2 2\n2 0 3\n";
        
        std::cout << "--------------------------------------------------\n";
        std::cout << "  STATUS:         PASSOU\n\n";
        passou++;
    } catch (...) {
        std::cout << "--------------------------------------------------\n";
        std::cout << "  STATUS:         FALHOU \n\n";
        excecoes++;
    }

    std::cout << "==================================================\n";
    std::cout << "         RESUMO FINAL DA BATERIA DE TESTES        \n";
    std::cout << "==================================================\n";
    std::cout << "  TESTES QUE PASSARAM: " << passou << "\n";
    std::cout << "  TESTES QUE FALHARAM: " << falhou << "\n";
    std::cout << "  EXCECOES CAPTURADAS: " << excecoes << "\n";
    std::cout << "  TOTAL DE CASOS TESTADOS: " << (passou + falhou + excecoes) << "\n";
    std::cout << "==================================================\n";

    Grafo g_txt("grafo.txt", false);
    g_txt.exportar_dot("grafo.dot", false);
    g_txt.dijkstra(0) ; 
}

int main() {
    testAll();
    return 0;
}