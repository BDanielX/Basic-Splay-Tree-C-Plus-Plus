#ifndef ARBOL_H
#define ARBOL_H
#include <QCoreApplication>

class Nodo
{
public:
    Nodo(int);
    ~Nodo();

    Nodo *izquierda,*derecha;
    int numero;
};

class Arbol
{
    void getDot(FILE*,Nodo*);
public:
    Arbol();
    ~Arbol();

    void Insertar(int,Nodo**);
    void PasarARaiz(int,Nodo** nodo);
    void ControlDeMovimiento(int numero,Nodo** nodo);
    void Graficar();
    bool Buscar(int,Nodo*);
    bool Eliminar(int);
    int ObtenerMayorDeMenores(Nodo*);

    void Zig(Nodo**);
    void ZigZig(Nodo**);
    void ZigZag(Nodo**);
    void Zag(Nodo**);
    void ZagZag(Nodo**);
    void ZagZig(Nodo**);

    Nodo* raiz;
};

#endif // ARBOL_H
