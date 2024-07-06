#include "../header/Sistema.h"
#include "Sistema.h"

Sistema::Sistema(Cliente* c)
{
    cliente = c;
    arbolDecision = c->getArbolDecision();
    arbol = c->getArbolTransaccion();
    nodoPadre = nullptr;
    raizArbolGeneral = nullptr;
    actualizar = false;
    arbolGeneral = new ArbolTransacciones();

}

Sistema::~Sistema()
{
    delete arbolGeneral;
}

Transaccion* Sistema::registrarTransaccion(string cuentaDeDestino, int monto, string ubicacion)
{
    Transaccion* transaccion = nullptr;
    try{
        transaccion = new Transaccion(cliente->getCuenta(),cuentaDeDestino,monto,ubicacion);
        NodoTransaccion* nodo = new NodoTransaccion(transaccion);
        nodoPadre = arbol->insertarNodoTransaccion(nodo);
        actualizar = true;
        
    } catch(const bad_alloc& e){
        cerr<<"Ocurrio un error al asignar memoria"<<endl;
    }
    return transaccion;
}

int Sistema::obtenerID(Transaccion *transaccion)
{
    if(transaccion == nullptr){
        return 0;
    }
 
    return transaccion->getID();;
}

bool Sistema::buscarTransaccion(int id)
{
    if(nodoPadre == nullptr){
        cout<<"Arbol vacio"<<endl;
        return false;
    }

    return arbol->buscarNodoTransaccion(nodoPadre,id,cliente->getCuenta());
}

void Sistema::modificarCriteriosDeTransaccionesSospechosas(int montoTransaccion, int cantTransacciones, int cantUbisDistintas)
{
    this->montoSospecha = montoTransaccion;
    this->cantTSospecha = cantTransacciones;
    this->cantUbiSospecha = cantUbisDistintas;

    arbolDecision->setMontoSospecha(montoTransaccion);
    arbolDecision->setCantTSospecha(cantTransacciones);
    arbolDecision->setCantUbiSospecha(cantUbisDistintas);

    arbolDecision->modificacionCriterioSospechoso(nodoPadre);
    
}

int Sistema::obtenerMontoTSospechosa()
{
    return arbolDecision->obtenerMontoSospecha();
}

int Sistema::obtenerCantTSospechosa()
{
    return arbolDecision->obtenerCantTSospecha();
}

int Sistema::obtenerCantUbiSospechosa()
{
    return arbolDecision->obtenerCantUbiSospecha();
}

void Sistema::generarReportes()
{
    if(cliente == nullptr){
        cerr<<"No hay cliente"<<endl;
        return;
    } else if(arbol == nullptr){
        cerr<<"Arbol de transacciones nulo"<<endl;
        return;
    } else if(arbol->obtenerNodoPadre() == nullptr){
        cout<<"Arbol vacio"<<endl;
    }

    cliente->registroDeTransacciones();
}

void Sistema::obtenerTransaccionesSospechosas(NodoTransaccion *nodo)
{
    
    if(nodo == nullptr|| arbol == nullptr || arbolDecision == nullptr || nodo->transaccion == nullptr){ 
        cout<<"No se pudo evaluar si existian Transacciones sospechosas debido a que no se pudieron obtener los datos correctamente"<<endl;
        return;
    }
    bool sospecha = arbolDecision->esSospechoso(arbolDecision->obtenerNodoPadre(),nodo,nodo->transaccion->getMontoTransaccion(),arbol->obtenerCantTHora(),arbol->obtenerCantUbi());
    if(sospecha){
        cout<<"--- Transacciones Sospechosas ---"<<endl;
        cliente->obtenerTransaccionesSospechosas();
    }else{cout<<"No se detecto ninguna transaccion sospechosa"<<endl;}
}

NodoTransaccion *Sistema::obtenerRaiz()
{
    return arbol->obtenerNodoPadre();
}

void Sistema::actualizarDatos(NodoTransaccion* nodoT,const string &nArchivo)
{
    if(actualizar == false) return;
    ofstream archivo(nArchivo);
    if(archivo.is_open()){
        
        actualizarDatosConRecursion(nodoT,archivo);
        archivo.close();
        cout<<"Datos actualizados correctamente"<<endl;
    } else{
        cerr<<"Ocurrio un problema al abrir el archivo"<<endl;
    }
}

void Sistema::actualizarDatosConRecursion(NodoTransaccion *nodoT, ofstream &archivo)
{
    if(nodoT != nullptr){
            archivo<<nodoT->transaccion->getID()<<","<<nodoT->transaccion->getCuentaDeOrigen()<<","<<nodoT->transaccion->getCuentaDeDestino()<<
            ","<<nodoT->transaccion->getMontoTransaccion()<<","<<nodoT->transaccion->getUbicacion()<<","<<nodoT->transaccion->obtenerFechaLegible()<<endl;
            
            actualizarDatosConRecursion(nodoT->tizquierda,archivo);
            actualizarDatosConRecursion(nodoT->tderecha,archivo);        
        }

}

void Sistema::cargarDatos(const string &nArchivo)
{
    int idTransaccion;
    string cuentaOrigen;
    string cuentaDestino;
    int monto;
    string ubicacion;
    string fechaYHoraSTR;
    time_t fechaYHora = 0;
    NodoTransaccion* nodoTemp = nullptr;
    Transaccion* tTemp = nullptr;

    ifstream archivo(nArchivo);

    if(archivo.is_open()){
        string linea;
        while(getline(archivo,linea)){
            stringstream ss(linea);

            ss>>idTransaccion;
            ss.ignore();
            getline(ss,cuentaOrigen,',');
            getline(ss,cuentaDestino,',');
            ss>>monto;
            ss.ignore();
            getline(ss,ubicacion,',');
            getline(ss,fechaYHoraSTR,',');

            struct tm tm = {};

            if (!fechaYHoraSTR.empty()) {
                if(strptime(fechaYHoraSTR.c_str(), "%Y-%m-%d %H:%M:%S", &tm)!= nullptr){
                    fechaYHora = mktime(&tm);
                } else {
                    cerr<<"Error: Formato de fecha y hora invalido"<<endl;
                }
                
            } else {
                cerr<<"Error: La cadena de fecha y hora esta vacia"<<endl;
                continue; 
            }

            tTemp = new Transaccion(idTransaccion,cuentaOrigen,cuentaDestino,monto,ubicacion,fechaYHora);
            nodoTemp = new NodoTransaccion(tTemp);
            raizArbolGeneral = arbolGeneral->insertarNodoTransaccion(nodoTemp);
            
            if(cliente != nullptr){
                if(cuentaDestino == cliente->getCuenta() || cuentaOrigen == cliente->getCuenta()){
                    cliente->insertarTransaccion(nodoTemp);
                }
            }
        }
        delete nodoTemp;
        delete tTemp;
        archivo.close();
    } else{
        cerr<<"Ocurrio un error al cargar el archivo"<<endl;
    }
}

void Sistema::EvaluarSospecha()
{
    if(cliente->getArbolTransaccion() == nullptr){
        cerr<<"Arbol de transacciones vacio"<<endl;
        return;
    }

    evaluarSospechaRecursivamente(arbol->obtenerNodoPadre());
}

void Sistema::evaluarSospechaRecursivamente(NodoTransaccion *nodo)
{
    if(nodo == nullptr){
        cerr<<"Nodo nulo"<<endl;
        return;
    }

    obtenerTransaccionesSospechosas(nodo);

    evaluarSospechaRecursivamente(nodo->tizquierda);
    evaluarSospechaRecursivamente(nodo->tderecha);

}
