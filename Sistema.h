#ifndef SISTEMA_H
#define SISTEMA_H

#include "ISistema.h"
#include "Datatypes/Status.h"
#include "ICollection.h"
#include "ICollection/interfaces/IDictionary.h"
#include "Datatypes/DTInmueble.h"

using namespace std;

class Usuario;
class Propietario;

class Sistema : public ISistema
{
private:
    Sistema();
    static Sistema *instance;
    IDictionary *usuarios;
    IDictionary *inmuebles;
    IDictionary *publicaciones;
    Propietario *propRecordado;
    int ultimoCodigoInmueble;
    int ultimoCodigoPub;
    Usuario *buscarPorNickname(string nickname);
    Inmobiliaria *inmoSeleccionada;
    IDictionary* publicaciones;

public:
    ~Sistema();
    static Sistema *getInstance();
    Status revisarNickname(string) override;                                             // TORTU
    Status altaCliente(string, string, string, string, string, string) override;         // TORTU
    Status altaPropietario(string, string, string, string, string, string) override;     // TORTU
    Status altaCasa(direccion, float, int, tipoTecho, bool) override;                    // MATIAS
    Status altaApto(direccion, float, int, int, bool, float) override;                   // MATIAS
    Status altaInmobiliaria(string, string, string, direccion, string, string) override; // TORTU
    ICollection *listarPropietarios() override;                                          // YANI
    void asociarPropietario(string) override;
    ICollection *listarInmobiliarias() override; // FRAN
    ICollection *seleccionarInmobiliaria(string) override;
    Status altaPublicacion(int, tipoPublicacion, string, float) override; // DIEGO
    ICollection *listarPublicaciones(string, float, float, opciones) override;
    DTEspecifica* listarEspecifica(int codigoPubli) override;    ICollection *listarPropiedades() override;                  // YANI
    DTInmueble* mostrarDetalle(int identificador) override;                  // FRAN
    Status eliminarInmueble(int) override;                      // MATIAS
    ICollection *listarInmueblesRepresentados(string) override; // FRAN
    Status altaAdministracion(int) override;
    fecha obtenerFechaActual(); // DIEGo
};

#endif
