#include "../header/Sistema.h"
#include "Sistema.h"

Sistema::Sistema(Cliente* c)
{
    cliente = c;
    arbolDecision = c->getArbolDecision();
    arbol = c->getArbolTransaccion();

}

Sistema::~Sistema()
{
}

Transaccion* Sistema::registrarTransaccion(string cuentaDeDestino, int monto, string ubicacion)
{
    Transaccion* transaccion = nullptr;
    try{
        transaccion = new Transaccion(cliente->getCuenta(),cuentaDeDestino,monto,ubicacion);
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

    arbolDecision->setMontoSospecha(montoTransaccion);
    arbolDecision->setCantTSospecha(cantTransacciones);
    arbolDecision->setCantUbiSospecha(cantUbisDistintas);

    arbolDecision->modificacionCriterioSospechoso(nodoPadre);
    
}

int Sistema::obtenerMontoTSospechosa()
{
    return arbolDecision->obtenerMontoSospecha();
}

int Sistema::obtenerCantTSospechosa()
{
    return arbolDecision->obtenerCantTSospecha();
}

int Sistema::obtenerCantUbiSospechosa()
{
    return arbolDecision->obtenerCantUbiSospecha();
}

void Sistema::generarReportes()
{
    if(cliente == nullptr){
        cerr<<"No hay cliente"<<endl;
        return;
    } else if(arbol == nullptr){
        cerr<<"Arbol de transacciones nulo"<<endl;
        return;
    } else if(arbol->obtenerNodoPadre() == nullptr){
        cout<<"Arbol vacio"<<endl;
    }

    cliente->registroDeTransacciones();
}

void Sistema::obtenerTransaccionesSospechosas(NodoTransaccion *nodo)
{
    
    if(nodo == nullptr|| arbol == nullptr || arbolDecision == nullptr || nodo->transaccion == nullptr){ 
        return;
    }
    bool sospecha = arbolDecision->esSospechoso(arbolDecision->obtenerNodoPadre(),nodo,nodo->transaccion->getMontoTransaccion(),arbol->obtenerCantTHora(),arbol->obtenerCantUbi());
    if(sospecha){
        cout<<"--- Transacciones Sospechosas ---"<<endl;
        arbol->recorrerArbolTSospechosas(nodoPadre);
    }else{cout<<"No se detecto ninguna transaccion sospechosa"<<endl;}
}

NodoTransaccion *Sistema::obtenerRaiz()
{
    return arbol->obtenerNodoPadre();
}

void Sistema::establecerZonaHoraria(const char* zonaHoraria)
{
    setenv("TZ", zonaHoraria, 1);
    tzset();
}
