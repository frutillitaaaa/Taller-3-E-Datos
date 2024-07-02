#include "../header/NodoTransaccion.h"

NodoTransaccion::NodoTransaccion(Transaccion* transaccion){
    
    if(transaccion == nullptr){
        throw invalid_argument("puntero transaccion es nulo");
    } 
    else{
        this->transaccion = transaccion;
        this->altura = 1;
        this->idTransaccion = transaccion->getID();
        this->tderecha = NULL;
        this->tizquierda = NULL;
    }
    
}

NodoTransaccion::~NodoTransaccion()
{
    
}



