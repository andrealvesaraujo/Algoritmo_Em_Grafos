#include "Vertices.h"
#include "Aresta_Arco.h"
#include "Grafo.h"

#include <string>
#include <iostream>
#include <cstddef>


#include <iterator>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include<set>

#include <stdlib.h>
#include <time.h>

using std::cout;
using std::endl;
using std::iterator;

using std::vector;
using std::stack;
using std::queue;
using std::set;




int main(){
    typename vector< vector<Aresta_Arco>  >::iterator it;
    typename vector<Aresta_Arco>::iterator jit;
    Grafo g("entrada.txt");

    vector<Aresta_Arco>  entrada;
    vector< vector<Aresta_Arco>  >lAdj = g.getLadj();
    int c=0;
    for(it = lAdj.begin(); it != lAdj.end() ; it++){
        c++;
        for(jit=it->begin();jit != it->end();jit++){
                    entrada.push_back(*jit);
        }
        if(c==2){
            break;
        }
    }

    bool passou = true;
    Aresta_Arco s(4,3,2);
    sort(entrada.begin(),entrada.end());

    cout <<"Entrada "<<endl;
    g.MostrarVectorAresta(entrada);

    vector<bool> x = g.CriarVetorVisitaVazio();

    vector<Aresta_Arco> ordenado=entrada;
    vector<Vertices> vS;
    for(jit = ordenado.begin();jit!= ordenado.end();jit++){
        if(((*jit).getI().getId())==0){
            x[(*jit).getJ().getId()]=true;
        }
        if((*jit).getJ().getId()==0){
            x[(*jit).getI().getId()]=true;
        }
    }
    for(int i=1;i< ordenado.size();i++){
        //cout << x[i] << endl;
        if(!x[i]){
            passou=false;
        }
    }
    if(passou){
        cout << "O caminho de entrada segue as restricoes" <<endl;
    }else{
        cout << "O caminho de entrada nao segue as restricoes" <<endl;
    }
    return 0;
}
