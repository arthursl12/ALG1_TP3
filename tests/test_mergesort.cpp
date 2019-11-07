#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <fstream>
#include <string>
#include "doctest.h"
#include "../mergesort.h"
#include "../ilha.h"

TEST_CASE("Mergesort: vetor vazio"){
    std::vector<ilha> Ilhas;
    CHECK_NOTHROW(mergesort(Ilhas, 0, 0));
    CHECK(Ilhas.size() == 0);
}

TEST_CASE("Mergesort: vetor unitário"){
    std::vector<ilha> Ilhas;
    ilha i1;
    i1.custo = 10;
    i1.valor = 1;
    i1.cdv = (double)10/(double)1;
    Ilhas.push_back(i1);

    
    CHECK_NOTHROW(mergesort(Ilhas, 0, 0));
    CHECK(Ilhas.size() == 1);
    CHECK(Ilhas[0].custo == 10);
}

void coloca_ilha(std::vector<ilha>& Ilhas, int custo, int valor){
    ilha i1;
    i1.custo = custo;
    i1.valor = valor;
    i1.cdv = (double)custo/(double)valor;
    Ilhas.push_back(i1);
}

TEST_CASE("Mergesort: vetor genérico aleatório"){
    std::vector<ilha> Ilhas;
    coloca_ilha(Ilhas,1000,10); // 100
    coloca_ilha(Ilhas,1000,20); // 50
    coloca_ilha(Ilhas,4000,30); // 133
    coloca_ilha(Ilhas,3300,40); // 82.5
    coloca_ilha(Ilhas,500,4);   // 125

    CHECK(Ilhas.size() == 5);
    CHECK(Ilhas[0].custo == 1000);
    CHECK(Ilhas[1].custo == 1000);
    CHECK(Ilhas[2].custo == 4000);
    CHECK(Ilhas[3].custo == 3300);
    CHECK(Ilhas[4].custo == 500);

    mergesort(Ilhas, 0, 4);

    CHECK(Ilhas.size() == 5);
    CHECK(Ilhas[0].custo == 1000);
    CHECK(Ilhas[1].custo == 3300);
    CHECK(Ilhas[2].custo == 1000);
    CHECK(Ilhas[3].custo == 500);
    CHECK(Ilhas[4].custo == 4000);
}

TEST_CASE("Mergesort: vetor em ordem decrescente"){
    std::vector<ilha> Ilhas;
    coloca_ilha(Ilhas,4000,30); // 133
    coloca_ilha(Ilhas,500,4);   // 125
    coloca_ilha(Ilhas,1000,10); // 100
    coloca_ilha(Ilhas,3300,40); // 82.5
    coloca_ilha(Ilhas,1000,20); // 50

    CHECK(Ilhas.size() == 5);
    CHECK(Ilhas[0].custo == 4000);
    CHECK(Ilhas[1].custo == 500);
    CHECK(Ilhas[2].custo == 1000);
    CHECK(Ilhas[3].custo == 3300);
    CHECK(Ilhas[4].custo == 1000);

    mergesort(Ilhas, 0, 4);

    CHECK(Ilhas.size() == 5);
    CHECK(Ilhas[0].custo == 1000);
    CHECK(Ilhas[1].custo == 3300);
    CHECK(Ilhas[2].custo == 1000);
    CHECK(Ilhas[3].custo == 500);
    CHECK(Ilhas[4].custo == 4000);
}

TEST_CASE("Mergesort: vetor em ordem crescente"){
    std::vector<ilha> Ilhas;
    
    coloca_ilha(Ilhas,1000,20); // 50
    coloca_ilha(Ilhas,3300,40); // 82.5
    coloca_ilha(Ilhas,1000,10); // 100
    coloca_ilha(Ilhas,500,4);   // 125
    coloca_ilha(Ilhas,4000,30); // 133

    CHECK(Ilhas.size() == 5);
    CHECK(Ilhas[0].custo == 1000);
    CHECK(Ilhas[1].custo == 3300);
    CHECK(Ilhas[2].custo == 1000);
    CHECK(Ilhas[3].custo == 500);
    CHECK(Ilhas[4].custo == 4000);

    mergesort(Ilhas, 0, 4);

    CHECK(Ilhas.size() == 5);
    CHECK(Ilhas[0].custo == 1000);
    CHECK(Ilhas[1].custo == 3300);
    CHECK(Ilhas[2].custo == 1000);
    CHECK(Ilhas[3].custo == 500);
    CHECK(Ilhas[4].custo == 4000);
}

