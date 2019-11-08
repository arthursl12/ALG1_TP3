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

    /* Execução */
    Grafo G(N);
    G.inicializa_grafo(N, I, J);
    // G.imprime_grafo();
    G.pre_colore(N, arq);

    Tabuleiro resultado;
    bool correto = G.resolve_sudoku(resultado);

    if (correto == true){
        std::cout << "solução" << std::endl;
    }else{
        std::cout << "sem solução" << std::endl;
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            std::cout << resultado[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    arq.close();
    return 0;
}