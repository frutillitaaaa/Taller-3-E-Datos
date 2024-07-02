#include "Transaccion.h"
#include "NodoTransaccion.h"
#include "ArbolTransacciones.h"

#include <iostream>

using namespace std;

class Sistema {

    private:
        ArbolTransacciones* arbol;
        NodoTransaccion* nodoPadre;

    public:
        Sistema();
        ~Sistema();
        Transaccion* registrarTransaccion(string cuentaDeOrigen, string cuentaDeDestino, int monto, string ubicacion);
        void buscarTransaccion(int id);
        void modificarTransaccion(int id);
        void historialTransaccionesSospechosas();
        void modificarCriteriosDeTransaccionesSospechosas();
        void generarReportes();
        void actualizarDatos();

};