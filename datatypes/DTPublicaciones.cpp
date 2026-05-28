#include "DTPublicaciones.h"

DTPublicaciones::DTPublicaciones()
    : activa(false), codigoPubli(0), fechaPubli(), textoDescriptivo(""), precio(0), nomInmo(""), tipoPublicacion(tipoPublicacion::Venta), tipoInmueble(tipoInmueble::Casa) {}

DTPublicaciones::DTPublicaciones(bool activa, int codigoPubli, fecha fechaPubli, string textoDescriptivo, float precio, string nomInmo, ::tipoPublicacion tipoPublicacion, ::tipoInmueble tipoInmueble)
    : activa(activa), codigoPubli(codigoPubli), fechaPubli(fechaPubli), textoDescriptivo(textoDescriptivo), precio(precio), nomInmo(nomInmo), tipoPublicacion(tipoPublicacion), tipoInmueble(tipoInmueble) {}

bool DTPublicaciones::getActiva()
{
    return activa;
}

int DTPublicaciones::getCodigoPubli()
{
    return codigoPubli;
}

fecha DTPublicaciones::getFechaPubli()
{
    return fechaPubli;
}

string DTPublicaciones::getTextoDescriptivo()
{
    return textoDescriptivo;
}

float DTPublicaciones::getPrecio()
{
    return precio;
}

string DTPublicaciones::getNomInmo()
{
    return nomInmo;
}

::tipoPublicacion DTPublicaciones::getTipoPublicacion()
{
    return tipoPublicacion;
}

::tipoInmueble DTPublicaciones::getTipoInmueble()
{
    return tipoInmueble;
}
