#ifndef SISTEMA_H
#define SISTEMA_H

#include "ISistema.h"
#include "Datatypes/Status.h"
#include "Datatypes/Fecha.h"
#include "ICollection.h"
#include "ICollection/interfaces/IDictionary.h"
#include "Datatypes/DTInmueble.h"

using namespace std;

class Usuario;
class Propietario;
class Inmobiliaria;

class Sistema : public ISistema
{
private:
    Sistema();
    static Sistema *instance;
    IDictionary *usuarios;
    IDictionary *inmuebles;
    IDictionary *publicaciones;
    Propietario *propRecordado;
    Inmobiliaria *inmoRecordada;
    int ultimoCodigoInmueble;
    int ultimoCodigoPub;
    Usuario *buscarPorNickname(string nickname);
    Inmobiliaria *inmoSeleccionada;

public:
    ~Sistema();
    static Sistema *getInstance();
    Status revisarNickname(string) override;                                             // TORTU
    Status altaCliente(string, string, string, string, string, string) override;         // TORTU
    Status altaPropietario(string, string, string, string, string, string, string) override;     // TORTU
    Status altaCasa(Direccion, float, Fecha, TipoTecho, bool) override;                  // MATIAS
    Status altaApto(Direccion, float, Fecha, int, bool, float) override;                 // MATIAS
    Status altaInmobiliaria(string, string, string, string, Direccion, string, string) override; // TORTU
    ICollection *listarPropietarios() override;                                          // YANI
    Status seleccionarPropietario(string) override;
    int obtenerUltimoCodigoInmueble() override;
    void asociarPropietario(string) override;                                            // TORTU
    ICollection *listarInmobiliarias() override;                                         // FRAN
    ICollection *seleccionarInmobiliaria(string) override;                               // DIEGO
    Status altaPublicacion(int, TipoPublicacion, string, float) override;                // DIEGO
    ICollection *listarPublicaciones(string, float, float, Opciones) override;
    DTEspecifica *listarEspecifica(int codigoPubli) override;
    ICollection *listarPropiedades() override;                  // YANI
    DTInmueble *mostrarDetalle(int identificador) override;     // FRAN
    Status eliminarInmueble(int) override;                      // MATIAS
    ICollection *listarInmueblesRepresentados(string) override; // FRAN
    ICollection *listarPropietariosRepresentados(string) override;
    Status altaAdministracion(int identificador) override;
    Fecha obtenerFechaActual(); // DIEGo
    void limpiarInmuebles();
    void limpiarPublicaciones();
    void limpiarUsuarios();
};

#endif
