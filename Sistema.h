#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include "ISistema.h"
#include "ColInmueble.h"
#include "ColUsuario.h"
#include "ColInmobiliaria.h"
#include "ColPublicacion.h"
#include //clases??

using namespace std;

class Sistema : public ISistema
{
private:
    Sistema();
    static Sistema *instance;
    ColInmueble *colInmuebles;
    ColUsuario *colUsuarios;
    ColInmobiliaria *colInmobiliarias;
    ColPublicacion *colPublicaciones;
    // punteros a las clases que conoce sistema

public:
    ~Sistema();
    static Sistema *getInstance();
    Status revisarNickname(string) override; // override sirve para detectar errores de parametros etc etc
    Status altaCliente(string, string, string, string, string) override;
    Status altaPropietario(string, string, string, string, string, string) override;
    Status altaCasa(direccion, float, int, tipoTecho, bool) override;
    Status altaApto(direccion, float, int, int, bool, float) override;
    Status altaInmobiliaria(string, string, string, direccion, string, string) override;
    DTProp listarPropietarios() override;
    void asociarPropietario(string) override;
    DTinmobiliaria listarInmobiliarias() override;
    DTInmuebles seleccionarInmobiliaria(string) override;
    Status altaPublicacion(int, TipoPublicacion, string, float) override;
    DTPublicacion listarPublicaciones(string, float, float, opciones) override;
    DTespecifica listarEspecifica(int) override;
    DTprop listarPropiedades() override;
    DTinmueble mostrarDetalle(int) override;
    Status eliminarInmueble(int) override;
    DTInmueblesRep listarInmueblesRepresentados(string) override;
    Status altaAdministracion(int) override;
};

#endif
