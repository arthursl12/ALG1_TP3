#include "grafo.h"
#include <iostream>
#include <fstream>
#include <algorithm> //Para a diferença entre set's

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

/* O(N^2) */
Grafo::Grafo(int N){
    this->n_coloridos = 0;
    this->Vertices = N*N;
    this->N = N;
    for (int i = 0; i < N*N; i++){
        std::set<int> linha_grafo;
        lista_adjacencias.push_back(linha_grafo);
    }
    for (int i = 0; i < N*N; i++){
        ColorMap.push_back(0);
    }
}

/* O(N^4): Loop de N^2 fazendo N^2 a cada iteração */
/* Cria as arestas do grafo seguindo o princípio de que se duas posições no 
tabuleiro não puderem ter o mesmo número no Sudoku (mesma cor no grafo), esses
vértices são conectados por uma aresta. Um vértice deve estar conectado com 
todos os outros de sua linha e de sua coluna, além daqueles no seu quadrante */
void Grafo::inicializa_grafo(int N, int I, int J){
    int N2 = N*N;
    for (int i = 0; i < N2; i++){
        int quo = i / N;
        int r = i % N;

        /* Vértices na mesma linha e mesma coluna devem ser conectados */
        for (int k = 0; k < N2; k++){
            if (i == k) continue;
            int quo_k = (k / N);
            int r_k = (k % N);
            if (quo == quo_k){
                /* Mesma linha do tabuleiro */
                lista_adjacencias[i].insert(k);
            }else if (r == r_k){
                /* Mesma coluna do tabuleiro */
                lista_adjacencias[i].insert(k);
            }
        }

        int _I = N/I; /* Quadrantes por linha */
        int _J = N/J; /* Quadrantes por coluna */
        int quo_q_l = quo/_I;
        int quo_q_c = r/_J;

        /* Vértices no mesmo quadrante devem ser conectados */
        for (int k = 0; k < N2; k++){
            if (i == k) continue;
            int quo_k = (k / N);
            int r_k = (k % N);

            int quo_k_l = quo_k/_I;
            int quo_k_c = r_k/_J;

            if ((quo_k_l == quo_q_l) && (quo_k_c == quo_q_c)){
                /* Estão no mesmo quadrante */
                lista_adjacencias[i].insert(k);
            }
        }
    }
}

void Grafo::imprime_grafo(){
    auto it = lista_adjacencias.begin();
    int i = 0;
    while(it != lista_adjacencias.end()){
        auto it1 = (*it).begin();
        std::cout << i << "=> ";
        while(it1 != (*it).end()){
            std::cout << *it1 << " ";
            it1++;
        }
        std::cout << std::endl;
        it++;
        i++;
    }
}

/* O(N^2): passa por todo o tabuleiro uma vez */
/* Dado o tabuleiro de sudoku de entrada, colore as posições dadas */
/* Cores: 1 a 9; 0 é sem cor */
void Grafo::pre_colore(int N, std::ifstream& arq){
    int k = 0;
    for (int i = 0; i < N; i++){
        std::string Linha, aux;
        std::getline(arq,Linha);
        for (int j = 0; j < N; j++){
            str_tok(Linha," ",aux);
            int cell =  std::stoi(aux);
            if (cell == 0){
                k++;
                continue;
            }
            ColorMap[k] = cell;
            n_coloridos++;
            k++;
        }
    }
}

/* Linear na quantidade de vizinhos de 'idx' */
/* Retorna quantos vértices vizinhos do vértice de índice 'idx' já estão 
coloridos (numerados) */
int Grafo::saturated_degree(int idx){
    int grau = 0;
    auto it = lista_adjacencias[idx].begin();
    while (it != lista_adjacencias[idx].end()){
        /* O número do vértice é o índice dele */
        bool colorido = is_colored(*it);
        if (colorido) grau++;
        it++;
    }
    return grau;
}

/* O(N^3) = N*O(N^2) */
/* Retorna o índice do vértice (ainda não colorido) com maior grau de saturação no grafo */
int Grafo::max_sat_degree(){
    auto it = lista_adjacencias.begin();
    int i = 0;
    int max = -1;
    int idx_max = -1;

    while(it != lista_adjacencias.end()){
        if (is_colored(i)){
            /* Ignorar os já coloridos */
            it++;
            i++;
            continue;
        }

        int grau_i = saturated_degree(i);
        if (grau_i > max){
            idx_max = i;
            max = grau_i;
        }
        it++;
        i++;
    }
    return idx_max;
}

