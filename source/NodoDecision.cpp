#include "../header/NodoDecision.h"

NodoDecision::NodoDecision(string criterio)
{
    this->sospecha = false;
    this->criterio = criterio;
    this->hIzquierda = nullptr;
    this->hDerecha = nullptr;
}