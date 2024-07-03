#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "../header/Transaccion.h"
#include "Transaccion.h"

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

time_t Transaccion::getFechaYHoraTransaccion() const
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
    this->fechaHoraTransaccion = tiempo;
}

void Transaccion::setUbicacion(string ubicacion)
{
    this->ubicacion = ubicacion;
}

//Cambia el formato de la fecha y hora de la transaccion para poder operarlo como int
int Transaccion::cambiarFormatoFecha(time_t fechaHoraTransaccion)
{
    tm* hora = localtime(&fechaHoraTransaccion);
    int tiempo = hora->tm_sec+ hora->tm_min*100+hora->tm_hour*10000+hora->tm_mday*1000000+(hora->tm_mon +1)*100000000+(hora->tm_year+1900)*10000000000;
    return tiempo;
}

//el id se genera con la concatenacion de la suma del monto de la transaccion y la fecha de la misma con la cuenta de origen y de destino
//con el fin de evitar duplicados, ya que los numeros de cuenta no se repiten
void Transaccion::generarID()
{
    int horaEnNumero = cambiarFormatoFecha(fechaHoraTransaccion);
    this->idTransaccion = abs(monto*100+horaEnNumero);
}
bool Transaccion::esSospechosa()
{
    return sospechosa;
}

string Transaccion::obtenerFechaLegible()
{
    tm* hora = localtime(&fechaHoraTransaccion);

    char formattedTime[80];
    strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", hora);
    
    return string(formattedTime);
}