/* Colore o vértice de índice 'idx' com o menor número possível;
Se não for possível colori-lo com alguma das 9 cores (números), isto é, o programa
não conseguiu achar a solução com a estratégia gulosa ou o sudoku não tem solução,
retorna 'false'. Se foi possível, retorna 'true' */
bool Grafo::colore_asc(int idx){
    if (is_colored(idx)) return false;
    std::set<int> Todas_cores;
    for (int i = 0; i < N; i++){
        Todas_cores.insert(i+1);
    }
    std::set<int> Cores_vizinhos;

    auto it = lista_adjacencias[idx].begin();
    while(it != lista_adjacencias[idx].end()){
        int cor_vizinho = ColorMap[*it];
        if (cor_vizinho != 0){
            Cores_vizinhos.insert(cor_vizinho);
        }
        it++;
    }

    std::set<int> Cores_disponiveis;
    std::set_difference(Todas_cores.begin(), Todas_cores.end(), \
                        Cores_vizinhos.begin(), Cores_vizinhos.end(), \
                        std::inserter(Cores_disponiveis, Cores_disponiveis.end()));
    if (Cores_disponiveis.empty()){
        /* Não achou cor válida para ser o vértice seja colorido */
        return false;
    }
    int cor = *Cores_disponiveis.begin();
    ColorMap[idx] = cor;
    n_coloridos++;
    return true;
}

/* Colore o vértice de índice 'idx' com o maior número possível;
Se não for possível colori-lo com alguma das 9 cores (números), isto é, o programa
não conseguiu achar a solução com a estratégia gulosa ou o sudoku não tem solução,
retorna 'false'. Se foi possível, retorna 'true' */
bool Grafo::colore_desc(int idx){
    if (is_colored(idx)) return false;
    std::set<int> Todas_cores;
    for (int i = 0; i < N; i++){
        Todas_cores.insert(i+1);
    }
    std::set<int> Cores_vizinhos;

    auto it = lista_adjacencias[idx].begin();
    while(it != lista_adjacencias[idx].end()){
        int cor_vizinho = ColorMap[*it];
        if (cor_vizinho != 0){
            Cores_vizinhos.insert(cor_vizinho);
        }
        it++;
    }

    std::set<int> Cores_disponiveis;
    std::set_difference(Todas_cores.begin(), Todas_cores.end(), \
                        Cores_vizinhos.begin(), Cores_vizinhos.end(), \
                        std::inserter(Cores_disponiveis, Cores_disponiveis.end()));
    if (Cores_disponiveis.empty()){
        /* Não achou cor válida para ser o vértice seja colorido */
        return false;
    }
    int cor = *(Cores_disponiveis.rbegin());
    ColorMap[idx] = cor;
    n_coloridos++;
    return true;
}

/* Custo constante: acesso a vector */
/* Retorna se o vértice de índice 'idx' já foi colorido */
bool Grafo::is_colored(int idx){
    return (ColorMap[idx] != 0);
}

/* O(N^2) */
void Grafo::remonta_tabuleiro(Tabuleiro& result){
    int N2 = Vertices;

    for (int i = 0; i < N; i++){
        std::vector<int> linha;
        result.push_back(linha);
        for (int j = 0; j < N; j++){
            result[i].push_back(-1);
        }
    }

    for (int i = 0; i < N2; i++){
        int quo = i / N;
        int r = i % N;
        
        result[quo][r] = ColorMap[i];
    }
}

bool Grafo::resolve_sudoku(Tabuleiro& result){
    bool possivel = false;
    std::vector<int> Copia_ColorMap = ColorMap;
    int n_coloridos_inicial = n_coloridos;
    while(n_coloridos != Vertices){
        int idx = max_sat_degree();
        possivel = colore_asc(idx);
        if (possivel == false) break;
    }

    if (possivel == false){
        ColorMap = Copia_ColorMap;
        n_coloridos = n_coloridos_inicial;
        while(n_coloridos != Vertices){
            int idx = max_sat_degree();
            possivel = colore_desc(idx);
            if (possivel == false) break;
        }
    }

    remonta_tabuleiro(result);
    return possivel;
}

