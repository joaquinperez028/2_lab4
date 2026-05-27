#ifndef DTPUBLICACIONES_H
#define DTPUBLICACIONES_H

#include <string>
#include "fecha.h"
#include "tipoPublicacion.h"
#include "tipoInmueble.h"

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
    DTPublicacion(bool activa, int codigoPubli, fecha fechaPubli, string textoDescriptivo, float precio, string nomInmo, tipoPublicacion tipoPublicacion, tipoInmueble tipoInmueble);
    bool getActiva();
    int getCodigoPubli();
    fecha getFechaPubli();
    string getTextoDescriptivo();
    float getPrecio();
    string getNomInmo();
    tipoPublicacion getTipoPublicacion();
    tipoInmueble getTipoInmueble();
};

#endif
