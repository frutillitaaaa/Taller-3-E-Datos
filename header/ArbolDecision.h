#ifndef ARBOLDECISION_H
#define ARBOLDECISION_H

#include "NodoDecision.h"

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
        bool esSospechoso(NodoDecision *nodo, int montoT, int cantT, int cantUbi);
        NodoDecision* obtenerNodoPadre();
        int obtenerMontoSospecha();
        int obtenerCantTSospecha();
        int obtenerCantUbiSospecha();
        


};

#endif