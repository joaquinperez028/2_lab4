#include "DTPublicacion.h"

DTPublicacion::DTPublicacion()
    : activa(false), codigoPubli(0), fechaPubli(), textoDescriptivo(""), precio(0), nomInmo(""), tipoPublicacion_(tipoPublicacion::Venta), tipoInmueble_(tipoInmueble::Casa) {}

DTPublicacion::DTPublicacion(bool activa, int codigoPubli, fecha fechaPubli, string textoDescriptivo, float precio, string nomInmo, ::tipoPublicacion tipoPublicacion, ::tipoInmueble tipoInmueble)
    : activa(activa), codigoPubli(codigoPubli), fechaPubli(fechaPubli), textoDescriptivo(textoDescriptivo), precio(precio), nomInmo(nomInmo), tipoPublicacion_(tipoPublicacion), tipoInmueble_(tipoInmueble) {}

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
    return tipoPublicacion_;
}

::tipoInmueble DTPublicacion::getTipoInmueble()
{
    return tipoInmueble_;
}

ostream &operator<<(ostream &os, const DTPublicacion &dt)
{
    os << "Codigo: " << dt.codigoPubli
       << " | Activa: " << (dt.activa ? "Si" : "No")
       << " | Fecha: " << dt.fechaPubli
       << " | Precio: " << dt.precio
       << " | Inmobiliaria: " << dt.nomInmo
       << " | Tipo pub.: " << dt.tipoPublicacion_
       << " | Tipo inm.: " << dt.tipoInmueble_
       << " | Descripcion: " << dt.textoDescriptivo;
    return os;
}
