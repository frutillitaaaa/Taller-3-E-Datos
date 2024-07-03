#include "../header/ArbolDecision.h"
#include "ArbolDecision.h"


ArbolDecision::ArbolDecision()
{
    this->nodoPadre = agregarNodo();
    montoSospecha = 10;
    cantTSospecha = 7;
    cantUbiSospecha = 4;
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

bool ArbolDecision::esSospechoso(NodoDecision *nodo, int montoT, int cantT, int cantUbi)
{
    if(nodo == nullptr){
        cout<<"nodo nulo"<<endl;
        return false;
    }
    if(nodo->hDerecha == nullptr && nodo->hIzquierda == nullptr){
        return nodo->sospecha;
    }
    bool sospecha1 = false;
    bool sospecha2 = false;

    if(nodo->criterio == "Transaccion mayor a monto"){
        //si la transaccion es mayor al monto establecido 
        if(montoT >= montoSospecha) {
            nodo->sospecha = true;
            if(nodo->hIzquierda != nullptr) sospecha1 = esSospechoso(nodo->hIzquierda, montoT, cantT, cantUbi);
            cout<<sospecha1<<endl;

        }
        //si la transaccion no es mayor al monto establecido
        if(nodo->hDerecha != nullptr) sospecha2 = esSospechoso(nodo->hDerecha, montoT, cantT, cantUbi); cout<<sospecha2<<endl;
    } else if(nodo->criterio == "Frecuencia alta de transacciones en corto tiempo"){
        //si la frecuencia de transacciones es alta en un corto tiempo
        if(cantT >= cantTSospecha){
            nodo->sospecha = true;
            if(nodo->hIzquierda != nullptr) sospecha1 = esSospechoso(nodo->hIzquierda, montoT, cantT, cantUbi);
            cout<<sospecha1<<endl;
        } 
        //si la frecuencia de transacciones no es alta
        if(nodo->hDerecha != nullptr) sospecha2 = esSospechoso(nodo->hDerecha, montoT, cantT, cantUbi); cout<<sospecha2<<endl;
    } else if(nodo->criterio == "Ubicaciones diferentes en corto tiempo"){
        //si las ubicaciones cambian mucho en poco tiempo
        if(cantUbi >= cantUbiSospecha){
            nodo->sospecha = true;
            if(nodo->hIzquierda != nullptr) sospecha1 = esSospechoso(nodo->hIzquierda, montoT, cantT, cantUbi);
            cout<<sospecha1<<endl;
        } 
        //si las ubicaciones no cambian mucho
        if(nodo->hDerecha != nullptr) sospecha2 = esSospechoso(nodo->hDerecha, montoT, cantT, cantUbi); cout<<sospecha2<<endl;
    }
    cout<<sospecha1<<" - "<<sospecha2<<endl;
    return sospecha1 || sospecha2;

}

NodoDecision *ArbolDecision::obtenerNodoPadre()
{
    return nodoPadre;
}
