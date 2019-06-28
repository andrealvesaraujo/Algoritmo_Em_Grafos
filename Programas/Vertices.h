#ifndef VERTICES_H_INCLUDED
#define VERTICES_H_INCLUDED


class Vertices{

    private:
        int id;
        int valor;
        static int VcontID;

    public:
        Vertices();
        Vertices(int );
        int getId() const;
        void setValor(int);
        int getValor() const;
        void mostrarInf();

};

#endif
