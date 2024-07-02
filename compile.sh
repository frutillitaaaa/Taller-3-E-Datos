#!/bin/bash

# orden de compilacion
g++ -Iheader -c source/Transaccion.cpp -o Transaccion.o
g++ -Iheader -c source/NodoTransaccion.cpp -o NodoTransaccion.o
g++ -Iheader -c source/ArbolTransacciones.cpp -o ArbolTrasacciones.o
g++ -Iheader -c source/Sistema.cpp -o Sistema.o
g++ -Iheader -c source/main.cpp -o main.o

# Enlazar los objetos
g++ Transaccion.o NodoTransaccion.o ArbolTrasacciones.o Sistema.o main.o -o programa


echo "Compilación completa"
