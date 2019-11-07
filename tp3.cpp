#include <fstream>
#include <iostream>
#include <vector>
#include "ilha.h"

typedef std::vector<std::vector<int>> Grafo;

/* Particiona a string 'str' pelo delimitador 'delimiter' e guarda o token particionado 
na string 'token' (o token é removido da string original); Se não encontrar o token, 
apenas coloca a string original no 'token'; Retorna 'True' se foi possível fazer 
a operação, 'False' se não encontrar o delimitador e não conseguir fazer o particionamento; */
bool str_tok(std::string& str, std::string delimiter, std::string& token){
    std::size_t idx = str.find(delimiter);
    token = str.substr(0, idx);

    if (idx == std::string::npos){
        /* Não achou o delimitador: não faz nada e coloca a string original no token*/
        token = str;
        return false;
    }
    str.erase(0, idx+1); /* Remove o token e o delimitador da string original */
    return true;
}

void inicializa_grafo(Grafo& grafo, int N, std::ifstream& arq){
    /* Alocação */
    for (int i = 0; i < N; i++){
        std::vector<int> linha_grafo;
        grafo.push_back(linha_grafo);
        for (int j = 0; j < N; j++){
            grafo[i].push_back(0);
        }
    }

    /* Coloração */ 
    /* Cores: 1 a 9 */
    for (int i = 0; i < N; i++){
        std::string Linha, aux;
        std::getline(arq,Linha);
        for (int j = 0; j < N; j++){
            str_tok(Linha," ",aux);
            int cell =  std::stoi(aux);
            if (cell == 0) continue;
            grafo[i][j] = cell;
            // std::cout << "(" << i << "," << j << "): " << cell << std::endl;
        }
    }
}

void imprime_grafo(Grafo& grafo){
    auto it = grafo.begin();
    while(it != grafo.end()){
        auto it1 = (*it).begin();
        while(it1 != (*it).end()){
            std::cout << *it1 << " ";
            it1++;
        }
        std::cout << std::endl;
        it++;
    }
}

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

    Grafo G;
    inicializa_grafo(G, N, arq);
    imprime_grafo(G);

    /* Execução */
    // TODO
    
    arq.close();
    return 0;
}