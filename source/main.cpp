#include "../header/Sistema.h"
#include "../header/Transaccion.h"
#include "../header/NodoTransaccion.h"
#include "../header/ArbolTransacciones.h"
#include "../header/Cliente.h"


#include <iostream>
#include <limits>


using namespace std;

Cliente* menuInicioSesion(){

    string nombre;
    string cuenta;

    cout<<"Bienvenido a su banco"<<endl;
    cout<<"Ingrese su nombre"<<endl;
    cin>>nombre;

    while (nombre.empty()) {
        cout << "El nombre no puede estar vacio. Ingrese su nombre nuevamente: ";
        cin >> nombre;
    }

    cout<<"Ingrese su numero de cuenta"<<endl;
    cin>>cuenta;

    while (cuenta.empty()) {
        cout << "El numero de cuenta no puede estar vacio. Ingrese su cuenta nuevamente: ";
        cin >> cuenta;
    }

    Cliente*  cliente = new Cliente(nombre, cuenta);

    return cliente;

}

void crearNuevaTransaccion(Sistema* sistema){
    cout<<"--- Crear Nueva Transaccion ---"<<endl;

    string cuentaDeDestino;
    int monto;
    string ubicacion;

    do{
        cout<<"Ingrese la cuenta de Destino: "<<endl;
        cin>>cuentaDeDestino;

        if(cuentaDeDestino.empty()){
            cout << "La cuenta de destino no puede estar vacia"<<endl;
        }

    }while(cuentaDeDestino.empty());
    
    

    bool validado = false;

    do{
        cout<<"Ingrese el monto: "<<endl;
        cin>>monto;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"El dato ingresado no es valido. Debe ingresar un numero entero"<<endl;
        } else{
            validado = true;
        }

    }while(!validado);
    

    do{
        cout<<"Ingrese su ubicacion: "<<endl;
        cin>>ubicacion;

        if(ubicacion.empty()){
            cout << "La ubicacion no puede estar vacia"<<endl;
        }

    }while(ubicacion.empty());
    

    int confirmar;

    do{
        cout<<"Desea confirmar la transaccion?\n1) si\n2) no"<<endl;
        cin>>confirmar;

        if(confirmar != 1 && confirmar != 2){
            cout<<"Ingrese una opcion valida"<<endl;
        }

    }while(confirmar != 1 && confirmar != 2);


    if(confirmar == 1){
        cout<<"Transaccion confirmada"<<endl;
        sistema->registrarTransaccion(cuentaDeDestino,monto,ubicacion);
    }else{
        cout<<"Transaccion rechazada"<<endl;
        cout<<"Retornando al menu"<<endl;
        return;
    }
    
}

void buscarTransaccion(Sistema* sistema){
    cout<<"--- Buscar Transaccion ---"<<endl;
    
    int idABuscar;
    bool validado = false;

    do{
        cout<<"Ingrese el ID de la Transaccion que desea buscar: "<<endl;
        cin>>idABuscar;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"El dato ingresado no es valido. Debe ingresar un numero entero"<<endl;
        } else{
            validado = true;
        }

    }while(!validado);

    bool encontrado = sistema->buscarTransaccion(idABuscar);

    if(encontrado){
        cout<<"Transaccion con ID: "<< idABuscar<<"encontrada"<<endl;
    } else{
        cout<<"Transaccion no encontrada"<<endl;
    }
}

void modificarTransaccion(Sistema* sistema){

}

