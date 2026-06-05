#include "DTPublicacion.h"

DTPublicacion::DTPublicacion()
    : activa(false), codigoPubli(0), fechaPubli(), textoDescriptivo(""), precio(0), nomInmo(""), tipoPublicacion(tipoPublicacion::Venta), tipoInmueble(tipoInmueble::Casa) {}

DTPublicacion::DTPublicacion(bool activa, int codigoPubli, fecha fechaPubli, string textoDescriptivo, float precio, string nomInmo, ::tipoPublicacion tipoPub, ::tipoInmueble tipoInm)
    : activa(activa), codigoPubli(codigoPubli), fechaPubli(fechaPubli), textoDescriptivo(textoDescriptivo), precio(precio), nomInmo(nomInmo), tipoPublicacion(tipoPub), tipoInmueble(tipoInm) {}

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

ostream &operator<<(ostream &os, const DTPublicacion &dt)
{
    os << "Codigo: " << dt.codigoPubli
       << " | Activa: " << (dt.activa ? "Si" : "No")
       << " | Fecha: " << dt.fechaPubli
       << " | Precio: " << dt.precio
       << " | Inmobiliaria: " << dt.nomInmo
       << " | Tipo pub.: " << dt.tipoPublicacion
       << " | Tipo inm.: " << dt.tipoInmueble
       << " | Descripcion: " << dt.textoDescriptivo;
    return os;
}
