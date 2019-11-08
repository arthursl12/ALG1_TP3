#include <fstream>
#include <iostream>
#include "grafo.h"

int main(int argc, char* argv[]){
    /* Coleta o argumento: nome do arquivo a ser lido e abre o arquivo*/
    if (argc != 2){std::cout << "Argumento faltando"; exit(1);}
    std::string nome_arq = argv[1];
    std::ifstream arq;
    arq.open(nome_arq, std::ios::in);
    if (!arq.is_open()){std::cout << "Erro na abertura do arquivo"; exit(1);}

    
    /* Leitura dos dados */
    int N; /* Tabuleiro NxN */
    int I; /* # de colunas (quadrante) */
    int J; /* # de linhas (quadrante) */

    std::string Linha;
    std::getline(arq,Linha);
    std::string aux;
    str_tok(Linha," ",aux);
    N = std::stoi(aux);
    str_tok(Linha," ",aux);
    I = std::stoi(aux);
    str_tok(Linha," ",aux);
    J = std::stoi(aux);

    Grafo G(N);
    G.inicializa_grafo(N, I, J);
    G.imprime_grafo();
    G.pre_colore(N, arq);

    std::cout << std::endl;
    for (int i = 0; i < N*N; i++){
        std::cout << "i = " << i << "; C = " << G.is_colored(i) << "; G = " << G.saturated_degree(i) << std::endl;
    }

    std::cout << std::endl;
    std::cout << "MAX = " << G.max_sat_degree() << std::endl;
    /* Execução */
    // TODO
    
    arq.close();
    return 0;
}