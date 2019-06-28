#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "Vertices.h"
#include "Aresta_Arco.h"

#include <iostream>
#include<vector>
#include<string>

#include<stack>
#include<queue>
#include <set>
#include<algorithm>
#include<iterator>

//Random()
#include<stdlib.h>
#include<time.h>

using std::set;
using std::string;
using std::cout;
using std::endl;
using std::iterator;

using std::vector;
using std::stack;
using std::queue;

//inicio= rand()% g.getNumV();

//Classe Principal que possui os métodos usados em sala. Uns funcionão melhor que outros
class Grafo{

    private:
        int **matrix; // Matrix de Adjacência
        int numV;
        int infinito;
        vector< vector<Aresta_Arco>  > lAdj; // Lista de Adjacência num grafo não ordenado
        vector< vector<Aresta_Arco>  > lin;  // Lista de Adjacência num grafo ordenado(entrada)
        vector< vector<Aresta_Arco>  > lout; // Lista de Adjacência num grafo  ordenado(saida)
        vector< Vertices > lvertices; // Lista com o indice dos vertices
        int * pai; // Usado no Kruskal
        int * ranking; // Usado no Kruskal
    public:

        //Construtores a partir de um arquivo texto de entrada
        Grafo();
        Grafo(string);
        Grafo(int, vector<Aresta_Arco>);

        //Principais
        int ** getMatrix();
        int** getMatrixDiagonalZero();
        vector< vector<Aresta_Arco>  > getLadj();
        void setLadj(vector< vector<Aresta_Arco>  >);
        vector< vector<Aresta_Arco>  > getLin();
        vector< vector<Aresta_Arco>  > getLout();
        vector< Vertices  > getLvertices();
        int getNumV();
        int getInfinito();


        int get_paiPorID(int i){return pai[i];};
        int get_rankPorID(int i){return ranking[i];};
        void set_paiPorID(int i, int j){pai[i]=j;};
        void set_rankPorID(int i, int j){ranking[i]=j;};

        //Mostrar Grafo
        void mostrarListaDeAdjacenciaNaoDirecionado();
        void mostrarListaDeAdjacenciaDirecionado();
        void mostrarMatrixAdjacencia();
        void mostrarCustosDaLista();

        vector<Aresta_Arco> GerarVectorAresta();
        void MostrarSetArestaComCusto(set<Aresta_Arco>);
        void MostrarVectorAresta(vector<Aresta_Arco>);
        void MostrarSetArestaSemCusto(set<Aresta_Arco>);

        vector<bool> CriarVetorVisitaVazio();
        vector<int> CriarVetorPrevNull();
        vector<int> CriarVetorCustoInfinito();
        bool isTodosCustosPositivo();

        int gerarRand();
        void adicionarNovoNoConectadoTodos();
        void removerNovoNoConectadoTodos();
        int recuperarValorDoIdVertice(int);

        //Usado para verificar densidade
        int fatorial(int);
        double combinacao(int, int);
        double getDensidade();
        bool isDenso();

        vector<Aresta_Arco> ordenarListaPorPeso();

        //Algoritmos Falados em Sala( nem todos funcionam 100%)
        // Para P1
        void InterfaceBuscaLargura(int);
        void InterfaceBuscaProfundidade(int);
        void InterfaceDIJK();
        void InterfaceFlyod();
        void InterfaceBellman();
        //void InterfaceJonson(); --> Incompleto

         // Para P2
        void Prim_AGM(int);
        void KrusKal_AGM();
        int meu_find(int);
        void meu_union(int, int);
        void EmparelhamentoMax();
        void InterfaceCaminhoAlterante();
        set<Aresta_Arco> CaminhoAlternante(set<Aresta_Arco>,vector<int>);
        int NSS(vector<int>);

        set<Aresta_Arco> InterfaceDFSmodificado(int,vector<int>,set<Aresta_Arco>);//Extra

};

#endif
