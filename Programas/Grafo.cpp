#include "Grafo.h"
#include <fstream>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>

using std::set_difference;
using std::insert_iterator;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::ios;
using std::set;
// NULL
//typename vector< vector<Aresta_Arco>  >::iterator it;
//typename vector<Aresta_Arco>::iterator jit;

Grafo::Grafo(){

    cout << "Criou grafo simples sem nada" << endl;
}

Grafo:: Grafo (string nomeArq){
    ifstream file;
    string linha;
    int NV;
    int NA;
    vector<Vertices> vs;
    vector<Aresta_Arco> as;

    file.open(nomeArq.c_str(),ios::in);

    file >> NV;
    file >> NA;

   pai = new int [NV];
   ranking = new int [NV];
   for(int i=0;i< NV;i++){
        pai[i] = i;
        ranking[i]=0;
        Vertices v;
        int val;
 //       int custo;
        file >> val;
//        file >> custo;
        v.setValor(val);
//        v.setCusto(custo);
        vs.push_back(v);
   }
   lvertices = vs;
   int somaCustoArestas=0;
   for(int i=0;i< NA;i++){
        Aresta_Arco a;
        int v1,v2,custoAresta;
        file >> v1;
        file >> v2;
        file >> custoAresta;
        for(int j=0;j< NV; j++){
            Vertices v = vs[j];

            if(v.getValor() == v1){
                a.setI(v);
            }
            if(v.getValor() == v2){
                a.setJ(v);
            }
        }
        a.setCusto(custoAresta);
        somaCustoArestas = somaCustoArestas + a.getCusto();
        as.push_back(a);
   }
    file.close();
    std::cout<< "Arquivo lido" << std::endl;
    this->numV=vs.size();
    std::cout<< "Criando Grafo" << std::endl;

    /*int op;
    cout <<"Digite o numero do tipo de estrutura de grafo deseja"<< endl;
    cout <<"1-Lista de adjacencia para um grafo nao direcionado "<< endl;
    cout <<"2-Listas de adjacencias(In,Out) para um grafo direcionado"<< endl;
    cout <<"3-Matrix de adjacencia"<< endl;
    cout <<"4-Sair do Laço"<< endl;
    cin>>op;
    cout <<"Opcao escolhida: "<< op<< endl;
    */
     //if(op==1){

        //cout << "Criando lista de adjacencia num grafo nao direcionado" <<endl;
        vector<vector<Aresta_Arco> > aux(vs.size());
        unsigned int totalAr=as.size();
        for(unsigned int i=0 ; i<totalAr ;i++){
            if(as[i].getJ().getId() == as[i].getI().getId()){
                aux[as[i].getI().getId()].push_back(as[i]);
            }else{
                //Aresta_Arco a2(as[i].getJ(),as[i].getI(),as[i].getCusto());
                //aux[a2.getI().getId()].push_back(a2);
                aux[as[i].getI().getId()].push_back(as[i]);

            }

        }
        this->lAdj=aux;
        //mostrarListaDeAdjacenciaNaoDirecionado();

    //}else if(op==2){
       // cout << "Criando listas de adjacencias para um grafo direcionado" <<endl;
        vector<vector<Aresta_Arco> > auxLin(vs.size());
        vector<vector<Aresta_Arco> > auxLout(vs.size());
        //unsigned int totalAr=as.size();

        for(unsigned int i=0 ; i<totalAr ;i++){

            if(as[i].getJ().getId() == as[i].getI().getId()){
                auxLout[as[i].getI().getId()].push_back(as[i]);
            }else{
                Aresta_Arco a2(as[i].getJ(),as[i].getI(),as[i].getCusto());
                auxLin[a2.getI().getId()].push_back(a2);
                auxLout[as[i].getI().getId()].push_back(as[i]);

            }

        }
        this->lin=auxLin;
        this->lout=auxLout;
        //mostrarListaDeAdjacenciaDirecionado();

    //}else{
       // cout << "Criando matrix de adjacencia para um grafo direcionado" <<endl;

        matrix= new int*[vs.size()]; // bool --> sem custo
        infinito=somaCustoArestas*10;
        for(unsigned  int i=0;i<vs.size();i++){
             matrix[i]=new int[vs.size()];
             for(unsigned int j=0;j<vs.size();j++){
                matrix[i][j]=somaCustoArestas*10;
            }
        }
        for(unsigned int i=0;i<as.size();i++){
            matrix[as[i].getI().getId()][as[i].getJ().getId()] = as[i].getCusto();
        }

        //mostrarMatrixAdjacencia();

    //}

}
void Grafo::mostrarMatrixAdjacencia(){

    cout << "Matrix de adjacencia" <<endl;
    for(int i=0;i<numV;i++){
         for(int j=0;j<numV;j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

}
vector<Aresta_Arco> Grafo::GerarVectorAresta(){

    typename vector< vector<Aresta_Arco>  >::iterator it;
    typename vector<Aresta_Arco>::iterator jit;

    vector<Aresta_Arco>  verificar;

    vector< vector<Aresta_Arco>  >lAdj = getLadj();
    int c=0;
    for(it = lAdj.begin(); it != lAdj.end() ; it++){
        c++;
        for(jit=it->begin();jit != it->end();jit++){
                    verificar.push_back(*jit);

        }
        if(c==2){
            break;
        }
    }
    return verificar;
}
void Grafo::mostrarListaDeAdjacenciaNaoDirecionado(){


    typename vector< vector<Aresta_Arco>  >::iterator it;
    typename vector<Aresta_Arco>::iterator jit;
    if(!lAdj.empty()){
        cout <<"Todas as arestas da lista de adjacencia "<< endl;
        int cont=0;
        for(it = lAdj.begin(); it != lAdj.end() ; it++){
            cout <<"ID: "<< cont<< endl;
            if(it->empty()){
                cout << "{ vazio }";
            }else{
                for(jit=it->begin();jit != it->end();jit++){
                    cout << (*jit).getI().getValor() << "->" << (*jit).getJ().getValor()  << "; ";

                }
            }
            cont++;
            cout << endl;
        }
    }else{
        cout <<"Lista de adjancencia vazia."<< endl;
    }
}

void Grafo::mostrarListaDeAdjacenciaDirecionado(){


    typename vector< vector<Aresta_Arco>  >::iterator it;
    typename vector<Aresta_Arco>::iterator jit;
    if(!lin.empty() && !lout.empty()){
        int cont=0;
        cout <<"Lista de adjancencia de entrada(IN) "<< endl;
        for(it = lin.begin(); it != lin.end() ; it++){
            cout <<"ID: "<< cont<< endl;
            if(it->empty()){
                cout << "{ vazio }";
            }else{
                for(jit=it->begin();jit != it->end();jit++){
                    cout << (*jit).getI().getValor() << "->" << (*jit).getJ().getValor()  << "; ";

                }
            }
            cont++;
            cout << endl;
        }
        cont=0;
        cout <<"Lista de adjancencia de saida(OUT) "<< endl;
        for(it = lout.begin(); it != lout.end() ; it++){
            cout <<"ID: "<< cont<< endl;
            if(it->empty()){
                cout << "{ vazio }";
            }else{
                for(jit=it->begin();jit != it->end();jit++){
                    cout << (*jit).getI().getValor() << "->" << (*jit).getJ().getValor()  << "; ";

                }
            }
            cont++;
            cout << endl;
        }

    }else{
        cout <<"Lista de adjancencia (IN e OUT) vazia."<< endl;
    }

}



vector< vector<Aresta_Arco>  > Grafo::getLadj(){
    return lAdj;

}
vector< vector<Aresta_Arco>  > Grafo::getLin(){
    return lin;

}
vector< vector<Aresta_Arco>  > Grafo::getLout(){
    return lout;

}
vector< Vertices  > Grafo::getLvertices(){
    return lvertices;

}
int** Grafo::getMatrix(){
    return matrix;

}
int Grafo::getNumV(){
    return numV;
}
int Grafo::getInfinito(){
    return infinito;
}
vector<bool> Grafo::CriarVetorVisitaVazio(){
    vector<bool> visited(numV,false);
    typename vector<bool>::iterator it;
    return visited;
}

bool Grafo::isTodosCustosPositivo(){

    for(int i=0;i<numV;i++){
         for(int j=0;j<numV;j++){
            if(matrix[i][j] < 0 ){
                return 0;
            }
        }
    }
    return 1;
}
int Grafo::gerarRand(){
    srand (time(NULL));
    return rand()% getNumV();
}
int** Grafo::getMatrixDiagonalZero(){
    int** novaMatrix = matrix;
    for(int i=0;i<numV;i++){
         for(int j=0;j<numV;j++){
            if(i==j){
                novaMatrix[i][i]=0;
            }
        }

    }

    for(int i=0;i<numV;i++){
         for(int j=0;j<numV;j++){
             cout << novaMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return novaMatrix;
}
int Grafo::recuperarValorDoIdVertice(int id){
    vector<Vertices> listaVertices = lvertices;
    return listaVertices[id].getValor();
}
void Grafo::adicionarNovoNoConectadoTodos(){
    Vertices q;
    numV = numV+1;

    lvertices.push_back(q);

    typename vector< vector<Aresta_Arco>  >::iterator it;
    typename vector<Aresta_Arco>::iterator jit;
    vector<Aresta_Arco> nas;
    //int cont=0;
    for(it = lAdj.begin(); it != lAdj.end() ; it++){

        for(jit=it->begin();jit != it->end();jit++){
            //cout << (*jit).getI().getValor() << "->" << (*jit).getJ().getValor()  << "; ";

            //jit = it->begin();
            //Aresta_Arco ar((*jit).getI(),q,0);
            Aresta_Arco ar2(q,(*jit).getI(),0);
            //it->push_back(ar);
            nas.push_back(ar2);
            //cout << "PArte 1" << endl;
            break;
        }

    }
    lAdj.push_back(nas);

    //Mudar matrix e mudar lin e lout
    //mostrarListaDeAdjacenciaNaoDirecionado();
}
void Grafo::removerNovoNoConectadoTodos(){
    numV = numV-1;
    lvertices.pop_back();
    lAdj.pop_back();
/*
    typename vector< vector<Aresta_Arco>  >::iterator it;
    typename vector<Aresta_Arco>::iterator jit;
    for(it = lAdj.begin(); it != lAdj.end() ; it++){

        if(it->begin() != it->end()){

            //it->pop_back();

        }

    }
    lAdj.pop_back();*/
    //mostrarListaDeAdjacenciaNaoDirecionado();
}


int Grafo::fatorial(int n){
    int fat;
    for(fat = 1; n > 1; n = n - 1)
    {
          fat = fat * n;
    }
    return fat;
}

double Grafo::combinacao(int n, int p){

    int fatN = fatorial(n);

    int fatP = fatorial(p);
    int fatNP = fatorial(n-p);
    return (fatN / fatP * fatNP);
}

double Grafo::getDensidade(){

    int totalArestas = lAdj.size();
    cout <<"total arestas "<<totalArestas <<endl;
    return totalArestas/(combinacao(numV,2));
}
bool Grafo::isDenso(){

    if(getDensidade() > 0.7){
        return 1;
    }else{
        return 0;
    }
}
void Grafo::mostrarCustosDaLista(){
    typename vector< vector<Aresta_Arco>  >::iterator it;
    typename vector<Aresta_Arco>::iterator jit;
    int cont=0;
    for(it = lAdj.begin(); it != lAdj.end() ; it++){
            cout <<"ID do vertice: "<< cont << endl;
            for(jit=it->begin();jit != it->end();jit++){
                    Aresta_Arco ar = *jit;
                    cout << ar.getCusto() << " ";

            }
            cout << endl;
            cont++;
    }
}

void Grafo::setLadj(vector< vector<Aresta_Arco>  > s){
    lAdj=s;
}
//BFS
void Grafo::InterfaceBuscaLargura(int n){

    vector<bool> visitados = CriarVetorVisitaVazio();
    vector< vector<Aresta_Arco> > adj= getLadj();
    vector<int> resultado;
    //double ** matrix = g.getMatrix();
    queue<int> fila;
    //int inicio=gerarRand();
    int inicio=n;
    cout <<"No inicial : "  << inicio << endl;
    while(visitados[inicio]==false){

        fila.push(inicio);
        while(!fila.empty()){
            int s=fila.front();
            fila.pop();
            if(!visitados[s]){
                //cout << s << " ";
                resultado.push_back(recuperarValorDoIdVertice(s));
                visitados[s]=true;
            }
            for(vector<Aresta_Arco>::iterator it = adj[s].begin();it !=adj[s].end();it++ ){
                int i =  (*it).getJ().getId();
                if(!visitados[i]){

                    fila.push(i);
                }
            }


        }
        for(int i=0;i< getNumV();i++){
            if(visitados[i]==false){
                inicio=i;
                break;
            }

        }

    }
    //cout << endl;
    for(int i=0; i< resultado.size();i++){
        if(i == resultado.size()-1){
           cout << resultado[i] <<endl;
         }
         else{
            cout << resultado[i] << ",";

         }
    }

}
//DFS
void Grafo::InterfaceBuscaProfundidade(int n){

     vector<bool> visitados = CriarVetorVisitaVazio();
    vector< vector<Aresta_Arco> > adj= getLadj();
    vector<int> resultado;
    //double ** matrix = g.getMatrix();
    stack<int> pilha;
    //int inicio=gerarRand();
    int inicio=n;
    cout <<"No inicial : "  << inicio << endl;
    while(visitados[inicio]==false){

        pilha.push(inicio);
        while(!pilha.empty()){
            int s=pilha.top();
            pilha.pop();
            if(!visitados[s]){
                //cout << s << " ";
                resultado.push_back(recuperarValorDoIdVertice(s));
                visitados[s]=true;
            }
            for(vector<Aresta_Arco>::iterator it = adj[s].begin();it !=adj[s].end();it++ ){
                int i =  (*it).getJ().getId();
                if(!visitados[i]){

                    pilha.push(i);
                }
            }


        }
        for(int i=0;i< getNumV();i++){
            if(visitados[i]==false){
                inicio=i;
                break;
            }

        }

    }
    //cout << endl;
    for(int i=0; i< resultado.size();i++){
        if(i == resultado.size()-1){
           cout << resultado[i] <<endl;
         }
         else{
            cout << resultado[i] << ",";

         }
    }

}
void Grafo::InterfaceDIJK(){
    vector<bool> visitados = CriarVetorVisitaVazio();
    vector<int> dist;
    vector<int> prev;
    for(int i=0;i< getNumV();i++){
        dist.push_back(getInfinito());
        prev.push_back(NULL);
    }
    vector< vector<Aresta_Arco> > adj= getLadj();
    //double ** matrix = g.getMatrix();
    vector<int> h;
    make_heap(h.begin(),h.end());
    vector<int> resultado;

    int inicio=gerarRand();
     //inicio=0;
    cout <<"No inicial de ID : "  << inicio << endl;
    //while(visitados[inicio]==false){
        dist[inicio]=0;
        h.push_back(inicio);
        push_heap(h.begin(), h.end());
        //int cont =0;
        while(!h.empty()){
            sort_heap(h.begin(),h.end());
            int x=h.front();
            int u=x;
            make_heap(h.begin(),h.end());
            h.pop_back();

            if(!visitados[u]){

                resultado.push_back(recuperarValorDoIdVertice(u));
                visitados[u]=true;
            }
            for(vector<Aresta_Arco>::iterator it = adj[u].begin();it !=adj[u].end();it++ ){
                int custoArco = (*it).getCusto();
                int vert =  (*it).getJ().getId();
                if(dist[vert] > dist[u]+ custoArco){
                    dist[vert] = dist[u]+ custoArco;
                    prev[vert] = u;
                }

                if(!visitados[vert]){
                    push_heap(h.begin(), h.end());
                    h.push_back(vert);


                }

            }


        }
        cout <<"Caminho minimo"<<endl;
        for(int i=0;i< resultado.size();i++){

             if(i == resultado.size()-1){
               cout << resultado[i] <<endl;
             }
             else{
                cout << resultado[i] << "->";

             }
        }
        cout <<"Distancia minima"<<endl;
        for(int i=0;i< dist.size();i++){

             cout << dist[i] <<  " ";
        }

    //}

}
void Grafo::InterfaceFlyod(){

    cout <<"Matrix antes do Floyd"<<endl;
    int** dist = getMatrixDiagonalZero();

    for(int k=0;k< getNumV();k++){
        for(int i=0;i< getNumV();i++){
            for(int j=0;j< getNumV();j++){
                if(dist[i][j] > dist[i][k]+ dist[k][j]){
                    dist[i][j] = dist[i][k]+ dist[k][j];
                }
            }
        }
    }
    cout <<endl;
    cout <<"Matrix depois do Floyd"<<endl;
    for(int i=0;i< getNumV();i++){
        for(int j=0;j< getNumV();j++){
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}
void Grafo::InterfaceBellman(){

    vector<int> dist;
    for(int i=0;i< getNumV();i++){
        dist.push_back(getInfinito());

    }
    typename vector< vector<Aresta_Arco>  >::iterator it;
    typename vector<Aresta_Arco>::iterator jit;

    int inicio = gerarRand();
    //inicio=0;
    cout <<"No de inicio "<< inicio << endl;
    dist[inicio]=0;
    vector<vector <Aresta_Arco> > adj = getLadj();
    for(int i=0; i< getNumV()-1;i++){
        for(it = adj.begin(); it != adj.end() ; it++){
            for(jit=it->begin();jit != it->end();jit++){
                    Aresta_Arco ar = *jit;
                    if(dist[ar.getJ().getId()] < dist[ar.getI().getId()] + ar.getCusto())
                    {
                        dist[ar.getJ().getId()] = dist[ar.getJ().getId()] ;

                    }else{
                        dist[ar.getJ().getId()] = dist[ar.getI().getId()] + ar.getCusto();
                    }
                    //cout << (*jit).getI().getValor() << "->" << (*jit).getJ().getValor()  << "; ";

            }
        }

    }
    for(int i=0;i< getNumV();i++){

         cout << dist[i] <<  " ";
    }


}
vector<Aresta_Arco> Grafo::ordenarListaPorPeso(){
    vector<bool> visitados = CriarVetorVisitaVazio();

    typename vector< vector<Aresta_Arco>  >::iterator it;
    typename vector<Aresta_Arco>::iterator jit;

    vector< vector<Aresta_Arco>  > lista = getLadj();
    vector<Aresta_Arco> ordenado;
    int pos=0;
    for(it = lista.begin(); it != lista.end() ; it++){

        for(jit=it->begin();jit != it->end();jit++){
                int IDj =  (*jit).getJ().getId();
                if(!visitados[IDj]){
                    ordenado.push_back(*jit);
               }

        }
        visitados[pos]=true;
        pos++;
    }
    sort(ordenado.begin(),ordenado.end());
    cout << "Ordenando por peso"<< endl;

    /*for(jit = ordenado.begin(); jit != ordenado.end() ; jit++){

                cout << (*jit).getI().getValor() << "->" << (*jit).getJ().getValor()  << " de custo " << (*jit).getCusto() << endl;

    }*/
    return ordenado;
}

vector<int> Grafo::CriarVetorCustoInfinito(){

     vector<int> cost;
    for(int i=0;i< getNumV();i++){
        cost.push_back(getInfinito());
    }
    return cost;
}
vector<int> Grafo::CriarVetorPrevNull(){
    vector<int> prev ;
    for(int i=0;i< getNumV();i++){
        prev.push_back(NULL);
    }
    return prev;
}

//contador
int Grafo::meu_find(int X){
    int paiX = get_paiPorID(X);
    if(X!=paiX){
        paiX=meu_find(paiX);
        set_paiPorID(X,paiX);
    }
    return paiX;
}
void Grafo::meu_union(int x, int y){
    int rx= meu_find(x);
    int ry= meu_find(y);
    //cout <<"rx = "<< rx<<endl;
    //cout <<"ry = "<< ry<<endl;
    if(rx == ry){
        return;
    }
    if(get_rankPorID(rx) > get_rankPorID(ry)){
        set_paiPorID(rx,ry);
    }else{
        set_paiPorID(ry,rx);
        if(get_rankPorID(rx) == get_rankPorID(ry)){
                int i=  get_rankPorID(ry) + 1;
                set_rankPorID(ry,i);

        }
    }
}

void Grafo::KrusKal_AGM(){

    typename vector<Aresta_Arco>::iterator it;
    vector<Aresta_Arco> resultado;
    vector<Aresta_Arco> ordenado=ordenarListaPorPeso();
    int x=0;
    for(it=ordenado.begin();it!= ordenado.end();it++){
        x++;
        Vertices u=it->getI();
        Vertices v=it->getJ();
        //cout <<"u-v : " << u.getId()<< "-"<< v.getId() <<endl;
        if(meu_find(u.getId()) != meu_find(v.getId())){
            resultado.push_back(*it);
            meu_union(u.getId(),v.getId());
        }

    }
    int peso=0;
    cout << "Arvore de caminho minimo" <<endl;
    for(it=resultado.begin();it!= resultado.end(); ++it){
        /*if(it == resultado.end() -1){
            cout << it->getI().getValor() <<"-"<< it->getJ().getValor() << endl;
        }else{
            cout << it->getI().getValor() <<"-"<< it->getJ().getValor() << ",";
        }*/
        peso+=it->getCusto();
    }
    //MostrarVectorAresta(resultado);
    cout <<"Peso da arvore " << peso << endl;

}
void Grafo::Prim_AGM(int no){
    vector<bool> visitados = CriarVetorVisitaVazio();
    vector<int> cost = CriarVetorCustoInfinito();
    vector<int> prev = CriarVetorPrevNull();
    vector< vector<Aresta_Arco> > adj= getLadj();
    //double ** matrix = g.getMatrix();
    vector<int> h;
    make_heap(h.begin(),h.end());
    vector<Aresta_Arco> resultado;
    //int inicio=gerarRand();
    int inicio=no;
    cout <<"No inicial de ID : "  << inicio << endl;
    //while(visitados[inicio]==false){
        cost[inicio]=0;
        h.push_back(inicio);
        push_heap(h.begin(), h.end());
        //int cont =0;
        while(!h.empty()){
            sort_heap(h.begin(),h.end());
            int x=h.front();
            int v=x;
            make_heap(h.begin(),h.end());
            h.pop_back();

            if(!visitados[v]){
                visitados[v]=true;
                //cout <<"Valor de v : "<< g.recuperarValorDoIdVertice(v) <<endl;

            }

            for(vector<Aresta_Arco>::iterator it = adj[v].begin();it !=adj[v].end();it++ ){
                int custoArco = (*it).getCusto();
                int j =  (*it).getJ().getId();
                if(!visitados[j]){
                    if(cost[j] > custoArco){
                        resultado.push_back((*it));
                        cost[j] = custoArco;
                        prev[j] = v;
                    }
                    push_heap(h.begin(), h.end());
                    h.push_back(j);

                }

            }

        }
        cout <<"Arvore Geradora Minima"<<endl;

        /*for(int i=0;i< prev.size();i++){
            if(i == prev.size()-1){
                cout << prev[i]+1 <<"-"<<i+1<<endl;
             }else{
                if(prev[i]+1 != i+1){
                    cout << prev[i]+1 <<"-"<<i+1<<",";
                }
             }


        }*/
        for(int i=0;i< resultado.size();i++){

             if(i == resultado.size()-1){
                cout << resultado[i].getI().getValor() << "->" << resultado[i].getJ().getValor()<<endl;
             }else{
                cout << resultado[i].getI().getValor() << "->" << resultado[i].getJ().getValor() << ",";

             }
        }
        //MostrarVectorAresta(resultado);
        int peso=0;
        for(int i=0;i< cost.size();i++){
            //cout <<"cost[i] = " <<cost[i] << endl;
            if(cost[i] == getInfinito()){
                peso=peso+0;
            }else{
                peso=peso+cost[i];
            }
        }
        cout <<"Peso da arvore geradora minima: "<< peso <<endl;


    //}

}

void Grafo::MostrarSetArestaComCusto(set<Aresta_Arco> x){

    typename set<Aresta_Arco>::iterator it;
    if(!x.empty()){
        for(it= x.begin();it!= x.end();it++){
            cout << (*it).getI().getValor()<< "->" << (*it).getJ().getValor() <<" Custo: "<< (*it).getCusto() << endl;

        }
    }else{
        cout <<"Conjunto esta vazio "<< endl;
    }

}
void Grafo::MostrarSetArestaSemCusto(set<Aresta_Arco> x){
     typename set<Aresta_Arco>::iterator it;
    if(!x.empty()){
        for(it= x.begin();it!= x.end();it++){
            cout << (*it).getI().getValor()<< "->" << (*it).getJ().getValor() << endl;
        }
    }else{
        cout <<"Conjunto esta vazio "<< endl;
    }
}
void Grafo::MostrarVectorAresta(vector<Aresta_Arco> x){
    typename vector<Aresta_Arco>::iterator it;

    if(!x.empty()){
        for(it= x.begin();it!= x.end();it++){
            cout << (*it).getI().getValor()<< "->" << (*it).getJ().getValor() <<" Custo: "<< (*it).getCusto() << endl;

        }
    }else{
        cout <<"Vetor esta vazio "<< endl;
    }
}

//N funciona
void Grafo::InterfaceCaminhoAlterante(){
    typename vector< vector<Aresta_Arco>  >::iterator it;
    typename vector<Aresta_Arco>::iterator jit;

    set<Aresta_Arco> p;
    //int valorMaximo=0;
    vector<int> s;
    for(int i=0;i< getNumV();i++){
        s.push_back(0);
    }
    vector< vector<Aresta_Arco> > adj= getLadj();
    for(it = adj.begin(); it != adj.end() ; it++){
        for(jit=it->begin();jit != it->end();jit++){
                int u=(*jit).getI().getId();
                int v=(*jit).getJ().getId();
                if((s[u]==0) && (s[v]==0)){
                    s[u]=1;
                    s[v]=1;
                    p.insert(*jit);
                }
        }
    }
    set<Aresta_Arco> C = CaminhoAlternante(p,s);
    MostrarSetArestaSemCusto(C);

}
//N funciona
void Grafo::EmparelhamentoMax(){
    typename vector< vector<Aresta_Arco>  >::iterator it;
    typename vector<Aresta_Arco>::iterator jit;

    set<Aresta_Arco> emparelhamentoMaximo;
    //int valorMaximo=0;
    vector<int> s;
    for(int i=0;i< getNumV();i++){
        s.push_back(0);
    }
    vector< vector<Aresta_Arco> > adj= getLadj();
    for(it = adj.begin(); it != adj.end() ; it++){
        for(jit=it->begin();jit != it->end();jit++){
                int u=(*jit).getI().getId();
                int v=(*jit).getJ().getId();
                if((s[u]==0) && (s[v]==0)){
                    s[u]=1;
                    s[v]=1;
                    emparelhamentoMaximo.insert(*jit);
                }
        }
    }

    //set<Aresta_Arco> C = CaminhoAlternante(emparelhamentoMaximo,s);
    /*while(C.size()>=3){
        //set_difference
        //Aux = P - C
        // P= aux U [C - C inter P]
        for(int i=0;i< s.size();i++){
            s[i]=0;
        }
        for(it = adj.begin(); it != adj.end() ; it++){
            for(jit=it->begin();jit != it->end();jit++){
                    int u=(*jit).getI().getId();
                    int v=(*jit).getJ().getId();
                    s[u]=1;
                    s[v]=1;
            }
        }

        C= CaminhoAlternante(emparelhamentoMaximo,s);
    }
    */


}

int Grafo::NSS(vector<int> s){
    int soma=0;
    for(int i=0;i<s.size();i++){
        soma+=s[i];
    }
    //cout <<"Soma = " << soma << endl;
    //cout <<"Resultato NSS = " << getNumV() - soma << endl;
    //return getNumV() - soma;
    return soma;
}

//N sei
set<Aresta_Arco> Grafo::CaminhoAlternante(set<Aresta_Arco> p,vector<int> s){
    set<Aresta_Arco> C;

    typename vector< vector<Aresta_Arco>  >::iterator it;
    typename vector<Aresta_Arco>::iterator jit;

    //cout <<"Valor de s "<< endl;
    for(vector<int>::iterator sit=s.begin();sit!= s.end();sit++){
        //cout << *sit << " , ";
    }
    cout <<endl;
    if(NSS(s)<2){
        cout <<" Saiu em 1 "<< endl;
        return C;
    }
    //ID de Vertice
    queue<int> NS;
    for(int i=0;i<s.size();i++){
        if(s[i]==0){
            NS.push(i);

        }
    }
    if(NS.empty()){
       cout <<"NS VAZIO"<<endl;
    }
    queue<int> copia=NS;
    //cout << "Valores de NS:" << endl;
    for(int i=0;i< copia.size();i++){
        //cout << copia.front() << endl;
        copia.pop();
    }
    while(!NS.empty()){

        int n = NS.front();
        NS.pop();
        C = InterfaceDFSmodificado(n,s,p);
        //MostrarSetArestaSemCusto(C);
        if(C.size()>=3){
            //cout <<" Saiu em 2 "<< endl;
            return C;
        }
    }
    //cout <<" Saiu em 3 "<< endl;
    return C;
}

// N sei
//Busca em profundidade alterado para CaminhoAlternante
set<Aresta_Arco> Grafo::InterfaceDFSmodificado(int n,vector<int> s,set<Aresta_Arco> p){

    vector<bool> visitados = CriarVetorVisitaVazio();
    vector< vector<Aresta_Arco> > adj= getLadj();
    set<Aresta_Arco> resultado;
    stack<Aresta_Arco> pilha;
    int inicio=n;
    cout <<"No inicial : "  << inicio << endl;
    int ea=0;
    while(visitados[inicio]==false){
        vector<Aresta_Arco>::iterator Nit = adj[inicio].begin();
        pilha.push((*Nit));
        //pilha.push(inicio);
        while(!pilha.empty()){
            Aresta_Arco e = pilha.top();
            int idJ=e.getJ().getId();
            pilha.pop();
            if(!visitados[idJ]){
                if((p.find(e)!= p.end()) && (ea==0)){
                    ea=1;
                    resultado.insert(e);
                    visitados[idJ]=true;
                }else if((p.find(e)== p.end()) && (ea==1)){
                    ea=0;
                    resultado.insert(e);
                    visitados[idJ]=true;
                }else{
                    visitados[idJ]=true;
                }
            }
            for(vector<Aresta_Arco>::iterator it = adj[idJ].begin();it !=adj[idJ].end();it++ ){
                int i =  (*it).getJ().getId();
                if(!visitados[i]){
                    pilha.push(*it);
                }
            }

        }
        for(int i=0;i< getNumV();i++){
            if(visitados[i]==false){
                inicio=i;
                break;
            }
        }
    }
    return resultado;
}

