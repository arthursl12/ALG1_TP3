#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <set>
#include <string>

bool str_tok(std::string& str, std::string delimiter, std::string& token);

class Grafo{
public:
    Grafo(int N);
    void inicializa_grafo(int N, int I, int J);
    void imprime_grafo();
    void pre_colore(int N, std::ifstream& arq);

    int saturated_degree(int idx);
    bool is_colored(int idx);
    int max_sat_degree();

private:
    std::vector<std::set<int>> lista_adjacencias;
    std::vector<int> ColorMap;
};


#endif /* GRAFO_H */