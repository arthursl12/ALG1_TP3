#include <fstream>
#include <chrono>
#include <cmath>
#include <bits/stdc++.h> 

#include "roteiros.h"

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
    std::vector<ilha> Ilhas;
    int N;
    int C_Max;
    std::string Linha;
    std::getline(arq,Linha);
    std::string aux;
    str_tok(Linha," ",aux);
    C_Max = std::stoi(aux);
    str_tok(Linha," ",aux);
    N = std::stoi(aux);
    for (int i = 0; i < N; i++){
        std::getline(arq,Linha);
        str_tok(Linha," ",aux);
        int custo = std::stoi(aux);
        str_tok(Linha," ",aux);
        int valor = std::stoi(aux);

        ilha i1;
        i1.custo = custo;
        i1.valor = valor;
        i1.cdv = (double)custo/(double)valor;

        Ilhas.push_back(i1);
    }


    /* Execução do programa: leitura e processamento */
    std::chrono::duration<double> tempos_guloso[N_TESTES];
    std::chrono::duration<double> tempos_dinamica[N_TESTES];
    

    for (int i = 0; i < N_TESTES; i++){
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        int dias = 0;
        int pontu = 0;
        guloso(pontu, dias, C_Max, N, Ilhas);

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        tempos_guloso[i] = elapsed_time;
    }

    for (int i = 0; i < N_TESTES; i++){
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        int dias = 0;
        int pontu = 0;
        dinamica(pontu, dias, C_Max, N, Ilhas);

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        tempos_dinamica[i] = elapsed_time;
    }
    arq.close();

    /* Finalização e tomada de testes */
    int tempos_guloso_int[N_TESTES];
    int tempos_dinamica_int[N_TESTES];

    std::ofstream out;
    out.open("tempo/tempos.txt", std::ofstream::out | std::ofstream::app);
    for (int i = 0; i < N_TESTES; i++){
        double x = tempos_guloso[i].count();
        x = x*pow(10,6);
        int y = (int) x;
        tempos_guloso_int[i] = y;
    }
    for (int i = 0; i < N_TESTES; i++){
        double x = tempos_dinamica[i].count();
        x = x*pow(10,6);
        int y = (int) x;
        tempos_dinamica_int[i] = y;
    }

    double med_G = media(tempos_guloso_int);
    double st_G = dev(tempos_guloso_int,med_G);
    double md_G = mediana(tempos_guloso_int);
    out << " G " << N << " " << C_Max << " " << med_G << " " << st_G << " " << md_G << std::endl;

    double med_D = media(tempos_dinamica_int);
    double st_D = dev(tempos_dinamica_int,med_D);
    double md_D = mediana(tempos_dinamica_int);
    out << " D " << N << " " << C_Max << " " << med_D << " " << st_D << " " << md_D << std::endl;
    return 0;
}