#include "arbol.h"

Arbol::Arbol()
{//contructor
    this->raiz = NULL;
}

Arbol::~Arbol()
{
    //destructor
}

void Arbol::Insertar(int numero, Nodo** nodo)
{
    if(*nodo==NULL)
        *nodo = new Nodo(numero);
    else if((*nodo)->numero<numero)
        Insertar(numero,&(*nodo)->derecha);
    else if((*nodo)->numero>numero)
        Insertar(numero,&(*nodo)->izquierda);
}

void Arbol::PasarARaiz(int numero,Nodo** nodo)
{
    while((*nodo)->numero != numero){
        ControlDeMovimiento(numero,nodo);
    }
}

void Arbol::ControlDeMovimiento(int numero, Nodo **nodo)
{
    if((*nodo)->numero > numero)
    {
        if((*nodo)->izquierda->numero == numero)
            Zig(nodo);
        else if((*nodo)->izquierda->numero > numero && ((*nodo)->izquierda->izquierda->numero) == numero)
            ZigZig(nodo);
        else if((*nodo)->izquierda->numero < numero && ((*nodo)->izquierda->derecha->numero) == numero)
            ZigZag(nodo);
        else
            ControlDeMovimiento(numero,&(*nodo)->izquierda);
    }
    else if((*nodo)->numero < numero)
    {
        if((*nodo)->derecha->numero == numero)
            Zag(nodo);
        else if((*nodo)->derecha->numero > numero && ((*nodo)->derecha->izquierda->numero) == numero)
            ZagZig(nodo);
        else if((*nodo)->derecha->numero < numero && ((*nodo)->derecha->derecha->numero) == numero)
            ZagZag(nodo);
        else
            ControlDeMovimiento(numero,&(*nodo)->derecha);
    }
}

void Arbol::Graficar()
{
    FILE * file;
    file = fopen("grafo.dot","w+");
    fprintf(file,"digraph G {\n");
    getDot(file,raiz);
    fprintf(file,"}");
    fclose(file);
    system("dot grafo.dot -o grafica.jpg -Tjpg -Grankdir=TB && xdg-open grafica.jpg");
}

bool Arbol::Buscar(int numero, Nodo * nodo)
{
    if(nodo!=NULL){
        if(nodo->numero == numero)
            return true;
        else if(nodo->numero > numero)
            return Buscar(numero,nodo->izquierda);
        else if(nodo->numero < numero)
            return Buscar(numero,nodo->derecha);
    }
    return false;
}

bool Arbol::Eliminar(int numero)
{
    if(!Buscar(numero,raiz)) return false;
    PasarARaiz(numero,&raiz);
    if(raiz->izquierda == NULL && raiz->derecha == NULL)
        raiz = NULL;
    else if(raiz->izquierda !=NULL && raiz->derecha !=NULL)
    {
        int aux = ObtenerMayorDeMenores(raiz->izquierda);
        if(aux != raiz->izquierda->numero)
            PasarARaiz(aux,&(raiz->izquierda));
        raiz->izquierda->derecha = raiz->derecha;
        raiz = raiz->izquierda;
    }
    else if(raiz->izquierda !=NULL)
        raiz = raiz->izquierda;
    else
        raiz = raiz->derecha;
    return true;
}

int Arbol::ObtenerMayorDeMenores(Nodo* nodo){
    if(nodo->derecha == NULL){
        return nodo->numero;
    }
    return ObtenerMayorDeMenores(nodo->derecha);
}

void Arbol::Zig(Nodo ** nodo)
{
    Nodo* aux = *nodo;
    *nodo = (*nodo)->izquierda;
    aux->izquierda = (*nodo)->derecha;
    (*nodo)->derecha = aux;
}

void Arbol::ZigZig(Nodo ** nodo)
{
    Zig(nodo);
    Zig(nodo);
}

void Arbol::ZigZag(Nodo ** nodo)
{
    Zag(&(*nodo)->izquierda);
    Zig(nodo);
}

void Arbol::Zag(Nodo ** nodo)
{
    Nodo* aux = *nodo;
    *nodo = (*nodo)->derecha;
    aux->derecha = (*nodo)->izquierda;
    (*nodo)->izquierda = aux;
}

void Arbol::ZagZag(Nodo ** nodo)
{
    Zag(nodo);
    Zag(nodo);
}

void Arbol::ZagZig(Nodo ** nodo)
{
    Zig(&(*nodo)->derecha);
    Zag(nodo);
}


void Arbol::getDot(FILE * file, Nodo * nodo)
{
    if(nodo == NULL) return;
    fprintf(file,"x%p[label=\"%i\"];\n",nodo,nodo->numero);
    if(nodo->izquierda != NULL)
        fprintf(file,"x%p->x%p[arrowhead = normalrtee];\n",nodo,nodo->izquierda);
    if(nodo->derecha != NULL)
        fprintf(file,"x%p->x%p[arrowhead = normalltee];\n",nodo,nodo->derecha);
    getDot(file,nodo->izquierda);
    getDot(file,nodo->derecha);
}

Nodo::Nodo(int numero){
    this->numero=numero;
    this->derecha = this->izquierda = NULL;
}

Nodo::~Nodo(){}
