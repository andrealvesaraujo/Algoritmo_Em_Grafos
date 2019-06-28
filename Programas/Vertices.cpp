#include "Vertices.h"
#include <iostream>

int Vertices::VcontID = 0;

Vertices::Vertices(){
    this->id=VcontID++;
    this->valor=0;

}
/*
Vertices::Vertices(int v,int c){

    this->id=VcontID++;
    this->valor=v;

}
*/
Vertices::Vertices(int v){

    this->id=VcontID++;
    this->valor=v;


}
int Vertices::getId() const{
   return this->id;
}
void Vertices::setValor(int v){
    this->valor=v;
}
int Vertices::getValor() const{
   return this->valor;
}
void Vertices:: mostrarInf(){
    std::cout << "VERTICE DE ID: " << this->id << " Valor: " << this->valor<< std::endl;
}


