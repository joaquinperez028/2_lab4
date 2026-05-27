#ifndef ISISTEMA_H
#define ISISTEMA_H

#include <iostream>
#include "datatypes/direccion.h"
#include "datatypes/tipoPublicacion.h"
#include "datatypes/tipoTecho.h"
#include "datatypes/DTEspecifica.h"
#include "datatypes/DTprop.h"
#include "datatypes/DTPublicacion.h"
#include "datatypes/DTInmueble.h" //falta implementar
#include "datatypes/DTInmobiliaria.h" //falta implementar
#include "datatypes/DTInmuebles.h"//falta implementar
#include "datatypes/DTInmueble.h" //falta implementar
#include "datatypes/DTEspecifica.h"
#include "datatypes/DTInmueblesRep.h"//falta implementar
#include "datatypes/Status.h"
using namespace std;

class ISistema {
    public:
        ~ISistema();
        static Sistema *getInstance();
        virtual Status revisarNickname(string) = 0; 
        virtual Status altaCliente(string, string, string, string, string)  = 0;
        virtual Status altaPropietario(string, string, string, string, string, string)  = 0;
        virtual Status altaCasa(direccion, float, int, tipoTecho, bool)  = 0;
        virtual Status altaApto(direccion, float, int, int, bool, float)  = 0;
        virtual Status altaInmobiliaria(string, string, string, direccion, string, string)  = 0;
        virtual DTprop listarPropietarios()  = 0;
        virtual void asociarPropietario(string)  = 0;
        virtual DTInmobiliaria listarInmobiliarias()  = 0;
        virtual DTInmueble seleccionarInmobiliaria(string)  = 0;
        virtual Status altaPublicacion(int, tipoPublicacion, string, float)  = 0;
        virtual DTPublicacion listarPublicaciones(string, float, float, opciones)  = 0;
        virtual DTEspecifica listarEspecifica(int)  = 0;
        virtual DTprop listarPropiedades()  = 0;
        virtual DTInmueble mostrarDetalle(int)  = 0;
        virtual Status eliminarInmueble(int)  = 0;
        virtual DTInmueblesRep listarInmueblesRepresentados(string)  = 0;
        virtual Status altaAdministracion(int)  = 0;
        
};

#endif