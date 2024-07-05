#ifndef ARBOLDECISION_H
#define ARBOLDECISION_H

#include "NodoDecision.h"
#include "NodoTransaccion.h"
#include "ArbolTransacciones.h"

#include <iostream>

using namespace std;

class ArbolDecision {
    private:
        NodoDecision* nodoPadre;
        int montoSospecha;
        int cantTSospecha;
        int cantUbiSospecha;

    public:
        ArbolDecision();
        void agregarCriterio(NodoDecision* nodo, string criterio1, string criterio2);
        NodoDecision* agregarNodo();
        bool esSospechoso(NodoDecision *nodo,NodoTransaccion* nodoAEvaluar, int montoT, int cantT, int cantUbi, string cuentaCliente);
        NodoDecision* obtenerNodoPadre();
        int obtenerMontoSospecha();
        int obtenerCantTSospecha();
        int obtenerCantUbiSospecha();
        void setMontoSospecha(int monto);
        void setCantTSospecha(int cantT);
        void setCantUbiSospecha(int cantUbi);
        void modificacionCriterioSospechoso(NodoTransaccion* nodo);
        


};

#endif