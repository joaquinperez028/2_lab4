#ifndef DTPUBLICACION_H
#define DTPUBLICACION_H

#include <iostream>
#include <string>
#include "Fecha.h"
#include "TipoPublicacion.h"
#include "TipoInmueble.h"
#include "ICollection/interfaces/ICollectible.h"


using namespace std;

class DTPublicacion : public ICollectible
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
    DTPublicacion(bool activa, int codigoPubli, fecha fechaPubli, string textoDescriptivo, float precio, string nomInmo, ::tipoPublicacion tipoPublicacion, ::tipoInmueble tipoInmueble);
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
