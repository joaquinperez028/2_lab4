#ifndef ISISTEMA_H
#define ISISTEMA_H

#include <iostream>
#include <string>
#include "Datatypes/Direccion.h"
#include "Datatypes/TipoPublicacion.h"
#include "Datatypes/TipoTecho.h"
#include "Datatypes/Opciones.h"
#include "Datatypes/DTEspecifica.h"
#include "Datatypes/DTpropietario.h"
#include "Datatypes/Fecha.h"
#include "Datatypes/DTPublicacion.h"
#include "Datatypes/DTInmueble.h"
#include "ICollection.h"
#include "Datatypes/Status.h"

using namespace std;

class Sistema;

class ISistema
{
public:
    virtual ~ISistema();
    virtual Status revisarNickname(string) = 0;
    virtual Status altaCliente(string, string, string, string, string, string) = 0;
    virtual Status altaPropietario(string, string, string, string, string, string) = 0;
    virtual Status altaCasa(Direccion, float, Fecha, TipoTecho, bool) = 0;
    virtual Status altaApto(Direccion, float, Fecha, int, bool, float) = 0;
    virtual Status altaInmobiliaria(string, string, string, Direccion, string, string) = 0;
    virtual ICollection *listarPropietarios() = 0;
    virtual void asociarPropietario(string) = 0;
    virtual ICollection *listarInmobiliarias() = 0;
    virtual ICollection *seleccionarInmobiliaria(string) = 0;
    virtual Status altaPublicacion(int, TipoPublicacion, string, float) = 0;
    virtual ICollection *listarPublicaciones(string, float, float, Opciones) = 0;
    virtual DTEspecifica *listarEspecifica(int) = 0;
    virtual ICollection *listarPropiedades() = 0;
    virtual DTInmueble *mostrarDetalle(int) = 0;
    virtual Status eliminarInmueble(int) = 0;
    virtual ICollection *listarInmueblesRepresentados(string) = 0;
    virtual Status altaAdministracion(int) = 0;
};

#endif
