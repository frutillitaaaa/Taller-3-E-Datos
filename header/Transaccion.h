#pragma once

#include <chrono>
#include <ctime>

#include <iostream>

using namespace std;

class Transaccion {

    private:
        int idTransaccion;
        string cuentaDeOrigen;
        string cuentaDeDestino;
        int monto;
        tm fechaHoraTransaccion;
        string ubicacion;
        

    public: 
        Transaccion(string cuentaDeOrigen, string cuentaDeDestino, int monto, string ubicacion);
        ~Transaccion();
        string getCuentaDeOrigen() const;
        string getCuentaDeDestino() const;
        int getMontoTransaccion() const;
        tm getFechaYHoraTransaccion() const;
        string getUbicacion() const;
        int getID() const;
        void setCuentaDeOrigen(string cuentaDeOrigen);
        void setCuentaDeDestino(string cuentaDeDestino);
        void setMontoTransaccion(int monto);
        void setFechaYHoraTransaccion();
        void setUbicacion(string ubicacion);
        int cambiarFormatoFecha(tm fechaHoraTransaccion);
        void generarID();

};