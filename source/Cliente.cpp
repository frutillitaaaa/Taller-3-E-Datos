#include "../header/Cliente.h"
#include "Cliente.h"

Cliente::Cliente(string nombre, string cuenta)
{
    this->nombre = nombre;
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
    arbolTransacciones->recorrerArbol(arbolTransacciones->obtenerNodoPadre());
}

string Cliente::getCuenta()
{
    return cuenta;
}

string Cliente::getNombre()
{
    return nombre;
}
