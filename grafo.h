#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <set>
#include <string>

typedef std::vector<std::vector<int>> Tabuleiro;

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

    bool colore_asc(int idx);
    bool colore_desc(int idx);
    void remonta_tabuleiro(Tabuleiro& result);
    bool resolve_sudoku(Tabuleiro& result);


private:
    std::vector<std::set<int>> lista_adjacencias;
    std::vector<int> ColorMap;
    int n_coloridos;
    int N;
    int Vertices;
};


#endif /* GRAFO_H */