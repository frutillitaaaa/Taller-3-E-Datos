#pragma once

#include "Transaccion.h"

class NodoTransaccion{

    public:
        Transaccion* transaccion;
        int altura;
        NodoTransaccion* tderecha;
        NodoTransaccion* tizquierda;

        NodoTransaccion(Transaccion* transaccion);
        ~NodoTransaccion();

};