void modificarCriteriosTSospechosas(Sistema* sistema){
    cout<<"Modificar Criterios Transacciones Sospechosas"<<endl;

    int montoTSospechosa = sistema->obtenerMontoTSospechosa();
    int cantTSospechosa = sistema->obtenerCantTSospechosa();
    int cantUbiDistintas = sistema->obtenerCantUbiSospechosa();

    cout<<"Los criterios actuales de determinacion de Transacciones sospechosas son:"<<endl;
    cout<<"Transacciones que exceden "<<montoTSospechosa<<" CLP"<<endl;
    cout<<"Cantidad de Transacciones en una hora mayor a "<<cantTSospechosa<<endl;
    cout<<"Cantidad de Ubicaciones distintas en un dia hora mayor a "<<cantUbiDistintas<<endl;

    int opcion;

    do{
        cout<<"Seleccione el criterio de sospecha que desea modificar\n1) Monto de Transaccion\n2) Cantidad de Transacciones en una hora"<<
        "\n3) Cantidad de Ubicaciones Distintas en un dia\n0) SALIR"<<endl;
    
        cin>>opcion;

        switch(opcion){
            case 1:
                cout<<"--- Modificar Monto de Sospecha ---"<<endl;
                cout<<"Ingrese el monto que considera sospechoso: "<<endl;

                bool validado = false;

                do{
                    cout<<"Ingrese el monto que considera sospechoso: "<<endl;
                    cin>>montoTSospechosa;

                    if(cin.fail()){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout<<"El dato ingresado no es valido. Debe ingresar un numero entero"<<endl;
                    } else{
                        validado = true;
                    }

                }while(!validado);
                break;
            case 2:
                cout<<"--- Modificar Cantidad de Transacciones en una hora ---"<<endl;
                validado = false;
                do{
                    cout<<"Ingrese la cantidad que considera sospechosa: "<<endl;
                    cin>>cantTSospechosa;

                    if(cin.fail()){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout<<"El dato ingresado no es valido. Debe ingresar un numero entero"<<endl;
                    } else{
                        validado = true;
                    }
                }while(!validado);
                break;
            case 3:
                cout<<"--- Modificar Cantidad de Ubicaciones Distintas en un dia ---"<<endl;
                validado = false;
                do{
                    cout<<"Ingrese la cantidad que considera sospechosa: "<<endl;
                    cin>>cantUbiDistintas;

                    if(cin.fail()){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout<<"El dato ingresado no es valido. Debe ingresar un numero entero"<<endl;
                    } else{
                        validado = true;
                    }
                }while(!validado);
                break;
            case 0:
                cout<<"Saliendo"<<endl;
                break;
            default:
                cout<<"La opcion ingresada no es valida"<<endl;
                break;
        }

    }while(opcion != 0);

    int confirmar;

    do{
        cout<<"Desea confirmar los cambios?\n1) si\n2) no"<<endl;
        cin>>confirmar;

        if(confirmar != 1 && confirmar != 2){
            cout<<"Ingrese una opcion valida"<<endl;
        }

    }while(confirmar != 1 && confirmar != 2);
    
    if(confirmar == 1){
        cout<<"Se aplicaron los cambios"<<endl;
        sistema->modificarCriteriosDeTransaccionesSospechosas(montoTSospechosa,cantTSospechosa,cantUbiDistintas);
    }else{
        cout<<"Los cambios fueron descartados"<<endl;
    }  
}

void verHistorialTSospechosas(Sistema* sistema){}

void verHistorialCompleto(Sistema* sistema){
    cout<<"Ver Historial Completo de Transacciones"<<endl;
    sistema->generarReportes();
}

void menuOpcionesBanco(Sistema* sistema){
    int opcion;

    do{
        cout<<"Seleccione lo que desea hacer\n1) Nueva Transaccion\n2) Buscar Transaccion\n3) Modificar Transaccion\n"<< 
        "4) Modificar criterios de Transacciones Sospechosas\n5) Ver historial de Transacciones Sospechosas\n6) Ver historial"<<
        "completo de Transacciones\n0) SALIR"<<endl;

        cin>>opcion;

        switch(opcion){
        case 1:
            crearNuevaTransaccion(sistema);
            break;
        case 2:
            buscarTransaccion(sistema);
            break;
        case 3:
            modificarTransaccion(sistema);
            break;
        case 4:
            modificarCriteriosTSospechosas(sistema);
            break;
        case 5:
            verHistorialTSospechosas(sistema);
            break;
        case 6:
            verHistorialCompleto(sistema);
            break;
        case 0:
            break;
        default:
            cout<<"Por favor ingrese una opcion valida"<<endl;
            break;

    }
    }while(opcion !=0);

    

}



int main(int argc, char const *argv[])
{
    Cliente* c = menuInicioSesion();
    Sistema* sistema = new Sistema(c);

    menuOpcionesBanco(sistema);

    

    delete sistema;

    return 0;
}
