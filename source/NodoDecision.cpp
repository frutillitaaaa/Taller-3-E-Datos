#include "../header/NodoDecision.h"

NodoDecision::NodoDecision(string criterio)
{
    this->criterio = criterio;
    this->hIzquierda = nullptr;
    this->hDerecha = nullptr;
}