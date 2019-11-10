#include <fstream>
#include <chrono>
#include <cmath>
#include <bits/stdc++.h> 

#include "grafo.h"

#define N_TESTES 30

double media(int tempos[]){
    double soma = 0;
    for (int i = 0; i < N_TESTES; i++){
        soma += tempos[i];
    }
    return soma/N_TESTES;
}

double mediana(int tempos[]){
    std::sort(tempos, tempos+N_TESTES);
    if (N_TESTES % 2 != 0) 
       return (double)tempos[N_TESTES/2]; 
      
    return (double)(tempos[(N_TESTES-1)/2] + tempos[N_TESTES/2])/2.0; 
}

double dev(int tempos[], double med){
    double soma = 0;
    for (int i = 0; i < N_TESTES; i++){
        soma += pow((tempos[i]-med),2);
    }
    double var = soma/(N_TESTES-1);
    return sqrt(var);
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

    /* Execução */
    Grafo G(N);
    G.inicializa_grafo(N, I, J);
    // G.imprime_grafo();
    G.pre_colore(N, arq);

    /* Execução do programa: leitura e processamento */
    std::chrono::duration<double> tempos[N_TESTES];
    bool correto = false;
    
    for (int i = 0; i < N_TESTES; i++){
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        Tabuleiro resultado;
        correto = G.resolve_sudoku(resultado);

        // if (correto == true){
        //     std::cout << "solução" << std::endl;
        // }else{
        //     std::cout << "sem solução" << std::endl;
        // }
        // for (int i = 0; i < N; i++){
        //     for (int j = 0; j < N; j++){
        //         std::cout << resultado[i][j] << " ";
        //     }
        //     std::cout << std::endl;
        // }


        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        tempos[i] = elapsed_time;
    }
    arq.close();

    /* Finalização e tomada de testes */
    int tempos_int[N_TESTES];

    std::ofstream out;
    out.open("tempo/tempos.txt", std::ofstream::out | std::ofstream::app);
    for (int i = 0; i < N_TESTES; i++){
        double x = tempos[i].count();
        x = x*pow(10,6);
        int y = (int) x;
        tempos_int[i] = y;
    }

    double med = media(tempos_int);
    double st = dev(tempos_int,med);
    double md = mediana(tempos_int);
    out << nome_arq << " ";
    out << correto << " ";
    out << N << "x" << N;
    out << " " << med << " " << st << " " << md << std::endl;

    return 0;
}