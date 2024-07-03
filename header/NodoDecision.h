#ifndef NODODECISION_H
#define NODODECISION_H

#include <iostream>

using namespace std;

class NodoDecision {

    public:
        bool sospecha;
        string criterio;
        NodoDecision* hIzquierda;
        NodoDecision* hDerecha;
    
        NodoDecision(string criterio);




};

#endif