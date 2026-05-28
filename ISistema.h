#ifndef ISISTEMA_H
#define ISISTEMA_H

#include <iostream>
#include <string>
#include "Datatypes/Direccion.h"
#include "Datatypes/TipoPublicacion.h"
#include "Datatypes/TipoTecho.h"
#include "Datatypes/Opciones.h"
#include "Datatypes/DTEspecifica.h"
#include "Datatypes/DTprop.h"
#include "Datatypes/DTPublicacion.h"
#include "Datatypes/DTInmueble.h"
#include "Datatypes/DTInmobiliaria.h"
#include "Datatypes/DTInmuebles.h"
#include "Datatypes/DTInmueblesRep.h"
#include "Datatypes/Status.h"

using namespace std;

class Sistema;

class ISistema {
public:
    virtual ~ISistema();
    virtual Status revisarNickname(string) = 0;
    virtual Status altaCliente(string, string, string, string, string, string) = 0;
    virtual Status altaPropietario(string, string, string, string, string, string) = 0;
    virtual Status altaCasa(direccion, float, int, tipoTecho, bool) = 0;
    virtual Status altaApto(direccion, float, int, int, bool, float) = 0;
    virtual Status altaInmobiliaria(string, string, string, direccion, string, string) = 0;
    virtual DTprop listarPropietarios() = 0;
    virtual void asociarPropietario(string) = 0;
    virtual DTInmobiliaria listarInmobiliarias() = 0;
    virtual DTInmuebles seleccionarInmobiliaria(string) = 0;
    virtual Status altaPublicacion(int, tipoPublicacion, string, float) = 0;
    virtual DTPublicacion listarPublicaciones(string, float, float, opciones) = 0;
    virtual DTEspecifica listarEspecifica(int) = 0;
    virtual DTprop listarPropiedades() = 0;
    virtual DTInmueble mostrarDetalle(int) = 0;
    virtual Status eliminarInmueble(int) = 0;
    virtual DTInmueblesRep listarInmueblesRepresentados(string) = 0;
    virtual Status altaAdministracion(int) = 0;
};

#endif
