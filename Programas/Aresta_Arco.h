#ifndef ARESTA_ARCO_H_INCLUDED
#define ARESTA_ARCO_H_INCLUDED
#include "Vertices.h"
class Aresta_Arco{

    private:
        int id;
        Vertices i;
        Vertices j;
        int custo;
        static int AcontID;


    public:
        Aresta_Arco();
        Aresta_Arco(Vertices,Vertices ,int);
        int getId();
        void setI(Vertices);
        Vertices getI() const;
        void setJ(Vertices);
        Vertices getJ() const;
        void setCusto(int);
        int getCusto() const;
        void mostrarInf();
        bool operator < (const Aresta_Arco& a) const;

};

#endif
