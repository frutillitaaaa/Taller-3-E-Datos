#include "../header/ArbolDecision.h"
#include "ArbolDecision.h"


ArbolDecision::ArbolDecision()
{
    this->nodoPadre = nullptr;
    montoSospecha = 10000000;
    cantTSospecha = 7;
    cantUbiSospecha = 4;
}
void ArbolDecision::agregarCriterio(NodoDecision *nodo, string criteriosi, string criteriono)
{
    nodo->hIzquierda = new NodoDecision(criteriosi);
    nodo->hDerecha = new NodoDecision(criteriono);
}

NodoDecision *ArbolDecision::agregarNodo()
{
    NodoDecision* nodoPadre = new NodoDecision("Transaccion mayor a monto");
    agregarCriterio(nodoPadre, "Transaccion sospechosa", "Frecuencia alta de transacciones en corto tiempo");
    agregarCriterio(nodoPadre->hDerecha, "Transaccion sospechosa", "Ubicaciones diferentes en corto tiempo");
    agregarCriterio(nodoPadre->hDerecha->hDerecha, "Transaccion sospechosa","Transaccion no sospechosa");
    return nodoPadre;
}

bool ArbolDecision::esSospechoso(NodoDecision *nodo, int montoT, int cantT, int cantUbi)
{
    if(nodo->hDerecha == nullptr && nodo->hIzquierda == nullptr){
        return nodo->sospecha;
    }

    if(nodo->criterio == "Transaccion mayor a monto"){
        //si la transaccion es mayor al monto establecido 
        if(montoT >= montoSospecha) {
            nodo->sospecha = true;
            esSospechoso(nodo->hIzquierda, montoT, cantT, cantUbi);

        }
        //si la transaccion no es mayor al monto establecido
        esSospechoso(nodo->hDerecha, montoT, cantT, cantUbi);
    } else if(nodo->criterio == "Frecuencia alta de transacciones en corto tiempo"){
        //si la frecuencia de transacciones es alta en un corto tiempo
        if(cantT >= cantTSospecha){
            nodo->sospecha = true;
            esSospechoso(nodo->hIzquierda, montoT, cantT, cantUbi);
        } 
        //si la frecuencia de transacciones no es alta
        esSospechoso(nodo->hDerecha, montoT, cantT, cantUbi);
    } else if(nodo->criterio == "Ubicaciones diferentes en corto tiempo"){
        //si las ubicaciones cambian mucho en poco tiempo
        if(cantUbi >= cantUbiSospecha){
            nodo->sospecha = true;
            esSospechoso(nodo->hIzquierda, montoT, cantT, cantUbi);
        } 
        //si las ubicaciones no cambian mucho
        esSospechoso(nodo->hDerecha, montoT, cantT, cantUbi);
    }
    return false;

}
