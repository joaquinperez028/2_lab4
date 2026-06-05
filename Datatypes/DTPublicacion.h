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
    Fecha fechaPubli;
    string textoDescriptivo;
    float precio;
    string nomInmo;
    TipoPublicacion tipoPublicacion;
    TipoInmueble tipoInmueble;

public:
    DTPublicacion();
    DTPublicacion(bool activa, int codigoPubli, Fecha fechaPubli, string textoDescriptivo, float precio, string nomInmo, ::TipoPublicacion tipoPublicacion, ::TipoInmueble tipoInmueble);
    bool getActiva();
    int getCodigoPubli();
    Fecha getFechaPubli();
    string getTextoDescriptivo();
    float getPrecio();
    string getNomInmo();
    ::TipoPublicacion getTipoPublicacion();
    ::TipoInmueble getTipoInmueble();

    friend ostream &operator<<(ostream &os, const DTPublicacion &dt);
};

#endif
