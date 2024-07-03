#pragma once

#include "NodoTransaccion.h"

class ArbolTransacciones {

    private:
        NodoTransaccion* nodoPadre;
        int cantTHora;
        int cantUbi;
        void setAlturaNodo(NodoTransaccion* nodo);
    
    public:
        ArbolTransacciones();
        ~ArbolTransacciones();
        int getAlturaNodo(NodoTransaccion* nodo);
        int getFactorBalanceo(NodoTransaccion* nodo);
        int getCantTHora();
        int getCantUbi();
        NodoTransaccion* insertarNodoTransaccion(NodoTransaccion* nodo);
        NodoTransaccion* insertarNodoTransaccionRecursivo(NodoTransaccion* aux, NodoTransaccion* nodo);
        NodoTransaccion* obtenerNodoPadre();
        bool buscarNodoTransaccion(NodoTransaccion* aux, int idTransaccion);
        void liberarMemoria(NodoTransaccion* nodo);
        NodoTransaccion* rotacionDerecha(NodoTransaccion* nodo);
        NodoTransaccion* rotacionIzquierda(NodoTransaccion* nodo);
        void recorrerArbol(NodoTransaccion* nodo);

};