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
        time_t fechaHoraTransaccion;
        string ubicacion;
        bool sospechosa;
        string zonaHoraria = "America/Santiago";
        

    public: 
        Transaccion(string cuentaDeOrigen, string cuentaDeDestino, int monto, string ubicacion);
        Transaccion(int idTransaccion, string cuentaDeOrigen, string cuentaDeDestino, int monto, string ubicacion, time_t horaTransaccion);
        ~Transaccion();
        string getCuentaDeOrigen() const;
        string getCuentaDeDestino() const;
        int getMontoTransaccion() const;
        time_t getFechaYHoraTransaccion() const;
        string getUbicacion() const;
        int getID() const;
        void setCuentaDeOrigen(string cuentaDeOrigen);
        void setCuentaDeDestino(string cuentaDeDestino);
        void setMontoTransaccion(int monto);
        void setFechaYHoraTransaccion();
        void setUbicacion(string ubicacion);
        int cambiarFormatoFecha(time_t fechaHoraTransaccion);
        void generarID();
        bool esSospechosa();
        void setSospecha(bool sospecha);
        string obtenerFechaLegible();
        void setFechaYHoraTransaccion2(time_t fechaHora);

};