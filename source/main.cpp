#include "../header/Sistema.h"
#include "../header/Transaccion.h"
#include "../header/NodoTransaccion.h"
#include "../header/ArbolTransacciones.h"


#include <iostream>


using namespace std;

int main(int argc, char const *argv[])
{
    Sistema* sistema = new Sistema();
    
    Transaccion* t = sistema->registrarTransaccion("1189694111","1292424894",10242400,"La Serena");
    //Transaccion* t1 = sistema->registrarTransaccion("111","129894",10000000,"La Serena");
    //Transaccion* t2 = sistema->registrarTransaccion("1121","12967657",105550000,"La Serena");

    //cout<<sistema->buscarTransaccion(sistema->obtenerID(t))<<endl;
    //cout<<sistema->buscarTransaccion(sistema->obtenerID(t1))<<endl;
    //cout<<sistema->buscarTransaccion(sistema->obtenerID(t2))<<endl;

    sistema->detectarTransaccionesSospechosas(sistema->obtenerRaiz());


    //sistema->generarReportes();
    delete sistema;

    return 0;
}
