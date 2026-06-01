#ifndef SISTEMA_H
#define SISTEMA_H

#include "ISistema.h"
#include "datatypes/Status.h" //agrego Status aca porq lo precisamos
#include "ICollection.h"
#include "ICollection/interfaces/IDictionary.h"

using namespace std;

class Sistema : public ISistema
{
private:
    Sistema();
    static Sistema *instance;
    ColUsuario *colUsuarios; // IDictionary* usuarios;
    IDictionary *inmuebles;
    Propietario *propRecordado;
    int ultimoCodigoInmueble;
    Usuario *buscarPorNickname(string nickname);
    // Inmobiliaria* inmoSeleccionada;
    // int ultimoCodigo; (para generar el codigo incremental)

public:
    ~Sistema();
    static Sistema *getInstance();
    Status revisarNickname(string) override;
    Status altaCliente(string, string, string, string, string, string) override;
    Status altaPropietario(string, string, string, string, string, string) override;
    Status altaCasa(direccion, float, int, tipoTecho, bool) override;
    Status altaApto(direccion, float, int, bool, float) override;
    Status altaInmobiliaria(string, string, string, direccion, string, string) override;
    DTprop listarPropietarios() override;
    void asociarPropietario(string) override;
    DTInmobiliaria listarInmobiliarias() override;
    DTInmuebles seleccionarInmobiliaria(string) override;
    Status altaPublicacion(int, tipoPublicacion, string, float) override;
    DTPublicacion listarPublicaciones(string, float, float, opciones) override;
    DTEspecifica listarEspecifica(int) override;
    DTprop listarPropiedades() override;
    DTInmueble mostrarDetalle(int) override;
    Status eliminarInmueble(int) override;
    DTInmueblesRep listarInmueblesRepresentados(string) override;
    Status altaAdministracion(int) override;
};

#endif
