#ifndef SISTEMA_H
#define SISTEMA_H


#include "Transaccion.h"
#include "NodoTransaccion.h"
#include "ArbolTransacciones.h"
#include "ArbolDecision.h"

#include <iostream>

using namespace std;

class Sistema {

    private:
        ArbolTransacciones* arbol;
        ArbolDecision* arbolDecision;
        NodoTransaccion* nodoPadre;
        int montoSospecha;
        int cantTSospecha;
        int cantUbiSospecha;

    public:
        Sistema();
        ~Sistema();
        Transaccion* registrarTransaccion(string cuentaDeOrigen, string cuentaDeDestino, int monto, string ubicacion);
        int obtenerID(Transaccion* transaccion);
        bool buscarTransaccion(int id);
        void modificarTransaccion(int id);
        void historialTransaccionesSospechosas();
        void modificarCriteriosDeTransaccionesSospechosas(int montoTransaccion, int cantTransacciones, int cantUbisDistintas);
        void generarReportes();
        void actualizarDatos();
        void detectarTransaccionesSospechosas(NodoTransaccion* nodo);

};

#endif