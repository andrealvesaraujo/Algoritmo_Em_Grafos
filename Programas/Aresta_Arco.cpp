#include "Aresta_Arco.h"
#include <iostream>

int Aresta_Arco::AcontID = 0;

Aresta_Arco::Aresta_Arco(){

    this->id=AcontID++;
    this->i= Vertices();
    this->j= Vertices();
    this->custo=0;
}
Aresta_Arco::Aresta_Arco(Vertices i,Vertices j,int c){
        this->id=AcontID++;
        this->i=i;
        this->j=j;
        this->custo=c;
}
int Aresta_Arco::getId(){
    return this->id;
}
void Aresta_Arco::setI(Vertices i){
    this->i=i;

}
Vertices Aresta_Arco::getI() const{
    return this->i;
}
void Aresta_Arco::setJ(Vertices j){
    this->j=j;

}
Vertices Aresta_Arco::getJ() const{
    return this->j;
}
void Aresta_Arco::setCusto(int c){
    this->custo=c;
}
int Aresta_Arco::getCusto() const{
    return this->custo;
}

void Aresta_Arco:: mostrarInf(){
   std::cout << "ARESTA/ARCO ID: " << this->id << " i: " << this->i.getValor() << " j: " << this->j.getValor() <<  " Custo: " << this->custo<< std::endl;
}

bool Aresta_Arco::operator < (const Aresta_Arco& a) const
{
    return (custo < a.custo);
}
