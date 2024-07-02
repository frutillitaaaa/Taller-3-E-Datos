#include "../header/ArbolTransacciones.h"

#include <cstdlib>
#include "ArbolTransacciones.h"

ArbolTransacciones::ArbolTransacciones()
{
    nodoPadre = nullptr;
}
ArbolTransacciones::~ArbolTransacciones()
{
    liberarMemoria(nodoPadre);
    nodoPadre = nullptr;
}

// Función de inserción de Nodo transacción en el árbol de transacciones
NodoTransaccion *ArbolTransacciones::insertarNodoTransaccion(NodoTransaccion *nodo)
{
     if(nodoPadre == nullptr) //si el arbol está vacío o si el nodoPadre inicial no tiene nodos hijos, el nuevo nodoPadre será el nodo que queríamos añadir
        nodoPadre = nodo;
    else {
        //si no esta vacio el arbol, se compara si el dato del nodo que se quiere ingresar es mayor o menor que el nodoPadre
        if(nodo->idTransaccion < nodoPadre->idTransaccion)
            nodoPadre->tizquierda = insertarNodoTransaccionRecursivo(nodoPadre->tizquierda,nodo);
        else if(nodo->idTransaccion > nodoPadre->idTransaccion)
            nodoPadre->tderecha = insertarNodoTransaccionRecursivo(nodoPadre->tderecha,nodo);
    }
    setAlturaNodo(nodoPadre);

    return nodoPadre;
}

//retorna la altura del nodo actual
int ArbolTransacciones::getAlturaNodo(NodoTransaccion* nodo)
{
    if(nodo == NULL){
        return -1;
    }
    return nodo->altura;
}


//retorna el factor de balanceo del nodo actual
int ArbolTransacciones::getFactorBalanceo(NodoTransaccion *nodo)
{
    if(nodo == NULL){
        return -1;
    }
    
    if(nodo->tderecha == nullptr && nodo->tizquierda == nullptr) return 0;
    if(nodo->tderecha == nullptr) return getAlturaNodo(nodo->tizquierda);
    if(nodo->tizquierda == nullptr) return getAlturaNodo(nodo->tderecha);

    return abs(getAlturaNodo(nodo->tizquierda) - getAlturaNodo(nodo->tderecha));
}

//modifica el valor de la altura del nodo actual
void ArbolTransacciones::setAlturaNodo(NodoTransaccion *nodo)
{
    if(nodo == nullptr){
        return;
    }
    int hDer = 0;
    int hIzq = 0;
    if(nodo->tderecha == nullptr && nodo->tizquierda == nullptr) nodo->altura = 1;
    if(nodo->tderecha == nullptr) hIzq = getAlturaNodo(nodo->tizquierda);
    if(nodo->tizquierda == nullptr) hDer = getAlturaNodo(nodo->tderecha);

    nodo->altura = 1 + max(hDer,hIzq);
}

//-SIN ERRRORES-
// Función de inserción de Nodo transacción en el árbol de transacciones de manera recursiva
NodoTransaccion* ArbolTransacciones::insertarNodoTransaccionRecursivo(NodoTransaccion* aux, NodoTransaccion* nodo) 
{
    if(aux == nullptr) //si el arbol está vacío o si el nodoPadre inicial no tiene nodos hijos, el nuevo nodoPadre será el nodo que queríamos añadir
        aux = nodo;
    //si no esta vacio el arbol, se compara si el dato del nodo que se quiere ingresar es mayor o menor que el nodoPadre
    if(nodo->idTransaccion < aux->idTransaccion)
        aux->tizquierda = insertarNodoTransaccionRecursivo(aux->tizquierda,nodo);
    else if(nodo->idTransaccion > aux->idTransaccion)
        aux->tderecha = insertarNodoTransaccionRecursivo(aux->tderecha,nodo);

    setAlturaNodo(aux);

    int factorBalanceo = getFactorBalanceo(aux);
    
    if(factorBalanceo > 1){
        cout<<"hhhh"<<endl;

        //RR
        if(nodo->idTransaccion > aux->tderecha->idTransaccion && nodo->idTransaccion > aux->idTransaccion){
            return rotacionIzquierda(aux);
        }

        //RL
        else if(nodo->idTransaccion < aux->tderecha->idTransaccion && nodo->idTransaccion > aux->idTransaccion){
            aux->tderecha = rotacionDerecha(aux->tderecha);
            return rotacionIzquierda(aux);
        }

        //LL
        else if(nodo->idTransaccion < aux->tderecha->idTransaccion && nodo->idTransaccion < aux->idTransaccion){
            rotacionDerecha(aux); 
        }


        //LR  
        else if(nodo->idTransaccion > aux->tderecha->idTransaccion && nodo->idTransaccion < aux->idTransaccion){
            aux->tizquierda = rotacionIzquierda(aux->tizquierda);
            return rotacionDerecha(aux);
        }     
    }

    return aux;

}

NodoTransaccion *ArbolTransacciones::obtenerNodoPadre()
{
    return nodoPadre;
}

//-SIN ERRRORES-
//Busca las transacciones en el arbol de transacciones de acuerdo al id de transaccion
bool ArbolTransacciones::buscarNodoTransaccion(NodoTransaccion* aux, int idTransaccion)
{
    if(aux != nullptr){
        cout<<"hola"<<endl;
        if(aux->idTransaccion == idTransaccion) return true;
        if(idTransaccion < aux->idTransaccion){
            cout<<"por aqui"<<endl;
            return buscarNodoTransaccion(aux->tizquierda, idTransaccion);
        } 
        if(idTransaccion > aux->idTransaccion){
            cout<<"por aca"<<endl;
            return buscarNodoTransaccion(aux->tderecha, idTransaccion);
        } 
    }
    return false;
}

//presenta errores
void ArbolTransacciones::liberarMemoria(NodoTransaccion *nodo)
{
    if(nodo == nullptr) return;

    liberarMemoria(nodo->tizquierda);
    liberarMemoria(nodo->tderecha);

    delete nodo->transaccion;
    delete nodo;
    
}

//Rotacion simple a la derecha de los nodos en el arbol
NodoTransaccion *ArbolTransacciones::rotacionDerecha(NodoTransaccion *nodo)
{
    if(nodo == nullptr || nodo->tizquierda == nullptr) return nodo;
    NodoTransaccion* aux = nodo->tizquierda;
    nodo->tizquierda = aux->tderecha;
    aux->tderecha = nodo;

    setAlturaNodo(nodo);
    setAlturaNodo(aux);
    
    return aux;
}

//Rotacion simple a la izquierda de los nodos en el arbol
NodoTransaccion *ArbolTransacciones::rotacionIzquierda(NodoTransaccion *nodo)
{
    if(nodo == nullptr || nodo->tderecha == nullptr) return nodo;
    NodoTransaccion* aux = nodo->tderecha;
    nodo->tderecha = aux->tizquierda;
    aux->tizquierda = nodo;

    setAlturaNodo(nodo);
    setAlturaNodo(aux);

    return aux;
}
