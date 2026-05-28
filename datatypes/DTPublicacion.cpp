#include "DTPublicacion.h"

DTPublicacion::DTPublicacion()
    : activa(false), codigoPubli(0), fechaPubli(), textoDescriptivo(""), precio(0), nomInmo(""), tipoPublicacion(tipoPublicacion::Venta), tipoInmueble(tipoInmueble::Casa) {}

DTPublicacion::DTPublicacion(bool activa, int codigoPubli, fecha fechaPubli, string textoDescriptivo, float precio, string nomInmo, ::tipoPublicacion tipoPublicacion, ::tipoInmueble tipoInmueble)
    : activa(activa), codigoPubli(codigoPubli), fechaPubli(fechaPubli), textoDescriptivo(textoDescriptivo), precio(precio), nomInmo(nomInmo), tipoPublicacion(tipoPublicacion), tipoInmueble(tipoInmueble) {}

bool DTPublicacion::getActiva()
{
    return activa;
}

int DTPublicacion::getCodigoPubli()
{
    return codigoPubli;
}

fecha DTPublicacion::getFechaPubli()
{
    return fechaPubli;
}

string DTPublicacion::getTextoDescriptivo()
{
    return textoDescriptivo;
}

float DTPublicacion::getPrecio()
{
    return precio;
}

string DTPublicacion::getNomInmo()
{
    return nomInmo;
}

::tipoPublicacion DTPublicacion::getTipoPublicacion()
{
    return tipoPublicacion;
}

::tipoInmueble DTPublicacion::getTipoInmueble()
{
    return tipoInmueble;
}
