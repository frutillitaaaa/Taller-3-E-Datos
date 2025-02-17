#include "../header/ArbolTransacciones.h"

#include <cstdlib>
#include "ArbolTransacciones.h"

ArbolTransacciones::ArbolTransacciones()
{
    nodoPadre = nullptr;
}
ArbolTransacciones::~ArbolTransacciones()
{
    if(nodoPadre!= nullptr){
        liberarMemoria(nodoPadre);
    }
}

// Función de inserción de Nodo transacción en el árbol de transacciones
NodoTransaccion *ArbolTransacciones::insertarNodoTransaccion(NodoTransaccion *nodo)
{
    if(nodoPadre == nullptr){ //si el arbol está vacío o si el nodoPadre inicial no tiene nodos hijos, el nuevo nodoPadre será el nodo que queríamos añadir
        if(nodo != nullptr) {nodoPadre = nodo;}
        else{return nullptr;}
        
    }else {
        if(nodoPadre->transaccion!= nullptr){
            if(nodoPadre->transaccion->getFechaYHoraTransaccion()-nodo->transaccion->getFechaYHoraTransaccion()<= 3600) cantTHora++;
            if(nodoPadre->transaccion->getUbicacion() != nodo->transaccion->getUbicacion() && nodoPadre->transaccion->getFechaYHoraTransaccion()-nodo->transaccion->getFechaYHoraTransaccion()<= 3600)
            cantUbi++;
        //si no esta vacio el arbol, se compara si el dato del nodo que se quiere ingresar es mayor o menor que el nodoPadre
            if(nodo->transaccion->getID() < nodoPadre->transaccion->getID()){
            nodoPadre->tizquierda = insertarNodoTransaccionRecursivo(nodoPadre->tizquierda,nodo);
            }else{
                nodoPadre->tderecha = insertarNodoTransaccionRecursivo(nodoPadre->tderecha,nodo);
            }
        }
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

int ArbolTransacciones::obtenerCantTHora()
{
    cantTHora = 0;
    contarTEnHora(nodoPadre);
    return cantTHora;
}

int ArbolTransacciones::obtenerCantUbi()
{
    cantUbi = 0;
    contarUbiEnDia(nodoPadre);
    return cantUbi;
}

void ArbolTransacciones::contarTEnHora(NodoTransaccion *nodo)
{
    if(nodo == nullptr) return;

    if(nodo->tizquierda != nullptr && nodo->tizquierda->transaccion->getFechaYHoraTransaccion()-nodo->transaccion->getFechaYHoraTransaccion()<3600){
        cantTHora++;
    }

    if(nodo->tderecha != nullptr && nodo->tderecha->transaccion->getFechaYHoraTransaccion()-nodo->transaccion->getFechaYHoraTransaccion()<3600){
        cantTHora++;
    }
    contarTEnHora(nodo->tizquierda);
    contarTEnHora(nodo->tderecha);

}

void ArbolTransacciones::contarUbiEnDia(NodoTransaccion *nodo)
{
    if(nodo == nullptr || nodo->transaccion == nullptr){
        return;
    }
    if(nodo->tizquierda != nullptr && nodo->tizquierda->transaccion->getFechaYHoraTransaccion()-nodo->transaccion->getFechaYHoraTransaccion()<86400){
        if(nodo->tizquierda->transaccion->getUbicacion() != nodo->transaccion->getUbicacion()) cantUbi++;
    }

    if(nodo->tderecha != nullptr && nodo->tderecha->transaccion->getFechaYHoraTransaccion()-nodo->transaccion->getFechaYHoraTransaccion()<86400){
        if(nodo->tderecha->transaccion->getUbicacion() != nodo->transaccion->getUbicacion()) cantUbi++;
    }

    contarUbiEnDia(nodo->tizquierda);
    contarUbiEnDia(nodo->tderecha);
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

// Función de inserción de Nodo transacción en el árbol de transacciones de manera recursiva
NodoTransaccion* ArbolTransacciones::insertarNodoTransaccionRecursivo(NodoTransaccion* aux, NodoTransaccion* nodo) 
{
    if(nodo == nullptr){
        cerr<<"Se intento insertar un nodo nullptr"<<endl;
        return aux;
    }

    if(aux == nullptr) //si el arbol está vacío o si el nodoPadre inicial no tiene nodos hijos, el nuevo nodoPadre será el nodo que queríamos añadir
        aux = nodo;
    
    
    if(nodo->transaccion == nullptr){
        cerr<<"Transaccion invalida"<<endl;
        return aux;
    }

    //si no esta vacio el arbol, se compara si el dato del nodo que se quiere ingresar es mayor o menor que el nodoPadre
    if(nodo->transaccion->getID() < aux->transaccion->getID())
        aux->tizquierda = insertarNodoTransaccionRecursivo(aux->tizquierda,nodo);
    else if(nodo->transaccion->getID() > aux->transaccion->getID())
        aux->tderecha = insertarNodoTransaccionRecursivo(aux->tderecha,nodo);

    setAlturaNodo(aux);

    int factorBalanceo = getFactorBalanceo(aux);
    
    if(factorBalanceo > 1){

        //RR
        if(nodo->transaccion->getID() > aux->tderecha->transaccion->getID() && nodo->transaccion->getID() > aux->transaccion->getID()){
            return rotacionIzquierda(aux);
        }

        //RL
        else if(nodo->transaccion->getID() < aux->tderecha->transaccion->getID() && nodo->transaccion->getID() > aux->transaccion->getID()){
            aux->tderecha = rotacionDerecha(aux->tderecha);
            return rotacionIzquierda(aux);
        }

        //LL
        else if(nodo->transaccion->getID() < aux->tderecha->transaccion->getID() && nodo->transaccion->getID() < aux->transaccion->getID()){
            rotacionDerecha(aux); 
        }


        //LR  
        else if(nodo->transaccion->getID() > aux->tderecha->transaccion->getID() && nodo->transaccion->getID() < aux->transaccion->getID()){
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

//Busca las transacciones en el arbol de transacciones de acuerdo al id de transaccion
bool ArbolTransacciones::buscarNodoTransaccion(NodoTransaccion* nodo, int idTransaccion, string cuentaCliente)
{
    if(nodo == nullptr){
        return false;
    }
    if(nodo->transaccion->getCuentaDeOrigen() != cuentaCliente && nodo->transaccion->getCuentaDeDestino() != cuentaCliente) return false;
    if(nodo->transaccion->getID() == idTransaccion ) {
        return true;
    } else if(idTransaccion < nodo->transaccion->getID()){
        return buscarNodoTransaccion(nodo->tizquierda, idTransaccion, cuentaCliente);
    } else{
        return buscarNodoTransaccion(nodo->tderecha, idTransaccion, cuentaCliente);
    } 
}


void ArbolTransacciones::liberarMemoria(NodoTransaccion *nodo)
{
    if(nodo == nullptr){
        cerr<<"No se pudo eliminar el nodo porque no existe"<<endl;
        return;
    } 

    if(nodo->tizquierda != nullptr){
        liberarMemoria(nodo->tizquierda);
    }
    
    if(nodo->tderecha != nullptr){
        liberarMemoria(nodo->tderecha);
    }
    

    if(nodo->transaccion != nullptr) {
        delete nodo->transaccion;
        nodo->transaccion = nullptr;
    }
    delete nodo;
    nodo = nullptr;
    
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

void ArbolTransacciones::recorrerArbol(NodoTransaccion* nodo, string cuentaCliente)
{
    if(nodo != nullptr && nodo->transaccion != nullptr){
        if(nodo->transaccion->getCuentaDeDestino() == cuentaCliente ||nodo->transaccion->getCuentaDeOrigen() == cuentaCliente){
            cout<<"ID Transaccion: "<<nodo->transaccion->getID()<<"\nFecha y Hora: "<<nodo->transaccion->obtenerFechaLegible()
            <<"\nCuenta de Destino: "<<nodo->transaccion->getCuentaDeDestino()<<"\nMonto: "<<nodo->transaccion->getMontoTransaccion()
            <<"\nUbicacion: "<<nodo->transaccion->getUbicacion()<<"\n--------------"<<endl;
            recorrerArbol(nodo->tizquierda,cuentaCliente);
            recorrerArbol(nodo->tderecha,cuentaCliente);
        }
    }    
}

void ArbolTransacciones::recorrerArbolTSospechosas(NodoTransaccion *nodo)
{

    if(nodo == nullptr || nodo->transaccion == nullptr){
        cerr<<"Error: no se pudieron cargar los datos"<<endl;
        return;
    }
    if(nodo->transaccion->esSospechosa()){
        cout<<"ID Transaccion: "<<nodo->transaccion->getID()<<"\nFecha y Hora: "<<nodo->transaccion->obtenerFechaLegible()
        <<"\nCuenta de Destino: "<<nodo->transaccion->getCuentaDeDestino()<<"\nMonto: "<<nodo->transaccion->getMontoTransaccion()
        <<"\nUbicacion: "<<nodo->transaccion->getUbicacion()<<"\n--------------"<<endl;
    } 
    recorrerArbolTSospechosas(nodo->tizquierda);
    recorrerArbolTSospechosas(nodo->tderecha);
}

 