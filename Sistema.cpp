#include "Sistema.h"

Sistema *Sistema::instance = nullptr;

Sistema::Sistema()
{
}

Sistema::~Sistema()
{
}

Sistema *Sistema::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Sistema();
    }
    return instance;
}

Status Sistema::revisarNickname(string)
{
    return {};
}

Status Sistema::altaCliente(string, string, string, string, string)
{
    return {};
}

Status Sistema::altaPropietario(string, string, string, string, string, string)
{
    return {};
}

Status Sistema::altaCasa(direccion, float, int, tipoTecho, bool)
{
    return {};
}

Status Sistema::altaApto(direccion, float, int, int, bool, float)
{
    return {};
}

Status Sistema::altaInmobiliaria(string, string, string, direccion, string, string)
{
    return {};
}

DTProp Sistema::listarPropietarios()
{
    return {};
}

void Sistema::asociarPropietario(string)
{
}

DTinmobiliaria Sistema::listarInmobiliarias()
{
    return {};
}

DTInmuebles Sistema::seleccionarInmobiliaria(string)
{
    return {};
}

Status Sistema::altaPublicacion(int, TipoPublicacion, string, float)
{
    return {};
}

DTPublicacion Sistema::listarPublicaciones(string, float, float, opciones)
{
    return {};
}

DTespecifica Sistema::listarEspecifica(int)
{
    return {};
}

DTprop Sistema::listarPropiedades()
{
    return DTprop();
}

DTinmueble Sistema::mostrarDetalle(int)
{
    return {};
}

Status Sistema::eliminarInmueble(int)
{
    return {};
}

DTInmueblesRep Sistema::listarInmueblesRepresentados(string)
{
    return {};
}

Status Sistema::altaAdministracion(int)
{
    return {};
}
