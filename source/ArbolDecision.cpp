#include "../header/ArbolDecision.h"
#include "ArbolDecision.h"


ArbolDecision::ArbolDecision()
{
    this->nodoPadre = agregarNodo();
    montoSospecha = 10;
    cantTSospecha = 10;
    cantUbiSospecha = 5;
}
void ArbolDecision::agregarCriterio(NodoDecision *nodo, string criteriosi, string criteriono)
{
    if(nodo == nullptr){
        cerr<<"Nodo nulo"<<endl;
    }
    if(!criteriosi.empty()){
        nodo->hIzquierda = new NodoDecision(criteriosi);
    }else{ nodo->hIzquierda = nullptr;}
    
    if(!criteriono.empty()){
        nodo->hDerecha = new NodoDecision(criteriono);
    }else{nodo->hDerecha = nullptr;}
}

NodoDecision *ArbolDecision::agregarNodo()
{
    NodoDecision* nodoPadre = new NodoDecision("Transaccion mayor a monto");
    agregarCriterio(nodoPadre, "Transaccion sospechosa", "Frecuencia alta de transacciones en corto tiempo");
    agregarCriterio(nodoPadre->hDerecha, "Transaccion sospechosa", "Ubicaciones diferentes en corto tiempo");
    agregarCriterio(nodoPadre->hDerecha->hDerecha, "Transaccion sospechosa","Transaccion no sospechosa");
    return nodoPadre;
}

bool ArbolDecision::esSospechoso(NodoDecision *nodo,NodoTransaccion* nodoAEvaluar, int montoT, int cantT, int cantUbi, string cuentaCliente)
{
    if(nodo == nullptr){
        cout<<"nodo nulo"<<endl;
        return false;
    }
    if(nodo->hDerecha == nullptr && nodo->hIzquierda == nullptr){
        if(nodoAEvaluar->transaccion->getCuentaDeOrigen() == cuentaCliente)
        return nodoAEvaluar->transaccion->esSospechosa();
    }
    bool sospecha1 = false;
    bool sospecha2 = false;

    if(nodoAEvaluar->transaccion->getCuentaDeOrigen() != cuentaCliente) return false;

    if(nodo->criterio == "Transaccion mayor a monto"){
        //si la transaccion es mayor al monto establecido 
        if(montoT >= montoSospecha) {
            nodoAEvaluar->transaccion->setSospecha(true);
            if(nodo->hIzquierda != nullptr) sospecha1 = esSospechoso(nodo->hIzquierda, nodoAEvaluar, montoT, cantT, cantUbi, cuentaCliente);

        }
        //si la transaccion no es mayor al monto establecido
        if(nodo->hDerecha != nullptr) sospecha2 = esSospechoso(nodo->hDerecha, nodoAEvaluar, montoT, cantT, cantUbi, cuentaCliente);
    } else if(nodo->criterio == "Frecuencia alta de transacciones en corto tiempo"){
        //si la frecuencia de transacciones es alta en un corto tiempo
        if(cantT >= cantTSospecha){
            nodoAEvaluar->transaccion->setSospecha(true);
            if(nodo->hIzquierda != nullptr) sospecha1 = esSospechoso(nodo->hIzquierda, nodoAEvaluar, montoT, cantT, cantUbi, cuentaCliente);
        } 
        //si la frecuencia de transacciones no es alta
        if(nodo->hDerecha != nullptr) sospecha2 = esSospechoso(nodo->hDerecha, nodoAEvaluar, montoT, cantT, cantUbi, cuentaCliente);
    } else if(nodo->criterio == "Ubicaciones diferentes en corto tiempo"){
        //si las ubicaciones cambian mucho en poco tiempo
        if(cantUbi >= cantUbiSospecha){
            nodoAEvaluar->transaccion->setSospecha(true);
            if(nodo->hIzquierda != nullptr) sospecha1 = esSospechoso(nodo->hIzquierda, nodoAEvaluar, montoT, cantT, cantUbi, cuentaCliente);
        } 
        //si las ubicaciones no cambian mucho
        if(nodo->hDerecha != nullptr) sospecha2 = esSospechoso(nodo->hDerecha, nodoAEvaluar, montoT, cantT, cantUbi, cuentaCliente);
    }
    return sospecha1 || sospecha2;

}

NodoDecision *ArbolDecision::obtenerNodoPadre()
{
    return nodoPadre;
}

int ArbolDecision::obtenerMontoSospecha()
{
    return montoSospecha;
}

int ArbolDecision::obtenerCantTSospecha()
{
    return cantTSospecha;
}

int ArbolDecision::obtenerCantUbiSospecha()
{
    return cantUbiSospecha;
}

void ArbolDecision::setMontoSospecha(int monto)
{
    this->montoSospecha = monto;
}

void ArbolDecision::setCantTSospecha(int cantT)
{
    this->cantTSospecha = cantT;
}

void ArbolDecision::setCantUbiSospecha(int cantUbi)
{
    this->cantUbiSospecha = cantUbi;
}

void ArbolDecision::modificacionCriterioSospechoso(NodoTransaccion *nodo)
{
    if(nodo == nullptr) return;
    nodo->transaccion->setSospecha(false);

    modificacionCriterioSospechoso(nodo->tizquierda);
    modificacionCriterioSospechoso(nodo->tderecha);
}
