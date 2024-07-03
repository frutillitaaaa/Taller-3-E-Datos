#include "../header/Sistema.h"
#include "Sistema.h"

Sistema::Sistema()
{
    arbol = new ArbolTransacciones();
    arbolDecision = new ArbolDecision();

}

Sistema::~Sistema()
{
    delete arbol; 
    delete arbolDecision;
}

Transaccion* Sistema::registrarTransaccion(string cuentaDeOrigen, string cuentaDeDestino, int monto, string ubicacion)
{
    Transaccion* transaccion = nullptr;
    try{
        transaccion = new Transaccion(cuentaDeOrigen,cuentaDeDestino,monto,ubicacion);
        NodoTransaccion* nodo = new NodoTransaccion(transaccion);
        nodoPadre = arbol->insertarNodoTransaccion(nodo);
        
    } catch(const bad_alloc& e){
        cerr<<"Ocurrio un error al asignar memoria"<<endl;
    }
    return transaccion;
}

int Sistema::obtenerID(Transaccion *transaccion)
{
    if(transaccion == nullptr){
        return 0;
    }
 
    return transaccion->getID();;
}

bool Sistema::buscarTransaccion(int id)
{
    if(nodoPadre == nullptr){
        cout<<"Arbol vacio"<<endl;
        return false;
    }
    return arbol->buscarNodoTransaccion(nodoPadre,id);
}

void Sistema::modificarCriteriosDeTransaccionesSospechosas(int montoTransaccion, int cantTransacciones, int cantUbisDistintas)
{
    this->montoSospecha = montoTransaccion;
    this->cantTSospecha = cantTransacciones;
    this->cantUbiSospecha = cantUbisDistintas;
}

void Sistema::generarReportes()
{
    if(nodoPadre == nullptr) return;
    arbol->recorrerArbol(nodoPadre);
}

void Sistema::detectarTransaccionesSospechosas(NodoTransaccion *nodo)
{
    if(nodo == nullptr|| arbol == nullptr || arbolDecision == nullptr || nodo->transaccion == nullptr) return;
    bool sospecha = arbolDecision->esSospechoso(arbolDecision->agregarNodo(),nodo->transaccion->getMontoTransaccion(),arbol->getCantTHora(),arbol->getCantUbi());
    if(sospecha)
    cout<<"Se ha detectado una transaccion sospechosa: "<<nodo->transaccion->getID()<<" - "<<nodo->transaccion->getMontoTransaccion()<<
    " - "<<nodo->transaccion->getUbicacion()<< " - "<<nodo->transaccion->getCuentaDeOrigen()<<" - "<<nodo->transaccion->getCuentaDeDestino()<<endl;
}
