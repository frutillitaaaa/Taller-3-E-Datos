#ifndef CLIENTE_H
#define CLIENTE_H

#include "Transaccion.h"
#include "ArbolDecision.h"
#include "ArbolTransacciones.h"

#include <iostream>

using namespace std;

class Cliente {

    private:
        string cuenta;
        ArbolDecision* arbolDecision;
        ArbolTransacciones* arbolTransacciones;

    public:
        Cliente(string cuenta);
        ~Cliente();
        ArbolDecision* getArbolDecision();
        void setArbolDecision(ArbolDecision* a);
        ArbolTransacciones* getArbolTransaccion();
        void setArbolTransaccion(ArbolTransacciones* a);
        void registroDeTransacciones();
        string getCuenta();
};

#endif