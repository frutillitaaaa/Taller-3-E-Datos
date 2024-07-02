#include "../header/Sistema.h"

Sistema::Sistema()
{
    arbol = new ArbolTransacciones();
}

Sistema::~Sistema()
{
    delete arbol; 
}

Transaccion* Sistema::registrarTransaccion(string cuentaDeOrigen, string cuentaDeDestino, int monto, string ubicacion)
{
    Transaccion* transaccion;
    try{
        Transaccion* transaccion = new Transaccion(cuentaDeOrigen,cuentaDeDestino,monto,ubicacion);
        NodoTransaccion* nodo = new NodoTransaccion(transaccion);
        nodoPadre = arbol->insertarNodoTransaccion(nodo);
    } catch(const bad_alloc& e){
        cerr<<"Ocurrio un error al asignar memoria"<<endl;
    }
    

    return transaccion;
}
