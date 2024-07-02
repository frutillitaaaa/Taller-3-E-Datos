#include <iostream>
#include <sstream>
#include <string>

#include "../header/Transaccion.h"

using namespace std;



Transaccion::Transaccion(string cuentaDeOrigen, string cuentaDeDestino, int monto, string ubicacion)
{
    this->cuentaDeOrigen = cuentaDeOrigen;
    this->cuentaDeDestino = cuentaDeDestino;
    this->monto = monto;
    setFechaYHoraTransaccion();
    this->ubicacion = ubicacion;
    generarID();
}

Transaccion::~Transaccion()
{
}

string Transaccion::getCuentaDeOrigen() const{
    return cuentaDeOrigen;
}

string Transaccion::getCuentaDeDestino() const{
    return cuentaDeDestino;
}

int Transaccion::getMontoTransaccion() const
{
    return monto;
}

tm Transaccion::getFechaYHoraTransaccion() const
{
    return fechaHoraTransaccion;
}

string Transaccion::getUbicacion() const
{
    return ubicacion;
}

int Transaccion::getID() const
{
    return idTransaccion;
}

void Transaccion::setCuentaDeOrigen(string cuentaDeOrigen)
{
    this->cuentaDeOrigen = cuentaDeOrigen;
}

void Transaccion::setCuentaDeDestino(string cuentaDeDestino)
{
    this->cuentaDeDestino = cuentaDeDestino;
}

void Transaccion::setMontoTransaccion(int monto)
{
    this->monto = monto;
}

void Transaccion::setFechaYHoraTransaccion()
{
    auto horaActual = chrono::system_clock::now();
    time_t tiempo = chrono::system_clock::to_time_t(horaActual);
    tm* datosTiempo = localtime(&tiempo);
    this->fechaHoraTransaccion = *datosTiempo;
}

void Transaccion::setUbicacion(string ubicacion)
{
    this->ubicacion = ubicacion;
}

//Cambia el formato de la fecha y hora de la transaccion para poder operarlo como int
int Transaccion::cambiarFormatoFecha(tm fechaHoraTransaccion)
{
    int fechaYHoraActual = fechaHoraTransaccion.tm_mday+ fechaHoraTransaccion.tm_mon+ fechaHoraTransaccion.tm_year
    +fechaHoraTransaccion.tm_hour+fechaHoraTransaccion.tm_min + fechaHoraTransaccion.tm_sec;
    return fechaYHoraActual;
}

//el id se genera con la concatenacion de la suma del monto de la transaccion y la fecha de la misma con la cuenta de origen y de destino
//con el fin de evitar duplicados, ya que los numeros de cuenta no se repiten
void Transaccion::generarID()
{
    /*
    int value = getMontoTransaccion() + cambiarFormatoFecha(getFechaYHoraTransaccion());
    ostringstream o;
    o<<value<<cuentaDeOrigen<<cuentaDeDestino;
    string valor = o.str();

    this->idTransaccion = stoi(valor);
     */
    int value = getMontoTransaccion() + cambiarFormatoFecha(getFechaYHoraTransaccion());

    this->idTransaccion = value;
}