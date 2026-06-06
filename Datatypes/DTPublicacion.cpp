#include "DTPublicacion.h"

DTPublicacion::DTPublicacion()
    : activa(false), codigoPubli(0), fechaPubli(), textoDescriptivo(""), precio(0), nomInmo(""), tipoPub_(tipoPublicacion::Venta), tipoInm_(tipoInmueble::Casa) {}

DTPublicacion::DTPublicacion(bool activa, int codigoPubli, fecha fechaPubli, string textoDescriptivo, float precio, string nomInmo, ::tipoPublicacion tipoPub, ::tipoInmueble tipoInm)
    : activa(activa), codigoPubli(codigoPubli), fechaPubli(fechaPubli), textoDescriptivo(textoDescriptivo), precio(precio), nomInmo(nomInmo), tipoPub_(tipoPub), tipoInm_(tipoInm) {}

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
    return tipoPub_;
}

::tipoInmueble DTPublicacion::getTipoInmueble()
{
    return tipoInm_;
}

ostream &operator<<(ostream &os, const DTPublicacion &dt)
{
    os << "Codigo: " << dt.codigoPubli
       << " | Activa: " << (dt.activa ? "Si" : "No")
       << " | Fecha: " << dt.fechaPubli
       << " | Precio: " << dt.precio
       << " | Inmobiliaria: " << dt.nomInmo
       << " | Tipo pub.: " << dt.tipoPub_
       << " | Tipo inm.: " << dt.tipoInm_
       << " | Descripcion: " << dt.textoDescriptivo;
    return os;
}
