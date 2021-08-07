#include <QCoreApplication>
#include "arbol.h"
int main()
{
    Arbol* splay = new Arbol();
    int opcion=0;
    int numero=0;
    do{
        printf("Ingrese una opcion\n");
        printf("1. Ingresar dato\n");
        printf("2. Eliminar dato\n");
        printf("3. Buscar dato\n");
        printf("4. Graficar\n");
        printf("5. Salir\n");
        scanf("%i",&opcion);
        switch (opcion) {
        case 1:
            printf("Ingresa un numero\n");
            scanf("%i",&numero);
            //Primero se inserta el numero como un arbol binario de busqueda
            splay->Insertar(numero,&(splay->raiz));
            //Luego el nodo empieza a subir hasta llegar a la raiz
            splay->PasarARaiz(numero,&(splay->raiz));
            break;
        case 2:
            printf("Ingresa un numero\n");
            scanf("%i",&numero);
            if(splay->Eliminar(numero))
                printf("El numero %i, fue eliminado\n",numero);
            else
                printf("No existe el numero ingresado para eliminar no sucede nada\n");
            break;
        case 3:
            printf("Ingresa un numero a buscar\n");
            scanf("%i",&numero);
            if(splay->Buscar(numero,splay->raiz))
            {
                printf("El numero %i si existe dentro del arbol spl\n",numero);
                splay->PasarARaiz(numero,&(splay->raiz));
                splay->Graficar();
            }
            else
                printf("No existe el numero buscado\n");
            break;
        case 4:
            splay->Graficar();
            break;
        case 5:
            return 0;
        default:
            printf("Seleccione una opcion correcta\n");
            break;
        }
    }while(true);
    return 0;
}
