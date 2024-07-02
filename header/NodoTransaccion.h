#pragma once

#include "Transaccion.h"

class NodoTransaccion{

    public:
        Transaccion* transaccion;
        int altura;
        int idTransaccion; //Identificador de búsqueda de Transacciones
        NodoTransaccion* tderecha;
        NodoTransaccion* tizquierda;

        NodoTransaccion(Transaccion* transaccion);
        ~NodoTransaccion();

};