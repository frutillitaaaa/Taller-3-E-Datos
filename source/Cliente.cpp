#include "../header/Cliente.h"
#include "Cliente.h"

Cliente::Cliente(string cuenta)
{
    this->cuenta = cuenta;
    arbolTransacciones = new ArbolTransacciones();
    arbolDecision = new ArbolDecision();
}

Cliente::~Cliente()
{
    if(arbolDecision != nullptr && arbolDecision->obtenerNodoPadre() != nullptr){
        delete arbolDecision;
        arbolDecision = nullptr;
    }
    
    if(arbolTransacciones != nullptr && arbolTransacciones->obtenerNodoPadre() != nullptr){
        delete arbolTransacciones;
        arbolTransacciones = nullptr;
    }
    
}

ArbolDecision *Cliente::getArbolDecision()
{

    return arbolDecision;
}

void Cliente::setArbolDecision(ArbolDecision *a)
{
    this->arbolDecision = a;
}

ArbolTransacciones *Cliente::getArbolTransaccion()
{
    return arbolTransacciones;
}

void Cliente::setArbolTransaccion(ArbolTransacciones *a)
{
    this->arbolTransacciones = a;
}

void Cliente::registroDeTransacciones()
{
    if(arbolTransacciones == nullptr){
        cout<<"arbol de transacciones es nulo"<<endl;
        return;
    } 
    arbolTransacciones->recorrerArbol(arbolTransacciones->obtenerNodoPadre(),cuenta);
}

string Cliente::getCuenta()
{
    return cuenta;
}

NodoTransaccion *Cliente::insertarTransaccion(NodoTransaccion* n)
{
    if(n!= nullptr){
        arbolTransacciones->insertarNodoTransaccion(n);
    }
    return arbolTransacciones->obtenerNodoPadre();
}

void Cliente::obtenerTransaccionesSospechosas(){
    if(arbolTransacciones == nullptr) return;
    arbolTransacciones->recorrerArbolTSospechosas(arbolTransacciones->obtenerNodoPadre());
}