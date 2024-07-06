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
    delete arbolDecision;
    delete arbolTransacciones;
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
    return nullptr;
}

void Cliente::obtenerTransaccionesSospechosas(){
    arbolTransacciones->recorrerArbolTSospechosas(arbolTransacciones->obtenerNodoPadre());
}