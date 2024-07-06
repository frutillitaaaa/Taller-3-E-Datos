#ifndef SISTEMA_H
#define SISTEMA_H


#include "Transaccion.h"
#include "NodoTransaccion.h"
#include "ArbolTransacciones.h"
#include "ArbolDecision.h"
#include "Cliente.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Sistema {

    private:
        Cliente* cliente;
        ArbolTransacciones* arbol;
        ArbolTransacciones* arbolGeneral;
        ArbolDecision* arbolDecision;
        NodoTransaccion* nodoPadre;
        NodoTransaccion* raizArbolGeneral;
        int montoSospecha;
        int cantTSospecha;
        int cantUbiSospecha;
        bool actualizar;

    public:
        Sistema(Cliente* c);
        ~Sistema();
        Transaccion* registrarTransaccion(string cuentaDeDestino, int monto, string ubicacion);
        int obtenerID(Transaccion* transaccion);
        bool buscarTransaccion(int id);
        void modificarCriteriosDeTransaccionesSospechosas(int montoTransaccion, int cantTransacciones, int cantUbisDistintas);
        int obtenerMontoTSospechosa();
        int obtenerCantTSospechosa();
        int obtenerCantUbiSospechosa();
        void generarReportes();
        void obtenerTransaccionesSospechosas(NodoTransaccion* nodo);
        NodoTransaccion* obtenerRaiz();
        void actualizarDatos(NodoTransaccion* nodo,const string &nArchivo);
        void actualizarDatosConRecursion(NodoTransaccion *nodoT, ofstream &archivo);
        void cargarDatos(const string& archivo);

};

#endif