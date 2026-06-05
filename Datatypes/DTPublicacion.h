#ifndef DTPUBLICACION_H
#define DTPUBLICACION_H

#include <iostream>
#include <string>
#include "Fecha.h"
#include "TipoPublicacion.h"
#include "TipoInmueble.h"

using namespace std;

class DTPublicacion
{
private:
    bool activa;
    int codigoPubli;
    fecha fechaPubli;
    string textoDescriptivo;
    float precio;
    string nomInmo;
    tipoPublicacion tipoPublicacion;
    tipoInmueble tipoInmueble;

public:
    DTPublicacion();
    DTPublicacion(bool activa, int codigoPubli, fecha fechaPubli, string textoDescriptivo, float precio, string nomInmo, ::tipoPublicacion tipoPub, ::tipoInmueble tipoInm);
    bool getActiva();
    int getCodigoPubli();
    fecha getFechaPubli();
    string getTextoDescriptivo();
    float getPrecio();
    string getNomInmo();
    ::tipoPublicacion getTipoPublicacion();
    ::tipoInmueble getTipoInmueble();

    friend ostream &operator<<(ostream &os, const DTPublicacion &dt);
};

#endif
