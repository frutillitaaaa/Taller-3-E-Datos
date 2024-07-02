#include "../header/Sistema.h"
#include "../header/Transaccion.h"
#include "../header/NodoTransaccion.h"
#include "../header/ArbolTransacciones.h"


#include <iostream>


using namespace std;

int main(int argc, char const *argv[])
{
    Sistema* sistema = new Sistema();
    
    sistema->registrarTransaccion("1189694111","1292424894",10242400,"La Serena");
    sistema->registrarTransaccion("11111","129894",1000,"La Serena");
    sistema->registrarTransaccion("1125611","12967657",105550,"La Serena");

    delete sistema;

    return 0;
}
