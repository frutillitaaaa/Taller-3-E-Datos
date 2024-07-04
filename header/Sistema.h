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
        ArbolDecision* arbolDecision;
        NodoTransaccion* nodoPadre;
        int montoSospecha;
        int cantTSospecha;
        int cantUbiSospecha;

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
        void establecerZonaHoraria(const char* zonaHoraria);
        void actualizarDatos(NodoTransaccion* nodo,const string &nArchivo);
        void actualizarDatosConRecursion(NodoTransaccion *nodoT, ofstream &archivo);
        void cargarDatos(const string &archivo);

};

#endif